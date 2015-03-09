/*
 * File.h
 *
 *  Created on: 24 Jan 2015
 *      Author: lester
 */

#ifndef FILE_H_
#define FILE_H_

#include <new>
#include "stdio.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdexcept>
#include <system_error>
#include <string.h>
#include "poll.h"
#include "ostreamstring.h"
#include <sys/sendfile.h>

namespace POSIX
{

class File
{
public:
    File(const char* name, int flag);
    File(const char* name, int flag, const std::nothrow_t& t);
    File(File&&);
    File& operator=(const File&&);
    virtual ~File();
    bool good();
    bool eof();
    void close();
    int ioctl(unsigned long request, void* arg);
    void* mmap(void *addr, size_t length, int prot = PROT_READ | PROT_WRITE, int flags = MAP_PRIVATE ,off_t offset = 0);
    size_t read(void *data, size_t size, const std::nothrow_t&)
    {
        return ::read(fd_,data, size);
    }
    /*
     * Get file descriptor to be used in system functions calls
     */
    int getfd() const
    {
        return fd_;
    }
    /*
     * Returns true if a event has been trigger
     */
    bool poll(short events,short& revents,int timeout,const std::nothrow_t&);
    /*
     * Call splice
     */
    ssize_t spliceTo(int fd_out, size_t len, loff_t *off_in = nullptr,loff_t *off_out=nullptr,unsigned int flags = 0)
    {
        ssize_t s;
        if ((s = ::splice(fd_,off_in,fd_out,off_out,len,flags)) < 0)
        {
            throw std::system_error(errno, std::system_category(),"splice");
        }
        return s;
    }
protected:
    File& operator=(const File&) = delete;
    File(const File&) = delete;
    //bool close(const std::nothrow_t& t);
private:
    int fd_ = -1;
    unsigned status_ = status_e::closed;
    enum status_e
    {
        ok, //
        fail,//
        eof_,//
        closed
    };
    //using fd_type = int;    ///< Linux generic file description type
    //fd_type fd = -1;        //!< the file descriptor
public:
    constexpr static unsigned F_RDONLY = O_RDONLY; ///< Wrapping read-only flag
    constexpr static unsigned F_WRONLY = O_WRONLY; ///< Wrapping write-only flag
    constexpr static unsigned F_RDWR = O_RDWR; ///< Wrapping read/write flag

    /**
     * Open the file at path
     * @param [in] path - Operating system name of the file, including path if necessary.
     * @param [in] flag - The requested input/output mode for the file.
     * @param [out] e - returns the result of operation.
     */
    void open(const char* path, int flag)
    {
        fd_ = ::open(path, flag, S_IRUSR | S_IWUSR);
        if (fd_ == -1)
        {
            throw std::system_error(errno, std::system_category(),"open");
        }
    }
    /**
     * Create a new file or delete current one if exist
     * exception safe function
     */
//    bool create_s(const char* fd_path)
//    {
//        open_s(fd_path,O_CREAT |O_WRONLY|O_TRUNC);
//        return error_;
//    }
    /**
     * Safe file open operation, not exception are generated file status is update with the result of operation
     * @param [in] path - Operating system name of the file, including path if necessary.
     * @param [in] flag - The requested input/output mode for the file.
     */
    void open_s(const char* path, int flag)
    {
        fd_ = ::open(path, flag, S_IRUSR | S_IWUSR);
        if (fd_ == -1)
            throw std::system_error(fd_, std::system_category());

    }

    bool open(const char* path, int flag,const std::nothrow_t&)
    {
        fd_ = ::open(path, flag, S_IRUSR | S_IWUSR);
        return (fd_ != -1);
    }

    //! default constructor
    File()
    {
    }
    /**
     * Constructor which opens the file at path
     *@param [in] path - Operating system name of the file, including path if necessary.
     *@param [in] flag - The requested input/output mode for the file.
     *@return - a exception is throw if operation can not complete
     */
//    File(const char* path, int flag)
//    {
//        File::open(path,flag);
//    }
//    File(const char* path, int flag,const std::nothrow_t&)
//    {
//        File::open(path,flag,std::nothrow);
//    }

    /**
     * read data from file
     * @param [in] d - pointer to the buffer stroing the data
     * @param [in,out] size - number of byte to be read from file on finish number of real bytes readed
     */
    size_t read(void* d,size_t len)
    {
        if (len)
        {
            auto r = ::read(fd_,d,len);
            if (r < 0)
            {

            }
            return r;
        }
        return 0;
    }
    /**
     * Write data to file
     * @param [in] d - pointer to the buffer holding the data
     * @param [in,out] size - number of bytes in the buffer in d, returns the number of bytes not written
     * @throws Exception on error
     */
    size_t write(const void* d, size_t size)
    {
        auto written = ::write(fd_, d, size);
        if (written < 0)
        {
            throw std::system_error(written, std::system_category());
        }
        return written;
    }
    int write(const void* d, size_t size,const std::nothrow_t&)
    {
        return ::write(fd_, d, size);
    }
    void write_all(const void* d, size_t size)
    {
        do
        {
            auto written = ::write(fd_, d, size);
            if (written < 0)
            {
                throw std::system_error(written, std::system_category());
            }
            size -= written;
        } while (size);
    }
    /** Constructor which opens the file at path as read-only
     * @param [in] path - Operating system name of the file, including path if necessary.
     * @param [out] e - returns the result of operation.
     */
    File(const char* path)
    {
        fd_ = ::open(path, O_RDONLY);
        if (fd_ == -1)
        {

        }
    }
    /**
     * Get the file descriptor and reset the internal file descriptor member.
     * The class loses ownership of the file descriptor, thus the caller of this function
     * is responsible for closing the file.
     *@return int - the file descriptor
     */
    int dettach()
    {
        int f = fd_;
        fd_ = -1;
        return f;
    }
    /**
     * Default destructor. Closes the file.
     */
//    ~File()
//    {
//        if (fd != -1)
//            ::close(fd);
//    }
    /**
     * Get boolean if file is open
     *@return bool - true if file is open, false if not opened
     */
    operator bool()
    {
        return fd_ != -1;
    }
    /**
     * Close the file.
     */
//    void close() noexcept
//    {
//        if (fd != -1)
//            ::close(fd);
//        fd = -1;
//    }


    /** Lock the file.
     * @throws Exception on error */
    void lock()
    {
        struct flock fl;
        memset(&fl, 0, sizeof(fl));
        fl.l_type = F_WRLCK;
        fl.l_whence = SEEK_SET;
        if (fcntl(fd_, F_SETLK, &fl) == -1)
        {

        }
    }
    /**
     * UnLock the file
     * @param [out] e - returns the result of operation.
     * @todo use exceptions
     */
    void unlock()
    {
        if (fd_ != -1)       // @todo remove when class become exception safe
        {
            struct flock fl;
            memset(&fl, 0, sizeof(fl));
            fl.l_type = F_UNLCK;
            fl.l_whence = SEEK_SET;
            if (fcntl(fd_, F_SETLK, &fl) == -1)
            {

            }
        }
    }

    /**
     * UnLock the file
     * @param [out] e - returns the result of operation.
     * @todo use exceptions
     */
    bool unlock_s() noexcept
    {
        if (fd_ != -1)       // @todo remove when class become exception safe
        {
            struct flock fl;
            memset(&fl, 0, sizeof(fl));
            fl.l_type = F_UNLCK;
            fl.l_whence = SEEK_SET;
            return (fcntl(fd_, F_SETLK, &fl) != -1);
        }
        return false;
    }

    /** Truncate the file
     * @throws Exception - on error
     */
    void truncate()
    {
        int r;
        if ((r = ::ftruncate(fd_, 0)) == -1)
        {
            throw std::system_error(r, std::system_category());
        }
    }
    /**
     * Flush all data to the file
     */
    bool flush(const std::nothrow_t&)
    {
        return (::fsync(fd_) == 0);
    }
    /**
     * No exception function to flush the file
     */
    void flush() noexcept
    {
        int r;
        if ((r = ::fsync(fd_)) != 0)
        {
            throw std::system_error(r, std::system_category());
        }
    }
    bool sync(const std::nothrow_t&)
    {
        return (::fsync(fd_) == 0);
    }
//    int ioctl(unsigned long request, void* arg,std::nothrow_t)
//    {
//        return ::ioctl(fd,request,arg);
//    }
//    void ioctl(unsigned long request, void* arg)
//    {
//        int r;
//        if ((r = ::ioctl(fd,request,arg)) != 0)
//        {
//            throw std::system_error(r, std::system_category());
//        }
//
//    }
    /*
     * Send file content from kernel space
     */
    ssize_t  sendFile(int dest_fd,size_t count,off_t* offset = nullptr)
    {
        ssize_t  r = ::sendfile(dest_fd,fd_,offset,count);
        if (r < 0)
        {
            throw std::system_error(errno, std::system_category(),"sendfile");
        }
        return r;
    }
};

} /* namespace POSIX */

#endif /* FILE_H_ */
