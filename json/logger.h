/*
 * logger.h
 *
 *  Created on: 10 Mar 2015
 *      Author: lester
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <syslog.h>
#include "file.h"


namespace os{

/**
 * Wrapper for syslog using insertion operator
 * Example usage:
 *      log.setLevel(Logger::debug);
 *      log.EnableOutput(Logger::o_stdout);
 *      bool my_value;
 *      Logger::getWritter<Logger::info>() << "this is my log message with bool value " << my_value;


 */
class Logger : public _no_shareable {
    Logger()
            : level_(error) {

    }
public:
    enum elevel {
        none, //
        error,      //!< log runtime level is not applied to this level
        warning,    //!< log runtime level is applied to this level
        info,
        debug,      //!< only print for debug build
    };
    //! logger available outputs to print out logs
    enum e_outputs {
        o_stderr = 1, //!< standard error console
        o_stdout, //!< standard console
        o_syslog, //!< use syslog
        o_file    //!< write to a file
    };

private:
    enum elevel level_=none;
    BitFlags<e_outputs> outputs_;
    File file_;

    friend class logStream;
    /**
     * Object for temporal print formated data before send to log
     */
    class logStream : public std::ostringstream {
        const elevel priority;
    public:
        logStream(elevel priority)
                : priority(priority) {
        }
        ~logStream() {
            std::string msg = str();        // construct string only ones
            if (msg.length()) {
                Logger::get().write(priority,msg.c_str());
            }
        }
    };
    /**
     * Logger null writter, when this type is use the log is remove at compiler time
     */
    class logNullStream {
    public:
        /**
         * Default constructor
         * @param level - log level to be produce when this log is printout
         */
        logNullStream(elevel) {
        }
        /**
         *
         */
        template<typename T>
        inline logNullStream& operator<<(const T&) {
            return *this;
        }
        // Manipulators
        typedef std::ostream& (*STRFUNC)(std::ostream&);

        /**
         * Manipulator overwritten
         * @param osstream manipulator
         */
        logNullStream& operator<<(STRFUNC )
        {
            return *this;
        }
    };
    /**
     * Write a log message
     * @param [in] l - message level or severity
     * @param [in] d - null terminated string message to log
     *
     * @todo do not throw an exception here because this function is used to trace exception message that means it is call in a catch clause
     */
    void write(enum elevel l, const char* d) {
        // level filter
        if (l <= level_) {
            if (outputs_.is(o_stdout))
                std::cout << d << std::endl;
            if (outputs_.is(o_stderr))
                std::cerr << d << std::endl;
            if (outputs_.is(o_syslog))
                ::syslog(l == error ? LOG_ERR : l == warning ? LOG_WARNING : l == info ? LOG_INFO : l == debug ? LOG_DEBUG : LOG_DEBUG, "%s", d);
            if (outputs_.is(o_file))
            {
                file_.write(d,strlen(d));
                file_.write("\r",1);
                file_.flush();
            }

        }
    }
public:
    /*
     * Use traits to return a different type for template specialization
     */
    template<Logger::elevel LVL>
    struct log_return {
        typedef Logger::logStream type;
    };

    template<Logger::elevel LVL>
    static typename log_return<LVL>::type getWritter() {
        return {LVL};
    }
    enum elevel getLevel() {
        return level_;
    }
    void setLevel(enum elevel lvl) {
        level_ = lvl;
    }
    void EnableOutput(e_outputs o) {
        outputs_.set(o);
    }
    void DisableOutput(e_outputs o) {
        outputs_.clear(o);
    }
    static Logger& get() {
        static Logger b;
        return b;
    }
    void EnableFile(const char* file)
    {
        file_.open_s(file,O_CREAT |O_WRONLY|O_TRUNC);
        if (file_)
        {
            EnableOutput(o_file);
        }
        else
            std::cout << "Failed to open " << file << " " << file_.getError() << std::endl;
    }
};

/**
 * Template specialization for log writer type when level is debug
 * Debug level is remove on compile time if application is not build for debug
 */
#ifndef _DEBUG
template<>
struct Logger::log_return<Logger::debug> { typedef Logger::logNullStream type; };
#endif

}
/* namespace os*/






#endif /* LOGGER_H_ */
