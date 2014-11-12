#if !defined(AFX_ERRORCODES_H__8A25A337_736D_448E_9A46_B3DD966441BF__INCLUDED_)
#define AFX_ERRORCODES_H__8A25A337_736D_448E_9A46_B3DD966441BF__INCLUDED_

typedef struct {} ERROR_CODES;

#define INVALID_HANDLE	(DWORD)-1	//0xFFFFFFFF
#define INVALID_INDEX	(DWORD)-1	//0xFFFFFFFF

// Estados de los comandos
#define ERR_NONE			0	// No hay error
#define ERR_PENDING			1	// la operacion esta pendiente
#define ERR_INVANSWER		3	// La respuesta llego con problemas ver error extendido
#define ERR_APIFAIL			4	// Una funcion de la API retorno un codigo de error
#define ERR_FAIL			5	// Error interno no explicable, ver error extendido
#define ERR_NODATA			6	// No hay datos nuevos disponibles
#define ERR_UNKNOWN			7	// Error desconocido o estado desconocido
#define ERR_INVCMD			8	// El comando solicitado es invalido
#define ERR_INV_FUNC		8	// La funcion solicitada es invalida o no esta implementada
#define ERR_CLOSE			9	// El dispositivo solicitado esta cerrado
#define ERR_NOINTERFACE		10	// La interfaz no esta disponible o no se puede crear 
#define ERR_OUT_RANGE		11	// Argumento fuera de rango
#define ERR_NOMEMORY		12	// No se pudo solicitar memoria
#define ERR_EOT				13	// No hay mas informacion end of target
#define ERR_INVARG			14	// Argumento invalido, se paso un parametro no valido
#define ERR_OLEDBFAIL		15	// Una funcion de una interfaz oledb devolvio un codigo de error
#define ERR_OPEN			16	// El dispositivo se encuentra abierto debe cerrarse
#define ERR_NORESOURCE		17	// No se encuentra disponible un recurso
#define ERR_INV_HANDLE		18	// Puntero o handle invalido
#define ERR_NO_INITIALIZE	19	// La interfaz no ha sido inicializada
#define ERR_NO_FILE			20  // Fichero no encontrado
#define ERR_NOTFOUND		21	// No se encontro el elemento solicitado
#define ERR_INVALID_ID		22	// Identificador no valido (db o CATALOGOS)
#define ERR_INVALID_INDEX	23	// Indice invalido
#define ERR_INV_ARG			24	// Argumento o parametro invalido
#define ERR_TIMEOUT			25	// Tiempo de espera agotado

#define ERX_NONE			100	// No hay error extendido
#define ERX_INVBED			101	// Numero de cama invalido
#define ERX_INV_BED_ORDER	102	// Llevo un numero de cama fuera de lugar
#define ERX_INV_PARAM_CANT	103	// Mas de X parametros
#define ERX_INV_NEXTMIN		104	// Proximo minuto sin haber llegado todos los parametros
#define ERX_INV_MINUT_CANT	105	// Mas de 15 minutos
#define ERX_INV_EOT			106	// EOT fuera de lugar
#define ERX_INV_CTRL_BYTE	107	// Byte de control no esperado en este comando
#define ERX_COMM_BREAK		108	// Ruptura de comunicación
#define ERX_INVBUSY_FRAME	109	// Busy fuera de lugar o sin terminar
#define ERX_NOANSWER		110	// No hay respuesta desde el dispositivo externo
#define ERX_MUCH_DATA 		111	// LLegaron mas bytes de datos de los debidos

#endif 