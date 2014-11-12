// DataBaseAplication.cpp: implementation of the CDataBaseAplication class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataBaseAplication.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataBaseAplication::CDataBaseAplication()
{
	GetCurrentDirectory(2000, bd_root.GetBuffer(2000));
	bd_root.ReleaseBuffer();
}

CDataBaseAplication::~CDataBaseAplication()
{

}

bool CDataBaseAplication::ShowRecordList(CListBox *pList, CDaoRecordset * pRecordset)
{
	
	int m_nRowCount, m_nFields;
	int x=0;
	COleVariant var;
	CString str;
	CString temp;

	GetRecordsetSize(pRecordset, &m_nRowCount, &m_nFields);
    
	pList->ShowWindow(SW_HIDE);

	pRecordset->MoveFirst();
	
	for(int j=0;j<m_nRowCount;j++)
	{
		
		for(int i=0;i<m_nFields;i++)
		{
			var=pRecordset->GetFieldValue(i);
			switch(var.vt)
			{
			case VT_BSTR:
				str=(LPCSTR) var.bstrVal;
				AdjustString(str, STRING);
				break;
			case VT_I2:
				str.Format("%d",(int)var.iVal);
				break;
			case VT_I4:
				str.Format("%d",(int)var.lVal);
				AdjustString(str, ENTERO);
				break;
			case VT_R4:
				str.Format("%10.2f",(double)var.fltVal);
				break;
			case VT_R8:
				str.Format("%10.2f",(double)var.dblVal);
				break;
			case VT_CY:
				str=COleCurrency(var).Format();
				break;
			case VT_DATE:
				str=COleDateTime(var).Format();
				break;
			case VT_BOOL:
				str=(var.boolVal==0) ? "FALSE" : "TRUE";
				break;
			case VT_NULL:
				str="----";
				break;
			default:
				str.Format("Unk type %d\n",var.vt);
			}
			
		temp += str;
		}
	  
      
	  pList->AddString(temp);
	  temp.Empty();
	  pRecordset->MoveNext();
	}
  
  pList->ShowWindow(SW_SHOW);
  return true;
}

bool CDataBaseAplication::AdjustString(CString &str, int kind)
{
	int size;
	char *fill;
	
	switch (kind)
	{
	case ENTERO:
		{
			size= MAXENTERO - str.GetLength();
			fill= (char*)calloc(1,size);
			fill[0] = ' ';
			for(int i=1;i<size-1;i++)
			{
				fill[i]='_';
			}
			fill[size-1]=0;
			str = str + fill;
			free (fill);
			break;
		}
	case STRING:
			{
				size= MAXSTRING - str.GetLength();
				fill= (char*)calloc(1,size);
				str = str + fill;
				free (fill);
				break;
			}
	}
return true;
}

bool CDataBaseAplication::ShowRecordGrid(CMSFlexGrid *pgrid, CDaoRecordset *pRecordset, CWnd* pWnd)
{

	int 	m_nRowCount, m_nFields;
	int x=0;
	COleVariant var;
	CString str;
	CString temp;

	if (!GetRecordsetSize(pRecordset, &m_nRowCount, &m_nFields))
    return false;

	CClientDC dc(pWnd);
	long XPixelsPorPulgada = dc.GetDeviceCaps(LOGPIXELSX);
	long YPixelsPorPulgada = dc.GetDeviceCaps(LOGPIXELSY);
	
	CRect rect;
	pgrid->GetWindowRect( rect);

    long AnchoRej, AltoRej;
	
    AnchoRej = rect.right - rect.left; // píxeles
    AltoRej = rect.bottom - rect.top;  // píxeles
    AnchoRej = (AnchoRej * 1440 / XPixelsPorPulgada) - 50; //AnchoCol - 50; // twips
    AltoRej = (AltoRej * 1440 / YPixelsPorPulgada) - 50; //AltoFila - 50;   // twips

     // Ajustar el número de filas y de columnas
    pgrid->SetRows(m_nRowCount+1);
    pgrid->SetCols(m_nFields);

	//ANCHO DE CELDA NORMAL 1000 TWIPS
    pgrid->ShowWindow(SW_HIDE);

	for ( int i=0; i < m_nFields; i++ )
	{
     pgrid->SetColWidth( i, (AnchoRej-255)/ m_nFields);
	}

	try
	{
	  pRecordset->MoveFirst();
	
	 for(int j=0;j<m_nRowCount;j++)
	 {
		
		for(int i=0;i<m_nFields;i++)
		{
			var=pRecordset->GetFieldValue(i);
			switch(var.vt)
			{
			case VT_BSTR:
				str=(LPCSTR) var.bstrVal;
				
				break;
			case VT_I2:
				str.Format("%d",(int)var.iVal);
				break;
			case VT_I4:
				str.Format("%d",(int)var.lVal);
				
				break;
			case VT_R4:
				str.Format("%10.2f",(double)var.fltVal);
				break;
			case VT_R8:
				str.Format("%10.2f",(double)var.dblVal);
				break;
			case VT_CY:
				str=COleCurrency(var).Format();
				break;
			case VT_DATE:
				str= COleDateTime(var).Format(VAR_DATEVALUEONLY, LANG_USER_DEFAULT);
				break;
			case VT_BOOL:
				str=(var.boolVal==0) ? "FALSE" : "TRUE";
				break;
			case VT_NULL:
				str="----";
				break;
			default:
				str.Format("Unk type %d\n",var.vt);
			}
			
	    pgrid->SetCol(i);
		pgrid->SetRow(j+1);
		pgrid->SetText(str);
	    
		}
	  
        pRecordset->MoveNext();
	}
    
	}
	catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	pgrid->ShowWindow(SW_SHOW);
	return false;
	}
	pgrid->ShowWindow(SW_SHOW);
	return true;
}

bool CDataBaseAplication::GetRecordsetSize(CDaoRecordset *pRecordset, int *Rows, int *Fields)
{
    
	try
	{
	     if(!pRecordset->IsBOF())
		 {
		   pRecordset->MoveLast();
           *Rows=pRecordset->GetAbsolutePosition()+1;
	       *Fields=pRecordset->GetFieldCount();
	       return true;
		 }
	}
	catch (CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	}
	return false;
}


bool CDataBaseAplication::ShowFieldComboBox(CComboBox *pComboBox, CDaoRecordset *pRecordset, CString Field)
{
    int m_nRowCount, m_nFields;
	
	COleVariant var;
	CString str;
	CString temp;

	GetRecordsetSize(pRecordset, &m_nRowCount, &m_nFields);

    if (!m_nRowCount)
	 return false;

	pComboBox->ShowWindow(SW_HIDE);
	try
	{
	pRecordset->MoveFirst();
    
		for(int j=0;j<m_nRowCount;j++)
		{
		    
			var=pRecordset->GetFieldValue(Field);
			switch(var.vt)
			{
			case VT_BSTR:
				str=(LPCSTR) var.bstrVal;
				
				break;
			case VT_I2:
				str.Format("%d",(int)var.iVal);
				break;
			case VT_I4:
				str.Format("%d",(int)var.lVal);
				
				break;
			case VT_R4:
				str.Format("%10.2f",(double)var.fltVal);
				break;
			case VT_R8:
				str.Format("%10.2f",(double)var.dblVal);
				break;
			case VT_CY:
				str=COleCurrency(var).Format();
				break;
			case VT_DATE:
				str=COleDateTime(var).Format();
				break;
			case VT_BOOL:
				str=(var.boolVal==0) ? "FALSE" : "TRUE";
				break;
			case VT_NULL:
				str="----";
				break;
			default:
				str.Format("Unk type %d\n",var.vt);
			}
			
	        pComboBox->AddString(str); 
			pRecordset->MoveNext();
           		
		}
	}
	catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	}
	
	pComboBox->ShowWindow(SW_SHOW);
	
	return true;
}

bool CDataBaseAplication::CleanGrid(CMSFlexGrid *pgrid)
{
   int cols, rows;
   
	cols = pgrid->GetCols();
    rows = pgrid->GetRows();
    
	pgrid->ShowWindow(SW_HIDE);
	for (int i=0; i<cols; i++)
	{
		if (rows == 1)
		return false;
		for (int j=1; j<rows; j++ )
		{
		  pgrid->SetCol(i);
		  pgrid->SetRow(j);
		  pgrid->SetText(" ");
		}
	}
	pgrid->ShowWindow(SW_SHOW);
  return true;
}

bool CDataBaseAplication::GetComboBoxSel(CComboBox *pCB, CString &Value)
{

    int index, size;
    Value.Empty();
    
	index = pCB->GetCurSel();
	if (index == CB_ERR)
		return false;

    size=pCB->GetLBTextLen(index);
	pCB->GetLBText(index,Value.GetBuffer(size));
	Value.ReleaseBuffer();
	
	return true;
}

CString* CDataBaseAplication::PutColString(int *cant, CDaoRecordset *pRS, CString Col)
{

	 int m_nRowCount, m_nFields;
	
	COleVariant var;
	CString str;
	CString temp;
    CString *data;
	data = NULL;

	GetRecordsetSize(pRS, &m_nRowCount, &m_nFields);

    if (m_nRowCount)
	
	{
    
	*cant = m_nRowCount;
	data = new CString[*cant]; 

		pRS->MoveFirst();
    
		for(int j=0;j<m_nRowCount;j++)
		{
		    
			var=pRS->GetFieldValue(Col);
			switch(var.vt)
			{
			case VT_BSTR:
				str=(LPCSTR) var.bstrVal;
				
				break;
			case VT_I2:
				str.Format("%d",(int)var.iVal);
				break;
			case VT_I4:
				str.Format("%d",(int)var.lVal);
				
				break;
			case VT_R4:
				str.Format("%10.2f",(double)var.fltVal);
				break;
			case VT_R8:
				str.Format("%10.2f",(double)var.dblVal);
				break;
			case VT_CY:
				str=COleCurrency(var).Format();
				break;
			case VT_DATE:
				str=COleDateTime(var).Format();
				break;
			case VT_BOOL:
				str=(var.boolVal==0) ? "FALSE" : "TRUE";
				break;
			case VT_NULL:
				str="----";
				break;
			default:
				str.Format("Unk type %d\n",var.vt);
			}
			
	        data[j] = str;
			pRS->MoveNext();
           		
		}
	}
	
	return data;
}

bool CDataBaseAplication::CalcSelSize(CMSFlexGrid *pgrid, CWnd* pWnd)
{

	//AJUSTAR EL TAMAÑO DE LAS CELDAS DE ACUERDO AL TITULO
	CString text;
	long CantCols;
    long AnchoCol;
	long AnchoVent; //NewAnchoGrid;
	float ancho;
    long AnchoGrid=0;

	CClientDC dc(pWnd);
	long XPixelsPorPulgada = dc.GetDeviceCaps(LOGPIXELSX);

	CRect rect;
	pgrid->GetWindowRect( rect);
	AnchoVent = rect.right - rect.left;
    AnchoVent = AnchoVent * 1440 / XPixelsPorPulgada;
    
    CantCols = pgrid->GetCols();
    pgrid->ShowWindow(SW_HIDE);
	

	for (int i=0; i < CantCols; i++ )
	{
     pgrid->SetCol(i);
	 pgrid->SetRow(0);
	 text = pgrid->GetText();
     ancho = pgrid->GetCellFontSize(); 
     ancho = (ancho * 1440 / XPixelsPorPulgada);
     AnchoCol = text.GetLength()* ancho;
	 if (AnchoCol > 1200) AnchoCol = 1200 ;
	 pgrid->SetColWidth( i, AnchoCol);
	}
	
	for (i=0; i < CantCols; i++ )
     AnchoGrid = AnchoGrid + pgrid->GetColWidth(i);

    if (AnchoVent > AnchoGrid)
	{
	   AnchoCol = AnchoVent/CantCols;
       for (i=0; i < CantCols; i++ )
		   pgrid->SetColWidth( i, AnchoCol);
	}
	pgrid->ShowWindow(SW_SHOW);
	//SI EL ANCHO TOTAL ES MENOR QUE EL TAMAÑO DE LA VENTANA, AJUSTAR AL TAMAÑO
	return true;
}

bool CDataBaseAplication::AbreAdicionar(CDaoRecordset *pRs, CString query)
{
    bool result = false;

	try
	{
	   pRs->Open(dbOpenDynaset,query,dbAppendOnly);
	   result = true;
	}
	catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	result = false;
	}

	return result;
}

bool CDataBaseAplication::AbreActualizar(CDaoRecordset *pRs, CString query)
{

	bool result = false;

	try
	{
	   pRs->Open(dbOpenDynaset,query,dbConsistent);
	   result = true;
	   
	   if (pRs->IsBOF() && pRs->IsEOF())
		  result = false;
	}
	catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	result = false;
	}

	return result;
}

bool CDataBaseAplication::AbreLeer(CDaoRecordset *pRs, CString query)
{

	bool result = false;

	try
	{
	   pRs->Open(dbOpenDynaset,query,dbReadOnly);
	   result = true;
	   
	   if (pRs->IsBOF() && pRs->IsEOF())
		  result = false;
	}
	catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	result = false;
	}

	return result;
}

/********************************************************************************************
/*Esta funcion permite copiar un recordset asociado a una tabla de una base de datos
a otro recordset igual pero asociado a otra base de datos, es útil en operaciones de 
exportar e importar de disco de 31/2
PARAMETROS
query_org-query asociado a bd desde donde se quiere copiar un determinado recordset
pRsorg-puntero a recordset de base de datos origen.
query_dest-query asociado a bd hacia donde se quiere copiar un determinado recordset
pRsdest-puntero a recordset de base de datos destino.
********************************************************************************************/
bool CDataBaseAplication::CopiarRecords(CString query_org, CString query_dest, CDaoRecordset *pRsorg, CDaoRecordset *pRsdest)
{
	int total;    /*cantidad de filas en el recordset*/
	bool result=false;
	try
	{
		/*Abre cada recordset en el modo adecuado para hacer la copia*/
		AbreLeer(pRsorg,query_org);
		AbreAdicionar(pRsdest,query_dest); 
		pRsdest->AddNew();

		/*copiando los datos al recordset a exportar*/
		if(!(pRsorg->IsBOF()&&pRsorg->IsEOF()))/*si la tabla no está vacía*/
		{
			pRsorg->MoveLast();  /*se para en el ultimo elemento del recordset*/
			total=pRsorg->GetRecordCount();
			for(int j=0;j<total;j++)
				/*GetRecordCount me da el total de filas en el recordset*/
			{
				/*me paro en la fila correspondiente en ambos recordset*/
				pRsorg->SetAbsolutePosition(j);
				
				for(int i=0;i<pRsorg->GetFieldCount();i++)
					/*GetFieldCount me da la cantidad de columnas*/
				{
					pRsdest->SetFieldValue(i,pRsorg->GetFieldValue(i));
				}
				pRsdest->Update();
				if(j<total-1) pRsdest->AddNew();
				
			}
			result=true;
		}
		else
		{
			AfxMessageBox("One Recordset is Empty");
			result=false;
		}
	}
	catch(CDaoException *e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
		
	}
	
	return result;
}

bool CDataBaseAplication::ShowRecordGrid(CMSFlexGrid *pgrid, CDaoRecordset *pRecordset, CWnd* pWnd, CString *pNoMostrar, int cantidad)
{
	int 	m_nRowCount, m_nFields;
	int x=0;
	COleVariant var;
	CDaoFieldInfo info;
	CString str;
	CString temp;
	bool puedemostrar;
	int quitarfilas;
	quitarfilas = 0;

	if (!GetRecordsetSize(pRecordset, &m_nRowCount, &m_nFields))
    return false;
    //aqui se le resta a m_nFields la cantidad de columnas que no se quieren mostrar
    m_nFields = m_nFields - cantidad;

	CClientDC dc(pWnd);
	long XPixelsPorPulgada = dc.GetDeviceCaps(LOGPIXELSX);
	long YPixelsPorPulgada = dc.GetDeviceCaps(LOGPIXELSY);
	
	CRect rect;
	pgrid->GetWindowRect( rect);

	long AnchoRej, AltoRej;
	AnchoRej = rect.right - rect.left; // píxeles
    AltoRej = rect.bottom - rect.top;  // píxeles
    AnchoRej = (AnchoRej * 1440 / XPixelsPorPulgada) - 50; //AnchoCol - 50; // twips
    AltoRej = (AltoRej * 1440 / YPixelsPorPulgada) - 50; //AltoFila - 50;   // twips

    // Ajustar el número de filas y de columnas
    pgrid->SetRows(m_nRowCount+1);
    pgrid->SetCols(m_nFields);

	//ANCHO DE CELDA NORMAL 1000 TWIPS
    for ( int i=0; i < m_nFields; i++ )
	   pgrid->SetColWidth( i, (AnchoRej-255)/ m_nFields);
	
	//aqui ocultar la ventana  para refrescar
	pgrid->ShowWindow(SW_HIDE);
    try
	{
	  pRecordset->MoveFirst();
	
	 for(int j=0;j<m_nRowCount;j++)
	 {
		quitarfilas = 0;
		for(int i=0;i<(m_nFields+cantidad);i++)
		{
			//verificar si la columna que se va a mostrar se puede mostrar
			puedemostrar = true;

			for (int k=0; k<cantidad; k++)
			{
			  pRecordset->GetFieldInfo(i, info);
			  if (info.m_strName == pNoMostrar[k])
			  {
				puedemostrar = false;
				quitarfilas++;
			  }
			}
			
			if (puedemostrar)
            {

			var=pRecordset->GetFieldValue(i);
			Crack(str, var);
			pgrid->SetCol(i- quitarfilas);
			pgrid->SetRow(j+1);
			pgrid->SetText(str);
	    
			}
		}
        pRecordset->MoveNext();
	}
    
	}
	catch(CDaoException *e)
	{
	AfxMessageBox(e->m_pErrorInfo->m_strDescription);
	e->Delete();
	pgrid->ShowWindow(SW_SHOW);
	return false;
	}
	
	pgrid->ShowWindow(SW_SHOW);
	return true;
}

bool CDataBaseAplication::Crack(CString &str, COleVariant var)
{
    
	switch(var.vt)
			{
			case VT_BSTR:
				str=(LPCSTR) var.bstrVal;
				break;
			case VT_I2:
				str.Format("%d",(int)var.iVal);
				break;
			case VT_I4:
				str.Format("%d",(int)var.lVal);
				break;
			case VT_R4:
				str.Format("%10.2f",(double)var.fltVal);
				break;
			case VT_R8:
				str.Format("%10.2f",(double)var.dblVal);
				break;
			case VT_CY:
				str=COleCurrency(var).Format();
				break;
			case VT_DATE:
				str= COleDateTime(var).Format(VAR_DATEVALUEONLY, LANG_USER_DEFAULT);
				break;
			case VT_BOOL:
				str=(var.boolVal==0) ? "No" : "Si";
				break;
			case VT_NULL:
				str="-";
				break;
			default:
				str.Format("Unk type %d\n",var.vt);
			}
	
	return true;
}
