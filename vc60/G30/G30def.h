#if !defined(G30DEF_FILE)
#define G30DEF_FILE


#ifdef G30_EXPORTS
#define G30_API __declspec(dllexport)
#else
#define G30_API __declspec(dllimport)
#endif

#include <ddraw.h>
#include <d3d.h>

typedef struct
{
	int a;
} DEFINICIONES;

typedef struct
{
	WORD	v1,v2,v3;
} S_DXFACE;



G30_API DWORD G30Initialize(HINSTANCE hInst);

// Mensajes para la comunicacion con hilos
#define UM_THREAD_CLOSE WM_APP+1
#define UM_THREAD_INIT	WM_APP+2
#define UM_THREAD_LAST	WM_APP+3

// Mensajes usados por la aplicacion del juego
#define UM_GAME_START	UM_THREAD_LAST+1
#define UM_GAME_STOP	UM_THREAD_LAST+2
#define UM_INIT_OPENGL	UM_THREAD_LAST+3   //Crear todo lo relacionado con las OpenGL
#define UM_RENDER		UM_THREAD_LAST+4
#define UM_GAME_END		UM_THREAD_LAST+5

// Errores obtenidos
#define ERR_NONE			0				//No hay error

#define ERR_FIRST			2
#define ERR_NO_DD			ERR_FIRST+1 // No se creo el DirectDraw
#define ERR_NO_DDS			ERR_FIRST+2	// No se creo la DirectDrawSurface
#define ERR_NO_CL			ERR_FIRST+3	// Cooperative Level
#define ERR_NO_DM			ERR_FIRST+4	// Display Mode
#define ERR_NO_D3DI			ERR_FIRST+5	// No se obtuvo la interfaz D3D
#define ERR_NO_D3DDEVICE	ERR_FIRST+6	// Direct 3D Device
#define ERR_NO_VIEWPORT		ERR_FIRST+7	
#define ERR_NO_ZBUFFER		ERR_FIRST+8


#endif