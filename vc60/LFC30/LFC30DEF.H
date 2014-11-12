#if !defined (LFC30DEF_FILE)
#define	LFC30DEF_FILE

#ifdef LFC30_EXPORTS
#define LFC30_API __declspec(dllexport)
#else
#define LFC30_API __declspec(dllimport)
#endif

typedef struct 
{

}LFC30_DEFINICIONES;

#define CLASS_NAME "WIND_CLASS"
// Nombre de la ventana registrada
#define	SHARE_MAXLEN 20
// maxima cantidad de caracteres 
// que posee el nombre de los objetos compartidos


extern LFC30_API int nLFC30;

extern HINSTANCE	hProg;

LFC30_API int fnLFC30(void);


//LFC30_API DWORD RegisterCWindClass();
//LRESULT CALLBACK WindProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);

LFC30_API DWORD LFC30Initialize(HINSTANCE hInst);
// Registra la ventana

LFC30_API DWORD LFC30GetString(char* lpString,DWORD index);
// Devuelve una cadena unica en cada llamada

typedef LRESULT (*LPWINDPROC)	(void* lpthis,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
/*
	Prototipo de funcion statica utilizada para el windproc de la ventana
*/

/*
	Comunicacion entre hilos
*/
typedef struct
{
	LPARAM	lParam;
	WPARAM	wParam;
	UINT	Msg;
	LPVOID	ExtraData;
	DWORD	Result;
} S_MESSAGE;

#endif