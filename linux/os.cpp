/*
 * os.cpp
 *
 *  Created on: 23 Jun 2014
 *      Author: lester.crespo
 */

#include "os.h"
#include "errno.h"

os::_error_tbl os::api_tbl[] = { { 0, "unknown" },    //
		{ EPERM, "EPERM (Operation not permitted) " },    //
		{ ENOENT, "ENOENT (No such file or directory " },    //
		{ ESRCH, "ESRCH - No such process " },    //
		{ EINTR, "EINTR - Interrupted system call " },    //
		{ EIO, "EIO - I/O error " },    //
		{ ENXIO, "ENXIO - No such device or address " },    //
		{ E2BIG, "E2BIG - Argument list too long " },    //
		{ ENOEXEC, "ENOEXEC - Exec format error " },    //
		{ EBADF, "EBADF - Bad file number " },    //
		{ ECHILD, "ECHILD - No child processes " },    //
		{ EAGAIN, "EAGAIN - Try again " },    //
		{ ENOMEM, "ENOMEM - Out of memory " },    //
		{ EACCES, "EACCES - Permission denied " },    //
		{ EFAULT, "EFAULT - Bad address " },    //
		{ ENOTBLK, "ENOTBLK - Block device required " },    //
		{ EBUSY, "EBUSY - Device or resource busy " },    //
		{ EEXIST, "EEXIST - File exists " },    //
		{ EXDEV, "EXDEV - Cross-device link " },    //
		{ ENODEV, "ENODEV - No such device " },    //
		{ ENOTDIR, "ENOTDIR - Not a directory " },    //
		{ EISDIR, "EISDIR - Is a directory " },    //
		{ EINVAL, "EINVAL - Invalid argument " },    //
		{ ENFILE, "ENFILE - File table overflow " },    //
		{ EMFILE, "EMFILE - Too many open files " },    //
		{ ENOTTY, "ENOTTY - Not a typewriter " },    //
		{ ETXTBSY, "ETXTBSY - Text file busy " },    //
		{ EFBIG, "EFBIG - File too large " },    //
		{ ENOSPC, "ENOSPC - No space left on device " },    //
		{ ESPIPE, "ESPIPE - Illegal seek " },    //
		{ EROFS, "EROFS - Read-only file system " },    //
		{ EMLINK, "EMLINK - Too many links " },    //
		{ EPIPE, "EPIPE - Broken pipe " },    //
		{ EDOM, "EDOM - Math argument out of domain of func " },    //
		{ ERANGE, "ERANGE - Math result not representable " },    //
		{ EDEADLK, "EDEADLK - Resource deadlock would occur" },    //
		{ ENAMETOOLONG, "ENAMETOOLONG - File name too long" },     //
		{ ENOLCK, "ENOLCK - No record locks available" },     //
		{ ENOSYS, "ENOSYS - Function not implemented" },     //
		{ ENOTEMPTY, "ENOTEMPTY - Directory not empty" },     //
		{ ELOOP, "ELOOP - Too many symbolic links encountered" },     //
		{ EWOULDBLOCK, "EWOULDBLOCK - Operation would block" },     //
		{ EAGAIN, "EAGAIN -Operation would block" },     //
		{ ENOMSG, "ENOMSG - No message of desired type" },     //
		{ EIDRM, "EIDRM - Identifier removed" },     //
		{ ECHRNG, "ECHRNG - Channel number out of range" },     //
		{ EL2NSYNC, "EL2NSYNC - Level 2 not synchronized" },     //
		{ EL3HLT, "EL3HLT - Level 3 halted" },     //
		{ EL3RST, "EL3RST - Level 3 reset" },     //
		{ ELNRNG, "ELNRNG - Link number out of range" },     //
		{ EUNATCH, "EUNATCH - Protocol driver not attached" },     //
		{ ENOCSI, "ENOCSI - No CSI structure available" },     //
		{ EL2HLT, "EL2HLT - Level 2 halted" },     //
		{ EBADE, "EBADE - Invalid exchange" },     //
		{ EBADR, "EBADR - Invalid request descriptor" },     //
		{ EXFULL, "EXFULL - Exchange full" },     //
		{ ENOANO, "ENOANO - No anode" },     //
		{ EBADRQC, "EBADRQC - Invalid request code" },     //
		{ EBADSLT, "EBADSLT - Invalid slot" },     //
		{ EDEADLOCK, "EDEADLOCK - Dead lock" },     //
		//{ EDEADLK, "EDEADLK - Dead lock" },     //
		{ EBFONT, "EBFONT - Bad font file format" },     //
		{ ENOSTR, "ENOSTR Device not a stream" },     //
		{ ENODATA, "ENODATA - No data available" },     //
		{ ETIME, "ETIME - Timer expired" },     //
		{ ENOSR, "ENOSR - Out of streams resources" },     //
		{ ENONET, "ENONET - Machine is not on the network" },     //
		{ ENOPKG, "ENOPKG - Package not installed" },     //
		{ EREMOTE, "EREMOTE - Object is remote" },     //
		{ ENOLINK, "ENOLINK - Link has been severed" },     //
		{ EADV, "EADV - Advertise error" },     //
		{ ESRMNT, "ESRMNT - Srmount error" },     //
		{ ECOMM, "ECOMM - Communication error on send" },     //
		{ EPROTO, "Protocol error" },     //
		{ EMULTIHOP, "Multihop attempted" },     //
		{ EDOTDOT, "RFS specific error" },     //
		{ EBADMSG, "Not a data message" },     //
		{ EOVERFLOW, "Value too large for defined data type" },     //
		{ ENOTUNIQ, "Name not unique on network" },     //
		{ EBADFD, "File descriptor in bad state" },     //
		{ EREMCHG, "Remote address changed" },     //
		{ ELIBACC, "Can not access a needed shared library" },     //
		{ ELIBBAD, "Accessing a corrupted shared library" },     //
		{ ELIBSCN, ".lib section in a.out corrupted" },     //
		{ ELIBMAX, "Attempting to link in too many shared libraries" },     //
		{ ELIBEXEC, "Cannot exec a shared library directly" },     //
		{ EILSEQ, "Illegal byte sequence" },     //
		{ ERESTART, "Interrupted system call should be restarted" },     //
		{ ESTRPIPE, "Streams pipe error" },     //
		{ EUSERS, "Too many users" },     //
		{ ENOTSOCK, "Socket operation on non-socket" },     //
		{ EDESTADDRREQ, "Destination address required" },     //
		{ EMSGSIZE, "Message too long" },     //
		{ EPROTOTYPE, "Protocol wrong type for socket" },     //
		{ ENOPROTOOPT, "Protocol not available" },     //
		{ EPROTONOSUPPORT, "Protocol not supported" },     //
		{ ESOCKTNOSUPPORT, "Socket type not supported" },     //
		{ EOPNOTSUPP, "Operation not supported on transport endpoint" },     //
		{ EPFNOSUPPORT, "Protocol family not supported" },     //
		{ EAFNOSUPPORT, "Address family not supported by protocol" },     //
		{ EADDRINUSE, "Address already in use" },     //
		{ EADDRNOTAVAIL, "Cannot assign requested address" },     //
		{ ENETDOWN, "Network is down" },     //
		{ ENETUNREACH, "Network is unreachable" },     //
		{ ENETRESET, "Network dropped connection because of reset" },     //
		{ ECONNABORTED, "Software caused connection abort" },     //
		{ ECONNRESET, "Connection reset by peer" },     //
		{ ENOBUFS, "No buffer space available" },     //
		{ EISCONN, "Transport endpoint is already connected" },     //
		{ ENOTCONN, "Transport endpoint is not connected" },     //
		{ ESHUTDOWN, "Cannot send after transport endpoint shutdown" },     //
		{ ETOOMANYREFS, "Too many references: cannot splice" },     //
		{ ETIMEDOUT, "Connection timed out" },     //
		{ ECONNREFUSED, "Connection refused" },     //
		{ EHOSTDOWN, "Host is down" },     //
		{ EHOSTUNREACH, "No route to host" },     //
		{ EALREADY, "Operation already in progress" },     //
		{ EINPROGRESS, "Operation now in progress" },     //
		{ ESTALE, "Stale NFS file handle" },     //
		{ EUCLEAN, "Structure needs cleaning" },     //
		{ ENOTNAM, "Not a XENIX named type file" },     //
		{ ENAVAIL, "No XENIX semaphores available" },     //
		{ EISNAM, "Is a named type file" },     //
		{ EREMOTEIO, "Remote I/O error" },     //
		{ EDQUOT, "Quota exceeded" },     //
		{ ENOMEDIUM, "No medium found" },     //
		{ EMEDIUMTYPE, "Wrong medium type" },     //
		{ ECANCELED, "Operation Canceled" },     //
		{ ENOKEY, "Required key not available" },     //
		{ EKEYEXPIRED, "Key has expired" },     //
		{ EKEYREVOKED, "Key has been revoked" },     //
		{ EKEYREJECTED, "Key was rejected by service for robust mutexes" },     //
		{ EOWNERDEAD, "Owner died" },     //
		{ ENOTRECOVERABLE, "State not recoverable" },     //
		{ ERROR_BASE64_LEN, " len of base 64 is not valid" },    //
		{ ERROR_BASE64_CHAR, "invalid base 64 char" },    //
		{ ERROR_WRONG_PROTOCOL, "unreconize character on protocol" },    //
		{ ERROR_CRC, "CRC does not match" },    //
		{ ERROR_OVERWRITTEN, "old data has been overwritten. (share memory consumer design)" },    //
		{ ERROR_EOF, "End of file, socket, or fd No more data" },    //
		{ ERROR_INVALID_CHAR, "Char sequence invalid" },    //
		{ ERROR_WRONG_PARAM, "The function was called with a not valid argument" },    //
		{ ERROR_LOCKED, "The resource is locked, operationa can not complete" },    //
		{ ERROR_CALL_NOT_IMPLEMENTED, "This function is not implement" },
		/*
		 { ERFKILL, "Operation not possible due to RF-kill" },     //
		 { EHWPOISON, "Memory page has hardware error" },     //
		 */
		{ 0xFF, "unknown" } };

os::_error_tbl* os::api_tbl_last = os::api_tbl + sizeof(os::api_tbl) / sizeof(*os::api_tbl);

