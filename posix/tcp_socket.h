/**
 * @copyright  Copyright (c) 2013, Faztech Research Ltd. All rights reserved.
 * @file
 * @date 8 July 2014
 * @author: Lester Crespo (lester.crespo@faztechnology.com)
 */

#ifndef TCP_SOCKET_H_
#define TCP_SOCKET_H_

#include "signal.h"
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <thread>
#include "poll.h"

/**
 * tcp sock wrapper class. supporting basic functionality for a socket
 * object will switch ownership for assignment and copy constructor.
 */
class tcpSock
{

    void bind(uint16_t port, uint32_t address = INADDR_ANY)
    {
        sock_addr_.sin_addr.s_addr = address;
        sock_addr_.sin_port = htons(port);
        if (::bind(sock_, (struct sockaddr*) &sock_addr_, sizeof(sock_addr_)) != 0)
        {
            good = false;
            throw std::system_error(errno, std::system_category(), SS() << "Failed to bind to socket. ip " << sock_addr_.sin_addr.s_addr << ":" << sock_addr_.sin_port);
        }
    }
    void listen(int count = 5)
    {
        if (::listen(sock_, count) != 0)
        {
            good = false;
            throw std::system_error(errno, std::system_category(), SS() << "failed to listen to socket. ip " << sock_addr_.sin_addr.s_addr << ":" << sock_addr_.sin_port);
        }
    }

    bool bind(uint16_t port, const std::nothrow_t&, uint32_t address = INADDR_ANY)
    {
        sock_addr_.sin_addr.s_addr = address;
        sock_addr_.sin_port = htons(port);
        if (::bind(sock_, (struct sockaddr*) &sock_addr_, sizeof(sock_addr_)) != 0)
        {
            good = false;
        }
        return good;
    }
    bool listen(int count, const std::nothrow_t&)
    {
        if (::listen(sock_, count) != 0)
        {
            good = false;
        }
        return good;
    }

    void connect(const struct in_addr& address, uint16_t port)
    {
        sock_addr_.sin_port = htons(port);
        sock_addr_.sin_addr = address;
        if (::connect(sock_, (const sockaddr*) &sock_addr_, sizeof(sock_addr_)) != 0)
        {
            good = false;
            throw std::system_error(errno, std::system_category(), SS() << "failed to connect to socket. ip " << sock_addr_.sin_addr.s_addr << ":" << sock_addr_.sin_port);
        }
    }
    /**
     * Constructor using socket descriptor
     */
    tcpSock(int sock, struct sockaddr_in& sock_addr) :
            sock_(sock), sock_addr_(sock_addr)
    {
    }
public:
    /*
     * Construct a connected socket
     */
    tcpSock(const char* srv, uint16_t port, int type = SOCK_STREAM, int domain = AF_INET, int protocol = 0) :
            tcpSock(type, domain, protocol)
    {
        if (::inet_aton(srv, &sock_addr_.sin_addr) == 0)
        {
            throw std::system_error(errno, std::system_category(), SS() << "inet_aton failed for " << srv);
        }
        sock_addr_.sin_port = htons(port);
        if (::connect(sock_, (const sockaddr*) &sock_addr_, sizeof(sock_addr_)) != 0)
        {
            throw std::system_error(errno, std::system_category(), SS() << "failed to connect to socket. ip " << sock_addr_.sin_addr.s_addr << ":" << sock_addr_.sin_port);
        }
    }

    /*
     * Default constructor
     */
    tcpSock(const std::nothrow_t&, int type = SOCK_STREAM, int domain = AF_INET, int protocol = 0)
    {
        sock_ = socket(domain, type, protocol);
        memset(&sock_addr_, 0, sizeof(sock_addr_));
        sock_addr_.sin_family = (sa_family_t) domain;
        good = (sock_ >= 0);
    }
    /**
     * Get a connected socket
     */
    tcpSock(const char* srv, uint16_t port, const std::nothrow_t&, int type = SOCK_STREAM, int domain = AF_INET, int protocol = 0) :
        tcpSock(std::nothrow,type, domain, protocol)
    {
        good = good && (::inet_aton(srv, &sock_addr_.sin_addr) != 0);
        sock_addr_.sin_port = htons(port);
        good = good && (::connect(sock_, (const sockaddr*) &sock_addr_, sizeof(sock_addr_)) == 0);
        if (!good)
            close();
    }
    /**
     * Create a socket
     */
    tcpSock(int type = SOCK_STREAM, int domain = AF_INET, int protocol = 0) :
            tcpSock(std::nothrow, type, domain, protocol)
    {
        if (sock_ < 0)
        {
            throw std::system_error(errno, std::system_category(), "socket");
        }
    }
    bool setupServer(uint16_t port, const std::nothrow_t&, uint32_t address = INADDR_ANY, int backlog = 5)
    {
        return (bind(port, std::nothrow, address) && listen(backlog, std::nothrow));
    }
    operator bool()
    {
        return (sock_ >= 0) && good;
    }
//    /**
//     * Get connection information
//     */
//    const struct sockaddr_in& getInfo() const
//    {
//        return sock_addr_;
//    }
    /**
     * Close the socket
     */
    void close()
    {
        if (!close(std::nothrow))
        {
            throw std::system_error(errno, std::system_category(), "close");
        }
    }
    bool close(const std::nothrow_t&)
    {
        bool b = (::close(sock_) == 0);
        sock_ = -1;
        return b;
    }
    /**
     * Copy constructor is not allowed
     * the socket handle can not be copy between objects
     * Only one object is the ownership of the socket
     * @param obj Object reference
     */
    tcpSock(const tcpSock& obj) = delete;
    /**
     * Assignment  is not allowed
     * the socket handle can not be share between objects
     * Only one object is the ownership of the socket
     * @param obj Object reference
     */
    tcpSock& operator=(const tcpSock& obj) = delete;

    /*!
     * Move constructor
     */
    tcpSock(tcpSock&& obj) :
            sock_(obj.sock_), sock_addr_(obj.sock_addr_)
    {
        obj.sock_ = -1;
    }
    /*
     * Move assignment
     */
    tcpSock& operator=(tcpSock&& obj) = delete;

    ~tcpSock()
    {
        if (sock_ != -1)
            ::close(sock_);
    }

    /**
     * Define blocking mode fr the socket
     * @param status - true to set blocking mode
     */
    void setBlockingMode(bool status)
    {
        int opt = status ? 0 : 1;
        if (::ioctl(sock_, FIONBIO, &opt) < 0)
        {
            throw std::system_error(errno, std::system_category(), SS() << "ioctl" << "failed to set blocking mode. ip " << sock_addr_.sin_addr.s_addr << ":" << sock_addr_.sin_port);
        }
    }
    /**
     * Setup a new socket using a incomming connectio
     */
    tcpSock accept()
    {
        struct sockaddr_in sock_addr;
        int size = sizeof(sock_addr);
        int fd = ::accept(sock_, (struct sockaddr*) &sock_addr, (socklen_t*) &size);
        if (fd < 0)
        {
            throw std::system_error(errno, std::system_category(), "accept");
        }
        return
        {   fd, sock_addr};
    }
    tcpSock accept(const std::nothrow_t&)
    {
        struct sockaddr_in sock_addr;
        int size = sizeof(sock_addr);
        int fd = ::accept(sock_, (struct sockaddr*) &sock_addr, (socklen_t*) &size);
        return
        {   fd, sock_addr};
    }
    /**
     * Get a server socket bind and listening in aspecific address
     * @param port - tcp/ip port
     * @param address - network interface to listen for connections
     * @param type - socket type to be create
     */
    static tcpSock getServer(uint16_t port, uint32_t address = INADDR_ANY, int type = SOCK_STREAM, int family = AF_INET, int protocol = 0)
    {
        tcpSock sock(type, family, protocol);
        sock.bind(port, address);
        sock.listen(5);
        return sock;
    }
    /**
     * Get a socket already connected to a client
     * @param srv - addres of server to connect to
     * @param port - tcp port to connect to
     * @return a connected socket or an exception is throw
     */
    static tcpSock getClient(const char* srv, uint16_t port)
    {
        struct in_addr addr;
        if (::inet_aton(srv, &addr) == 0)
        {
            throw std::system_error(errno, std::system_category(), SS() << "inet_atom" << "failed to get client. ip " << srv << ":" << port);
        }
        return getClient(addr, port);
    }
    /**
     * Convert from string ip address to network one
     *
     */
//    static uint32_t getAddress(const char* address)
//    {
//        char str[22];
//        struct addrinfo *ai;
//        struct addrinfo hints;
//        if (address == nullptr)
//            throw Exception();
//        /* Check parameters */
//           if (address == NULL) {
//               cob_err("Null address\n");
//               return COB_STATUS_INVAL;
//           }
//           retVal = (int)cob_strnlen(address, OS_IP_ADDR_STR_LEN);
//           if (retVal == OS_IP_ADDR_STR_LEN) {
//               cob_err("Address string too long\n");
//               return COB_STATUS_INVAL;
//           }
//
//           /* Convert port number to string for passing to getaddrinfo() */
//           snprintf(portStr, sizeof("65536"), "%u", port);
//
//           /*
//            * This hint tells getaddrinfo() that inputs are numeric format of IP address and port number (as opposed to a
//            * hostname that DNS can resolve to IP address), and that we want a stream (TCP) socket.
//            */
//           memset(&hints, 0, sizeof(hints));
//           hints.ai_flags = AI_ADDRCONFIG | AI_NUMERICHOST | AI_NUMERICSERV;
//           hints.ai_socktype = SOCK_STREAM;
//
//           /* Get info needed to open up socket for the given host */
//           if (strncmp("*", address, sizeof("*")) == 0) {
//               hints.ai_flags |= AI_PASSIVE;  /* AI_PASSIVE flag is equivalent to INADDR_ANY/IN6ADDR_ANY_INIT */
//               retVal = getaddrinfo(NULL, portStr, &hints, &ai);
//           } else {
//               retVal = getaddrinfo(address, portStr, &hints, &ai);
//           }
//           if (retVal < 0) {
//               cob_err("getaddrinfo(%s:%u) failed: %s\n", address, port, gai_strerror(retVal));
//               return COB_STATUS_ERROR;
//           }
//
//    }
    /**
     * Get non-blocking server socket
     * create an return an initialize socket listening for an specific port
     * @param [in] backlog How many listen connection on queue
     * @param [in] port listen port for
     * @param [in] address ip address or network interface to use
     * @param [in] type socket type to be create
     * @param [in] family - socket family
     * @param [in] protocol - tcp/ip protocol to use
     * @return a tcpsock object already initialise or an exception is throw
     */
    static tcpSock getNonBlockingServer(int backlog, uint16_t port, uint32_t address = INADDR_ANY, int type = SOCK_STREAM, int family = AF_INET, int protocol = 0)
    {
        tcpSock sock(type | SOCK_NONBLOCK | SOCK_CLOEXEC, family, protocol);
        int opt = 1;
        sock.setOption(SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        sock.bind(port, address);
        sock.listen(backlog);
        return sock;
    }
    /**
     * Get a socket already connected to a client
     * @param [in] address ip address or network interface to use
     * @param [in] port listen port for
     * @return a tcpsock object already initialise or an exception is throw
     */
    static tcpSock getClient(struct in_addr address, uint16_t port)
    {
        tcpSock sock;
        sock.connect(address, port);
        return sock;
    }
    /**
     * read data from sock
     * @param [in/out] buff - pointer to memory where data will be copied
     * @param [in] len - max numbers of bytes to be read
     * @param [in] flags - flags controlling the read operation
     * @return numbers of byte copied to the buffer or an exception is throw
     */
    size_t read(void* buff, size_t len, int flags = MSG_NOSIGNAL)
    {
        auto ir = ::recv(sock_, buff, len, flags);
        if (ir <= 0)
        {
            good = false;
            // socket is close or gracefully shutdown
            throw std::system_error(errno, std::system_category(), "read");
        }
        return ir;
    }
    /**
     * Read data from socket exception safe
     * @param [in/out] buff - pointer to memory where data will be copied
     * @param [in] len - max numbers of bytes to be read
     * @param [in] flags - flags controlling the read operation
     * @return how many bytes has been read 0 mean error or eof
     */
    size_t read_s(void* buff, size_t len, int flags = MSG_NOSIGNAL)
    {
        auto s = ::recv(sock_, buff, len, flags);
        return s > 0 ? s : 0;
    }
    /**
     * Write data to sock exception safe
     * @param [in] buff - pointer to memory where data is hold
     * @param [in] len - max numbers of bytes to be write
     * @param [in] flags - flags controlling the write operation
     * @return numbers of bytes written 0 means error
     */
    size_t write_s(const void* buff, size_t len, int flags = MSG_NOSIGNAL) noexcept
    {
        // use MSG_NOSIGNAL to avoid signal pipe
        auto s = ::send(sock_, buff, len, flags);
        return s > 0 ? s : 0;
    }

    /**
     * Write data to the sock
     * @param [in] buff - pointer to memory where data is hold
     * @param [in] len - max numbers of bytes to be write
     * @param [in] flags - flags controlling the write operation
     * @return numbers of bytes written or throw an exception
     */
    size_t write(const void* buff, size_t len, int flags = MSG_NOSIGNAL)
    {
        auto ir = ::send(sock_, buff, len, flags);
        if (ir <= 0)
            throw std::system_error(errno, std::system_category(), "write");
        return ir;
    }
    /**
     * Get tcp connected port
     * @return the tcp port number that this socket is connected
     */
    uint16_t getPort() const
    {
        return ntohs(sock_addr_.sin_port);
    }
    uint16_t getInPort() const
    {
        return ntohs(sock_addr_.sin_port);
    }

    /**
     * Wait for data become available on the socket for read or timeout
     * @param [in] msTimeout - How many milliseconds will elapsed before the function return timeout
     * @return true : data is available to be read on socket , false the specify time goes without data
     */
    bool waitData_s(unsigned int msTimeout)
    {
        struct pollfd poll_fd;
        poll_fd.fd = sock_;
        poll_fd.events = POLLIN;
        return (poll(&poll_fd, 1, msTimeout) > 0);
    }
    /**
     * Set read and write timeout for blocking operations
     * @param [in] rd_ms - read timeout in milliseconds
     * @param [in] wr_ms - write timeout in milliseconds
     */
    void setReadWriteTimeout_ms(int rd_ms, int wr_ms)
    {
        struct timeval rd = { rd.tv_sec = rd_ms / 1000, rd.tv_usec = (rd_ms % 1000) * 1000 };
        struct timeval wr = { wr.tv_sec = wr_ms / 1000, wr.tv_usec = (wr_ms % 1000) * 1000 };
        if ((setsockopt(sock_, SOL_SOCKET, SO_RCVTIMEO, &rd, sizeof(rd)) != 0) || (setsockopt(sock_, SOL_SOCKET, SO_SNDTIMEO, &wr, sizeof(wr)) != 0))
        {
            throw std::system_error(errno, std::system_category(), "setsockopt");
        }
    }
    /**
     * Set read write buffers size
     * @param [in] rd - read buffer size for tcp stack
     * @param [in] wr - write buffer size for tcp stack
     */
    void setReadWriteBuffers(int rd, int wr)
    {
        if ((setsockopt(sock_, SOL_SOCKET, SO_RCVBUF, &rd, sizeof(rd)) != 0) || (setsockopt(sock_, SOL_SOCKET, SO_SNDBUF, &wr, sizeof(wr)) != 0))
            throw std::system_error(errno, std::system_category(), "setsockopt");
    }
    /*!
     * send write data as soon as possible disabling this delay, and avoid waiting some time to send more data
     */
//    void setTCPnodelay(bool b = true) {
//        if (setsockopt(sock_, IPPROTO_TCP, TCP_NODELAY, &b, sizeof(int)) != 0)
//            throw Faz::os::std::system_error(errno,std::system_category(),"setsockopt");
//    }
    /**
     * Shutdown read/write channels on socket
     * @param [in] read - true to disable read on this socket a packet is send to the connected client
     * @param [in] write - true to disable write on this socket all pending write operations are finished
     */
    void shutdown(bool read, bool write)
    {
        if (::shutdown(sock_, (read && write ? SHUT_RDWR : read ? SHUT_RD : write ? SHUT_WR : 0)) != 0)
            throw std::system_error(errno, std::system_category(), "shutdown");
    }
    /**
     * Shutdown read/write channels on socket no exception is produce if the operation is unsuccessfully
     * @param read bool - set to true to shutdown read channel
     * @param write bool - set to true to shutdown write channel
     */
    bool shutdown_s(bool read, bool write) noexcept
    {
        return (::shutdown(sock_, (read && write ? SHUT_RDWR : read ? SHUT_RD : write ? SHUT_WR : 0)) == 0);
    }
    /**
     * Change a socket option
     * @param [in] __level - Option level to modified
     * @param [in] __optname - option to modified
     * @param [in] __optval - pointer to the new value to be set
     * @param [in] __optlen - size of value
     */
    void setOption(int __level, int __optname, __const void *__optval, socklen_t __optlen)
    {
        if (setsockopt(sock_, __level, __optname, __optval, __optlen) != 0)
        {
            throw std::system_error(errno, std::system_category(), "setsockopt");
        }
    }
    /// Change signalpipe status
//    void setsignalPipe(bool b = false) {
//        int set = b ? 1 : 0;
//        if (::setsockopt(sock_, SOL_SOCKET, SO_NOSIGPIPE, (void *) &set, sizeof(int)) != 0)
//            throw Faz::os::std::system_error(errno,std::system_category(),"setsockopt");
//    }
    /**
     * The socket descriptor is detached from the object
     * the socket will not be release by this class
     */
    int dettach()
    {
        int fd = sock_;
        sock_ = -1;
        return fd;
    }
    /**
     * Test socket file descriptor
     * @return true if socket is valid
     */
    bool isValid() const
    {
        return sock_ != -1;
    }
    /** Get the socket file descriptor
     * @return
     */
    int getfd() const
    {
        return sock_;
    }
    /**
     * Wait for a event on the socket
     * @param [in/out] event - events to poll for, return events that has been trigger
     * @param [in] timeout - time to wait for the events
     * @return true if the event is trigger, false if timeout
     */
    bool poll_event(short& event, int timeout)
    {
        struct pollfd fds = pollfd();
        fds.fd = sock_;
        fds.events = event;
        int i = poll(&fds, 1, timeout);
        if (i < 0)
            throw std::system_error(errno, std::system_category(), "poll");
        event = fds.revents;
        return i > 0;
    }
private:
    int sock_ = -1;                        ///< setting as mutable will allow invalidate this handle on copy constructor and assignment
    struct sockaddr_in sock_addr_;    ///< connection information
    bool good = true;
    /**
     * Write a block of data to the socket
     * @param [in] b data to be written
     * @return
     */
//    tcpSock& operator<<(const cBlock& b) {
//        size_t size = b.size();
//        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(b.data());
//        while (size) {
//            auto wr = write(ptr, size);
//            size -= wr;
//            ptr += wr;
//        }
//        return *this;
//    }
};

/**
 * Interface for implementing a tcpserver
 *
 * We need to implement polymorphy using templates to avoid race condition.
 * All members on class need to be initialize before start the thread.
 * and also the virtual function table need to be initialise (this is impossible inside base class ctor)
 */
//template<class S>
//class tcpServer : public os::Runnable {
//    tcpSock sock_;      ///< Server sock
//    S* srv_;            ///< Pointer to template parent class
//    /// thread function
//    void loop() override {
//        try {
//            disableSignal(SIGPIPE);
//            LOG(info) << "Starting Server on port " << sock_.getPort();
//            while (Running()) {
//                srv_->onCLient(std::move(sock_.accept()));
//            }
//       } catch (const std::exception &e) {
//            //if (Running())
//               // LOG(ERROR_UNCAUGHT_EXCEPTION) << e.what();
//        }
//       // LOG(info) << "ShutDown server on port " << sock_.getPort();
//    }
//    virtual void stop() override
//    {
//        Runnable::stop();
//        sock_.shutdown_s(true, false);
//    }
//public:
//    /// Constructor using tcp port
//    tcpServer(uint16_t port, S* srv)
//            : sock_(tcpSock::getServer(port)), srv_(srv) {
//    }
//    const tcpSock& getSock() const
//    {
//        return sock_;
//    }
//
//};
#endif /* TCP_SOCKET_H_ */
