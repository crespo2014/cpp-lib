
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

