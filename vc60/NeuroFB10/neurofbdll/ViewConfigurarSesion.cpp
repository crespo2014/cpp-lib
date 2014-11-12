// ViewConfigurarSesion.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "ViewConfigurarSesion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "app.h"
#include "viewcondicion.h"


#define CANT_COND_DEFAULT 10

/////////////////////////////////////////////////////////////////////////////
// CViewConfigurarSesion dialog
void *pMyApp;

CViewConfigurarSesion::CViewConfigurarSesion(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_CONFIGURARSESION", pParent)
{
	//{{AFX_DATA_INIT(CViewConfigurarSesion)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CViewConfigurarSesion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewConfigurarSesion)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewConfigurarSesion, CDialog)
	//{{AFX_MSG_MAP(CViewConfigurarSesion)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewConfigurarSesion message handlers

bool CViewConfigurarSesion::Mostrar(void *pApp)
{
	
	pMyApp = (CApp*) pApp;
	COleVariant Valor;
	
	if (DoModal() == IDOK) 
	{
		((CApp*)pMyApp)->paciente.nueva_sesion = true;	
		return true;
	}
	else
	{
		//SI SE DA CANCEL HAY QUE BORRAR DE LA BASE DE DATOS TODO LO QUE SE COPIO!!!!
		//SI ES NUEVA SESION SINO NO HACER NADA
		//TAMBIEN CERRAR LOS RECORDSETS DE PACIENTE
		int tarea;
		tarea = ((CApp*)pMyApp)->medico.task;
		
		if(tarea == NUEVASESION)
		{
			//borrar la sesion adicionada y descontar una sesion de la tabla paciente
			CDaoRecordset* pR = new CDaoRecordset(&(((CApp*)pMyApp)->database)); 
			try
			{
				
				((CApp*)pMyApp)->paciente.pRs_nueva_sesion->Close();
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->Close();
				
				CString query, temp;
				temp.Format("%d", ((CApp*)pMyApp)->paciente.codigo_sesion);
				query = "SELECT Sesiones.* FROM Sesiones WHERE (((Sesiones.Codigo_Sesion)="+temp+"))";
				((CApp*)pMyApp)->AbreActualizar(pR, query);
				pR->Delete();
				pR->Close();
				
				//aqui se decrementa la cantidad de sesiones al paciente
				temp.Format("%d", ((CApp*)pMyApp)->paciente.numero);
				query = "SELECT Paciente.Total_Sesiones FROM Paciente WHERE (((Paciente.No_Paciente)="+temp+"))";
				((CApp*)pMyApp)->AbreActualizar(pR, query); 
				
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
			}
		
			    pR->Close();
				delete pR;
		}

		return false;
	}
	
}

void CViewConfigurarSesion::OnDestroy() 
{
	CDialog::OnDestroy();
	COleVariant Valor;
	    
	try
		{
	    ((CApp*)pMyApp)->paciente.pRs_nueva_sesion->MoveFirst();
		((CApp*)pMyApp)->paciente.pRs_nueva_sesion->Edit();
	       
		   Valor.vt= VT_I4;
		   Valor.lVal = ((CApp*)pMyApp)->paciente.cantidad_condiciones;
		   ((CApp*)pMyApp)->paciente.pRs_nueva_sesion->SetFieldValue("No_Total_Condiciones", Valor);
	    
		((CApp*)pMyApp)->paciente.pRs_nueva_sesion->Update();
		}
		catch(CDaoException *e)
		{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
		}
}

BOOL CViewConfigurarSesion::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString query, temp;
	COleVariant Valor;
	long Codigo_Sesion;
	
	CButton* pB = (CButton*) GetDlgItem(IDC_UPDATE);
	pB->EnableWindow(false);
		
	CDaoRecordset* pR = new CDaoRecordset(&(((CApp*)pMyApp)->database));
	CMSFlexGrid* pGrid = (CMSFlexGrid*)GetDlgItem(IDC_REJILLA);
    
	
	//AQUI SI ES UNA NUEVA SESION HAY QUE LLENAR EL GRID CON 
	//PARAMETROS POR DEFAULT SINO CARGARLOS DEL RECORDSET
	
	if (((CApp*)pMyApp)->paciente.nueva_sesion == false) //es nueva sesion
	{
		
		//buscar la cantidadad de sesiones que tiene el paciente 
		//para agregarle una y escribirla de nuevo en la BD
		temp.Format("%d", ((CApp*)pMyApp)->paciente.numero);
		query = "SELECT Paciente.Total_Sesiones FROM Paciente WHERE (((Paciente.No_Paciente)="+temp+"))";
		
		try
		{
			if (!(((CApp*)pMyApp)->AbreActualizar(pR, query)))
			{
				pR->Close();
				delete pR;
				return false;
			}
			
			 //aqui se busca en la tabla de paciente la cantidad de sesiones, se le adiciona 1
			 //y se vuelve a guardar en el mismo lugar y se guarda en paciente.cantidad_sesiones
			 pR->GetFieldValue("Total_Sesiones", Valor);
			 ((CApp*)pMyApp)->paciente.cantidad_sesiones = Valor.lVal+1;
             pR->Edit();
			 Valor.lVal = ((CApp*)pMyApp)->paciente.cantidad_sesiones;
             pR->SetFieldValue("Total_Sesiones", Valor);
             pR->Update();  

            //aqui se abre el recordset paciente.pRs_nueva_sesion para agregar una nueva sesion
            //a la tabla de sesiones, se coge el codigo de la nueva sesion y se guarda en 
			//paciente.codigo_sesion
			query = "SELECT Sesiones.* FROM Sesiones WHERE (((Sesiones.No_Paciente)="+temp+"))";
            
			((CApp*)pMyApp)->AbreAdicionar(((CApp*)pMyApp)->paciente.pRs_nueva_sesion, query);
			
            ((CApp*)pMyApp)->paciente.pRs_nueva_sesion->AddNew();
			
			//Coger el codigo de la nueva sesion para agregar las condiciones
            ((CApp*)pMyApp)->paciente.pRs_nueva_sesion->GetFieldValue("Codigo_Sesion", Valor);
            Codigo_Sesion = Valor.lVal;
			
			Valor.vt= VT_I4;
				//aqui se guarda en la tabla de sesion el numero de paciente, el numero de la
			    //sesion y el numero total de condiciones
				Valor.lVal = ((CApp*)pMyApp)->paciente.numero;
				((CApp*)pMyApp)->paciente.pRs_nueva_sesion->SetFieldValue("No_Paciente", Valor);

				Valor.lVal = ((CApp*)pMyApp)->paciente.cantidad_sesiones;
				((CApp*)pMyApp)->paciente.pRs_nueva_sesion->SetFieldValue("No_Sesion", Valor);

				Valor.lVal = CANT_COND_DEFAULT;
				((CApp*)pMyApp)->paciente.pRs_nueva_sesion->SetFieldValue("No_Total_Condiciones", Valor);

				COleDateTime fecha;
				fecha = COleDateTime::GetCurrentTime();
				((CApp*)pMyApp)->paciente.pRs_nueva_sesion->SetFieldValue("Fecha", fecha);
			
			
			((CApp*)pMyApp)->paciente.pRs_nueva_sesion->Update();
			
			//aqui se abrre el recordset paciente.pRs_parametros_sesion para guardar 
			//los parametros de las condiciones en la tabla condiciones
			
			((CApp*)pMyApp)->paciente.codigo_sesion = Codigo_Sesion;
			temp.Format("%d", Codigo_Sesion);
			query = "SELECT Condiciones.Codigo_Sesion, Condiciones.No_Condicion, Condiciones.Duracion_Condicion, Condiciones.Nivel_Inhibicion_Musculo, Condiciones.Nivel_Inhibicion_Eeg, Condiciones.Nivel_Reward_Eeg, Condiciones.Criterio_Comparacion_Burst, Condiciones.Tiempo_Conteo_Burst, Condiciones.Temperatura, Condiciones.Bf_Inhibicion_Eeg, Condiciones.Af_Inhibicion_Eeg, Condiciones.Bf_Reward_Eeg, Condiciones.Af_Reward_Eeg, Condiciones.Af_Musculo, Condiciones.Codigo_Condicion FROM Condiciones WHERE (((Condiciones.Codigo_Sesion)="+temp+"))";
            
			((CApp*)pMyApp)->AbreActualizar(((CApp*)pMyApp)->paciente.pRs_parametros_sesion, query);
			
			
			for (long i=0; i< CANT_COND_DEFAULT; i++)
			{
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->AddNew();
                
				Valor.vt= VT_I4;
				
				Valor.lVal = Codigo_Sesion;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Codigo_Sesion", Valor);

				Valor.lVal = i+1;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("No_Condicion", Valor);

				Valor.lVal = 5;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Duracion_Condicion", Valor);
				
				Valor.lVal = 20;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Criterio_Comparacion_Burst", Valor);
				
				Valor.lVal= 10;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Tiempo_Conteo_Burst", Valor);
				
				Valor.lVal = 30;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Temperatura", Valor);
				
				Valor.lVal = 4;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Bf_Inhibicion_Eeg", Valor);
				
				Valor.lVal = 7;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Af_Inhibicion_Eeg", Valor);
				
				Valor.lVal = 15;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Bf_Reward_Eeg", Valor);
				
				Valor.lVal = 18;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Af_Reward_Eeg", Valor);
				
				Valor.lVal = 22;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Af_Musculo", Valor);

				
				Valor.vt =  VT_R8;
				Valor.dblVal = 12;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Nivel_Inhibicion_Eeg", Valor);
				
				Valor.dblVal = 4;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Nivel_Reward_Eeg", Valor);
				
				Valor.dblVal = 16;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Nivel_Inhibicion_Musculo", Valor);
				
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->Update();
				((CApp*)pMyApp)->paciente.cantidad_condiciones = CANT_COND_DEFAULT;
				
			}
			
		    //aqui se muestran los valores en el grid
			CString No_Mostrar[2];
			No_Mostrar[0] = "Codigo_Sesion";
			No_Mostrar[1] = "Codigo_Condicion";
			if (((CApp*)pMyApp)->ShowRecordGrid(pGrid, ((CApp*)pMyApp)->paciente.pRs_parametros_sesion, this, No_Mostrar, 2))
			{
			   PonerNombres(pGrid);
               ((CApp*)pMyApp)->CalcSelSize(pGrid, this);
			}
		
		}
		catch(CDaoException *e)
		{
			AfxMessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
			pR->Close();
			delete pR;
			return false;
		}
		
	}
	else
	{
		try
		{
			CString No_Mostrar[2];
			No_Mostrar[0] = "Codigo_Sesion";
			No_Mostrar[1] = "Codigo_Condicion";

		if (((CApp*)pMyApp)->ShowRecordGrid(pGrid, ((CApp*)pMyApp)->paciente.pRs_parametros_sesion, this, No_Mostrar, 2))
			{
			   PonerNombres(pGrid);
               ((CApp*)pMyApp)->CalcSelSize(pGrid, this);
			}
		}
        catch(CDaoException *e)
		{
			AfxMessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
			return false;
		} 
	}
	
	pR->Close();
	delete pR;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

bool CViewConfigurarSesion::PonerNombres(CMSFlexGrid *pGrid)
{
        pGrid->SetCol(0);
		pGrid->SetRow(0);
		pGrid->SetText("Condition");

		pGrid->SetCol(1);
		pGrid->SetRow(0);
		pGrid->SetText("Length (min)");

		pGrid->SetCol(2);
		pGrid->SetRow(0);
		pGrid->SetText("SP Muscle Inhibit Level (µV)");

		pGrid->SetCol(3);
		pGrid->SetRow(0);
		pGrid->SetText("SP EEG Inhibit Level (µV)");

		pGrid->SetCol(4);
		pGrid->SetRow(0);
		pGrid->SetText("SP EEG Reward Level (µV)");

		pGrid->SetCol(5);
		pGrid->SetRow(0);
		pGrid->SetText("SP #Burst");

		pGrid->SetCol(6);
		pGrid->SetRow(0);
		pGrid->SetText("Burst Timing Count (sec)");

		pGrid->SetCol(7);
		pGrid->SetRow(0);
		pGrid->SetText("SP Temperature");

		pGrid->SetCol(8);
		pGrid->SetRow(0);
		pGrid->SetText("SP Inhibit Low Frequency (Hz)");

		pGrid->SetCol(9);
		pGrid->SetRow(0);
		pGrid->SetText("SP Inhibit High Frequency (Hz)");

		pGrid->SetCol(10);
		pGrid->SetRow(0);
		pGrid->SetText("SP Reward Low Frequency (Hz)");

		pGrid->SetCol(11);
		pGrid->SetRow(0);
		pGrid->SetText("SP Reward High Frequency (Hz)");

		pGrid->SetCol(12);
		pGrid->SetRow(0);
		pGrid->SetText("SP Muscle High Frequency (Hz)");
		
		return false;
}

void CViewConfigurarSesion::OnAdd() 
{
	//AQUI MOSTRAR LA VENTANA CON LOS PARAMETROS POR DEFAULT
	//DEJAR QUE EL USUARIO MODIFIQUE Y AGREGAR LA CONDICION 
	//AL FINAL 
	CViewCondicion cond;
	COleVariant Valor;
    cond.GetAppPointer(pMyApp, ADICIONAR);
	
	CButton* pB = (CButton*) GetDlgItem(IDC_UPDATE);
	pB->EnableWindow(false);

	if (cond.DoModal() == IDOK)
	{
	
		        try
				{
		        
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->AddNew();
                
				//aqui se pasan los datos de la nueva condicion al recordset
				Valor.vt= VT_I4;
				Valor.lVal = ((CApp*)pMyApp)->paciente.codigo_sesion;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Codigo_Sesion", Valor);

				Valor.lVal = ((CApp*)pMyApp)->paciente.cantidad_condiciones+1;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("No_Condicion", Valor);

				Valor.lVal = cond.m_Duracion_Cond;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Duracion_Condicion", Valor);
				
				Valor.lVal = cond.m_Crit_Comp_Burst;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Criterio_Comparacion_Burst", Valor);
				
				Valor.lVal= cond.m_Tiempo_Conteo_Burst;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Tiempo_Conteo_Burst", Valor);
				
				Valor.lVal = cond.m_Temperatura;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Temperatura", Valor);
				
				Valor.lVal = cond.m_Bf_I_Eeg;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Bf_Inhibicion_Eeg", Valor);
				
				Valor.lVal = cond.m_Af_I_Eeg;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Af_Inhibicion_Eeg", Valor);
				
				Valor.lVal = cond.m_Bf_R_Eeg;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Bf_Reward_Eeg", Valor);
				
				Valor.lVal = cond.m_Af_R_Eeg;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Af_Reward_Eeg", Valor);
				
				Valor.lVal = 22;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Af_Musculo", Valor);
				
				Valor.vt =  VT_R8;
				Valor.dblVal = cond.m_Nivel_I_Eeg;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Nivel_Inhibicion_Eeg", Valor);
				
				Valor.dblVal = cond.m_Nivel_R_Eeg;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Nivel_Reward_Eeg", Valor);
				
				Valor.dblVal = cond.m_Nivel_I_Musculo;
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Nivel_Inhibicion_Musculo", Valor);
				
				((CApp*)pMyApp)->paciente.pRs_parametros_sesion->Update();
				
				
				//aqui se adiciona la condicion!!
				((CApp*)pMyApp)->paciente.cantidad_condiciones++;
				  
				RefrescarParametros();
				
				}
                catch(CDaoException *e)
				{
			      AfxMessageBox(e->m_pErrorInfo->m_strDescription);
			      e->Delete();
			    } 
	    }
}

void CViewConfigurarSesion::OnDelete() 
{
	//ELIMINAR ULTIMA CONDICION e ir a la tabla de sesiones y descontar una condicion
	if (AfxMessageBox("Delete last condition?", MB_YESNO|MB_ICONSTOP) != IDYES)
		return;

	CButton* pB = (CButton*) GetDlgItem(IDC_UPDATE);
	pB->EnableWindow(false);

	CString query, temp_codigo, temp_numero;
    CDaoRecordset *pR = new CDaoRecordset(&(((CApp*)pMyApp)->database));
    COleVariant Valor;

	temp_codigo.Format("%d", ((CApp*)pMyApp)->paciente.codigo_sesion);
	temp_numero.Format("%d", ((CApp*)pMyApp)->paciente.cantidad_condiciones);


	query = "SELECT Condiciones.* FROM Condiciones WHERE (((Condiciones.Codigo_Sesion)="+temp_codigo+") AND ((Condiciones.No_Condicion)="+temp_numero+"))";

	try
	{
	    if (((CApp*)pMyApp)->AbreActualizar( pR, query))
		{
		   pR->Delete();
		   ((CApp*)pMyApp)->paciente.cantidad_condiciones--;
		   pR->Close();
		}
	}
	catch(CDaoException *e)
	{
	   AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	   e->Delete();
	}
	RefrescarParametros();
	delete pR;
	pR = NULL;
}

void CViewConfigurarSesion::OnUpdate() 
{
	//ACTULIZAR LA CONDICION SELECCIONADA EN EL GRID Y SALVAR
	CViewCondicion cond;
    COleVariant Valor;
	
	CMSFlexGrid* pGrid = (CMSFlexGrid*)GetDlgItem(IDC_REJILLA);
	int index;
	
	index = pGrid->GetRowSel();
	
	if (index == 0)
	{
		AfxMessageBox ("No Condition selected");
		return;
	}
    try
	{
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->MoveFirst();
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->Move(index-1);
		cond.GetAppPointer(pMyApp, ACTUALIZAR);
		if (cond.DoModal() == IDOK)
		{
			
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->Edit();
			
			//aqui se pasan los datos hacia el recordset
			Valor.vt= VT_I4;
			//Valor.lVal = ((CApp*)pMyApp)->paciente.codigo_sesion;
			//((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Codigo_Sesion", Valor);
			
			//pGrid->SetRow(index);
			//pGrid->SetCol(1);
			//Valor.lVal = StrToInt(pGrid->GetText());
			//((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("No_Condicion", Valor);
			
			Valor.lVal = cond.m_Duracion_Cond;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Duracion_Condicion", Valor);
			
			Valor.lVal = cond.m_Crit_Comp_Burst;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Criterio_Comparacion_Burst", Valor);
			
			Valor.lVal= cond.m_Tiempo_Conteo_Burst;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Tiempo_Conteo_Burst", Valor);
			
			Valor.lVal = cond.m_Temperatura;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Temperatura", Valor);
			
			Valor.lVal = cond.m_Bf_I_Eeg;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Bf_Inhibicion_Eeg", Valor);
			
			Valor.lVal = cond.m_Af_I_Eeg;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Af_Inhibicion_Eeg", Valor);
			
			Valor.lVal = cond.m_Bf_R_Eeg;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Bf_Reward_Eeg", Valor);
			
			Valor.lVal = cond.m_Af_R_Eeg;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Af_Reward_Eeg", Valor);
			
			Valor.lVal = cond.m_Af_Musculo;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Af_Musculo", Valor);

			Valor.vt =  VT_R8;
			Valor.dblVal = cond.m_Nivel_I_Eeg;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Nivel_Inhibicion_Eeg", Valor);
			
			Valor.dblVal = cond.m_Nivel_R_Eeg;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Nivel_Reward_Eeg", Valor);
			
			Valor.dblVal = cond.m_Nivel_I_Musculo;
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->SetFieldValue("Nivel_Inhibicion_Musculo", Valor);
			
			((CApp*)pMyApp)->paciente.pRs_parametros_sesion->Update();
			
			
			RefrescarParametros();
			
			CButton* pB = (CButton*) GetDlgItem(IDC_UPDATE);
	        pB->EnableWindow(false);
			
		}
	}
	
	catch(CDaoException *e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}
	
}



bool CViewConfigurarSesion::RefrescarParametros()
{
  CMSFlexGrid* pGrid = (CMSFlexGrid*)GetDlgItem(IDC_REJILLA);
  
  try
  {
    ((CApp*)pMyApp)->paciente.pRs_parametros_sesion->Requery();
	//((CApp*)pMyApp)->CleanGrid(pGrid);
	CString No_Mostrar[2];
			No_Mostrar[0] = "Codigo_Sesion";
			No_Mostrar[1] = "Codigo_Condicion";
    
	((CApp*)pMyApp)->ShowRecordGrid(pGrid, ((CApp*)pMyApp)->paciente.pRs_parametros_sesion, this, No_Mostrar, 2);
	PonerNombres(pGrid);
    ((CApp*)pMyApp)->CalcSelSize(pGrid, this);
  
  }
  catch(CDaoException *e)
  {
	  AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	  e->Delete();
	  return false;
  } 
	
  return true;
}

BEGIN_EVENTSINK_MAP(CViewConfigurarSesion, CDialog)
    //{{AFX_EVENTSINK_MAP(CViewConfigurarSesion)
	ON_EVENT(CViewConfigurarSesion, IDC_REJILLA, -600 /* Click */, OnClickRejilla, VTS_NONE)
	ON_EVENT(CViewConfigurarSesion, IDC_REJILLA, -601 /* DblClick */, OnDblClickRejilla, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CViewConfigurarSesion::OnClickRejilla() 
{
	CButton* pB = (CButton*) GetDlgItem(IDC_UPDATE);
	pB->EnableWindow(true);
}

void CViewConfigurarSesion::OnDblClickRejilla() 
{
	OnUpdate();
}
