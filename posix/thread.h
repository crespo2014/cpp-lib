/**
 * @copyright  Copyright (c) 2013, Faztech Research Ltd. All rights reserved.
 * @file
 * @date 8 July 2014
 * @author: Lester Crespo (lester.crespo@faztechnology.com)
 *  A general object which describe operating system character
 *  Data type, error descriptions wrapping Linux system specific
 *  functions so to allow multi-platform applications.
 *  @todo move non OS related classes into other file. Maybe common.h?
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <thread>
#include <pthread.h>
#include <stdexcept>
#include <system_error>

class Runnable {
    friend class Thread;
public:
    enum policy {
        runonce, //
        runalways
    };
    virtual void loop() = 0;     ///<
    virtual void stop();
    bool Running() const;
    void run(enum policy pol);
    static void disableSignal(int signal);         ///< Disable specific signal catch execute from thread
protected:
    virtual ~Runnable() {
    }
private:
    volatile bool running = false;
    void run_once();
    void run_always();

};

class Thread
{
public:
    Thread(Runnable&,Runnable::policy = Runnable::policy::runonce);
    ~Thread();
protected:
private:
    Runnable& obj_;
    std::thread thread_;
};


#endif /* THREAD_H_ */
