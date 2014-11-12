// cconsole.cpp: implementation of the cconsole class.
//
//////////////////////////////////////////////////////////////////////

#include "cconsole.h"		// incluir la definicion de la clase para luego implementarla

#ifdef WIN32

#include "w32\cconsole.cpp"

#else

#include "linux\cconsole.cpp"

#endif


