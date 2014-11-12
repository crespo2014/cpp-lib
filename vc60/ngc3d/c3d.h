
/*
	Todos los .h deben incluir este fichero
*/

#ifdef C3D_EXPORTS
#define C3D_API __declspec(dllexport)
#else
#define C3D_API __declspec(dllimport)
#endif

#include <windows.h>

