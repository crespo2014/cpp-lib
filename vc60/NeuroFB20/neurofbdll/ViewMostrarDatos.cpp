// ViewMostrarDatos.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "ViewMostrarDatos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "app.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CViewMostrarDatos dialog



CViewMostrarDatos::CViewMostrarDatos(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_MOSTRARDATOS", pParent)
{
	//{{AFX_DATA_INIT(CViewMostrarDatos)
	m_Af_I_Eeg = 0;
	m_Af_R_Eeg = 0;
	m_Bf_I_Eeg = 0;
	m_Bf_R_Eeg = 0;
	m_Crit_Comp_Burst = 0;
	m_Duracion_Cond = 0;
	m_Nivel_I_Eeg = 0.0;
	m_Nivel_I_Musculo = 0.0;
	m_Nivel_R_Eeg = 0.0;
	m_Fecha_Sesion = COleDateTime::GetCurrentTime();
	m_Reporte_Sesion = _T("");
	m_Temperatura = 0;
	m_Tiempo_Conteo_Burst = 0;
	m_Af_Muscle = 0;
	//}}AFX_DATA_INIT

	cantidad_condiciones_por_sesion = NULL;
	pRc = NULL;
	pRm = NULL;
	pRs = NULL;
}


void CViewMostrarDatos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewMostrarDatos)
	DDX_Control(pDX, IDC_TREEPACIENTE, m_tree_paciente);
	DDX_Text(pDX, IDC_EDITAFINHIBICIONEEG, m_Af_I_Eeg);
	DDX_Text(pDX, IDC_EDITAFREWARDEEG, m_Af_R_Eeg);
	DDX_Text(pDX, IDC_EDITBFINHIBICIONEEG, m_Bf_I_Eeg);
	DDX_Text(pDX, IDC_EDITBFREWARDEEG, m_Bf_R_Eeg);
	DDX_Text(pDX, IDC_EDITCRITERIOCOMPARACIONBURST, m_Crit_Comp_Burst);
	DDX_Text(pDX, IDC_EDITDURACIONCONDICION, m_Duracion_Cond);
	DDX_Text(pDX, IDC_EDITNIVELINHIBICIONEEG, m_Nivel_I_Eeg);
	DDX_Text(pDX, IDC_EDITNIVELINHIBICIONMUSCULO, m_Nivel_I_Musculo);
	DDX_Text(pDX, IDC_EDITNIVELREWARDEEG, m_Nivel_R_Eeg);
	DDX_Text(pDX, IDC_EDITSESSIONDATE, m_Fecha_Sesion);
	DDX_Text(pDX, IDC_EDITSESSIONREPORT, m_Reporte_Sesion);
	DDX_Text(pDX, IDC_EDITTEMPERATURA, m_Temperatura);
	DDX_Text(pDX, IDC_EDITTIEMPOCONTEOBURST, m_Tiempo_Conteo_Burst);
	DDX_Text(pDX, IDC_EDITAFMUSCLEFREG, m_Af_Muscle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewMostrarDatos, CDialog)
	//{{AFX_MSG_MAP(CViewMostrarDatos)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewMostrarDatos message handlers

bool CViewMostrarDatos::Mostrar(void *pApp)
{
    pAppt = pApp;
	DoModal();
	return true;
}

BOOL CViewMostrarDatos::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDITAFINHIBICIONEEG);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITAFREWARDEEG);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITAFMUSCLEFREG);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITBFINHIBICIONEEG);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITBFREWARDEEG);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITCRITERIOCOMPARACIONBURST);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITDURACIONCONDICION);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITNIVELINHIBICIONEEG);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITNIVELINHIBICIONMUSCULO);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITNIVELREWARDEEG);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITSESSIONDATE);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITSESSIONREPORT);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITTEMPERATURA);
	pEdit->SendMessage(EM_SETREADONLY,true,0);

	pEdit = (CEdit*)GetDlgItem(IDC_EDITTIEMPOCONTEOBURST);
	pEdit->SendMessage(EM_SETREADONLY,true,0);
	
	//AQUI HACE FALTA PINTAR EL TREE CON LOS DATOS DEL PACIENTE CARGADO
	//PARA ESTO BUSCAR PARA UN PACIENTE LA CANTIDAD DE SESIONES Y LA CANTIDAD
	//DE CONDICIONES

    CString query, temp, str_no_sesion;
	COleVariant Valor;
	CDaoRecordset *pR;
	pR = NULL;

	try
	{
	  pR = new CDaoRecordset(&(((CApp*)pAppt)->database));
	  pRc = new CDaoRecordset(&(((CApp*)pAppt)->database));
	  pRm = new CDaoRecordset(&(((CApp*)pAppt)->database));
	  pRs = new CDaoRecordset(&(((CApp*)pAppt)->database));
	}
	catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	delete pR;
	
	delete pRc;
	delete pRm;
	delete pRs;
	pRc = NULL;
	pRm = NULL;
	pRs = NULL;

	return false;
	}
	
    temp.Format("%d", ((CApp*)pAppt)->paciente.numero);
    query = "SELECT Paciente.Total_Sesiones FROM Paciente WHERE (((Paciente.No_Paciente)="+temp+"))";
    
	try
	{
    ((CApp*)pAppt)->AbreLeer(pR, query);

	pR->GetFieldValue("Total_Sesiones", Valor);
    cantidad_sesiones = Valor.lVal; //aqui se toma la cantidad de sesiones del 
	                                //paciente seleccionado
    pR->Close();
    
	cantidad_condiciones_por_sesion = new long[cantidad_sesiones+1];
    //aqui se va a buscar para cada sesion la cantidad de condiciones    
	    for (long i=1; i<= cantidad_sesiones; i++)
		{
		  str_no_sesion.Format("%d", i);
	      query = "SELECT Sesiones.No_Total_Condiciones FROM Sesiones WHERE (((Sesiones.No_Paciente)="+temp+") AND ((Sesiones.No_Sesion)="+str_no_sesion+"))";
	      
		  if (!((CApp*)pAppt)->AbreLeer(pR, query))
          {
			  AfxMessageBox("Session table empty");
              pR->Close();
			  delete pR;
	          return false;
		  }
		  pR->GetFieldValue("No_Total_Condiciones", Valor);
		  cantidad_condiciones_por_sesion[i] = Valor.lVal;

		  pR->Close();
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
    
	//Aqui pintar el tree con los datos obtenidos

	m_tree_paciente.PintarTree(cantidad_sesiones, cantidad_condiciones_por_sesion, pAppt, this);
	
	delete pR;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewMostrarDatos::OnDestroy() 
{
	CDialog::OnDestroy();
	
    delete cantidad_condiciones_por_sesion;

  	delete pRs;
	delete pRc;
	delete pRm;
}

bool CViewMostrarDatos::RefrescarDatos(long sesion, long condicion)
{

	CString query;
	COleVariant Valor;
    CString str_sesion, str_condicion, str_numero_paciente;

	if ((sesion <= 0) && (condicion <= 0))
		return false;

    str_sesion.Format("%d", sesion);
	str_condicion.Format("%d", condicion);
	str_numero_paciente.Format("%d", ((CApp*)pAppt)->paciente.numero);

     try
	{
    query = "SELECT Sesiones.Reporte, Sesiones.Fecha FROM Sesiones WHERE (((Sesiones.No_Paciente)="+str_numero_paciente+") AND ((Sesiones.No_Sesion)="+str_sesion+"))";

	((CApp*)pAppt)->AbreLeer(pRs, query);

	pRs->GetFieldValue("Reporte", Valor);
    m_Reporte_Sesion = (LPCSTR) Valor.bstrVal;
	
    m_Fecha_Sesion = pRs->GetFieldValue("Fecha");

	pRs->Close();
    
	query = "SELECT Condiciones.* FROM Sesiones INNER JOIN Condiciones ON Sesiones.Codigo_Sesion = Condiciones.Codigo_Sesion WHERE (((Sesiones.No_Paciente)="+str_numero_paciente+") AND ((Sesiones.No_Sesion)="+str_sesion+") AND ((Condiciones.No_Condicion)="+str_condicion+"))";

	((CApp*)pAppt)->AbreLeer(pRc, query);

    Valor.vt= VT_I4;
    pRc->GetFieldValue("Duracion_Condicion", Valor);
    m_Duracion_Cond = Valor.lVal;

    pRc->GetFieldValue("Criterio_Comparacion_Burst", Valor);
    m_Crit_Comp_Burst = Valor.lVal;

	pRc->GetFieldValue("Tiempo_Conteo_Burst", Valor);
    m_Tiempo_Conteo_Burst = Valor.lVal;

	pRc->GetFieldValue("Temperatura", Valor);
    m_Temperatura = Valor.lVal;

	pRc->GetFieldValue("Bf_Inhibicion_Eeg", Valor);
    m_Bf_I_Eeg = Valor.lVal;

	pRc->GetFieldValue("Af_Inhibicion_Eeg", Valor);
    m_Af_I_Eeg = Valor.lVal;

	pRc->GetFieldValue("Bf_Reward_Eeg", Valor);
    m_Bf_R_Eeg = Valor.lVal;

	pRc->GetFieldValue("Af_Reward_Eeg", Valor);
    m_Af_R_Eeg = Valor.lVal;

	pRc->GetFieldValue("Af_Musculo", Valor);
    m_Af_Muscle = Valor.lVal;

    Valor.vt =  VT_R8;
    pRc->GetFieldValue("Nivel_Inhibicion_Eeg", Valor);
    m_Nivel_I_Eeg = Valor.dblVal;

	pRc->GetFieldValue("Nivel_Reward_Eeg", Valor);
    m_Nivel_R_Eeg = Valor.dblVal;

	pRc->GetFieldValue("Nivel_Inhibicion_Musculo", Valor);
    m_Nivel_I_Musculo = Valor.dblVal;
	
    pRc->Close();

    query = "SELECT Minutos.No_Minuto, Minutos.Cantidad_Puntos_Minutos, Minutos.Promedio_Ieeg_Minuto, Minutos.Promedio_Reeg_Minuto, Minutos.Promedio_Iemg_Minuto, Minutos.Promedio_Temperatura_Minuto FROM Sesiones INNER JOIN (Condiciones INNER JOIN Minutos ON Condiciones.Codigo_Condicion = Minutos.Codigo_Condicion) ON Sesiones.Codigo_Sesion = Condiciones.Codigo_Sesion WHERE (((Sesiones.No_Paciente)="+str_numero_paciente+") AND ((Sesiones.No_Sesion)="+str_sesion+") AND ((Condiciones.No_Condicion)="+str_condicion+"))";

	CMSFlexGrid* pGrid = (CMSFlexGrid*)GetDlgItem(IDC_GRIDMINUTOS);
	
	if (((CApp*)pAppt)->AbreLeer(pRm, query))
	{
		((CApp*)pAppt)->ShowRecordGrid(pGrid, pRm, this);
	    
		pGrid->SetCol(0);
		pGrid->SetRow(0);
		pGrid->SetText("Minute");
		
		pGrid->SetCol(1);
		pGrid->SetRow(0);
		pGrid->SetText("Points");

		pGrid->SetCol(2);
		pGrid->SetRow(0);
		pGrid->SetText("IEEG Avg");

		pGrid->SetCol(3);
		pGrid->SetRow(0);
		pGrid->SetText("REEG Avg");

		pGrid->SetCol(4);
		pGrid->SetRow(0);
		pGrid->SetText("IEMG Avg");

		pGrid->SetCol(5);
		pGrid->SetRow(0);
		pGrid->SetText("Temperature Avg");

		((CApp*)pAppt)->CalcSelSize(pGrid, this);
	}
	
	pRm->Close();
	
	UpdateData(FALSE);
	}
    catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
    pRs->Close();
    pRc->Close();
    pRm->Close(); 
	return false;
	}   

	return true;
}
