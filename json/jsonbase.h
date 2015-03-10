
#ifndef JSONBASE_H_
#define JSONBASE_H_

#include <stdexcept>
#include <limits>
#include <stdint.h>
#include <type_traits>
#include <memory>
#include <list>
#include <initializer_list>
#include <vector>
#include "os/os.h"
#include "common.h"
#include "numeric_check.h"

namespace Json {

/**
 * Json item can has different status
 */
enum jsonItemFlags {
    MANDATORY = 1,      //!< this item can not be null
    READ,               //!< this item has been read
    REMOVED,               //!< this item has been remove not longer use, ignore is a default behavior
};

/**
 * Class holding error type for json generic objects
 */
class JsonItemError : public Error {
public:
    /**
     * define enum items
     */
    enum ecode_e {
        BEGIN = 300,               //
        ERROR_INVALID_TYPE,               //
        ERROR_INVALID_VALUE,               //
        ERROR_MISSING_VALUE,               //
        ERROR_DUPLICATE_OBJECT,               //
        ERROR_NOT_FOUND,               //
        ERROR_UNIMPLEMENT,               //
        ERROR_NOT_ROOT_NODE,               //
        ERROR_INVALID_ROOT_NODE,               //
        ERR_TO_MANY_ITEMS,
        END //
    };
    static const enumString<enum ecode_e> err_map_;
    /**
     * Constructor.
     * @param - error code associate to this exception
     */
    JsonItemError(enum ecode_e code)
            : Error(code, err_map_.get(code)) {
    }
};

/**
 * Json base exception for item handling
 *
 */
class JsonItemException  {
public:
    /**
     * Constructor from error code
     * @param [in]  code - error code enum
     */
    JsonItemException(enum JsonItemError::ecode_e code)
            : Exception(JsonItemError(code)/*,JsonItemError::err_map_.get(code) enumString<enum JsonItemError::_code>().get(code)*/) {
    }
    /** Destructor */
    virtual ~JsonItemException() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Exception for invalid type on json items
 */
class JsonInvalidTypeException : public JsonItemException {
    std::string name_, type_;
public:
    /** Constructor
     * @param name [in] item name that produce the exception
     * @param type [in] type data type that does not match item type
     */
    JsonInvalidTypeException(const std::string& name, const std::string& type)
            : JsonItemException(JsonItemError::ERROR_INVALID_TYPE), name_(name), type_(type) {
    }
    /**
     * Virtual function use by insertion operator to call derived class
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "Item " << name_ << " is not of type " << type_;
    }
    /** Destructor */
    virtual ~JsonInvalidTypeException() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Exception for invalid value on json items
 */
class JsonInvalidValueException : public JsonItemException {
    std::string name_, val_;
public:
    /**
     * Constructor
     * @param [in] name item name that produce the exception
     * @param [in] val data type that does not match item type
     */
    template<class T>
    JsonInvalidValueException(const std::string& name, const T& val)
            : JsonItemException(JsonItemError::ERROR_INVALID_VALUE), name_(name), val_(FormatString() << val) {
    }
    /**
     * Virtual function use by insertion operator to call derived class
     * @param [in] os - out stream for print out all exception information
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "Value " << val_ << " for item " << name_ << " is invalid or out of range";
    }

    /** Destructor */
    virtual ~JsonInvalidValueException() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Exception when a item has not value and it is mandatory
 */
class JsonMissingValueException : public JsonItemException {
    std::string name_, parent_name_;
public:
    /** Constructor
     * @param [in] name item name that is missing
     * @param [in] parent parent name where the item is missing
     */
    JsonMissingValueException(const std::string& name, const std::string& parent)
            : JsonItemException(JsonItemError::ERROR_INVALID_VALUE), name_(name), parent_name_(parent) {
    }
    /**
     * Virtual function use by insertion operator to call derived class
     * @param [in] os - out stream for print out all exception information
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "Item " << name_ << " is missing in object " << parent_name_;
    }

    /** Destructor */
    virtual ~JsonMissingValueException() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Exception when a item has the same id than other on the same list
 */
class JsonDuplicateObjectException : public JsonItemException {
    std::string name_, id_;
public:
    /** Constructor
     * @param [in] item name that is duplicate
     * @param [in] id value of duplicate id
     */
    template<class T>
    JsonDuplicateObjectException(const std::string& name, const T& id)
            : JsonItemException(JsonItemError::ERROR_DUPLICATE_OBJECT), name_(name), id_(FormatString() << id) {
    }
    /**
     * Virtual function use by insertion operator to call derived class
     * @param [in] os - out stream for print out all exception information
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "Item " << name_ << " with id " << id_ << " is duplicate";
    }

    /** Destructor */
    virtual ~JsonDuplicateObjectException() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Exception when a item appear more than one in the json
 */
class JsonDuplicateItemException : public JsonItemException {
    std::string name_;
public:
    /** Constructor
     * @param [in] item name that is duplicate
     * @param [in] id value of duplicate id
     */
    JsonDuplicateItemException(const std::string& name)
            : JsonItemException(JsonItemError::ERROR_DUPLICATE_OBJECT), name_(name) {
    }
    /**
     * Virtual function use by insertion operator to call derived class
     * @param [in] os - out stream for print out all exception information
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "Item " << name_ << " appear more than one";
    }

    /** Destructor */
    virtual ~JsonDuplicateItemException() _GLIBCXX_USE_NOEXCEPT {
    }
};
/**
 * Exception when a item has been removed or it does not exits
 */
class JsonItemNotFoundException : public JsonItemException {
    std::string name_, parent_;
public:
    /** Constructor
     * @param [in] name item name that is duplicate
     * @param [in] type data type that does not match item type
     */
    JsonItemNotFoundException(const std::string& name, const std::string& parent)
            : JsonItemException(JsonItemError::ERROR_NOT_FOUND), name_(name), parent_(parent) {
    }
    /**
     * Virtual function use by insertion operator to call derived class
     * @param [in] os - out stream for print out all exception information
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "Item " << name_ << " does not exists on " << parent_;
    }

    /** Destructor */
    virtual ~JsonItemNotFoundException() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Exception when a item has been removed or it does not exits
 */
class ItemRemoved : public JsonItemException {
    std::string name_, parent_;
public:
    /** Constructor
     * @param [in] name item name that is duplicate
     * @param [in] type data type that does not match item type
     */
    ItemRemoved(const std::string& name, const std::string& parent)
            : JsonItemException(JsonItemError::ERROR_NOT_FOUND), name_(name), parent_(parent) {
    }
    /**
     * Virtual function use by insertion operator to call derived class
     * @param [in] os - out stream for print out all exception information
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "Item " << name_ << " has been remove from " << parent_;
    }

    /** Destructor */
    virtual ~ItemRemoved() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Exception when a item object does not implement and specific c++ function  id than other on the same list
 */
class JsonMethodNotImplementException : public JsonItemException {
    std::string name_, method_;
public:
    /** Constructor
     * @param [in] name item name that produce the exception
     * @param [in] method name of method that was call for this item
     */
    JsonMethodNotImplementException(const std::string& name, const std::string& method)
            : JsonItemException(JsonItemError::ERROR_UNIMPLEMENT), name_(name), method_(method) {
    }
    /**
     * Virtual function use by insertion operator to call derived class
     * @param [in] os - out stream for print out all exception information
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "C++ Object item " << name_ << " does not implement the function " << method_;
    }

    /** Destructor */
    virtual ~JsonMethodNotImplementException() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Interface use by a json parser to supply data to temporal objects
 * All json have a name to identify it and match again json elements
 */
class IjsonItem {
public:
    /**
     * Enum type use to classify json items
     */
    enum item_type_ {
        none,           ///< not defined json type
        object,         ///< type for json objects
        array,          ///< type for json array
        boolean,        ///< type for booleans
        signed_number,  ///< type for signed or int numbers
        unsigned_number,  ///< type for unsigned numbers
        float_number,   ///< type for float or double
        string,         ///< type string items
    };
protected:
    const enum item_type_ type;             //!< type for this item
    const char* const name;                 //!< name for this item in json
    BitFlags<jsonItemFlags> flags;          //!< flags for this item
    /**
     * Item in a container or list of item must provided identity comparation using id
     * this a object to which provided an id that never is the same
     */
    class nullID {
    public:
        /**
         * Comparation operator
         * @param a reference to compare to
         * @return true if the object is equal to the reference
         */
        bool operator==(const nullID&) {
            return false;
        }
        /**
         * Print to out stream operator
         * @param [in] os - out stream reference to print out
         * @param [in] object reference to print
         */
        friend std::ostream& operator<<(std::ostream& os, const nullID&) {
            return os;
        }
    };

    /** Constructor for type , name and flag
     * @param [i] type - specified type type
     * @param [in] name - item name
     * @param [in] flag  - for this item as (mandatory)
     */

    IjsonItem(enum item_type_ type, const char *name = "", unsigned flags = 0)
            : type(type), name(name), flags(flags) {

    }
    /**
     * Constructor for type, name and subitems
     * @param [i] type - specified type type
     * @param [in] name - item name
     * @param [in] items - list of pointers to subitems for this object
     * name
     */
    IjsonItem(enum item_type_ type, const char *name, std::initializer_list<IjsonItem*> items)
            : type(type), name(name), items(items) {

    }
    ///Destructor
    virtual ~IjsonItem() {
    }
    /**
     * Call this function before set a new value to the item
     * to validate that everything is ok
     */
    void preSetCheck() {
        if (isRemoved())
            throw JsonItemNotFoundException(name, "");
        if (isValue())
            throw JsonDuplicateItemException(name);
        setWriten();
    }
public:
    const std::vector<IjsonItem*> items;    //!< list of pointer to subitems for this item, this list must be fill up at constructor
    /**
     * Get item type
     * @return
     */
    enum item_type_ getType() const {
        return type;
    }
    /**
     * A name is open get a item to received the value
     * @param [in] str - item name to looking for
     * @return pointer to subitem or nullptr if the subitem is not found
     */
    IjsonItem* getItem(const SubString& str) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->isName(str))
                return (*it);
        }
        throw JsonItemNotFoundException(str, name);
    }
    /**
     * Open Object mark
     * @return If this item is a object then return nullptr, if item is a container then return a new object
     */
    virtual IjsonItem* OpenObject() {
        throw JsonInvalidTypeException(name, "object");
    }
    /**
     * Close Object mark
     * If this item is an object then all data is checked
     */
    virtual void CloseObject() {
        throw JsonInvalidTypeException(name, "object");
    }
    /**
     * Open Container mark
     * If this item is a container then return nullptr, if item is root for a container then return a container
     */
    virtual IjsonItem* OpenContainer() {
        throw JsonInvalidTypeException(name, "array");
    }
    /**
     * Close container mark
     * If this item is an object then all data is checked
     */
    virtual void CloseContainer() {
        throw JsonInvalidTypeException(name, "array");
    }
    /**
     * Objects when close must be flush on its parents
     * this function tell to parent to sore this object that previously was in temporal store
     */
    virtual void flush(IjsonItem*) {
        throw JsonMethodNotImplementException(name, "flush");
    }
    //! Setter for all basic data type, default set to throw an invalid data format
    virtual void setDouble(double) {
        throw JsonInvalidTypeException(name, "double");
    }
    /**
     * Assign signed value to this item
     * @param t - value to be assigned
     */
    virtual void setSigned(int64_t) {
        throw JsonInvalidTypeException(name, "int64");
    }
    /**
     * Assign unsigned value to this item
     * @param t - value to be assigned
     */
    virtual void setUnSigned(uint64_t) {
        throw JsonInvalidTypeException(name, "uint64");
    }
    /**
     * Assign unsigned value to this item
     * @param t - value to be assigned
     */
    virtual void setBool(bool) {
        throw JsonInvalidTypeException(name, "bool");
    }
    /**
     * Get signed value from this item
     * @return the item value if type is signed or throw an exception
     */
    virtual int64_t getSigned() const {
        throw JsonInvalidTypeException(name, "int64");
    }
    /**
     * Get unsigned value from this item
     * @return the item value if type is unsigned or throw an exception
     */
    virtual uint64_t getUnSigned() const {
        throw JsonInvalidTypeException(name, "uint64");
    }
    /**
     * Get string value from this item
     * @return the item value if type is string or throw an exception
     */
    virtual const char* getString() const {
        throw JsonInvalidTypeException(name, "string");
    }
    /**
     * Get double value from this item
     * @return the item value if type is double or throw an exception
     */
    virtual double getDouble() const {
        throw JsonInvalidTypeException(name, "double");
    }
    /**
     * Generic setter, sscanf will be use to get the value from the string
     * @param const char * v - value to set as null terminated ascii string
     */
    virtual void setString(const SubString&) {
        throw JsonInvalidTypeException(name, "string");
    }
    /**
     * Print out this item into a out stream
     * @param
     */
//    virtual void print(std::ostream&) const {
//        throw MethodNotImplement(name, "print");
//    }
    /**
     * Check if this item has a valid value
     * @return true if the item has a valid value
     */
    bool isValue() const {
        return flags.is(READ);
    }
    /**
     * Change item status or value to valid after update item value
     */
    void setWriten() {
        flags.set(READ);
    }
    /**
     * Change item status to be mandatory
     */
    void setMandatory(bool b = true) {
        if (b)
            flags.set(MANDATORY);
        else {
            flags.clear(MANDATORY);
        }
        flags.clear(REMOVED);
    }
    /**
     * Set this item as removed, it must not be present
     */
    void setRemovedNotIgnore(bool b = true) {
        if (b) {
            flags.set(REMOVED);
        } else
            flags.clear(REMOVED);
        flags.clear(MANDATORY);
    }
    /**
     * Check if this item is mandatory
     */
    bool isMandatory() const {
        return flags.is(MANDATORY);
    }
    /**
     * Check item name
     */
    bool isName(const SubString& name) {
        return (name == this->name);
    }
    /**
     * Get item name
     */
    const char* getName() const {
        return name;
    }
    /**
     * Test if this item is of type object
     */
    bool isObject() const {
        return (type == object);
    }
    /**
     * Test if this item is of type array
     */
    bool isArray() const {
        return (type == array);
    }
    /**
     * Test if this item is of type string
     */
    bool isString() const {
        return (type == string);
    }
    /**
     * Test if this item is of type number
     */
    bool isNumber() const {
        return (type == signed_number) || (type == unsigned_number) || (type == float_number);
    }
    /**
     * Test if this item is of type signed number
     */
    bool isSigned() const {
        return (type == signed_number);
    }
    /**
     * Test if this item is of type unsigned number
     */
    bool isUnSigned() const {
        return (type == unsigned_number);
    }
    /**
     * Test if this item is of type bool
     */
    bool isBool() const {
        return (type == boolean);
    }
    /**
     * Test if this item is of type float or double
     */
    bool isFloat() const {
        return (type == float_number);
    }
    /**
     * Test if the item has been removed
     */
    bool isRemoved() const {
        return flags.is(REMOVED);
    }

    /**
     * insertion operator for printing to ostream.
     * @param [in] os - the ostream object
     * @param [in] e - the Error object
     */
//    friend std::ostream& operator<<(std::ostream& os, const IjsonItem& e) {
//        e.print(os);
//        return os;
//    }
    /**
     * Function to describe the item
     * @param [in] writter template parameter that received events
     */
    template<class W>
    void describe(W& writer) const {
        switch (type) {
        case object:
            writer.StartObject();
            for (auto &it : items) {
                writer.String(it->getName());
                it->describe(writer);
            }
            writer.EndObject();
            break;
        case array:
            writer.StartArray();
            for (auto &it : items) {
                it->describe(writer);
            }
            writer.EndArray();
            break;
        case boolean:
            writer.Bool(getUnSigned());
            break;
        case signed_number:
            writer.Int64(getSigned());
            break;
        case unsigned_number:
            writer.Uint64(getUnSigned());
            break;
        case float_number:
            writer.Double(getDouble());
            break;
        case string:
            writer.String(getString());
            break;
        default:
            throw Exception(UserError(UserError::ERROR_WRONG_PARAM), "incorrect item type parsing json");
        }
    }
}
;

/*
 * @todo
 * jsonItemContainer is needed
 *
 */

//! type traits for json item
template<class T>
struct item_type {
    constexpr static IjsonItem::item_type_ type = std::is_floating_point<T>::value ? IjsonItem::float_number :
                                                  std::is_signed<T>::value ? IjsonItem::signed_number :
                                                  std::is_unsigned<T>::value ? IjsonItem::unsigned_number : IjsonItem::boolean;
};

/**
 *  Base template class for json item
 */
template<class T>
class jsonItem : public IjsonItem, _no_shareable {
    static_assert(std::is_pointer<T>::value == false,"Items of type pointer are not allowed");
    T val;      ///< current value
    T max_;     ///< max value allowed
    T min_;     ///< min value allowed
public:
    //http://stackoverflow.com/questions/17070351/why-does-numeric-limitsmin-return-a-negative-value-for-int-but-positive-values
    constexpr static const T max_c = std::numeric_limits<T>::max();     ///< max value for the the item type
    constexpr static const T min_c = std::is_integral<T>::value ? std::numeric_limits<T>::min() : -std::numeric_limits<T>::max(); /// min value for the item time
    using type = T;
    /**
     * Json item constructor
     * @param item name
     * @param minimum allowed value
     * @param maximum allowed value
     */
    jsonItem(const char* name, T min = min_c, T max = max_c)
            : IjsonItem(item_type<T>::type, name), max_(max), min_(min) {

    }
    /**
     * Set a value of type doble fpr this item
     * @param s new value to be set
     */
    virtual void setDouble(double s) override
    {
        if (std::is_integral<T>::value)
            throw JsonInvalidTypeException(name, "double");
        if (s > std::numeric_limits<T>::max())
            throw JsonInvalidValueException(name, s);
        return set(s);
    }
    /**
     * Set a value of type signed for this item
     * @param s new value to be set
     */
    virtual void setSigned(int64_t s) override
    {
        if (std::is_unsigned<T>::value)
            throw JsonInvalidTypeException(name, "int64");
        return set(s);
    }
    /**
     * Set a value of type unsigned for this item
     * @param s new value to be set
     */
    virtual void setUnSigned(uint64_t s) override
    {
        if (s > std::numeric_limits<T>::max())
            throw JsonInvalidValueException(name, s);
        return set(s);
    }
    /**
     * Get the item value as double
     */
    virtual double getDouble() const override
    {
        if (std::is_integral<T>::value)
            throw JsonInvalidTypeException(name, "double");
        return val;
    }
    /**
     * Get the item value as signed integer
     */
    virtual int64_t getSigned() const override
    {
        if ((!std::is_integral<T>::value) || (std::is_unsigned<T>::value))
            throw JsonInvalidTypeException(name, "int64");
        return (int64_t) val;
    }
    /**
     * Get the item value as unsigned
     */
    virtual uint64_t getUnSigned() const override
    {
        if ((!std::is_integral<T>::value) || (std::is_signed<T>::value))
            throw JsonInvalidTypeException(name, "uint64");
        return (uint64_t) val;
    }
    /**
     * Print to a output stream all object information
     * @param os : output stream
     */
//    void print(std::ostream& os) const override
//    {
//        os << "\"" << name << "\":";
//        os << val;
//    }
    /**
     * Set a new value to the item of template type
     * @param new value to set pas by reference
     */
    template<typename V>
    void set(V& value) {
        preSetCheck();
        if (value > max_ || value < min_) {
            throw JsonInvalidValueException(name, value);
        }
        val = static_cast<T>(value);
    }
    /// Destructor
    virtual ~jsonItem() {

    }
    /**
     * Set a new range for this value
     * @param minimum allowed value
     * @param max maximum allowed value
     */
    void setRange(T min, T max = max_c) {
        min_ = min;
        max_ = max;
    }
    /**
     * Set the max allowed value for this item
     * @param maximum allowed value
     */
    void setMax(T max) {
        max_ = max;
    }
    /**
     * Access the item value
     */
    const T get() const {
        return val;
    }
    /**
     * Helper operator
     */
    operator T() const {
        return val;
    }
};

/**
 * Json item specialization for type bool
 */
template<>
class jsonItem<bool> : public IjsonItem, _no_shareable {
    bool val = false;       ///< item value
    /**
     * Bool data is comming in this way
     */
    virtual void setBool(bool b) override {
        preSetCheck();
        val = b;
    }
public:
    /**
     * Json item constructor
     * @param item name
     * @param minimum allowed value
     * @param maximum allowed value
     */
    jsonItem(const char* name)
            : IjsonItem(boolean, name) {
    }
    /**
     * Get the current item value as const reference
     */
    bool get() const {
        return val;
    }
    /**
     * Helper operator
     */
    operator bool() const {
        return val;
    }
};

/**
 * Class to store string type json items
 */
template<>
class jsonItem<std::string> : public IjsonItem, _no_shareable {
    std::string val;        ///< current value of the item
    unsigned maxsize;    ///< maximum number of characters allowed
protected:
    /**
     * Set a new value for the item using a substring
     * @param str substring wih the new value to be set
     */
    virtual void setString(const SubString& str) override
    {
        preSetCheck();
        if (str.size() > maxsize)
            throw JsonInvalidValueException(name, "--- too long ---");
        val.assign(str.begin(), str.size());
    }
    /**
     * Print to a output stream all object information
     * @param os : output stream
     */
//    void print(std::ostream& os) const override
//    {
//        os << "\"" << name << "\":";
//        os << "\"" << val.c_str() << "\"";
//    }
public:
    /**
     * Constructor
     * @param item name
     * @param max numbers of characters allowed
     */
    jsonItem(const char* name, unsigned max_len = std::numeric_limits<unsigned>::max())
            : IjsonItem(string, name), maxsize(max_len) {
    }
    /**
     * Get string value in this item
     * @return const ref to std::string
     */
    const std::string& get() const {
        return val;
    }
    operator const std::string&() const {
        return val;
    }
    /**
     * use it carrefour
     */
    operator const char*() const {
        return val.c_str();
    }
    /**
     * Set a new string value for the item
     * @param str sew string to be set
     */
    void set(const std::string& str) {
        val = str;
    }
    /**
     * Get the value of the item
     * @return const char* current string store in this item
     */
    virtual const char* getString() const override
    {
        return val.c_str();
    }
    /// Destructor
    virtual ~jsonItem() {
    }
};

//using jsonItem<char*> = jsonItem<std::string> ;
//using jsonItem<const char*> = jsonItem<std::string> ;

/**
 * Class for items of enum type
 * Usage:
 * a .cpp file must contains next few lines
 *
 * DEFINE_ENUM_MAP_ITEMS(<enum type>,emap,jsonEnumItem<enum type>) = { {},{},{}};//
 * DEFINE_ENUM_MAP_ITEMS(<enum type>,emap,jsonEnumItem<enum type>);
 * OR
 * DEFINE_JSON_ENUM_MAP_ITEMS_DATA(<enum type>,{ {},{},{}});
 */
template<class E>
class jsonEnumItem : public IjsonItem, _no_shareable {
    //using enum_type = E;
public:
    E e {};    /// <
    DECLARE_ENUM_MAP_FOR_TEMPLATE(E,emap);   ///<
    /**
     * Constructor
     * @param item name
     * @param max numbers of characters allowed
     */
    jsonEnumItem(const char* name)
    : IjsonItem(string, name) {
    }
    /**
     * Set a new string value for the item
     * @param str sew string to be set
     */
    void set(E ne) {
        e = ne;
    }
    /**
     * Get current item value
     * @return value of type enum
     */
    E get() const {
        return e;
    }
    /**
     * Get the value of the item
     * @return const char* current string store in this item or nullptr
     */
    virtual const char* getString() const override
    {
        return emap.getStr(e);
    }
    /// Destructor
    virtual ~jsonEnumItem() {
    }
    /**
     * Helper function from enum to sring convertion
     * @return string or a exception
     */
    static const char* toString(const E e) {
        const char * r = emap.getStr(e);
        if (r == nullptr)
        throw JsonMissingValueException("enum", TYPE_NAME(E));
        return r;
    }
    /**
     * Find enum value or throw an exception
     */
    template<class S>
    static E getEnum(const S& s)
    {
        E e {};
        if (!emap.getEnum(s, e))
            throw std::invalid_argument(FormatString() << "Value "<< s << " is not valid ");
        return e;
    }
    /**
     * Get internal enum value as string
     * @return string value or a n exception is throw
     */
    const char* toString() const {
        const char * r = emap.getStr(e);
        if (r == nullptr)
        throw JsonMissingValueException("enum", TYPE_NAME(E));
        return r;
    }
    /**
     * Helper function to translate from enum to string
     */
    static const char* sGetString(E e)
    {
        return emap.getStr(e);
    }
    /**
     * Implicit convertion to enum type
     */
    operator E() const
    {
        return e;
    }
protected:
    /**
     * Set a new value for the item using a substring
     * @param str substring wih the new value to be set
     */
    virtual void setString(const SubString& str) override
    {
        preSetCheck();
        if (!emap.getEnum(str, e))
        throw JsonInvalidValueException(name, str);
    }
    /**
     * Set a new value to the item of template type number
     * @param new value to set pas by reference
     */
    template<typename V>
    void set(V value) {
        std::ostringstream os;
        os << value;
        setString(os.str().c_str());
    }
    /**
     * Set a value of type doble fpr this item
     * @param s new value to be set
     */
    virtual void setDouble(double s) override
    {
        set(s);
    }
    /**
     * Set a value of type signed for this item
     * @param s new value to be set
     */
    virtual void setSigned(int64_t s) override
    {
        set(s);
    }
    /**
     * Set a value of type unsigned for this item
     * @param s new value to be set
     */
    virtual void setUnSigned(uint64_t s) override
    {
        set(s);
    }
};

#define DEFINE_JSON_ENUM_MAP_ITEMS(type) \
    template<> \
    DEFINE_ENUM_MAP_ITEMS(type,emap,jsonEnumItem<type>)

#define DEFINE_JSON_ENUM_MAP(type) \
    template<> \
    DEFINE_ENUM_MAP(type,emap,jsonEnumItem<type>)

#define DEFINE_JSON_ENUM_MAP_ITEMS_DATA(type,...) \
    DEFINE_JSON_ENUM_MAP_ITEMS(type) = __VA_ARGS__; \
    DEFINE_JSON_ENUM_MAP(type)

/**
 * Base class for a item of type object
 */
class jsonObject : public IjsonItem, _no_shareable {
    bool open_ = true;      ///< Status of object when de serialise
protected:
    /**
     * Constructor
     * @name - item json name
     * @items - list of subitem in this object
     */
    jsonObject(const char* name, std::initializer_list<IjsonItem*> items)
            : IjsonItem(object, name, items) {
    }
    /**
     * Called from parser when the object is open {
     */
    virtual IjsonItem* OpenObject() override
    {
        preSetCheck();
        //if_debug(std::cout << "OpenObject for " << getName() << std::endl;);
        open_ = true;
        return nullptr;
    }
    /**
     * Called when the object is close using } it is time to validate the object
     */
    void flush(IjsonItem*) override
    {
        //if_debug(std::cout << "flush for " << getName()<< std::endl;);
    }
    /**
     * If this item is an object then all data is checked
     */
    virtual void CloseObject() override
    {
        open_ = false;
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->isMandatory() && !(*it)->isValue())
                throw JsonMissingValueException((*it)->getName(), name);
        }
    }
    /// destructor
    virtual ~jsonObject() {
    }
};

/**
 * Base type for a item of type container that hold basic types
 */
template<class T>
class jsonContainer : public IjsonItem, public std::vector<T>, public _no_shareable {
    static_assert(std::is_pointer<T>::value == false,"Pointers types are not allowed");
    T max_;     ///< max value allowed
    T min_;     ///< min value allowed
public:
    //http://stackoverflow.com/questions/17070351/why-does-numeric-limitsmin-return-a-negative-value-for-int-but-positive-values
    /// max value for the the item type
    constexpr static const T max_c = std::numeric_limits<T>::max();
    /// min value for the item time
    constexpr static const T min_c = std::is_integral<T>::value ? std::numeric_limits<T>::min() : -std::numeric_limits<T>::max();

    using type = T;
    unsigned count = 0;     //!< counter how many object are inside
    bool open = false;      ///< check if container is open and ready to accept objects

    //! This function is invoke at started of the list for this item
    virtual IjsonItem* OpenContainer() override
    {
        preSetCheck();
        open = true;
        return nullptr;
    }
    /**
     * This object has finished receiving data,
     * Do some validation of current data
     */
    virtual void CloseContainer() override
    {
        open = false;
        // there is not duplicate item
    }
    // Overwritten all set function do validation and so
public:
    /**
     * Constructor
     * @param item name
     * @param minimum allowed value
     * @param maximum allowed value
     */
    jsonContainer(const char* name, T min = min_c, T max = max_c)
            : IjsonItem(IjsonItem::array, name), max_(max), min_(min) {

    }

    /// Destructor
    virtual ~jsonContainer() {
    }
    /**
     * Get count of item holding
     * @return number of items on this container
     */
    size_t getCount() const {
        return count;
    }

    /**
     * Set a value of type doble fpr this item
     * @param s new value to be set
     */
    virtual void setDouble(double s) override
    {
        if (std::is_integral<T>::value)
            throw JsonInvalidTypeException(name, "double");
        if (s > std::numeric_limits<T>::max())
            throw JsonInvalidValueException(name, s);
        return set(s);
    }
    /**
     * Set a value of type signed for this item
     * @param s new value to be set
     */
    virtual void setSigned(int64_t s) override
    {
        if (std::is_unsigned<T>::value)
            throw JsonInvalidTypeException(name, "int64");
        return set(s);
    }
    /**
     * Set a value of type unsigned for this item
     * @param s new value to be set
     */
    virtual void setUnSigned(uint64_t s) override
    {
        return set(s);
    }
    /**
     * Set a new value to the item of template type
     * @param new value to set pas by reference
     */
    template<typename V>
    void set(V& value) {
        if (!open) {
            throw JsonInvalidTypeException(name, "item");
        }
        if (!Range::check(value, min_, max_))
            throw JsonInvalidValueException(name, value);
        this->push_back(static_cast<T>(value));
        count++;
    }
    /**
     * Set a new range for this value
     * @param minimum allowed value
     * @param max maximum allowed value
     */
    void setRange(T min, T max = max_c) {
        min_ = min;
        max_ = max;
    }
    /**
     * Set the max allowed value for this item
     * @param maximum allowed value
     */
    void setMax(T max) {
        max_ = max;
    }
};

/**
 * Specialisation of json container for type string
 */
template<>
class jsonContainer<std::string> : public IjsonItem, public std::vector<std::string>, public _no_shareable {
    unsigned maxsize;    ///< maximum number of characters allowed

    unsigned count = 0;     //!< counter how many object are inside
    bool open = false;      ///< check if container is open and ready to accept objects

    //! This function is invoke at started of the list for this item
    virtual IjsonItem* OpenContainer() override
    {
        preSetCheck();
        open = true;
        return nullptr;
    }
    /**
     * This object has finished receiving data,
     * Do some validation of current data
     */
    virtual void CloseContainer() override
    {
        open = false;
        // there is not duplicate item
    }
    /**
     * Set a new value for the item using a substring
     * @param str substring wih the new value to be set
     */
    virtual void setString(const SubString& str) override
    {
        if (str.size() > maxsize)
            throw JsonInvalidValueException(name, "--- too long ---");
        this->emplace_back(str.begin(), str.size());
    }
public:
    /**
     * Constructor
     * @param item name
     * @param minimum allowed value
     * @param maximum allowed value
     */
    jsonContainer(const char* name, unsigned max_len = std::numeric_limits<unsigned>::max())
            : IjsonItem(IjsonItem::array, name), maxsize(max_len) {
    }
};

/**
 * Base for an item of type array
 */
template<class T>
class jsonObjectContainer : public IjsonItem, public std::list<T>, _no_shareable {
    unsigned count = 0;     //!< counter how many object are inside
    bool open = false;      ///< check if container is open and ready to accept objects

    //! This function is invoke at started of the list for this item
    virtual IjsonItem* OpenContainer() override
    {
        preSetCheck();
        //if_debug(std::cout << "OpenContainer for " << getName()<< std::endl;);
        open = true;
        return nullptr;
    }
    /**
     * This object has finished receiving data,
     * Do some validation of current data
     */
    virtual void CloseContainer() override
    {
        //if_debug(std::cout << "CloseContainer for " << getName() << std::endl;);
        open = false;
        // validate agains duplicate items list
        T* new_item = &std::list<T>::back();
        for (auto it = std::list<T>::begin(); &(*it) != new_item; ++it) {
            if (new_item->getId() == (*it).getId())
                throw JsonDuplicateObjectException((*it).getName(), (*it).getId());
        }
    }
    /**
     *
     */
    virtual IjsonItem* OpenObject() override
    {
        //if_debug(std::cout << "OpenObject for " << getName()<< std::endl;);
        if (!open)
            throw JsonInvalidTypeException(getName(), "object");
        count++;
        std::list<T>::emplace_back();
        IjsonItem * it = &std::list<T>::back();
        it->OpenObject();
        return it;
    }
    /**
     * If this item is an object then all data is checked
     */
    virtual void flush(IjsonItem*) override
    {
        //if_debug(std::cout << "flush for " << getName()<< std::endl;);
        // check item properties now or do when the container is close
    }
public:
    /**
     * Constructor
     * @name name of the item in json
     */
    jsonObjectContainer(const char* name)
            : IjsonItem(IjsonItem::array, name) {

    }
    /// Destructor
    virtual ~jsonObjectContainer() {
    }
    /**
     * Get count of item holding
     * @return number of items on this container
     */
    size_t getCount() const {
        return count;
    }
};

/**
 * Error class discribing all error produce by the broker that
 * convert json event into data objects
 */
class JsonError : public Error {

public:
    /**
     * define enum items
     */
    enum ecode_e {
        BEGIN = 400,        //
        TO_MANY,        //
        TO_MANY_SENSORS,        //
        TO_MANY_FIBERS,        //
        TO_MANY_CHANNELS,        //
        MISSING_VALUE,  //
        END //
    };
    static const enumString<enum ecode_e> err_map_;
    /**
     * Error Constructor from code
     * @param [in] code - Error code base on
     */
    JsonError(enum ecode_e code)
            : Error(code, err_map_.get(code)) {
    }
};

/**
 * Exception produce when the max count of item for an specific time is superate
 */
class ToManyItems : public JsonItemException {
    unsigned max_;       ///< Maximum number of item allowed
    std::string name_;   ///< name of the item producing the exception
public:
    /**
     * Exception constructor from item name and max allowed
     * @param [in] name - item name
     * @param [in] max - maximum allowed
     */
    ToManyItems(const std::string & name, unsigned max)
            : JsonItemException(JsonItemError::ERR_TO_MANY_ITEMS), max_(max), name_(name) {
        //   message_ = error_.description_;
    }

    /**
     * Virtual function called from insertion operator
     * @param [in] ostream use to push all object information
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "To many items of type " << name_ << " max allowed is  " << max_;
    }
    /** Destructor */
    virtual ~ToManyItems() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Reply content for JSON - REST interface
 */
class JsonReply : public Json::jsonObject {
    constexpr static const char* code_s = "code";
    constexpr static const char* msg_s = "message";

    Json::jsonItem<unsigned> code;    //!< Error code
    Json::jsonItem<std::string> msg;         //!< Error Message
public:
    /**
     * Object constructor from error code and error message
     * @param [in] pcode - Number representing error
     * @param [in] pmsg - Error message
     */
    JsonReply(unsigned pcode, const std::string& pmsg)
            : jsonObject("", { &code, &msg }), code("code"), msg("message") {
        code.set(pcode);
        msg.set(pmsg);
    }
    /**
     * Describe code and message data to be use for serialization
     * @param code - error code to describe
     * @param message - error message to describe
     * @param handler - handler receiving all describe events
     */
    template<class H>
    static void describe(unsigned code, const char* message, H& handler) {
        handler.StartObject();
        handler.String(code_s);
        handler.Uint(code);
        handler.String(msg_s);
        handler.String(message);
        handler.EndObject();
    }
    /**
     * Describe this class to be use for serialization
     * @param handler - handler receiving all describe events
     */
    template<class H>
    void describe(H& handler) const {
        return describe(code.get(), msg.getString(), handler);
    }
};

} // namespace
} // namespace
#endif /* JSONBASE_H_ */
