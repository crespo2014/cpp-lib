// Medico.cpp: implementation of the CMedico class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Medico.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "viewmostrardatos.h"
#include "viewconfigurarsesion.h"
#include "viewallreports.h"
#include "app.h"


#include "viewregistro.h"
#include "viewbuscarpaciente.h"
#include "filemanage.h"
#define DEMO 1000
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CApp *pAppt;

CMedico::CMedico()
{
    pAppt = NULL;
	exist_medico = false;

}

CMedico::~CMedico()
{

}

bool CMedico::ExistMedico()
{

	return exist_medico;
}

void CMedico::SetExistMedico(bool value)
{
	exist_medico = value;

}

bool CMedico::ChequearPassword(CString password)
{
    bool result = false;
    CString pass;
	FILE* f;
   
    f = fopen (((CApp*)pAppt)->bd_root+ "\\data.inf", "r");
    if (f == NULL)
	{
	  AfxMessageBox("System error, please reinstall the system");
	  return false;
	}
	fscanf(f,"%s", pass);
    fclose (f);

	if (password == pass)
		result = true;
	else
		AfxMessageBox("Password not valid!");

    return result;
}

bool CMedico::MostrarDatos()
{

	CViewMostrarDatos mostrar_datos;

	mostrar_datos.Mostrar(pAppt);
	return true;
}

bool CMedico::SetAppPointer(void *pApp)
{

	if (pApp)
	{
	  pAppt = pApp;
	  return true;
	}
	
	return false;
}

bool CMedico::ConfigurarSesion()
{

	CViewConfigurarSesion configurar;


	  if (configurar.Mostrar(pAppt))
		  return true;
		  //GUARDAR DATOS DE LA SESION DEL PACIENTE
		  //PARA USARLOS EN EL ENTRENAMIENTO
		  //UN RECORDSET CON LOS PARAMETROS DE CADA CONDICION
		  //EN LA CLASE PACIENTE

	return true;
}

bool CMedico::MostrarReportes()
{

	CString query, temp;
	COleVariant Valor;
	COleDateTime Fecha;

	CString texto, separador, retorno, header, date, numero, reporte;
	CDaoRecordset *pR = new CDaoRecordset(&(((CApp*)pAppt)->database));

	separador="____________________________________________" ;
	
	char ret[3];
	ret[0]= 13;
	ret[1]= 10;
	ret[2]=NULL;
	retorno=ret;
	
	temp.Format("%d", ((CApp*)pAppt)->paciente.numero);
	query = "SELECT Sesiones.* FROM Sesiones WHERE (((Sesiones.No_Paciente)="+temp+"))";

	try
	{
    
	if (!(((CApp*)pAppt)->AbreLeer(pR, query)))
	{
	  AfxMessageBox("There is no sessions");
	  pR->Close();
	  delete pR;
	  return false; 
	}

    do
	{
    
	pR->GetFieldValue("No_Sesion", Valor);
	numero.Format("%d", Valor.lVal);

	Fecha = pR->GetFieldValue("Fecha");
    date = "    Date: " + Fecha.Format(VAR_DATEVALUEONLY, LANG_USER_DEFAULT);

	pR->GetFieldValue("Reporte", Valor);
    if (Valor.vt == VT_NULL)
       reporte = " ";
	else
	   reporte = (LPCSTR) Valor.bstrVal;
    
	header = "Session: " + numero;
	texto +=header+" "+date+retorno+reporte+retorno+separador+retorno;

	pR->MoveNext();
	
	}
    while(!(pR->IsEOF()));
	
	CViewAllReports view;
	view.m_reporte = texto;
    view.DoModal();
	//aqui mostrar la ventana con el reporte

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
	return true;
}

bool CMedico::ActualizarPaciente(long id)
{
	bool result=false;
	bool out=true;
	COleVariant	valor;
	COleDateTime fecha;
	CDaoRecordset* pRs=new CDaoRecordset(&(((CApp*)pAppt)->database)) ;
	CString query, temp;
	CViewRegistro vr; /*ventana de actualizar los datos de un paciente*/
	
	/*Seleccion de búsqueda por ID*/
	temp="SELECT * FROM Paciente WHERE (((Paciente.No_Paciente)=";
	query.Format("%s%d));",temp,id);
	//acceso a la base de datos
	((CApp*)pAppt)->AbreLeer(pRs,query);
		
	/*Se muestra la ventana de actualización, con los datos por defecto del paciente 
	seleccionado*/
	vr.m_No_Paciente=id;
	valor = pRs->GetFieldValue("Nombre_Paciente");
	vr.m_Nombre_Paciente = (LPCSTR) valor.bstrVal;
	vr.m_Fecha_Nacimiento=pRs->GetFieldValue("Fecha_Nacimiento");
	valor = pRs->GetFieldValue("Apellido_Paciente");
	vr.m_Apellido_Paciente = (LPCSTR) valor.bstrVal;
	valor = pRs->GetFieldValue("Telefono");
	vr.m_Telefono = (LPCSTR) valor.bstrVal;
	valor = pRs->GetFieldValue("Direccion");
	vr.m_Direccion = (LPCSTR) valor.bstrVal;
	valor = pRs->GetFieldValue("Diagnostico");
	vr.m_Diagnostico = (LPCSTR) valor.bstrVal;
	valor = pRs->GetFieldValue("Medicacion_Actual");
	vr.m_Medicacion_Actual = (LPCSTR) valor.bstrVal;

	/*se cierra el recordset*/
	pRs->Close();
	
	
	do
	{
		if(vr.Mostrar())  
		{
			/*se actualizaron los datos y se dió OK*/
			
			if(vr.m_No_Paciente!=id)
				/*se modificó el id lo cual no es válido*/
			{
				/*El único dato que no se puede actualizar es el id*/
				AfxMessageBox("id no accepted");
				out=false;
				
			}
			
			
			else
			{
				/*actualización válida, no se modificó el id */
				try
				{
					/*se abre la base de datos en modo actualización*/ 
					((CApp*)pAppt)->AbreActualizar(pRs,query);
					/*actualizando los campos de la base de datos*/
					pRs->Edit();
					valor.SetString((LPCTSTR)vr.m_Nombre_Paciente, VT_BSTRT); 
					pRs->SetFieldValue("Nombre_Paciente",valor);
					valor.SetString((LPCTSTR)vr.m_Apellido_Paciente, VT_BSTRT); 
					pRs->SetFieldValue("Apellido_Paciente",valor);
					valor.SetString((LPCTSTR)vr.m_Telefono, VT_BSTRT); 
					pRs->SetFieldValue("Telefono",valor);
					valor.SetString((LPCTSTR)vr.m_Direccion, VT_BSTRT); 
					pRs->SetFieldValue("Direccion",valor);
					valor.SetString((LPCTSTR)vr.m_Diagnostico, VT_BSTRT); 
					pRs->SetFieldValue("Diagnostico",valor);
					valor.SetString((LPCTSTR)vr.m_Medicacion_Actual, VT_BSTRT); 
					pRs->SetFieldValue("Medicacion_Actual",valor);
					pRs->SetFieldValue("Fecha_Nacimiento",vr.m_Fecha_Nacimiento);
					
					pRs->Update();
					pRs->Close();
					
					/*indicacion de que los datos del paciente han sido modificados
					correctamente*/			
					AfxMessageBox("The data has been updated succesfully");
					result=true;  /*Los datos fueron actualizados en la base de datos*/	
					out=true;
					
				}/*try*/
				catch(CDaoException *e)
				{
					AfxMessageBox(e->m_pErrorInfo->m_strDescription);
					e->Delete();
					result=false;
				}
				
			}/*else*/
			
			
		}
		/*se dió cancel*/
		else
		{
			result=false;
			out=true;
		}
	}while(!out);


	/*se libera la memoria reservada para el recordset y se sale*/
	delete pRs;
	pRs=NULL;
	return result;    /*caso en que se dió cancel y los datos no fueron actualizados en la bd*/
	
	
}

bool CMedico::EliminarPaciente(long valor)
{
	/*creo un recordset*/
    CDaoRecordset* pRs=new CDaoRecordset(&(((CApp*)pAppt)->database)) ;
    CString query, temp;
    bool result = false; 
	
    try
	{
	  /*Selecciona de la tabla paciente el paciente a borrar, o sea el que su No_Paciente
	  matchea con valor*/
      
	  temp="SELECT * FROM Paciente WHERE (((Paciente.No_Paciente)=";
	  query.Format("%s%d));",temp,valor);

	  /*Se abre el Recordset en un modo que permita borrar*/

	  ((CApp*)pAppt)->AbreActualizar(pRs,query);
	   /*Confirmación de eliminación*/ 
      
	  if (AfxMessageBox("The Patient will be permanent deleted", MB_YESNO|MB_ICONSTOP) == IDYES)
	  { 
    		pRs->Delete();  /*Se elimina el paciente y todos los datos asociados a este*/
			result =  true;  /*en las demás tablas*/
	  }
	  else
     		result = false;
	
	}	
	catch(CDaoException* e)
		{
			AfxMessageBox( e->m_pErrorInfo->m_strDescription);
			e->Delete();
			result =  false;
		}
   	
	pRs->Close();      /*cerrando y destruyendo el recordset*/
	delete pRs;
	pRs = NULL;
	return result;
}

bool CMedico::ExportarPaciente(long id)
{
	
	CString query_org,temp,query_dest;
	CDaoDatabase database_backup;
	CFileManage fm;
	
	CString pathold= ((CApp*)pAppt)->bd_root+"\\bd\\swap\\backup.mdb";
	CString pathnew= ((CApp*)pAppt)->bd_root+"\\bd\\backup.mdb";
	
	
	///////////copiando base de datos de swapeo hacia dir de trabajo//////////////
	if (!CopyFile(pathold,pathnew,FALSE))
	{
		AfxMessageBox("Can't copy data file");
		return false;
	}
	
	
	try
	{
		/*creando recordset origen*/
		CDaoRecordset* pRsorg=new CDaoRecordset(&(((CApp*)pAppt)->database));
		/*creando recordset destino (usado para exportar los datos)*/
		CDaoRecordset* pRsdest=new CDaoRecordset(&(database_backup));
		/*Abriendo la base de datos destino*/
		database_backup.Open(((CApp*)pAppt)->bd_root+"\\bd\\backup.mdb");
		
		
		/////codigo asociado a exportar un paciente/////////////////
		
		/*realizando la copia de los records asociados a los datos personales del paciente*/
        temp="SELECT * FROM Paciente WHERE (((Paciente.No_Paciente)=";
		query_org.Format("%s%d));",temp,id);
		query_dest="SELECT * FROM Paciente";
		((CApp*)pAppt)->CopiarRecords(query_org,query_dest,pRsorg,pRsdest);
		/*cerrando el recordset origen*/
		pRsorg->Close();
		/*cerrando la tabla a exportar*/
		pRsdest->Close();
		
		
		/*realizando la copia de los records asociados a las sesiones del paciente*/
		temp="SELECT * FROM Sesiones WHERE (((Sesiones.No_Paciente)=";
		query_org.Format("%s%d));",temp,id);
		query_dest="SELECT * FROM Sesiones";
        ((CApp*)pAppt)->CopiarRecords(query_org,query_dest,pRsorg,pRsdest);
		/*cerrando el recordset origen*/
		pRsorg->Close();
		/*cerrando la tabla a exportar*/
		pRsdest->Close();

		/*realizando la copia de los records asociados a las condiciones de cada una de 
		las sesiones de ese paciente*/
		temp="SELECT Condiciones.* FROM (Paciente INNER JOIN Sesiones ON Paciente.No_Paciente = Sesiones.No_Paciente) INNER JOIN Condiciones ON Sesiones.Codigo_Sesion = Condiciones.Codigo_Sesion WHERE (((Paciente.No_Paciente)=";
        query_org.Format("%s%d));",temp,id);
		query_dest="SELECT * FROM Condiciones";
        ((CApp*)pAppt)->CopiarRecords(query_org,query_dest,pRsorg,pRsdest);
		/*cerrando el recordset origen*/
		pRsorg->Close();
		/*cerrando la tabla a exportar*/
		pRsdest->Close();

		/*realizando la copia de los records asociados a los minutos de cada una de las
		condiciones de cada una de las sesiones del paciente en cuestión*/
        temp="SELECT Minutos.* FROM ((Paciente INNER JOIN Sesiones ON Paciente.No_Paciente = Sesiones.No_Paciente) INNER JOIN Condiciones ON Sesiones.Codigo_Sesion = Condiciones.Codigo_Sesion) INNER JOIN Minutos ON Condiciones.Codigo_Condicion = Minutos.Codigo_Condicion WHERE (((Paciente.No_Paciente)=";
;
        query_org.Format("%s%d));",temp,id);
		query_dest="SELECT * FROM Minutos";
        ((CApp*)pAppt)->CopiarRecords(query_org,query_dest,pRsorg,pRsdest);
		/*cerrando el recordset origen*/
		pRsorg->Close();
		/*cerrando la tabla a exportar*/
		pRsdest->Close();
		
		/////////////////////////
		/*eliminando recordset origen y destino*/	
		delete pRsorg;
		pRsorg=NULL;
		delete pRsdest;
		pRsdest=NULL;
		/*cerrando la base de datos a exportar*/
		database_backup.Close();
		
		
	}
	catch(CDaoException *e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
		
	}
	/*los datos del paciente fueron copiados exitosamente */
    fm.SaveFile(pathnew);
	if(!DeleteFile(pathnew))
	{
		AfxMessageBox("Can't delete data base swap file");
		return false;	
	}
	return true;	
}

bool CMedico::ImportarPaciente()
{
	CString query_org,temp,query_dest;
	CDaoDatabase database_backup;
	CFileManage fm;
	CString pathold;
	CString pathnew=((CApp*)pAppt)->bd_root+"\\bd\\backup.mdb";
	CString current="a:\\*.mdb";
	CFileDialog open(TRUE,"mdb",current);
	
	//////copiando base de datos de swapeo desde disco de 3 1/2hacia dir de trabajo//////////

	if (open.DoModal()==IDOK)
	{
		pathold =open.GetPathName();
		
		if (!CopyFile(pathold,pathnew,FALSE))
		{
			AfxMessageBox("Can't copy new data file");
			return false;
		}
	}
		
	
	
	try
	{
		/*creando recordset origen*/
		CDaoRecordset* pRsdest=new CDaoRecordset(&(((CApp*)pAppt)->database));
		/*creando recordset destino (usado para exportar los datos)*/
		CDaoRecordset* pRsorg=new CDaoRecordset(&(database_backup));
		/*Abriendo la base de datos destino*/
		database_backup.Open(((CApp*)pAppt)->bd_root+"\\bd\\backup.mdb");
		
		
		/////codigo asociado a exportar un paciente/////////////////
		
		/*realizando la copia de los records asociados a los datos personales del paciente*/
        temp="SELECT * FROM Paciente";
		query_org=temp;
		query_dest="SELECT * FROM Paciente";
		((CApp*)pAppt)->CopiarRecords(query_org,query_dest,pRsorg,pRsdest);
		/*cerrando el recordset origen*/
		pRsorg->Close();
		/*cerrando la tabla a exportar*/
		pRsdest->Close();
		
		
		/*realizando la copia de los records asociados a las sesiones del paciente*/
		temp="SELECT * FROM Sesiones";
		query_org=temp;
		query_dest="SELECT * FROM Sesiones";
        ((CApp*)pAppt)->CopiarRecords(query_org,query_dest,pRsorg,pRsdest);
		/*cerrando el recordset origen*/
		pRsorg->Close();
		/*cerrando la tabla a exportar*/
		pRsdest->Close();

		/*realizando la copia de los records asociados a las condiciones del paciente*/
		temp="SELECT * FROM Condiciones";
		query_org=temp;
		query_dest="SELECT * FROM Condiciones";
        ((CApp*)pAppt)->CopiarRecords(query_org,query_dest,pRsorg,pRsdest);
		/*cerrando el recordset origen*/
		pRsorg->Close();
		/*cerrando la tabla a exportar*/
		pRsdest->Close();
		
		/*realizando la copia de los records asociados a las condiciones del paciente*/
		temp="SELECT * FROM Minutos";
		query_org=temp;
		query_dest="SELECT * FROM Minutos";
        ((CApp*)pAppt)->CopiarRecords(query_org,query_dest,pRsorg,pRsdest);
		/*cerrando el recordset origen*/
		pRsorg->Close();
		/*cerrando la tabla a exportar*/
		pRsdest->Close();
		
		/////////////////////////
		/*eliminando recordset origen y destino*/	
		delete pRsorg;
		pRsorg=NULL;
		delete pRsdest;
		pRsdest=NULL;
		/*cerrando la base de datos a exportar*/
		database_backup.Close();
		
	}
	catch(CDaoException *e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
		
	}
	/*los datos del paciente fueron copiados exitosamente */
    
	if(!DeleteFile(pathnew))
	{
		AfxMessageBox("Can't delete data base swap file");
		return false;	
	}
	return true;	

}

bool CMedico::RegistrarPaciente()
{

	bool out=1;
	bool result=false;
   
	
	CViewRegistro vr; /*ventana de registrar un paciente*/
	COleVariant	valor;
	CDaoRecordset* pRs=new CDaoRecordset(&(((CApp*)pAppt)->database)) ;
	CString query, temp;
	
	

	do
	{
		
		if(vr.Mostrar())  /*retorna cuando se da OK y se entraron todos los datos o si se da CANCEL*/
		{
           
			temp.Format("%d",vr.m_No_Paciente);
			query = "SELECT * FROM Paciente WHERE (((No_Paciente)="+temp+"))";
			pRs->Close();
			/*se entraron todos los datos y se dió OK*/
			
			
			/*primero verificar si el paciente que se va a entrar tiene un numero igual a uno 
			que ya existía*/
			
			try
			{
				if (((CApp*)pAppt)->AbreLeer(pRs, query))
				{
					/*Un paciente con igual Numero ya ha sido registrado*/
					out=0;
					AfxMessageBox("The patient already exist");
					
				}
				
				else
				{
					/*El paciente no se encontraba por lo que es válida la adición*/
					out=1;
					pRs->Close();
					((CApp*)pAppt)->AbreAdicionar(pRs,"SELECT * FROM Paciente");
					
					pRs->AddNew();
					/*Adicionando los datos entrados en la ventana CViewRegistro en el recordset*/
					valor.vt= VT_I4;
					valor.lVal= vr.m_No_Paciente;
					pRs->SetFieldValue("No_Paciente",valor);
					
					valor.SetString((LPCTSTR) vr.m_Nombre_Paciente, VT_BSTRT); 
					pRs->SetFieldValue("Nombre_Paciente",valor);
					
					valor.SetString((LPCTSTR) vr.m_Apellido_Paciente, VT_BSTRT);
					pRs->SetFieldValue("Apellido_Paciente",valor);
					
					pRs->SetFieldValue("Fecha_Nacimiento", vr.m_Fecha_Nacimiento);
					
					valor.SetString((LPCTSTR) vr.m_Telefono, VT_BSTRT); 
					pRs->SetFieldValue("Telefono",valor);
					
					valor.SetString((LPCTSTR) vr.m_Direccion, VT_BSTRT); 
					pRs->SetFieldValue("Direccion",valor);
					
					valor.SetString((LPCTSTR) vr.m_Diagnostico, VT_BSTRT); 
					pRs->SetFieldValue("Diagnostico",valor);
					
					valor.SetString((LPCTSTR) vr.m_Medicacion_Actual, VT_BSTRT); 
					pRs->SetFieldValue("Medicacion_Actual",valor);
					
					pRs->Update();
					pRs->Close();
					
					/*Poniendo al paciente como activo*/
					((CApp*)pAppt)->paciente.numero=vr.m_No_Paciente;
					((CApp*)pAppt)->paciente.nombre=vr.m_Nombre_Paciente;
                    ((CApp*)pAppt)->paciente.paciente_cargado = true;
					((CApp*)pAppt)->paciente.RefrescarStatusBar();
					
					/*El nuevo paciente fue registrado en la base de datos*/	
					AfxMessageBox("The patient has been registered succesfully");
					result=true;
				}
				
			}/*try*/
			catch(CDaoException *e)
			{
				AfxMessageBox(e->m_pErrorInfo->m_strDescription);
				e->Delete();
			}
			
			 
		}/*if*/
		else 
		{
			out=1;
			result=false;
		}
	}while(!out);

	delete pRs;
	pRs=NULL;
	return result;  
	

}

bool CMedico::BuscaPaciente()
{
	CViewBuscarPaciente vbp; /*ventana que muestra las diferentes opciones a ejecutar con
	un paciente*/
	vbp.Mostrar(pAppt);
	return true;	
}