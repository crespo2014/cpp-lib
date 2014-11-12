// Paciente.cpp: implementation of the CPaciente class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Paciente.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "app.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//CApp* pAppt;

CPaciente::CPaciente()
{

	nueva_sesion = false;
	paciente_cargado = false;
	pAppt = NULL;
	pRs_parametros_sesion = NULL;
    pRs_nueva_sesion = NULL;
	contador_condiciones = 1;
}

CPaciente::~CPaciente()
{
    /*if (nueva_sesion == true)
	{
		AbortarSesion();
		
		if (((CApp*)pAppt)->pDatos != NULL)
		{
		    for (int i=0; i< ((CApp*)pAppt)->pParam->m_Duracion_Cond; i++)
			delete ((CApp*)pAppt)->pDatos[i];
		
		    delete[] ((CApp*)pAppt)->pDatos;
		    ((CApp*)pAppt)->pDatos = NULL;   
		}
		
		if(((CApp*)pAppt)->pParam != NULL)
		{
		  delete ((CApp*)pAppt)->pParam;
		  ((CApp*)pAppt)->pParam = NULL;
		}
	}
	*/
	delete pRs_parametros_sesion;
    delete pRs_nueva_sesion;
}

bool CPaciente::SetAppPointer(void *pApp)
{

	if (pApp)
	{
	  pAppt = (CApp*)pApp;
	  pRs_parametros_sesion = new CDaoRecordset(&(((CApp*)pAppt)->database));
      pRs_nueva_sesion = new CDaoRecordset(&(((CApp*)pAppt)->database)); 
	  return true;
	}
	
	return false;
}

bool CPaciente::GetParametros(parametros *pParam)
{
    if (!nueva_sesion)
	{
	AfxMessageBox("No configurated session");
	return false;
	}
	
	COleVariant Valor;

	try
	{
	
		pRs_parametros_sesion->SetAbsolutePosition(contador_condiciones-1);

		if (pRs_parametros_sesion->IsBOF() && pRs_parametros_sesion->IsEOF())
		{
		   AfxMessageBox("Condition not valid");
	       return false;
		}
		
		Valor.vt= VT_I4;
        pRs_parametros_sesion->GetFieldValue("Duracion_Condicion", Valor);
        pParam->m_Duracion_Cond = Valor.lVal;
		cantidad_minutos = Valor.lVal;
		
		pRs_parametros_sesion->GetFieldValue("Criterio_Comparacion_Burst", Valor);
		pParam->m_Crit_Comp_Burst = Valor.lVal;
		
		pRs_parametros_sesion->GetFieldValue("Tiempo_Conteo_Burst", Valor);
		pParam->m_Tiempo_Conteo_Burst = Valor.lVal;
		
		pRs_parametros_sesion->GetFieldValue("Temperatura", Valor);
		pParam->m_Temperatura = Valor.lVal;
		
		pRs_parametros_sesion->GetFieldValue("Bf_Inhibicion_Eeg", Valor);
		pParam->m_Bf_I_Eeg = Valor.lVal;
		
		pRs_parametros_sesion->GetFieldValue("Af_Inhibicion_Eeg", Valor);
		pParam->m_Af_I_Eeg = Valor.lVal;
		
		pRs_parametros_sesion->GetFieldValue("Bf_Reward_Eeg", Valor);
		pParam->m_Bf_R_Eeg = Valor.lVal;
		
		pRs_parametros_sesion->GetFieldValue("Af_Reward_Eeg", Valor);
		pParam->m_Af_R_Eeg = Valor.lVal;

		pRs_parametros_sesion->GetFieldValue("Af_Musculo", Valor);
		pParam->m_Af_Musculo = Valor.lVal;

		pRs_parametros_sesion->GetFieldValue("Codigo_Condicion", Valor);
		codigo_condicion = Valor.lVal;
		
		Valor.vt =  VT_R8;
		pRs_parametros_sesion->GetFieldValue("Nivel_Inhibicion_Eeg", Valor);
		pParam->m_Nivel_I_Eeg = Valor.dblVal;
		
		pRs_parametros_sesion->GetFieldValue("Nivel_Reward_Eeg", Valor);
		pParam->m_Nivel_R_Eeg = Valor.dblVal;
		
		pRs_parametros_sesion->GetFieldValue("Nivel_Inhibicion_Musculo", Valor);
		pParam->m_Nivel_I_Musculo = Valor.dblVal;

	}
	catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	}
	
	return true;
}

bool CPaciente::AlmacenarDatos(datos **pDatos)
{
    CDaoRecordset *pR = new CDaoRecordset(&(((CApp*)pAppt)->database));
    CString query, temp1, temp2;
	COleVariant Valor;

	try
	{
	    temp1.Format("%d", codigo_sesion);
		temp2.Format("%d", contador_condiciones);
        query = "SELECT Minutos.* FROM Condiciones INNER JOIN Minutos ON Condiciones.Codigo_Condicion = Minutos.Codigo_Condicion WHERE (((Condiciones.Codigo_Sesion)="+temp1+") AND ((Condiciones.No_Condicion)="+temp2+"))";
    
		((CApp*)pAppt)->AbreAdicionar(pR, query);

		for (long i=0; i < cantidad_minutos; i++)
		{
		
		pR->AddNew();
		
		Valor.vt= VT_I4;
		
		Valor.lVal = pDatos[i]->minuto;
	    pR->SetFieldValue("No_Minuto", Valor);

        Valor.lVal = pDatos[i]->puntos;
	    pR->SetFieldValue("Cantidad_Puntos_Minutos", Valor);

		Valor.lVal = codigo_condicion;
        pR->SetFieldValue("Codigo_Condicion", Valor);

        Valor.vt =  VT_R8;
		
		Valor.dblVal = pDatos[i]->prom_ieeg_min;
		pR->SetFieldValue("Promedio_Ieeg_Minuto", Valor);

        Valor.dblVal = pDatos[i]->prom_iemg_min;
		pR->SetFieldValue("Promedio_Iemg_Minuto", Valor);

        Valor.dblVal = pDatos[i]->prom_reeg_min;
		pR->SetFieldValue("Promedio_Reeg_Minuto", Valor);

        Valor.dblVal = pDatos[i]->prom_temp_min;
		pR->SetFieldValue("Promedio_Temperatura_Minuto", Valor);

		
		pR->Update();

		}
		
		if (contador_condiciones == cantidad_condiciones)
		{
			FinalizarSesion();
			AfxMessageBox("All data has been saved to disk \n Session end ");

			pR->Close();

				for (int i=0; i< ((CApp*)pAppt)->pParam->m_Duracion_Cond; i++)
	            delete ((CApp*)pAppt)->pDatos[i];
	            
				delete[] ((CApp*)pAppt)->pDatos;
                ((CApp*)pAppt)->pDatos = NULL;   

  	            delete ((CApp*)pAppt)->pParam;
				((CApp*)pAppt)->pParam = NULL;
	        
			delete pR;
			return true;
		}
			contador_condiciones++;

	}
    catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	pR->Close();

		for (int i=0; i< ((CApp*)pAppt)->pParam->m_Duracion_Cond; i++)
	    delete ((CApp*)pAppt)->pDatos[i];
	    delete[] ((CApp*)pAppt)->pDatos;
		((CApp*)pAppt)->pDatos = NULL;   

  	    delete ((CApp*)pAppt)->pParam;
		((CApp*)pAppt)->pParam = NULL;
	
	delete pR;
	return false;
	}
	
	pR->Close();
	delete pR;

	for (int i=0; i< ((CApp*)pAppt)->pParam->m_Duracion_Cond; i++)
	delete ((CApp*)pAppt)->pDatos[i];
	delete[] ((CApp*)pAppt)->pDatos;
	((CApp*)pAppt)->pDatos = NULL;   

  	delete ((CApp*)pAppt)->pParam;
	((CApp*)pAppt)->pParam = NULL;

	return true;
}

bool CPaciente::AbortarSesion()
{
 
	if (nueva_sesion == false)
		return false;

	if (AfxMessageBox("Abort training session will cause completely lost of data OK?", MB_YESNO|MB_ICONSTOP) != IDYES)
		return false;
    
	contador_condiciones = 1;
	nueva_sesion = false;
	COleVariant Valor;
	
	CString query, temp;
	CDaoRecordset *pR = new CDaoRecordset(&(((CApp*)pAppt)->database));
	
	try
    {
	   pRs_nueva_sesion->Close();
	   pRs_parametros_sesion->Close();
	   //aqui borrar la sesion y decrementar la cantidad de sesiones para el paciente!!!!!
       temp.Format("%d", codigo_sesion);
	   query = "SELECT Sesiones.* FROM Sesiones WHERE (((Sesiones.Codigo_Sesion)="+temp+"))";
       ((CApp*)pAppt)->AbreActualizar(pR, query);
	   pR->Delete();

	    temp.Format("%d", numero);
		query = "SELECT Paciente.Total_Sesiones FROM Paciente WHERE (((Paciente.No_Paciente)="+temp+"))";
		pR->Close();
		((CApp*)pAppt)->AbreActualizar(pR, query); 
				
		pR->GetFieldValue("Total_Sesiones", Valor);
		long total;
		total = Valor.lVal;
		total--;
		Valor.vt = VT_I4;
		Valor.lVal = total;
		pR->Edit();
		pR->SetFieldValue("Total_Sesiones", Valor);
		pR->Update();
	   

    }
    catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	pR->Close();
	delete pR;
	return false;
	}
	
    pR->Close();
	delete pR; 
	return true;
}

bool CPaciente::FinalizarSesion()
{
    
	contador_condiciones = 1;
	nueva_sesion = false;
	
	pRs_nueva_sesion->Close();
	pRs_parametros_sesion->Close();
     
	return true;
}

bool CPaciente::AbortarCondicion()
{
     //no salvar la condicion que se realizo 
	if ((nueva_sesion == true) && (((CApp*)pAppt)->pParam))
		AfxMessageBox("No condition saved");
	return true;
}

void CPaciente::RefrescarStatusBar()
{
   CString show;
   /*En estas variables se setea desde la ventana CViewBuscarPacientes el id y el nombre
   del paciente cargado en el sistema*/
   show.Format("Neurofb  ID: %d Patient: %s",numero,nombre);
   /*toma el puntero a la ventana principal*/
   AfxGetApp()->m_pMainWnd->SetWindowText(show);
}
