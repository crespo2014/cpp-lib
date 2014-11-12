
/*
	Todos los .h deben incluir este fichero
*/

#ifdef SIG_EXPORTS
#define SIG_API __declspec(dllexport)
#else
#define SIG_API __declspec(dllimport)
#endif

#include <windows.h>

