// App.cpp: implementation of the CApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "App.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "entradasistema.h"
#include "viewtraining.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CApp::CApp()
{

	medico.SetAppPointer(this);
	paciente.SetAppPointer(this);
	senales.SetApp(this);
	m_3dgame.SetApp(this);
	m_device.SetApp(this);
	pDatos=NULL;
	pParam=NULL;
	senales.Wnd.SetSignalDevice(&m_device);
    
	try
	{
	database.Open( bd_root + "\\bd\\neurofb.mdb");
	}
	catch(CDaoException* e)
	{
	  AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	  e->Delete();
	}
}

CApp::~CApp()
{

	if (pDatos != NULL)
	{
	  for (int i=0; i< pParam->m_Duracion_Cond; i++)
	  delete pDatos[i];
	  delete[] pDatos;
	  pDatos = NULL;   
    }
  	
	if(pParam != NULL)
	{
	  delete pParam;
	  pParam = NULL;
	}
	
	database.Close();
}

bool CApp::EntrarSistema()
{
    CEntradaSistema ent;
	bool result = false;

	do
	{
	  if (ent.DoModal() == IDCANCEL)
	  { 
	      medico.SetExistMedico(false);	  
		  return false;
	  }
	     medico.SetExistMedico(true);
		 result = true;
	}
	while(!medico.ChequearPassword(ent.m_Password));

	return result;
}

bool CApp::ChangePassword()
{
   CChangePass pass;

   if ((pass.DoModal() != IDOK) || !(pass.CheckData()))
   {
       return false;
   }

   FILE* f;
   
   f = fopen (bd_root+ "\\data.inf", "w");

    if (f == NULL)
	{
	  AfxMessageBox("System error, please reinstall the system");
	  return false;
	}

   fprintf(f,"%s", (LPCSTR) pass.m_new_pass);
   fclose (f);
   AfxMessageBox("Password changed successfully");
   
   return true;
}



bool CApp::Training()
{

	CViewTraining training;

	training.SetApp(this);
	training.DoModal();

	return true;

}
