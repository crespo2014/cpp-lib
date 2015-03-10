
#ifndef COMMON_H_
#define COMMON_H_

#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <stdarg.h>
#include <map>
#include <exception>
#include <stdexcept>

#include <vector>
#include <iostream>
/**
 * base class to hide copy and move constructor from derived class
 */
class _no_copyable {
public:
    /**
     * Hide copy constructor
     */
    _no_copyable(const _no_copyable&) = delete;
    /**
     * Hide move constructor
     */
    _no_copyable(const _no_copyable&&) = delete;
protected:
    /**
     * Default constructor without parameters use only by derived class
     */
    _no_copyable() {
    }
};

/**
 * base class to hide copy and move assignment  operator from derived class
 */
class _no_assignable {
public:
    /**
     * Hide assignment operator
     */
    _no_assignable& operator =(const _no_assignable&) = delete;
    /**
     * Hide move operator
     */
    _no_assignable& operator =(const _no_assignable&&) = delete;
protected:
    /**
     * Default constructor without parameters use only by derived class
     */
    _no_assignable() {
    }
    ;
};

/**
 * Base class that make derived not copyable and not assignable
 * because the object can not share internal data with other object
 */
class _no_shareable : public _no_copyable, _no_assignable {
protected:
    /**
     * Default constructor without parameters use only by derived class
     */
    _no_shareable() {
    }
};


/**
 * Block of memory or buffer
 */
class cBlock : public _no_shareable {
    const void * const data_;   ///< pointer to data
    const size_t size_;     ///< size of data pointed to
public:
    /**
     * Constructor
     * @param [in] data - pointer to current data
     * @param [in] size - len of this buffer
     */
    cBlock(const void* data, size_t size)
            : data_(data), size_(size) {

    }
    /**
     * Copy constructor
     */
    cBlock(const cBlock& b)
            : data_(b.data_), size_(b.size_) {

    }
    /// Move constructor
    cBlock(const cBlock&& b)
            : data_(b.data_), size_(b.size_) {

    }
    /**
     * Get pointer to data
     * @return a pointer to current data
     */
    const void * data() const {
        return data_;
    }
    /**
     * Get size or len of data pointed
     * @return size in bytes of the block
     */
    size_t size() const {
        return size_;
    }

};

/**
 * Object -map from enum to const char *
 * declare an static object on .h define on .cpp with all mapping
 * gap are not allowed
 * use enum string template with the enum as template
 * the enum must implement BEGIN END enum to delimiter the list
 */
template<class T>
class enumString {
public:
    struct str_map {
        T id;
        const char * const str;
    };
    //static const char* const data_[T::END - T::BEGIN];
    const char* get(T idx) const {
        return SetGet(idx);
    }
    /**
     * Constructor
     * An static enumString class must be define per enumtype to allow string map creation
     * declare the enum as static inside some object and defined in cpp file with table
     * @args list with id and string
     */
    enumString(const std::initializer_list<struct str_map>& args) {
        SetGet(static_cast<T>(T::BEGIN + 1),args);
    }
    /**
     * Define enum string mapping
     */
    const char* SetGet(T id, const std::initializer_list<struct str_map>& args = {}) const {
        static bool init = false;
        static const char* IdMap[T::END - T::BEGIN - 1];
        if (!init) {
            for (auto it : args) {
                IdMap[it.id - T::BEGIN - 1] = it.str;
            }
            init = true;
        }
        const char *r = ((id > T::BEGIN) && (id < T::END)) ? IdMap[id - (T::BEGIN + 1)] : "";
        return (r != nullptr) ? r : "";
    }
    //static int a;
};

/**
 * Bit flags from enum
 */
template<typename B, typename S = unsigned>
class BitFlags {
    static_assert(std::is_unsigned<S>::value,"Member variable holding bit flags must be an unsigned type");
    S flag;
public:
    BitFlags(S v = 0)
            : flag(v) {

    }
    bool is(B bit) const {
        //static_assert((1<< bit) <= std::numeric_limits<S>::max(),"There is not enough space to hold this flag");
        return ((flag & (1 << bit)) != 0);
    }
    void set(B bit) {
        //static_assert((1<< bit) <= std::numeric_limits<S>::max(),"There is not enough space to hold this flag");
        flag |= (1 << bit);
    }
    void clear(B bit) {
        //static_assert((1<< bit) <= std::numeric_limits<S>::max(),"There is not enough space to hold this flag");
        flag &= ~(1 << bit);
    }
};

/**
 * Simple buffer with overflow control
 * it needs a memory block to store incoming data until it is full
 */
class Buffer {
    bool overflow = false;    //!< set to true on overflow
    char* const d;            //!< pointer to data
    size_t const max_size;            //!< max size
    size_t pos = 0;                    //!< write position
public:
    /**
     * Constructor to create buffer from memory and size
     * @param [in] d - the input data buffer
     * @param [in] len - the size of the data buffer
     */
    Buffer(void *d, size_t len)
            : d(reinterpret_cast<char*>(d)), max_size(len) {
    }
    /**
     * insertion operator for null terminated string
     * @param [in] s - the string
     *@return Buffer& - the reference to the current buffer
     */
    Buffer& operator <<(const char* s) {
        if (!overflow) {
            auto l = strlen(s);
            if (l + pos > max_size) {
                l = max_size - pos;
                overflow = true;
            }
            memcpy(d + pos, s, l);
            pos += l;
        }
        return *this;
    }
    /**
     * insertion operator for a char
     * @param [in] c - the char
     *@return Buffer& - the reference to the current buffer
     */
    Buffer& operator<<(const char c) {
        if (pos < max_size) {
            d[pos] = c;
            ++pos;
        } else
            overflow = true;
        return *this;
    }
    /**
     * Get the size of the data currently in the buffer
     *@return size_t - the number of bytes
     */
    size_t getSize() const {
        return pos;
    }
    /**
     * Check if buffer overflow occurred
     *@return bool - true if overflow occurred, else false
     */
    bool isOverflow() const {
        return overflow;
    }
    /**
     * Check if buffer contains only ASCII
     *@return bool - true if ASCII, else false
     */
    bool isASCII() const {
        for (size_t i = 0; i != max_size; ++i) {
            if (d[i] > 0)
                return false;
        }
        return true;
    }
    /**
     * Iterator begin method. Gets the pointer to the first character in buffer.
     *@return const char* - the pointer.
     */
    const char* begin() const {
        return d;
    }
    /**
     * Iterator begin method. Gets the pointer to the past-the-last element in the buffer
     *@return const char* - the pointer.
     */
    const char* end() const {
        return d + max_size;
    }
    /**
     * insertion operator for printing to ostream.
     * @param [in] os - the ostream object
     * @param [in] b - the buffer object
     */
    friend std::ostream& operator<<(std::ostream& os, const Buffer& b) {
        auto s = b.d;
        auto e = s + b.max_size;
        while (s != e) {
            os << *s;
            ++s;
        }
        return os;
    }
};

/**
 * SubString is a object to manage a const string
 * It is useful for getting substrings in the const string, allowing easier string comparison.
 * using this class copying a const char* for later processing can be avoided manipulating the string directly over the original one
 *
 *      const char *text = "this a const string";
 *      SubString str(text+5,4);
 *      if (str == "a co") { //do something
 *      }
 *      std::string s1 = str;
 */
class SubString {
    const char* start;    //!< pointer to first character of string
    size_t len;         //!< size of string
public:
    //! Copy constructor
    SubString(const SubString &str)
            : start(str.start), len(str.len) {

    }
    //!Copy assignment
    SubString& operator=(const SubString& n_s) {
        start = n_s.start;
        len = n_s.len;
        return *this;
//        new (this) SubString(n_s);
//        return *this;
    }
    /** Constructor specifying start and end positions of string to get the substring.
     * @param [in] start - the pointer to the starting position of the const string
     * @param [in] end - the past-the-last pointer for the sub string
     */
    SubString(const char* start, const char* end)
            : start(start), len(end == nullptr ? strlen(start) : end - start) {

    }
    /** Constructor from a null terminated string
     * @param [in] start - the pointer to the starting position of the null terminated string
     */
    SubString(const char* start)
            : start(start), len(strlen(start)) {

    }
    /** Constructor using start char and len
     * @param [in] start - the pointer to the starting position of the string
     * @param [in] len - the size in bytes for the sub string
     */
    SubString(const char* start, size_t len)
            : start(start), len(len) {

    }
    /** Implicit conversion to std::string
     */
    operator std::string() const {
        return
        {   start,len};
    }

    std::string getString() const {
        return
        {   start,len};
    }

    ~SubString() {
    } //!< destructor
    /** Equal-to operator for a null terminated string
     * @param str - a null terminated string
     * @return bool - true if equal, else false.
     */
    bool operator ==(const char* str) const {
        return str && (strncmp(str, start, len) == 0) && str[len] == 0;
    }
    /** Equal-to operator SubString object
     * @param str - a SubString object
     * @return bool - true if equal, else false.
     */
    bool operator ==(const SubString & str) const {
        return len == str.len && strncmp(str.start, start, len) == 0;
    }
    /** Not-Equal-to operator for a null terminated string
     * @param str - a null terminated string
     * @return bool - true if not equal, else false.
     */
    bool operator !=(const char* str) const {
        return !(operator ==(str));
    }
    /** Not-Equal-to operator for SubString object
     * @param str - a SubString object
     * @return bool - true if not equal, else false.
     */
    bool operator !=(const SubString & str) const {
        return !(operator ==(str));
    }

    /**Get the len of the string contained in the class
     * @return size_t - the size of the SubString in bytes
     */
    size_t size() const {
        return len;
    }
    /** Get a pointer to the first character in the SubString
     * @return char* - the pointer to the first char
     */
    const char* begin() const {
        return start;
    }
    /** Get a pointer to the past-the-last character in the SubString
     * @return char* - the pointer to the past-the-last char
     */
    const char* end() const {
        return start + len;
    }
    /**
     * Insertion operator implementation
     */
    friend std::ostream& operator<<(std::ostream &out, const SubString &str) {
        return out.write(str.start, str.len);
    }
};

/**
 * Base Error class to encapsulate all error codes and description strings
 * Constructors are private to avoid object creation of this class directly,
 * since no error codes and corresponding description strings are defined here.
 * Instead inherit from this class and implement own error codes @see UserError,
 * or OSError for wrapping OS errno and strerror.
 */
class Error {
protected:
    int code_;
    std::string description_;

    /** Default constructor initialises to [0]: No Error */
    Error() {
        code_ = 0;
        description_ = "No Error";
    }
    Error(int code, std::string description) {
        code_ = code;
        description_ = description;
    }

public:
    int getCode() const {
        return code_;
    }
    const char* getMsg() const {
        return description_.c_str();
    }

    /** overloading equals operator so that comparing two error object
     * checks that both code and string are equal.
     */
    bool operator ==(const Error& e) {
        return (code_ == e.code_ && description_ == e.description_);
    }

    /** return true if error exists, else error code is 0. */
    operator bool() const {
        return (code_ != 0);
    }

    /** implicit cast operator for int */
    operator int() const {
        return code_;
    }

    Error(const Error&e) {
        code_ = e.code_;
        description_ = e.description_;
    }

    operator std::string() const {
        return description_;
    }

    void print(std::ostream& os) const {
        os << "ERR: [" << code_ << "]: " << description_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Error& e) {
        e.print(os);
        return os;
    }
};

/**
 * User exception class.
 * @todo implement severity and more
 */
class Exception : public std::exception {
protected:
    const Error error_;     ///< error which caused exception
    // mutable to be able to change in virtual function what
    std::string message_;       ///< exception message
    mutable std::string what_; ///< exception message

protected:
    /**
     * Constructor from Error object
     * @error - Error object to copy info from
     */
    Exception(const Error& error)
            : error_(error) {
    }
public:
    /**
     * Add extra information to the exception
     * @param [in] msg - null terminated string to be added
     * @return a reference to this object
     */
    Exception& append(const char* msg) {
        message_ += msg;
        return *this;
    }

    /** constructor from error message
     * @error - Error object to copy info from
     * @msg - Message to be displayed
     */
    Exception(const Error& error, const char* msg)
            : error_(error), message_(msg) {
    }
    /** Constructor from error message and code
     * @param [in] msg - the user error message
     * @param [in] ecode - the error code
     */
    Exception(const Error& error, const std::string & msg)
            : error_(error), message_(msg) {
    }

    /** Constructor from other exception
     * @param [in] e - exception object
     */
    Exception(const Exception& e)
            : error_(e.error_), message_(e.message_) {
    }

    /** Accessor method to return the contained Error */
    const Error& getError() const {
        return error_;
    }

    /** Insertion operator for ostream. For easier printing of object.
     * @param [in] os - the ostream object
     * @param [in] e - the exception object to print
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, const Exception& e) {
        return e.print(os);
    }
    /**
     * Virtual function use by insertion operator to call derived class
     * @os out stream use to print out object information
     */
    virtual std::ostream& print(std::ostream& os) const {
        return os << "Exception: " << message_ << std::endl << "->" << error_;
    }
    /** Get the exception message
     * @return const char* - the exception message
     */
    virtual const char* what() const _GLIBCXX_USE_NOEXCEPT override
    {
        if (what_.length() == 0) {
            std::ostringstream s;
            print(s);
            what_ = s.str();
        }
        return what_.c_str();
    }
    /** Destructor */
    virtual ~Exception() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * Class Holding error codes and Message
 */
class UserError : public Error {

public:
    /** User defined error codes.*/
    enum user_errors {
        ERROR_BASE64_LEN = 200, ///< length of base 64 is not valid
        ERROR_BASE64_CHAR = 201, ///< invalid base 64 char
        ERROR_WRONG_PROTOCOL = 202, ///< unrecognised character on protocol
        ERROR_CRC = 203, ///< CRC does not match
        ERROR_OVERWRITTEN = 204, ///< data has been overwritten. (share memory consumer design)
        ERROR_EOF = 205, ///< End of file, socket, or fd No more data
        ERROR_INVALID_CHAR = 206, ///< Char sequence invalid
        ERROR_WRONG_PARAM = 207, ///< The function was called with a not valid argument
        ERROR_LOCKED = 208, ///< The resource is locked, operation can not complete"
        ERROR_CALL_NOT_IMPLEMENTED = 209, ///< This function is not implement
        ERROR_NULL_PTR = 210, ///< a function call has returned a null pointer
        ERROR_INVALID_RESULT = 211, ///< return value from function is unexpected
        ERROR_SYS_COMMAND = 212, ///< failed to execute sys command
        ERROR_WRONG_NUMBER_START = 500, //
        ERROR_NOT_NUMBER, //
        ERROR_MISSING_DELIMITER, //
        ERROR_OVERFLOW, //
        ERROR_NOT_FOUND, //
        ERROR_INVALID_STATUS, //    Object is not in a valid status to execute this operation
        ERROR_INVALID_FILE_STREAM, // Invalid file stream (remove if file stream wrapper added in OS)
        ERROR_INVALID_FILE_DATA, // Invalid or unexpected XML format
        ERROR_DESERIALIZING_FILE, // Problem loading serialized data from file
        ERROR_SERIALIZING_FILE, // Problem serializing data to file
        ERROR_OUT_OF_RANGE,
        ERROR_ASSERT, // Assertion failed.
        ERROR_MIB_DATA_CHECK // Problem with parameter provided to MIB
    };
    /**
     * Constructot
     * @param - error code to store on class
     */
    UserError(enum user_errors code) {
        code_ = code;
        description_ = code2string(code);
    }
    /// Map which contains pairs of error code with message
    static const std::map<enum user_errors, std::string> code2string_map_;      /// move to common.cpp for optimisation
private:

    std::string code2string(enum user_errors code) {
        std::map<enum user_errors, std::string>::const_iterator it = code2string_map_.find(code);
        if (it != code2string_map_.end()) {
            return code2string_map_.find(code)->second;
        }
        // only if enum user_errors code does not match entries in code2string_map_
        return "Error code not found!"; //throw Exception(ERROR_INVALID_RESULT);
    }

};

/**
 * A object to create a formatted string on fly
 */
class FormatString : public std::ostringstream {
public:
    FormatString() {
    }
    template<class T>
    FormatString& operator<<(const T& t) {
        static_cast<std::ostringstream&>(*this) << t;
        return *this;
    }
    operator std::string() {
        return std::ostringstream::str();
    }
};

#define TYPE_NAME(x)    #x
/**
 * Another enum to string structure, Hope this time be more simple
 *
 * How to use
 * On header file declare enum on this way CREATE_ENUM_MAP(type,name_e)
 *
 * a.h
 * Class A {
 *  DECLARE_ENUM_MAP(mode_e,modes);
 *  }
 *
 * On cpp file define and use it
 * a.cpp
 *
 * DEFINE_ENUM_MAP_ITEMS(mode_e,A,modes) = { {2,"2"}, {3,"3"} };
 * DEFINE_ENUM_MAP(mode_e,A,modes);
 *
 * std::cout << A::modes.getStr(2);
 *
 *
 */
#define DECLARE_ENUM_MAP(type,name) \
    static const enumMap<type>::s_item name ## _items[]; \
    static const enumMap<type> name

#define DEFINE_ENUM_MAP_ITEMS(type,name,object) \
        const enumMap<type>::s_item object::name ## _items[]

#define DEFINE_ENUM_MAP(type,name,object) \
        const enumMap<type> object::name = {object::name ## _items,sizeof(object::name ## _items)/sizeof(*object::name ## _items)}

#define DECLARE_ENUM_MAP_FOR_TEMPLATE(type,name) \
    static const typename enumMap<type>::s_item name ## _items[]; \
    static const typename enumMap<type> name

#define DEFINE_ENUM_MAP_ITEMS_DATA(type,name,object,...) \
        DEFINE_ENUM_MAP_ITEMS(type,name,object) = __VA_ARGS__; \
        DEFINE_ENUM_MAP(type,name,object) \


template<class E>
struct enumMap {
    struct s_item {
        E e;
        const char* str;
    };
    const struct s_item * items;
    const size_t count_;
    /*
     * Get string that map to enum value
     * @e enum value to looking for
     * @return nullptr if failed to found
     */
    const char* getStr(E e) const {
        for (size_t i = 0; i < count_; ++i) {
            if (items[i].e == e)
                return items[i].str;
        }
        return nullptr;
    }
    bool getEnum(const char* str, E& e) const {
        for (size_t i = 0; i < count_; ++i) {
            if (strcmp(str, items[i].str) == 0) {
                e = items[i].e;
                return true;
            }
        }
        return false;
    }
    template<class S>
    bool getEnum(const S& str, E& e) const {
        for (size_t i = 0; i < count_; ++i) {
            if (str == items[i].str) {
                e = items[i].e;
                return true;
            }
        }
        return false;
    }
};

/**
 * Exception class covering all error relative to read hexadecimal numbers on itHexiterator
 */

class InvalidNumberException : public Exception {
public:
    /**
     * Constructor
     */
    InvalidNumberException(const Error& e)
            : Exception(e) {

    }
    InvalidNumberException(enum UserError::user_errors e)
            : Exception(UserError(e)) {
    }
    ;
    /**
     * Virtual function use by insertion operator to call derived class
     */
    virtual std::ostream& print(std::ostream& os) const override {
        return os << "Invalid number " << Exception::error_.getCode() << " " << Exception::error_.getMsg();
    }
    /** Destructor */
    virtual ~InvalidNumberException() _GLIBCXX_USE_NOEXCEPT {
    }
};

/**
 * split string containing hex values seperated by delimiter into a vector of hex values
 * @param str
 * @param delimiter
 * @return
 */
template<typename T = uint32_t>
std::vector<T> strToHexArray(const char* str, char delimiter){
    std::istringstream is(str);
    std::vector<T> val;
    T hexVal;
    is >> std::hex;
    while (is >> hexVal)
    {
        val.push_back(hexVal);
        if (is.peek() == delimiter){
            is.ignore();
        } else {
            throw std::invalid_argument("Delimiter is missing");//InvalidNumberException(UserError::ERROR_MISSING_DELIMITER);
        }
    }
    if (is.fail() && !is.eof()){
        throw std::invalid_argument("Missing or invalid number");// throw InvalidNumberException(UserError::ERROR_NOT_NUMBER);
    }
    return val;
}



#endif /* COMMON_H_ */
