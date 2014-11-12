// Medico.h: interface for the CMedico class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDICO_H__A6527B82_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_MEDICO_H__A6527B82_BFBB_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "neurofbdlldef.h"

class NEUROFBDLL_API CMedico
//class AFX_EXT_CLASS CMedico
{
public:
	bool BuscaPaciente();
	bool RegistrarPaciente();
	bool ImportarPaciente();
	bool ExportarPaciente(long id);
	bool EliminarPaciente(long valor);
	bool ActualizarPaciente(long id);
	bool MostrarReportes();
	int task;
	bool ConfigurarSesion();
	void* pAppt;
	bool SetAppPointer(void *pApp);
	bool MostrarDatos();
	bool ChequearPassword(CString password);
	void SetExistMedico(bool value);
	bool ExistMedico();
	CMedico();
	virtual ~CMedico();

private:
	bool exist_medico;
};

#endif // !defined(AFX_MEDICO_H__A6527B82_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
