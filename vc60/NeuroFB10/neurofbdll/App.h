// App.h: interface for the CApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APP_H__FEC7B9BD_BFA8_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_APP_H__FEC7B9BD_BFA8_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataBaseAplication.h"
#include "medico.h"
#include "paciente.h"
#include "shlwapi.h" 
#include "changepass.h"
#include "..\lfc10\lfc10c03.h"
#include "viewsenales.h"
#include "..\g_01\g_01c06.h"

#define NUEVASESION 0
#define SESSIONSETTINGS 1

struct parametros
{
    long	m_Af_I_Eeg;    //filtro para IEEG
	long	m_Af_R_Eeg;
	long	m_Bf_I_Eeg;   //filtro para REEG
	long	m_Bf_R_Eeg;
	long    m_Af_Musculo;  //filtro de af para el musculo
	long	m_Crit_Comp_Burst;
	long	m_Duracion_Cond;
	double	m_Nivel_I_Eeg;
	double	m_Nivel_I_Musculo;
	double	m_Nivel_R_Eeg;
	long	m_Temperatura;
	long	m_Tiempo_Conteo_Burst;
};

struct datos
{
	long minuto;
	long puntos;
	double prom_ieeg_min;
	double prom_reeg_min;
	double prom_iemg_min;
	double prom_temp_min;
};

class CApp : public CDataBaseAplication  
{
public:
	bool Training();
	bool ChangePassword();
	CDaoDatabase database;
	bool EntrarSistema();
	CApp();
	virtual ~CApp();

	CMedico medico;
	CPaciente paciente;
	CSignalDevice	m_device;
	CViewSenales	senales;
	C3DViewGame		m_3dgame;
	struct parametros *pParam;
	struct datos** pDatos;

};

#endif // !defined(AFX_APP_H__FEC7B9BD_BFA8_11D4_9126_0000E83D722B__INCLUDED_)
