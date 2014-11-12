// db11c1.cpp: implementation of the CCartasDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "db11c1.h"
#include "db11d2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCartasDatabase::CCartasDatabase()
{
	InitCartasDatabase();
}

CCartasDatabase::~CCartasDatabase()
{
	Close();
	delete m_CartasDatabase->Explorer;
	delete m_CartasDatabase->daodatabase;
	delete m_CartasDatabase->cartas;
	delete m_CartasDatabase;
}

int CCartasDatabase::InitCartasDatabase()
{
	m_CartasDatabase=new S_CARTASDATABASE;
	if (m_CartasDatabase)
	{
		m_CartasDatabase->daodatabase=new CDaoDatabase(&m_CartasDatabase->daoworkspace);
		m_CartasDatabase->Explorer=new CDaoRecordset(m_CartasDatabase->daodatabase);
		m_CartasDatabase->cartas= new CDaoRecordset(m_CartasDatabase->daodatabase);
		m_CartasDatabase->clasificaciones.cantidad=0;
		m_CartasDatabase->departamentos.cantidad=0;
		m_CartasDatabase->municipios.cantidad=0;
		m_CartasDatabase->provincias.cantidad=0;
		m_CartasDatabase->sindicatos.cantidad=0;
		m_CartasDatabase->temas.cantidad=0;
		m_CartasDatabase->OnOpen=false;
		m_CartasDatabase->OnNew=false;
		return true;
	}
	return false;
}

int CCartasDatabase::OpenDatabase()
{
	if (m_CartasDatabase->OnOpen)
		return true;
	CDaoRecordset*	cartas=m_CartasDatabase->cartas;
	CString	filename=_T("D:\\USR\\LESTER\\Visual Studio\\Microsoft Access\\Cartas99.mdb");
	/*
	static char ExtFilter[] = "Database Files (*.mdb) |*.mdb||"; 
	CFileDialog Dlg(true,NULL,NULL,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,ExtFilter);
	if (Dlg.DoModal() == IDOK)
	*/
	{
		//filename=Dlg.GetPathName();
		try
		{
			m_CartasDatabase->daodatabase->Open(filename);
			cartas->Open(dbOpenDynaset,_T("SELECT * FROM CARTAS"));
			if (!(cartas->IsBOF() && cartas->IsEOF()))
				cartas->MoveFirst();
		}
		catch (CDaoException* e)
		{
			AfxMessageBox("Error abriendo la base de datos");
			e->Delete();
		}
		m_CartasDatabase->OnOpen=true;
	}
	LeerDepartamentos();
	LeerMunicipios();
	LeerProvincias();
	LeerSindicatos();
	LeerOrganismos();
	return true;	
}

int CCartasDatabase::LeerProvincias()
{
	return LeerCampo(&m_CartasDatabase->provincias,"PROVINCIAS ORDER BY PROVINCIAS.NOMBRE");
}
//
// dada una tabla lee los campos id y nombre y los almacena
//
int CCartasDatabase::LeerCampo(S_RECORDINFO *recordinfo, char *tabla)
{
	int cantidad=0;
	COleVariant id;
	COleVariant	nombre;
	CString sql("SELECT * FROM ");
	sql+=tabla;

	CDaoRecordset recordset(m_CartasDatabase->daodatabase);
	try
	{
		recordset.Open(dbOpenDynaset,sql);
		recordset.MoveFirst();
		while (!recordset.IsEOF())
		{
			cantidad++;
			recordset.MoveNext();			
		}
		recordinfo->cantidad=cantidad;
		recordinfo->valor=new S_CAMPO[cantidad];
		recordset.MoveFirst();
		for (int i=0;i<cantidad;i++)
		{
			recordset.GetFieldValue("ID",id);
			recordset.GetFieldValue("NOMBRE",nombre);
			recordinfo->valor[i].id=id.lVal;
			memcpy(recordinfo->valor[i].nombre,nombre.pbVal,strlen((char*)nombre.pbVal)+1);
			recordset.MoveNext();
		}
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return false;
	}
	return true;
}

int CCartasDatabase::LeerMunicipios()
{
	return LeerCampo(&m_CartasDatabase->municipios,"MUNICIPIOS ORDER BY MUNICIPIOS.NOMBRE");
}

int CCartasDatabase::LeerSindicatos()
{
	return LeerCampo(&m_CartasDatabase->sindicatos,"SINDICATOS ORDER BY SINDICATOS.NOMBRE");
}

int CCartasDatabase::LeerDepartamentos()
{
	return LeerCampo(&m_CartasDatabase->departamentos,"DEPARTAMENTOS ORDER BY DEPARTAMENTOS.NOMBRE");
}

int CCartasDatabase::Buscar()
{
	CSQLDlg	Dlg;
	Dlg.DoModal();
	return true;
}

//
// este miembro es llamado en cualquier momento
// es usado en el InitView para tomar el contenido del campo actual
//
int CCartasDatabase::UpDate(CCarta *carta)
{
	if (!m_CartasDatabase->OnOpen)
		return false;

	CDaoRecordset* cartas=m_CartasDatabase->cartas;
	if (cartas->IsBOF() || cartas->IsEOF())
		return false;

	COleVariant numero;
	COleVariant nombre;
	COleVariant apellido1;
	COleVariant	apellido2;
	COleVariant	fechaentrada;
	COleVariant	tema;
	COleVariant	tipo;
	COleVariant	sintesis;
	COleVariant	fecharespuesta(_T(""),VT_BSTRT);
	COleVariant	clasificacion;
	// los siguentes campos necesitan un ID
	COleVariant organismo;
	COleVariant	municipio;
	COleVariant	sindicato;
	COleVariant	tsindicato;
	COleVariant	tprovincia;
	COleVariant	tdepartamento;
	try
	{
		cartas->GetFieldValue("NUMERO",numero);
		cartas->GetFieldValue("nombre",nombre);
		cartas->GetFieldValue("apellido1",apellido1);
		cartas->GetFieldValue("apellido2",apellido2);
		cartas->GetFieldValue("organismo",organismo);
		cartas->GetFieldValue("municipio",municipio);
		//cartas->GetFieldValue("tema",tema);
		cartas->GetFieldValue("tipo",tipo);
		cartas->GetFieldValue("sintesis",sintesis);
		cartas->GetFieldValue("sindicato",sindicato);
		cartas->GetFieldValue("tsindicato",tsindicato);
		cartas->GetFieldValue("tprovincia",tprovincia);
		cartas->GetFieldValue("tdepartamento",tdepartamento);

		carta->numero=numero.lVal;
		strcpy(carta->nombre,(char*)nombre.pbVal);
		strcpy(carta->apellido1,(char*)apellido1.pbVal);
		strcpy(carta->apellido2,(char*)apellido2.pbVal);
		strcpy(carta->sintesis,(char*)sintesis.pbVal);
		carta->organismo=organismo.lVal;
		carta->municipio=municipio.lVal;
		carta->sindicato=sindicato.lVal;
		carta->tsindicato=tsindicato.lVal;
		carta->tprovincia=tprovincia.lVal;
		carta->tdepartamento=tdepartamento.lVal;
	}
	catch (CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
	}

	return true;	
}

//
// si se esta creando una carta entonces la adiciona
// de lo contrario la actualiza
//
int CCartasDatabase::Save(CCarta *pcarta)
{
	if (!m_CartasDatabase->OnOpen)
		return false;
	CDaoRecordset*	cartas=m_CartasDatabase->cartas;
	COleVariant numero(pcarta->numero);
	
	COleVariant nombre(pcarta->nombre,VT_BSTRT);
	COleVariant apellido1(pcarta->apellido1,VT_BSTRT);
	COleVariant	apellido2(pcarta->apellido2,VT_BSTRT);
	COleVariant	fechaentrada(_T(""),VT_BSTRT);
	COleVariant	tema(pcarta->tema);
	COleVariant	tipo((long)0);
	COleVariant	sintesis(pcarta->sintesis,VT_BSTRT);
	COleVariant	fecharespuesta(_T(""),VT_BSTRT);
	COleVariant	clasificacion((BYTE)0);
	// los siguentes campos necesitan un ID
	COleVariant organismo(m_CartasDatabase->organismos.valor[pcarta->organismo].id);
	COleVariant	municipio(m_CartasDatabase->municipios.valor[pcarta->municipio].id);
	COleVariant	sindicato(m_CartasDatabase->sindicatos.valor[pcarta->sindicato].id);
	COleVariant	tsindicato(m_CartasDatabase->sindicatos.valor[pcarta->tsindicato].id);
	COleVariant	tprovincia(m_CartasDatabase->provincias.valor[pcarta->tprovincia].id);
	COleVariant	tdepartamento(m_CartasDatabase->departamentos.valor[pcarta->tdepartamento].id);


	try
	{
		if (m_CartasDatabase->OnNew)
			cartas->AddNew();
		else
			cartas->Edit();

		cartas->SetFieldValue("nombre",nombre);
		cartas->SetFieldValue("numero",numero);
		cartas->SetFieldValue("apellido1",apellido1);
		cartas->SetFieldValue("apellido2",apellido2);
		cartas->SetFieldValue("organismo",organismo);
		cartas->SetFieldValue("municipio",municipio);
		//cartas->SetFieldValue("tema",tema);
		cartas->SetFieldValue("tipo",tipo);
		cartas->SetFieldValue("sintesis",sintesis);
		cartas->SetFieldValue("sindicato",sindicato);
		cartas->SetFieldValue("tsindicato",tsindicato);
		cartas->SetFieldValue("tprovincia",tprovincia);
		cartas->SetFieldValue("tdepartamento",tdepartamento);
		cartas->Update();
		m_CartasDatabase->OnNew=false;
		cartas->SetBookmark(cartas->GetLastModifiedBookmark());
	}
	catch (CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}
	return true;
}

//
//	Inicializa esta estructura para adicionar una nueva carta y 
//	Salva la que fue editada
int CCartasDatabase::New(CCarta *pcarta)
{
	if (!m_CartasDatabase->OnOpen)
		return false;
	COleVariant numero;
	try
	{
		CDaoRecordset* cartas=m_CartasDatabase->cartas;
		pcarta->InitCarta();
		if (cartas->IsBOF() && cartas->IsEOF())
		{
			pcarta->numero=1;
		}
		else
		{
			cartas->MoveLast();
			cartas->GetFieldValue("NUMERO",numero);
			pcarta->numero=numero.lVal+1;
		}
	}
	catch(CDaoException* e)
	{
		e->Delete();
		return false;
	}
	m_CartasDatabase->OnNew=true;
	return true;	
}

//
//  Devuelve una de las tablas previamente leidas
//
S_RECORDINFO* CCartasDatabase::GetTable(char *table)
{
	if (!m_CartasDatabase->OnOpen)
		return NULL;
	if (strcmp(table,"MUNICIPIOS")==0)
		return &m_CartasDatabase->municipios;
	if (strcmp(table,"PROVINCIAS")==0)
		return &m_CartasDatabase->provincias;
	if (strcmp(table,"SINDICATOS")==0)
		return &m_CartasDatabase->sindicatos;
	if (strcmp(table,"DEPARTAMENTOS")==0)
		return &m_CartasDatabase->departamentos;
	if (strcmp(table,"ORGANISMOS")==0)
		return &m_CartasDatabase->organismos;
	return NULL;
}

int CCartasDatabase::Close()
{
	if (!m_CartasDatabase->OnOpen)
		return true;
	m_CartasDatabase->OnOpen=false;
	m_CartasDatabase->Explorer->Close();
	m_CartasDatabase->cartas->Close();

	if (m_CartasDatabase->clasificaciones.cantidad)
		delete m_CartasDatabase->clasificaciones.valor;
	if (m_CartasDatabase->departamentos.cantidad)
		delete m_CartasDatabase->departamentos.valor;
	if (m_CartasDatabase->municipios.cantidad)
		delete m_CartasDatabase->municipios.valor;
	if(m_CartasDatabase->provincias.cantidad)
		delete m_CartasDatabase->provincias.valor;
	if (m_CartasDatabase->sindicatos.cantidad)
		delete m_CartasDatabase->sindicatos.valor;
	if (m_CartasDatabase->temas.cantidad)
		delete m_CartasDatabase->temas.valor;
	if (m_CartasDatabase->organismos.cantidad)
		delete m_CartasDatabase->organismos.valor;
	return true;
}

int CCartasDatabase::LeerOrganismos()
{
	return LeerCampo(&m_CartasDatabase->organismos,"ORGANISMOS ORDER BY ORGANISMOS.NOMBRE");	
}

int CCartasDatabase::Next(CCarta *carta)
{
	if (!m_CartasDatabase->OnOpen)
		return false;
	CDaoRecordset* cartas=m_CartasDatabase->cartas;
	try
	{
		if (cartas->IsEOF()) 
			return false;		
		cartas->MoveNext();
		if (cartas->IsEOF())
		{
			cartas->MoveLast();
			return false;
		}
		return UpDate(carta);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
	}
}

int CCartasDatabase::Prev(CCarta *carta)
{
	if (!m_CartasDatabase->OnOpen)
		return false;
	CDaoRecordset* cartas=m_CartasDatabase->cartas;
	try
	{
		if (cartas->IsBOF()) 
			return false;
		cartas->MovePrev();
		if (cartas->IsBOF())
		{
			cartas->MoveFirst();
			return false;
		}
		return UpDate(carta);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
	}	
}

int CCartasDatabase::First(CCarta *carta)
{
	if (!m_CartasDatabase->OnOpen)
		return false;
	CDaoRecordset* cartas=m_CartasDatabase->cartas;
	try
	{
		if (cartas->IsBOF()) 
			return false;
		cartas->MovePrev();
		if (cartas->IsBOF())
		{
			cartas->MoveFirst();
			return false;
		}
		cartas->MoveFirst();
		return UpDate(carta);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
	}	

}
