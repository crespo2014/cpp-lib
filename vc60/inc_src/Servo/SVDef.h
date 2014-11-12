// SVDef.h: interface for the SVDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVDEF_H__B1459AE8_B24A_4470_8B54_7AA41F04D410__INCLUDED_)
#define AFX_SVDEF_H__B1459AE8_B24A_4470_8B54_7AA41F04D410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_IUnknown.h"

typedef struct {} SERVOVENTILATOR_DEFINES;

#define SV_NONE					0
#define SV_CHECKCONNECTION		1	// Chequeo de coneccion
#define SV_CHECKVERSION			2	// Chequeo de version
#define SV_SETTIME				3	// Poner timer del servo
#define SV_ALARMSTATUS			4	// Leer estado de las alarmas
#define SV_READCURVES			5	// Leer curvas
#define SV_READPARAMS			6	// Leer parametros puntuales
#define SV_READTRENDS			7	// Leer promedio de parametros puntuales
#define SV_READBATERY			8	// Leer voltaje de la bateria
#define SV_READADDRESS			9	// Leer direccion del equipo
#define SV_DEFINECURVE			10	// Setea los canales de los puntules
#define SV_DEFINEBREATH			11	// Setea los canales de las curvas

#define SV_CRV_FLOW				1	// Canal de flujo
#define SV_CRV_PRESSURE_E		2	// Canal de presion de espiracion
#define SV_CRV_PRESSURE_I		3	// Canal de presion de inspiracion

#define SV_PRM_INSPTIDALVOL		1	//
#define SV_PRM_EXPTIDALVOL		2	//
#define SV_PRM_O2CONCENTRATION	3	//
#define SV_PRM_BAROPRESSURE		4	//
#define SV_PRM_AUXCODE			5	//
#define SV_PRM_PAUSEPRESSURE	6	//
#define SV_PRM_EXPMINUTEVOL		7	//
#define SV_PRM_MEANAIRWAYPRESS	8	//
#define SV_PRM_ENDEXPRESSURE	9	//


// Estructura utilizada cuando se leen curva
struct SV_CRV
{
	DWORD	id;				// Canal de curva
	DWORD	Count;			// Cantidad de datos validos que contiene el buffer
	float	Samples[600];	// Buffer de datos
};

// Tipo de estrcutura utilizada cuando se leen los parametros puntuales
struct SV_PRM
{
	DWORD	id;
	float	fValue;
};

// Tipo de estructura utilizada cuando se leen promedio de parametros puntuales
struct SV_TREND
{
	DWORD	id;
	DWORD	dwDataCount;	// Cantidad de datos validos que contiene el buffer
	float*	lpBuffer;		// Buffer de datos
};

typedef struct 
{
	float volt;		// mV
}SV_BATERY;

struct SV_PP
{
	//DWORD	dwSize;
	DWORD	channel;
	float	fValue;
};

// Tipos de datos que se pueden leer
#define DATA_TYP_INV		-1	// Tipo invalido
#define DATA_TYP_CRV		1	// Curvas
#define DATA_TYP_PUN		2	// Parametros puntuales
#define DATA_TYP_PPUN		3	// Promedio parametros puntuales

class IServo : public _IUnknown
{
public:
	virtual DWORD _stdcall RequestCommand(DWORD CommandID,LPVOID lpCmdData) = 0;
	virtual DWORD _stdcall GetCommandExtError(DWORD CommandID) = 0;
	virtual DWORD _stdcall InitializeDevice() = 0;
};

#endif // !defined(AFX_SVDEF_H__B1459AE8_B24A_4470_8B54_7AA41F04D410__INCLUDED_)
