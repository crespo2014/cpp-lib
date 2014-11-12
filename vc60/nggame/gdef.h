#if !defined (G_01_ESTRUCTURAS)
#define G_01_ESTRUCTURAS


#include <windows.h>
#include <math.h>
#include <gl\glu.h>
#include <gl\gl.h>
#include <stdio.h>
#include <ddraw.h>
#include <d3d.h>

typedef struct
{
	float x,y,z;
} S_3DSPOINT;

typedef struct 
{
	float	r,g,b;
}S_3DSCOLOR;

typedef struct
{
	DWORD	v1,v2,v3;
} S_3DSFACE;


typedef struct
{
	double x1,y1,z1,x2,y2,z2;
} S_3DSIZE;
/*
	esta estructura es la primera que aparece en el fichero
*/
typedef struct
{
	DWORD		m_size;		// Cantidad de bytes que ocupa toda la informacion de la clase
	DWORD		m_version;	// Size of the structure	
	char		m_name[21];	// Mesh name 
	DWORD		m_index;	// Mesh index
	WORD		m_nvertex;	// Vertex cant
	WORD		m_nfaces;	// faces cant
	WORD		m_nmat;		// cantidad de materiales
} S_3DMESH;

// Errores que pueden devolver las funciones de la clase C3DViewGame

#define G_OK				0	//No hay error
#define GERR_FIRST			1
#define GERR_BACKDC			GERR_FIRST+1	//No se pudo crear el DC trasero
#define GERR_BACKBMP		GERR_FIRST+2	//No se pudo crear el bitmap del buffer trasero
#define GERR_BACKDCBMP		GERR_FIRST+3	//No se pudo seleccionar el bitmap en el dc trasero
#define GERR_BACKDCPF		GERR_FIRST+4	//No se pudo poner el formato de pixel en el back DC 
#define GERR_BACKRC			GERR_FIRST+5	//No se pudo crear el Render Context
#define GERR_BACKRCCURRENT	GERR_FIRST+6	//RC is not current to the DC
#define GERR_WND			GERR_FIRST+7	//No se pudo crear la ventana de juego
#define GERR_DD				GERR_FIRST+8	//No se pudo crear el Objeto DirectDraw
#define GERR_DDS			GERR_FIRST+9	//No se pudo crear la superficie DirectDraw
#define GERR_DDCL			GERR_FIRST+10	//No se pudo poner el nivel de cooperacion
#define GERR_DDDM			GERR_FIRST+11	//No se pudo poner el modo de display
#define GERR_DDFDC			GERR_FIRST+12	//No se pudo obtener un DC frontal
#define GERR_DDFS			GERR_FIRST+13	//No se pudo crear la superficie DD

// Errores que pueden devolver las funciones de la clase C3DViewGame

#define ERR_NONE			0				//No hay error
#define ERR_FIRST			1
#define ERR_NOPF			ERR_FIRST+1		//No PixelFormat
#define ERR_NORC			ERR_FIRST+2		//No Render Context
#define ERR_NOCRC			ERR_FIRST+3		//No Current Render Context
#define ERR_NOWND			ERR_FIRST+4		//

#define ERR_NO_DD			ERR_FIRST+1 // No se creo el DirectDraw
#define ERR_NO_DDS			ERR_FIRST+2	// No se creo la DirectDrawSurface
#define ERR_NO_CL			ERR_FIRST+3	// Cooperative Level
#define ERR_NO_DM			ERR_FIRST+4	// Display Mode
#define ERR_NO_D3DI			ERR_FIRST+5	// No se obtuvo la interfaz D3D
#define ERR_NO_D3DDEVICE	ERR_FIRST+6
#define ERR_NO_VIEWPORT		ERR_FIRST+7


#define ERR_NORESOURCE		ERR_FIRST+1
#define ERR_NOHGLOBAL		ERR_FIRST+2
#define ERR_NOLPPOINTER		ERR_FIRST+2
#define ERR_INVALID_FILE	ERR_FIRST+3

// mensajes usados por el hilo de juego




#endif 