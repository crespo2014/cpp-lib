

#include "csocket.h"

#ifdef WIN32

#include "w32\csocket.cpp"

#else

#include "linux\csocket.cpp"

#endif


