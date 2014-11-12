// Paciente.h: interface for the CPaciente class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACIENTE_H__A6527B81_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_PACIENTE_H__A6527B81_BFBB_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class  CPaciente  
{
public:
	long codigo_condicion;
	void RefrescarStatusBar();
	bool AbortarCondicion();
	bool FinalizarSesion();
	bool AbortarSesion();
	bool AlmacenarDatos(struct datos **pDatos);
	bool GetParametros(struct parametros *pParam);
	long codigo_sesion;
	long cantidad_condiciones;
	long cantidad_sesiones;
	CDaoRecordset* pRs_parametros_sesion;
    CDaoRecordset* pRs_nueva_sesion;
	void* pAppt;
	bool SetAppPointer(void* pApp);
	bool paciente_cargado;
	bool nueva_sesion;
	long numero;
	CString nombre;
	CPaciente();
	virtual ~CPaciente();

private:
	long cantidad_minutos;
	long contador_condiciones;
};

#endif // !defined(AFX_PACIENTE_H__A6527B81_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
