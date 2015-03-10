
#ifndef THREAD_H_
#define THREAD_H_

#include <thread>
#include <pthread.h>
#include <stdexcept>
#include <system_error>
#include "signal.h"
#include "common.h"
#include "os/os_error.h"


namespace os {

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
    void disableSignal(int signal);         ///< Disable specific signal catch execute from thread
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

} /* namespace os*/


#endif /* THREAD_H_ */
