
/*
	Todos los .h deben incluir este fichero
*/

#ifdef G3D_EXPORTS
#define G3D_API __declspec(dllexport)
#else
#define G3D_API __declspec(dllimport)
#endif

#define INITGUID
#include <windows.h>

