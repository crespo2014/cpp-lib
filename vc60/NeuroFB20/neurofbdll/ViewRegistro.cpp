// ViewRegistro.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "ViewRegistro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewRegistro dialog


CViewRegistro::CViewRegistro(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_REGISTRO", pParent)
{
	//{{AFX_DATA_INIT(CViewRegistro)
	m_Apellido_Paciente = _T("");
	m_Diagnostico = _T("");
	m_Direccion = _T("");
	m_Fecha_Nacimiento = COleDateTime::GetCurrentTime();
	m_Medicacion_Actual = _T("");
	m_No_Paciente = 0;
	m_Nombre_Paciente = _T("");
	m_Telefono = _T("");
	//}}AFX_DATA_INIT
}


void CViewRegistro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewRegistro)
	DDX_Text(pDX, Apellido_Paciente, m_Apellido_Paciente);
	DDX_Text(pDX, Diagnostico, m_Diagnostico);
	DDX_Text(pDX, Direccion, m_Direccion);
	DDX_Text(pDX, Fecha_Nacimiento, m_Fecha_Nacimiento);
	DDX_Text(pDX, Medicacion_Actual, m_Medicacion_Actual);
	DDX_Text(pDX, No_Paciente, m_No_Paciente);
	DDX_Text(pDX, Nombre_Paciente, m_Nombre_Paciente);
	DDX_Text(pDX, Telefono, m_Telefono);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewRegistro, CDialog)
	//{{AFX_MSG_MAP(CViewRegistro)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewRegistro message handlers

bool CViewRegistro::Mostrar()
{
   bool out=1;
   do
   {
    if(DoModal()==IDOK)
    {
     if(ChekData())
	 {
	  /*todo OK*/
      out=1;
      return true;
	 }
	 /*faltaron campos por llenar*/
	 else out=0;
    }
	/*se dió cancel*/
	else out=1;
   }while(!out);
    return false;

}

bool CViewRegistro::ChekData()
{
	bool result=false;
    
	if ( m_Nombre_Paciente.IsEmpty()
		|| m_Apellido_Paciente.IsEmpty() 
		|| m_Telefono.IsEmpty() || m_Direccion.IsEmpty() || m_Diagnostico.IsEmpty()
		||m_Medicacion_Actual.IsEmpty())
	{
	  AfxMessageBox("Information is not complete");
	}
	
	else
      result = true;

	return result;  
}
