// HtmlData.cpp: implementation of the CHtmlData class.
//
//////////////////////////////////////////////////////////////////////

#include "HtmlData.h"
#include "bstr.h"

#define _FILENAME_ "htmldata.cpp"

// cuando nos metemos en un tr, hay que poner un nodo de salto en el ultimo node
// Tipos de nodos a utilizar
#define NODE_NONE		0
#define NODE_TTEXT		1
#define NODE_TD 		3	// es un elemento de una tabla, se incrementa la posicion
#define NODT_TNL		4	// new line, es un salto a
#define NODE_TBUTTOM	5	// poner un bottom
#define NODE_TEDIT		6	// poner una caja de edicion
#define NODE

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHtmlData::CHtmlData(IMem *pMem)
{
	mfirstNode = NULL;
	mlastNode = NULL;
	mpIMem = pMem;
}

CHtmlData::~CHtmlData()
{

}

/*
Convertir el documento en una estructura de datos
*/
DWORD CHtmlData::load(IHTMLDocument2 *pHtmlDoc)
{
	HRESULT hr;
	IDispatch *id;
	IHTMLElementCollection *ec;
	IHTMLDOMNode *form;
	int i;
	long count;
	VARIANT index;


	// obtener listado de todos los formularios de la pagina web
	hr = pHtmlDoc->get_forms(&ec); if (hr != S_OK) return _LOG_AT;
	hr = ec->get_length(&count); if (hr != S_OK) return _LOG_AT;

	// obtener el primer elemento de la coleccion
	for (i=0;i<count;i++)
	{
		index.vt = VT_INT;
		index.intVal = i;
		hr = ec->item(index,index,&id); 						if (hr != S_OK) return _LOG_AT;
		//hr = id->QueryInterface(IID_IHTMLElement, (void**)&e);	if (hr != S_OK) return _LOG_AT;
		hr = id->QueryInterface(IID_IHTMLDOMNode,(void**)&form); if (hr != S_OK) return _LOG_AT;
		id->Release();
		processNode(form);
		form->Release();
	}
	return ERR_OK;
}


/*
Obtiene el texto del nodo y lo adiciona al look que hay en memoria
la funcion es recursiva cada llamada barre todos los hijos del nodo
*/
void CHtmlData::pushText(IHTMLDOMNode *node)
{
	IHTMLDOMNode *child,*next;
	HRESULT hr;
	VARIANT v;
	CbBSTR	bstr;
	long	type;
	// obtener primer hijo
	hr = node->get_firstChild(&child);	if (hr != S_OK) { _LOG_AT; return; }

	while(child)
	{
		child->get_nodeType(&type);
		if (type == NODE_ELEMENT) pushText(child);
		if (type == NODE_TEXT)
		{
			child->get_nodeValue(&v);
			bstr.Attach(v.bstrVal);
			mpIMem->lockAdd(v.bstrVal,bstr.getSize()*2);
		}
		hr = child->get_nextSibling(&next);
		child->Release();
		child = next;
	}
}

struct _htmlAttr *CHtmlData::getAttributes(IHTMLDOMNode *node)
{
	VARIANT v;
	VARIANT val;
	long	max;
	HRESULT hr;
	IDispatch	*d;
	IHTMLAttributeCollection* pattr;
	IHTMLDOMAttribute*		pItem;
	BSTR	bstr;
	CbBSTR	obstr;
	struct _htmlAttr	*pfirstAttr = NULL,*plastAttr;

	node->get_attributes(&d);
	hr = d->QueryInterface(IID_IHTMLAttributeCollection, (void**)&pattr);
	d->Release();
	hr = pattr->get_length(&max);
	if (!max) return NULL;

	v.vt = VT_I4;
	for(int i = 0; i < max; ++i)
	{
		v.lVal = i;
		hr = pattr->item(&v, &d);
		hr = d->QueryInterface(IID_IHTMLDOMAttribute, (void**)&pItem);
		d->Release();
		hr = pItem->get_nodeValue(&val);
		if ((val.vt == VT_BSTR) && (val.bstrVal != NULL))
		{
			// Adicionar atributo
			if (pfirstAttr)
			{
				mpIMem->get(sizeof(*plastAttr),(void**)&plastAttr->next);
				plastAttr = plastAttr->next;
			}
			else
			{
				mpIMem->get(sizeof(*pfirstAttr),(void**)&pfirstAttr);
				plastAttr = pfirstAttr;
			}
			plastAttr->next = NULL;
			// tomar nombre y valor
			obstr.Attach(val.bstrVal);
			mpIMem->add(val.bstrVal,(obstr.getSize()+1)*2,(void**)&plastAttr->value);
			hr = pItem->get_nodeName(&bstr);
			obstr.Attach(bstr);
			mpIMem->add(bstr,(obstr.getSize()+1)*2,(void**)&plastAttr->name);
		}
	}
	return pfirstAttr;
}

/*
En dependencia del tipo de nodo se va a procesar,
si se ignora se continua con el proximo
*/
void CHtmlData::processNode(IHTMLDOMNode *node)
{
	HRESULT hr;
	CbBSTR	obstr;
	long	type;		
	IHTMLDOMNode *child,*next;
	BSTR bstr;
	void*	pvoid;
	DWORD	size;
	struct _htmlnode*	nnode;
	WORD	ntype = TYPE_NONE;		// se define el tipo de nodo si es un nodo conocido se procesa


	node->get_nodeType(&type);	if (type == NODE_COMMENT)	return;

	node->get_nodeName(&bstr);
	obstr.Attach(bstr);
	if (wcscmp(bstr,L"INPUT") == 0) ntype = TYPE_INPUT;
	if (wcscmp(bstr,L"P") == 0) ntype = TYPE_P; 
	if ((wcscmp(bstr,L"LABEL") == 0) ||
		(wcscmp(bstr,L"SPAN") == 0) ||
		(wcscmp(bstr,L"A")	== 0)) ntype = TYPE_TEXT;
	if (wcscmp(bstr,L"H1") == 0) ntype = TYPE_H1;
	if (wcscmp(bstr,L"H2") == 0) ntype = TYPE_H2;
	if (wcscmp(bstr,L"H3") == 0) ntype = TYPE_H3;

	switch(ntype)
	{
	case TYPE_INPUT:
		nnode = _newNext(); if (nnode==NULL) return;
		nnode->type = ntype;
		nnode->firstAttr = getAttributes(node);
		nnode->type = TYPE_INPUT;
		return;
	case TYPE_P:
	case TYPE_TEXT:
	case TYPE_H1:
	case TYPE_H2:
	case TYPE_H3:
		{
			nnode = _newNext(); if (nnode==NULL) return;
			nnode->type = ntype;
			mpIMem->lock();
			pushText(node);
			mpIMem->lockCompact(&pvoid,&size);
			nnode->text = CbBSTR::toChar((LPWSTR)pvoid,size/2,mpIMem);
			mpIMem->lockFree();
			nnode->dwFlags = F_TEXT;
			break;
		}
	default:
		{
			// recorrer los nodos hijos
			node->get_firstChild(&child);
			while(child)
			{
				processNode(child);
				child->get_nextSibling(&next);
				child->Release();
				child = next;
			}
			break;
		}
	}
}

struct _htmlnode*	CHtmlData::_newNext()
{
	if (mfirstNode)
	{
		mpIMem->get(sizeof(*mlastNode),(void**)&mlastNode->next);
		mlastNode = mlastNode->next;
	}
	else
	{
		mpIMem->get(sizeof(*mfirstNode),(void**)&mfirstNode);
		mlastNode = mfirstNode;
	}
	memset(mlastNode,0,sizeof(*mlastNode));
	return mlastNode;
}

WCHAR*	CHtmlData::getAttribute(struct _htmlnode* node,WCHAR* name)
{
	struct _htmlAttr*	pAttr;
	for (pAttr = node->firstAttr;pAttr;)
	{
		if (wcscmp(pAttr->name,name) == 0) return pAttr->value;
		pAttr = pAttr->next;
	}
	return NULL;
}

struct _htmlnode* CHtmlData::nextNode(struct _htmlnode* node,WORD type)
{
	if (!node) node = mfirstNode;
	else
		node = node->next;
	while(node)
	{
		if (node->type == type) return node;
		node = node->next;
	}
	return NULL;
}
