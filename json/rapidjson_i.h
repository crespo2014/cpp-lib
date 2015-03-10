/*
 * rapidjson_i.h
 *
 *  Created on: 10 Mar 2015
 *      Author: lester
 */

#ifndef RAPIDJSON_I_H_
#define RAPIDJSON_I_H_

#include <vector>
#include <ostream>
#include <type_traits>
#include <ostream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filestream.h"
#include "os/os.h"
#include "DataProcessing/data_processor_config.h"
#include "jsonbase.h"
#include "os/file.h"

namespace Json {
namespace rapidjson_wrapper {

class JsonError {
    const rapidjson::ParseResult pr_;
public:
    JsonError(const rapidjson::ParseResult& pr)
            : pr_(pr) {
    }
    JsonError(const JsonError& err)
            : Faz::Error(err), pr_(err.pr_) {
    }
    ;
    friend std::ostream& operator<<(std::ostream& os, const JsonError& e) {
        return os << "code : " << e.pr_.Code() << " at offset " << e.pr_.Offset() << " " << GetParseError_En(e.pr_.Code());
    }
};

/**
 * User exception class for rapid json parser library related error
 *
 */
class JsonException  {
    JsonError err_;
    std::string message_; ///< exception message extra information for this exception like item
public:
    JsonException(const JsonError &error, const char* msg)
            :  err_(error), message_(msg) {

    }
    /**
     * Print all exception information in a output stream
     */
    virtual std::ostream& print(std::ostream& os) const override
    {
        return os << message_ << " " << err_;
    }
    virtual ~JsonException() _GLIBCXX_USE_NOEXCEPT
    {
    }
};

/**
 * Rapid json sax parser handler.
 * This object will received all notifications from sax parser and it will build a c++ DOM
 */
template<class I>           //!< item type that implements Open,Close - Object, Container, setUnsigned, setSigned, setString, getItem, flushItem
class Handler {
    std::vector<I*> stack;
    I* current;
    bool key = true;    //!< true for waiting a item name, false means reading item data
public:
    Handler(I& root)
            : current(&root) {

    }
    /**
     * Push old item in the stack and use a new one as current
     * if new elemnt is null then do nothing
     */
    void SwitchTo(I* element) {
        if (element != nullptr) {
            //if_debug(std::cout << "stacked " << element << " " << element->getName() << std::endl;);
            stack.push_back(current);
            current = element;
        }
    }
    /// remove last element from the stack and make it current
    void PopStack() {
        key = true;
        if (stack.size() == 0) {
            current = nullptr;
        } else {
            current = stack.back();
            stack.pop_back();
        }
        //if_debug(std::cout << "poped " << current << " " << ((current != nullptr) ? current->getName() : "") << std::endl;);
    }
    /// Handler for null type value
    bool Null() {
        std::cout << "Null()" << std::endl;
        PopStack();
        return true;
    }
    /// Handler for bool type value
    bool Bool(bool b) {
        current->setBool(b);
        if (!current->isArray())        // an array receiving a value can received more
            PopStack();
        return true;
    }
    /**
     * Handler for int value
     */
    bool Int(int i) {
        current->setSigned(i);
        if (!current->isArray())        // an array receiving a value can received more
            PopStack();
        return true;
    }
    /**
     * Handler for unsigned value
     */
    bool Uint(unsigned u) {
        current->setUnSigned(u);
        if (!current->isArray())        // an array receiving a value can received more
            PopStack();
        return true;
    }
    /**
     * Handler for integer 64bits value
     */
    bool Int64(int64_t i) {
        current->setSigned(i);
        if (!current->isArray())        // an array receiving a value can received more
            PopStack();
        return true;
    }
    /**
     * Handler for unsigned 64bits value
     */
    bool Uint64(uint64_t u) {
        current->setUnSigned(u);
        if (!current->isArray())        // an array receiving a value can received more
            PopStack();
        return true;
    }
    /**
     * Handler for double value
     */
    bool Double(double d) {
        current->setDouble(d);
        if (!current->isArray())        // an array receiving a value can received more
            PopStack();
        return true;
    }
    /**
     * A new item or value was found
     * @param copy - true the string is a copy of original, false - original string was update with zero
     */
    bool String(const char* str, rapidjson::SizeType length, bool)
    {
        if (key)
            throw Exception(UserError(UserError::ERROR_NULL_PTR),Faz::FormatString()<< "Received unwanted data " << Faz::SubString(str, length) );

        current->setString(Faz::SubString(str, length));
        if (!current->isArray())        // an array receiving a value can received more
            PopStack();
        return true;
    }
    /**
     * A new item was found
     */
    bool Key(const char* str, rapidjson::SizeType length, bool)
    {
        if (key)
        {
            SwitchTo(current->getItem(Faz::SubString(str, length)));
            key = false;
        } else
        {
            throw Exception(UserError(UserError::ERROR_NULL_PTR),Faz::FormatString()<< "Received unwanted key " << Faz::SubString(str, length) );
        }
        return true;
    }

    /**
     * Handler for start object character
     */
    bool StartObject() {
        if (current == nullptr)
            throw Exception(UserError(UserError::ERROR_NULL_PTR), "current object is NULL");
        SwitchTo(current->OpenObject());
        key = true;
        return true;
    }
    /**
     * Handler for end object character
     */
    bool EndObject(rapidjson::SizeType) {
        current->CloseObject();
        I* t = current;
        PopStack();
        // if root element is closed then pop will produce nullptr.
        if (current != nullptr)
            current->flush(t);
        return true;
    }
    /**
     * Handler for start array character
     */
    bool StartArray() {
        SwitchTo(current->OpenContainer());
        key = false;
        return true;
    }
    /**
     * Handler for end array character
     */
    bool EndArray(rapidjson::SizeType) {
        current->CloseContainer();
        PopStack();
        return true;
    }
}
;
/**
 * Object to convert events describing a object to rapid json writter events
 */
template<class H>
class WriteHandler : public H {
public:
    template<class ... Arg>
    WriteHandler(Arg& ... arg)
            : H(arg ...) {

    }
    void String(const char* str) {
        H::String(str, static_cast<uint>(strlen(str)));
    }
};

/*
 * usefull function to work with json
 */
template<class I>
void FileToJson(const char* file_name, I& root) {
    Faz::os::MemHeap jsonFile;
    jsonFile.LoadFile(file_name);
    Faz::Json::rapidjson_wrapper::Handler<Faz::Json::IjsonItem> handler(root);
    rapidjson::Reader reader;
    rapidjson::InsituStringStream ss(jsonFile.get<char>());
    rapidjson::ParseResult pr = reader.Parse(ss, handler);
    if (pr.IsError()) {
        throw Faz::Json::rapidjson_wrapper::JsonException(Faz::Json::rapidjson_wrapper::JsonError(pr), "");
    }
}

/**
 * Serialize to file
 * @file_name - output file path
 * @root - Object that implement Describe function
 */
template<class I>
void JsonToFile(const char* file_name, I& root) {
    Faz::os::FFile of(file_name, "w");
    rapidjson::FileStream wr(of.get());
    rapidjson::Writer<rapidjson::FileStream> writer(wr);
    root.Describe(writer);
}

/**
 * Parse Json string and fill up C++ DOM
 * String must be not constant , the fucntion will modified the string content
 * @json - null terminate ascii string
 * @root - root object of the c++ dom model
 * @return a JsonException exception is throw is something is wrong
 */
template<class I>
void JsonStringToDOM(char* json, I& root) {
    Faz::Json::rapidjson_wrapper::Handler<Faz::Json::IjsonItem> handler(root);
    rapidjson::Reader reader;
    rapidjson::InsituStringStream ss(json);
    rapidjson::ParseResult pr = reader.Parse(ss, handler);
    if (pr.IsError()) {
        throw Faz::Json::rapidjson_wrapper::JsonException(Faz::Json::rapidjson_wrapper::JsonError(pr), "");
    }
}

} /* rapidjson_wrapper */

/**
     * Generic objects describers for rest interface  for simple objects or arrays
     * T is the object or container type.
     * D is the rest object that describe T
     */
    template<class T,class D>
    class ContainerDescriptor
    {
    public:
        ContainerDescriptor(const T& o)
                : c_(o) {
        }
        template<class H>
        void describe(H& handler) const {
            handler.StartArray();
            for (auto &f : c_)
            {
                D::describe(*f.second, handler, true);
            }
            handler.EndArray();
        }
    private:
        const T& c_;
    };
    /**
     * Generic objects describers for rest interface  for simple objects or arrays
     * T is the object or container type.
     * D is the rest object that describe T
     */
    template<class T,class D>
    class ObjectDescriptor
    {
    public:
        ObjectDescriptor(const T& c)
                : o_(c) {
        }
        template<class H>
        void describe(H& handler) const {
            D::describe(o_,handler,true);
        }
    private:
        const T& o_;
    };

} /* namespace Json */
} /* namespace Faz */

#endif /* RAPIDJSONFAZ_H_ */




#endif /* RAPIDJSON_I_H_ */
