// ViewBuscarPaciente.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "ViewBuscarPaciente.h"
#include "app.h"
#include "msflexgrid.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewBuscarPaciente dialog


CViewBuscarPaciente::CViewBuscarPaciente(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_BUSCARPACIENTE", pParent)
{
	//{{AFX_DATA_INIT(CViewBuscarPaciente)
	m_opcion = -1;
	m_id = 0;
	m_name = _T("");
	//}}AFX_DATA_INIT
	/*Inicialización de la estructura message*/
	paciente_data.valor=0;
}


void CViewBuscarPaciente::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewBuscarPaciente)
	DDX_Radio(pDX, IDC_TODOS, m_opcion);
	DDX_Text(pDX, IDC_ID, m_id);
	DDX_Text(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewBuscarPaciente, CDialog)
	//{{AFX_MSG_MAP(CViewBuscarPaciente)
	ON_BN_CLICKED(IDC_BUSCAR_PACIENTE, OnBuscarPaciente)
	ON_BN_CLICKED(IDC_BORRA_PACIENTE, OnBorraPaciente)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CARGA_PACIENTE, OnCargaPaciente)
	ON_BN_CLICKED(IDC_ACTUALIZAR_PACIENTE, OnActualizarPaciente)
	ON_BN_CLICKED(IDC_EXPORTA_PACIENTE, OnExportaPaciente)
	ON_BN_CLICKED(IDC_IMPORTA_PACIENTE, OnImportaPaciente)
	ON_BN_CLICKED(IDC_TODOS, OnTodos)
	ON_BN_CLICKED(IDC_NOMBRE, OnNombre)
	ON_BN_CLICKED(IDC_BUSCA_TODOS, OnBuscaTodos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewBuscarPaciente message handlers



bool CViewBuscarPaciente::Mostrar(void* pApp)
{
	bool out = 0;
	pAppt=pApp;
	/*El recordset pRefresh se usará para refrescar en el grid los cambios hechos */
	try
	{
		/*Reservando memoria para el recordset a usar en esta clase*/
		pRs=new CDaoRecordset(&(((CApp*)pAppt)->database));
		
	}
	catch(CDaoException *e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}
	
	do
	{
		DoModal();    /*muestra la ventana */
		if (((CApp*)pAppt)->paciente.paciente_cargado == false)
		{
			if (AfxMessageBox("No patient loaded, try again?",MB_YESNO|MB_ICONSTOP) == IDYES)
			{
				out=0;
			    
				try
				{
				   //preparando el nuevo recordset
                   pRs=new CDaoRecordset(&(((CApp*)pAppt)->database));
				}
				catch(CDaoException *e)
				{
		          AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		          e->Delete();
				}
			}
				else
				out =1;
		}
		else
			out = 1;
	}
	
	while (!out);
	
	return true;
}

void CViewBuscarPaciente::OnBuscarPaciente() 
{
    CString temp, query;
    UpdateData (true);
    
	CMSFlexGrid* pFg=(CMSFlexGrid*)GetDlgItem(IDC_MSFLEXGRID1);


    if ( m_opcion == 0)
	{
		pRs->Close(); /*antes de abrir el recordset(no se puede volver a abrir uno abierto)*/
		((CApp*)pAppt)->CleanGrid(pFg); /*borra lo que aparece en el flex grid*/
		/*Seleccion de búsqueda por ID*/
		temp="SELECT * FROM Paciente WHERE (((Paciente.No_Paciente)=";
		query.Format("%s%d));",temp,m_id);
		//acceso a la base de datos
       ((CApp*)pAppt)->AbreLeer(pRs,query);
		((CApp*)pAppt)->ShowRecordGrid(pFg,pRs,this);
		/*el recordset queda abierto para cualquier opción que implique refrescamiento*/

	}
	
	if ( m_opcion == 1)
	{
		pRs->Close();/*antes de abrir el recordset(no se puede volver a abrir uno abierto)*/	
		((CApp*)pAppt)->CleanGrid(pFg); /*borra lo que aparece en el flex grid*/
		/*Seleccion de Búsqueda por Nombre*/
		temp="SELECT * FROM Paciente WHERE (((Paciente.Nombre_Paciente)=";
		query.Format("%s\"%s\"));",temp,m_name);
		//acceso a la base de datos
       ((CApp*)pAppt)->AbreLeer(pRs,query);
		((CApp*)pAppt)->ShowRecordGrid(pFg,pRs,this);
		/*el recordset queda abierto para cualquier opción que implique refrescamiento*/
       			
	}
	
	if ( m_opcion == 2)
	{
		pRs->Close();/*antes de abrir el recordset(no se puede volver a abrir uno abierto)*/
		((CApp*)pAppt)->CleanGrid(pFg); /*borra lo que aparece en el flex grid*/
		/*Mostrarlos a todos*/
	   	temp="SELECT * FROM Paciente";
		query.Format("%s;",temp);
		//acceso a la base de datos
		((CApp*)pAppt)->AbreLeer(pRs,query);
		((CApp*)pAppt)->ShowRecordGrid(pFg,pRs,this);
		/*el recordset queda abierto para cualquier opción que implique refrescamiento*/
	}
	
	/*mostrando el encabezamiento del grid*/
	pFg->SetCol(0);
	pFg->SetRow(0);
	pFg->SetText("ID");
	pFg->SetCol(1);
	pFg->SetRow(0);
	pFg->SetText("First Name");
	pFg->SetCol(2);
	pFg->SetRow(0);
	pFg->SetText("Last Name");
	pFg->SetCol(3);
	pFg->SetRow(0);
	pFg->SetText("Birth Date");
	pFg->SetCol(4);
	pFg->SetRow(0);
	pFg->SetText("Phone");
	pFg->SetCol(5);
	pFg->SetRow(0);
	pFg->SetText("Address");
	pFg->SetCol(6);
	pFg->SetRow(0);
	pFg->SetText("Diagnosis");
	pFg->SetCol(7);
	pFg->SetRow(0);
	pFg->SetText("Actual Medication");
    pFg->SetCol(8);
	pFg->SetRow(0);
	pFg->SetText("Sessions");
	
	((CApp*)pAppt)->CalcSelSize(pFg, this); 
	
	/*se inhabilitan las opciones a hacer con un paciente*/
	CDialog::OnInitDialog();
	CButton* pB=(CButton*)GetDlgItem(IDC_CARGA_PACIENTE);
	pB->EnableWindow(false);
	pB=(CButton*)GetDlgItem(IDC_IMPORTA_PACIENTE);
	pB->EnableWindow(false);
    pB=(CButton*)GetDlgItem(IDC_EXPORTA_PACIENTE);
	pB->EnableWindow(false);
	pB=(CButton*)GetDlgItem(IDC_BORRA_PACIENTE);
	pB->EnableWindow(false);
	pB=(CButton*)GetDlgItem(IDC_ACTUALIZAR_PACIENTE);
	pB->EnableWindow(false);

	
}




void CViewBuscarPaciente::OnBorraPaciente() 
{
  /*Esta opcion elimina el paciente seleccionado mediante llamada al metodo Eliminar de la clase
	CMedico*/
  ((CApp*)pAppt)->medico.EliminarPaciente(paciente_data.valor);
  RefrescarPacientes();
  	
}

BEGIN_EVENTSINK_MAP(CViewBuscarPaciente, CDialog)
    //{{AFX_EVENTSINK_MAP(CViewBuscarPaciente)
	ON_EVENT(CViewBuscarPaciente, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CViewBuscarPaciente::OnClickMsflexgrid1() 
{
	//CDialog::OnInitDialog();
	/*Aqui se selecciona un paciente*/
	int row;
	CMSFlexGrid* pFg=(CMSFlexGrid*)GetDlgItem(IDC_MSFLEXGRID1);
	row = pFg->GetRowSel();
	
    CString buffer;
    
	pFg->SetCol(0);
	pFg->SetRow(row);
	buffer = pFg->GetText();
	sscanf(buffer.GetBuffer(10),"%d", &(paciente_data.valor));
	buffer.ReleaseBuffer();
	pFg->SetCol(1);
	pFg->SetRow(row);
	paciente_data.name= pFg->GetText();
	if(paciente_data.name=="") return;
    
	/*se habilitan los botones que permiten hacer operaciones con el paciente seleccionado*/
	CButton* pB=(CButton*)GetDlgItem(IDC_CARGA_PACIENTE);
	pB->EnableWindow(true);
	pB=(CButton*)GetDlgItem(IDC_IMPORTA_PACIENTE);
	pB->EnableWindow(true);
    pB=(CButton*)GetDlgItem(IDC_EXPORTA_PACIENTE);
	pB->EnableWindow(true);
	pB=(CButton*)GetDlgItem(IDC_BORRA_PACIENTE);
	pB->EnableWindow(true);
	pB=(CButton*)GetDlgItem(IDC_ACTUALIZAR_PACIENTE);
	pB->EnableWindow(true);

}

void CViewBuscarPaciente::OnDestroy() 
{
	CDialog::OnDestroy();
	

	/*Termino con el recordset pRs usado para mostrar los cambios hechos en el grid*/
	pRs->Close();
	delete pRs;
	pRs=NULL;
	
}

void CViewBuscarPaciente::RefrescarPacientes()
{

	CString query,temp;
	
	CMSFlexGrid* pFg = (CMSFlexGrid*)GetDlgItem(IDC_MSFLEXGRID1); /*Apunta al flex grid*/
	((CApp*)pAppt)->CleanGrid(pFg); /*borra lo que aparece en el flex grid*/
	try
	{
     if(m_opcion==0||m_opcion==2)
	 pRs->Requery(); /*ejecuta el último query que se ha hecho al recordset */
	 else
	 {
		 //caso en que la búsqueda realizada fue por nombre.
		 pRs->Close();
		 /*query por id*/
		 ((CApp*)pAppt)->CleanGrid(pFg); /*borra lo que aparece en el flex grid*/
		 /*Seleccion de búsqueda por ID*/
		 temp="SELECT * FROM Paciente WHERE (((Paciente.No_Paciente)=";
		 query.Format("%s%d));",temp,paciente_data.valor);
		 //acceso a la base de datos
		 ((CApp*)pAppt)->AbreLeer(pRs,query);
		 ((CApp*)pAppt)->ShowRecordGrid(pFg,pRs,this);
		 /*el recordset queda abierto para cualquier opción que implique refrescamiento*/
	
	 }

	}
	catch(CDaoException *e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}
	/*muestra el grid*/
	((CApp*)pAppt)->ShowRecordGrid(pFg,pRs,this);
	
	
}

void CViewBuscarPaciente::OnCargaPaciente() 
{
	/*En esta opción se carga en el sistema el paciente seleccionado en el grid
	de modo que a partir de ese momento cada vez que se haga referencia a una sesión
	, condición etc. sea de ese paciente, cuando se vaya a la opción de mostrar 
	sesiones son las de ese paciente las que son mostradas */
	/*
	Este es el código definitivo
	((CApp*)pAppt)->paciente.numero=paciente_data.valor;
	((CApp*)pAppt)->paciente.nombre=paciente_data.name;
    ((CApp*)pAppt)->paciente.paciente_cargado = true;*/
    
	/*VERSION DEMO*/

	AfxMessageBox("Warning:\n Demo Version, only Patient with id=0 will be loaded");
    ((CApp*)pAppt)->paciente.numero=0;
	((CApp*)pAppt)->paciente.nombre=paciente_data.name;
    ((CApp*)pAppt)->paciente.paciente_cargado = true;
    
	//refrescar el status bar de la vista principal con el nombre de ese paciente	
	((CApp*)pAppt)->paciente.RefrescarStatusBar();
}

void CViewBuscarPaciente::OnActualizarPaciente() 
{
	
  /*El médico es quién actualiza los datos del paciente*/	
	if(((CApp*)pAppt)->medico.ActualizarPaciente(paciente_data.valor))
	/*Muestra en el grid los datos del paciente modificados*/
	RefrescarPacientes();
	
}

void CViewBuscarPaciente::OnExportaPaciente() 
{
	
         
        /*el medico es quien exporta al paciente al disco de 31/2*/
		
		((CApp*)pAppt)->medico.ExportarPaciente(paciente_data.valor);
				
    
}

void CViewBuscarPaciente::OnImportaPaciente() 
{
	/*el medico es quien importa al paciente del disco de 31/2*/
		
		((CApp*)pAppt)->medico.ImportarPaciente();
		RefrescarPacientes();		
}

BOOL CViewBuscarPaciente::OnInitDialog() 
{
	/*La ventana aparece con los botones y los edit inhabilitados*/
	CDialog::OnInitDialog();
	CButton* pB=(CButton*)GetDlgItem(IDC_CARGA_PACIENTE);
	pB->EnableWindow(false);
	pB=(CButton*)GetDlgItem(IDC_IMPORTA_PACIENTE);
	pB->EnableWindow(false);
    pB=(CButton*)GetDlgItem(IDC_EXPORTA_PACIENTE);
	pB->EnableWindow(false);
	pB=(CButton*)GetDlgItem(IDC_BORRA_PACIENTE);
	pB->EnableWindow(false);
	pB=(CButton*)GetDlgItem(IDC_ACTUALIZAR_PACIENTE);
	pB->EnableWindow(false);
	CEdit* pE=(CEdit*)GetDlgItem(IDC_ID);
	pE->EnableWindow(false);
    pE=(CEdit*)GetDlgItem(IDC_NAME);
	pE->EnableWindow(false);

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewBuscarPaciente::OnTodos() 
{

  
	  	/*habilita solo la caja de texto de entrar id*/	
		CEdit* pE=(CEdit*)GetDlgItem(IDC_ID);
		pE->EnableWindow(true);
		pE=(CEdit*)GetDlgItem(IDC_NAME);
		pE->EnableWindow(false);

}

void CViewBuscarPaciente::OnNombre() 
{
        /*habilita solo la caja de texto de entrar nombre*/	
		CEdit* pE=(CEdit*)GetDlgItem(IDC_ID);
		pE->EnableWindow(false);
		pE=(CEdit*)GetDlgItem(IDC_NAME);
		pE->EnableWindow(true);	
}

void CViewBuscarPaciente::OnBuscaTodos() 
{
	    /*no se habilita ninguna caja de texto*/	
		CEdit* pE=(CEdit*)GetDlgItem(IDC_ID);
		pE->EnableWindow(false);
		pE=(CEdit*)GetDlgItem(IDC_NAME);
		pE->EnableWindow(false);
	
}
