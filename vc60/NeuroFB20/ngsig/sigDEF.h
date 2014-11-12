#if !defined (LFC10DEF_H)
#define LFC10DEF_H

typedef struct
{
} DEFINICIONES;

// Mensajes enviados al hilo que atiende el dispositivo
#define UM_GET_BUFFER	UM_LAST+1
#define UM_WAIT_COMMAND	UM_LAST+2
#define UM_CLEAR_STATE	UM_LAST+3
#define UM_UPDATE		UM_LAST+5
#define UM_COMMAND		UM_LAST+6

// Valor de wparam para UM_UPDATE
#define SIGCANT		0
#define COEF		1
#define BUFFERLEN	2

// Valores de wParam para UM_COMMAND

/*
	Borrar todos los buffer de senales y la
	informacion de las mismas
*/
#define CLEAR_BUFFER	0

// Mensajes enviados a la ventana que grafica las senales
#define UM_DEVICE_STATE UM_LAST+12


// Estados del dispositivo de comunicacion serie
#define UKNOW_STATE 0
#define GETING_DATA 2
#define COMM_ERROR	4   // Error en funcion del puerto
#define LINE_ERROR  8	// Error en linea de comunicacion
#define PRESENT		16  // El dispositivo se encuentra activo
#define LOSS_DATA	32  // Se perdieron datos de los que recoje el hilo
#define BAD_DEVICE	0x40 // Se recibio una respuesta invalida

// Mensajes enviados al hilo que grafica las senales
#define ID_FONT_DLGBAR	1000
#define UM_CLOSETHREAD	WM_APP+0
#define	UM_PARAMCHANGE	WM_APP+1
#define UM_NULL			WM_APP+2

// Valor de LParam para el mensaje UM_PARAMCHANGE

#define NAME_CHANGE		2
#define VOLTPERDIV_CHANGE 3
#define FONT_CHANGE		5
#define SHOW_CHANGE		6
#define	SHOW_ALL_GRAPHICS 7
#define	GRAPHIC_STATE	8
#define NAME_CHANGE1	9
#define GM_RESIZE		10

// Separaciones que poseen los graficos
#define TOP_SPACE1	1
#define TOP_SPACE2	-1
#define LEFT_SPACE1 2
#define LEFT_SPACE2 1
#define RIGHT_SPACE1 1
#define BOTTOM_SPACE1 0

// Mensajes enviados por el hilo que atiende el puerto
#define UM_THREAD_CLOSE	WM_APP+0
#define UM_PORT_OPEN	WM_APP+1
#define UM_PORT_CLOSE   WM_APP+2
#define UM_THREAD_INIT	WM_APP+3
#define UM_LAST			WM_APP+20


/* 
	Estructuras
*/

typedef struct 
{
	DWORD pOrder;
	double *pCoefA,*pCoefB;
}S_COEF;


typedef struct
{
	char* Caption;
	DWORD Order;
	double *CoefA,*CoefB;
} S_FILTERDATA;
/*
	Contiene la cantidad y un puntero con los datos 
	de los filtros
*/
typedef struct
{
	DWORD Cant;
	S_FILTERDATA* Filters;
}S_SIGFILTERS;

/*
	Comunicacion serie
*/
#define MAXBYTESIZE 4
#define MAXPORTS 4
#define MAXBAUDRATE 15
#define MAXPARITY 5
#define MAXSTOPBITS 3


#endif