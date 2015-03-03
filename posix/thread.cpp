/*
 * thread.cpp
 *
 *  Created on: 29 Jan 2015
 *      Author: lester.crespo
 */

#include <csignal>
#include "thread.h"

Thread::Thread(Runnable& obj, Runnable::policy pol)
        : obj_(obj) {
    obj.running = true;
    thread_ = std::thread(&Runnable::run, std::ref(obj), pol);
}

Thread::~Thread() {
    obj_.stop();
    thread_.join();
}

void Runnable::disableSignal(int signal) {
    sigset_t set;
    sigaddset(&set, signal);
    if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0)
        throw std::system_error(errno, std::system_category());
}

void Runnable::stop() {
    running = false;
}

void Runnable::run(policy pol) {
    switch (pol) {
    case runonce:
        run_once();
        break;
    case runalways:
        run_always();
        break;
    }
    running = false;
}

void Runnable::run_once() {
    try
    {
        loop();
    } catch (const std::exception &e)
    {
       // LOG(ERROR_UNCAUGHT_EXCEPTION) << e.what();
    }
}

bool Runnable::Running() const {
    return running;
}

void Runnable::run_always() {

    do
    {
        try
        {
            loop();
        } catch (const std::exception &e)
        {
           // LOG(ERROR_UNCAUGHT_EXCEPTION) << e.what();
        }
    } while (running);

}


