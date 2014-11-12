#if !defined(AFX_LISA2000DEF_H__A0CCFF77_9E9A_4D60_A870_AC1F8BCB237D__INCLUDED_)
#define AFX_LISA2000DEF_H__A0CCFF77_9E9A_4D60_A870_AC1F8BCB237D__INCLUDED_

#define MAX_ANALYSIS 24
#define MAX_POCI	 96

#define ANALYSIS_MAXLEN 15
#define UNIT_MAXLEN 10
#define POCI_MAXLEN 15

#define ERR_SUCCESS			0	// No hay error
#define ERR_NO_LIBRARY 		1	// No se encuentra la dll especificada
#define ERR_INV_LIBRARY		2	// La dll es invalida
#define ERR_INIT_FAILED		3	// No se pudo inicializar el driver (Falta de recursos en windows)
#define ERR_CONNECTING		4	// Estableciendo coneccion
#define ERR_CONNECT_FAILED	5	// No se pudo establecer una coneccion
#define ERR_GETING_RESULT	6	// Procesando los resultados
#define ERR_UNSUPORTED		7	// Funcion o capacidad no soportada
#define ERR_NODRIVE			8	// No se ha cargado ningun driver
#define ERR_NOPATIENT		9	// No se encuentra el paciente especificado
#define ERR_NOANALISYS		10	// El paciente no tiene realizado este tipo de analisis o el analisis no existe
#define ERR_MOREBUFFER		11	// Se necesita mas espacio para devolver la cadena
#define ERR_INVALIDDATA		12	// La solicitud de resultados tuvo problemas
#define ERR_UNKNOWN			13	// Error desconocido


typedef struct
{
	float	val;	// valor del analisis
	BYTE	reads;	// Numero de lectura
} ANA_STATUS;

typedef struct
{
	char name[POCI_MAXLEN];
	ANA_STATUS analysis[MAX_ANALYSIS];
} POCI_INFO;

typedef struct
{
	char name[ANALYSIS_MAXLEN];
	char measured_unit[UNIT_MAXLEN];
} ANALYSIS_INFO;


// Comados disponibles para la coneccion cliente servidor

#define CMD_NONE	0
#define CMD_ANAINFO	1	// Informacion acerca de los tipos de analisis
#define CMD_RESULTS 2	// Lectura de resultados



#endif // !defined(AFX_LISA2000RESULTFILTER_H__A0CCFF77_9E9A_4D60_A870_AC1F8BCB237D__INCLUDED_)