// bVariant.cpp: implementation of the CbVariant class.
//
//////////////////////////////////////////////////////////////////////

#include "bVariant.h"
#include "utils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtils	gutils;

CbVariant::CbVariant()
{
	 VariantInit(&m_var);
}

CbVariant::~CbVariant()
{
	Release();
}

DWORD CbVariant::Release()
{
	char	*fnc_name = "CbVariant::Release";
	HRESULT	hr;
	hr = VariantClear(&m_var);	if (hr == S_OK) return ERR_OK;
	return LOG_TERROR ERR_FATAL,"VariantClear ... failed with code %u",hr);
}

VARIANT* CbVariant::GetNewPtr()
{
	Release();
	return &m_var;
}

VARIANT* CbVariant::GetPtr()
{
	return &m_var; 
}

DWORD CbVariant::GetCharString(char *str, WORD max_size)
{
	// intentar devolver el contenido de la variable
	*str = 0;
	switch (m_var.vt)
	{
	case VT_EMPTY:strcpy(str,"(empty)");break;
	case VT_NULL:strcpy(str,"(null)");break;
	case VT_I2:_snprintf(str,max_size,"%d",m_var.iVal);break;
	case VT_I4:_snprintf(str,max_size,"%d",m_var.iVal);break;
	case VT_UI1:_snprintf(str,max_size,"%u",m_var.bVal);break;
	case VT_R4:_snprintf(str,max_size,"%f",m_var.fltVal);break;
	case VT_BSTR: gutils.Char_Get(m_var.bstrVal,str,max_size);break;
	}
	return ERR_OK;

}
/*
			LONG lVal;
                SHORT iVal;
                FLOAT fltVal;
                DOUBLE dblVal;
                VARIANT_BOOL boolVal;
                _VARIANT_BOOL bool;
                SCODE scode;
                CY cyVal;
                DATE date;
                BSTR bstrVal;
                IUnknown __RPC_FAR *punkVal;
                IDispatch __RPC_FAR *pdispVal;
                SAFEARRAY __RPC_FAR *parray;
                BYTE __RPC_FAR *pbVal;
                SHORT __RPC_FAR *piVal;
                LONG __RPC_FAR *plVal;
                FLOAT __RPC_FAR *pfltVal;
                DOUBLE __RPC_FAR *pdblVal;
                VARIANT_BOOL __RPC_FAR *pboolVal;
                _VARIANT_BOOL __RPC_FAR *pbool;
                SCODE __RPC_FAR *pscode;
                CY __RPC_FAR *pcyVal;
                DATE __RPC_FAR *pdate;
                BSTR __RPC_FAR *pbstrVal;
                IUnknown __RPC_FAR *__RPC_FAR *ppunkVal;
                IDispatch __RPC_FAR *__RPC_FAR *ppdispVal;
                SAFEARRAY __RPC_FAR *__RPC_FAR *pparray;
                VARIANT __RPC_FAR *pvarVal;
                PVOID byref;
                CHAR cVal;
                USHORT uiVal;
                ULONG ulVal;
                INT intVal;
                UINT uintVal;
                DECIMAL __RPC_FAR *pdecVal;
                CHAR __RPC_FAR *pcVal;
                USHORT __RPC_FAR *puiVal;
                ULONG __RPC_FAR *pulVal;
                INT __RPC_FAR *pintVal;
                UINT __RPC_FAR *puintVal;


 *    LONG           VT_I4
 *    BYTE           VT_UI1
 *    SHORT          VT_I2
 *    FLOAT          VT_R4
 *    DOUBLE         VT_R8
 *    VARIANT_BOOL   VT_BOOL
 *    SCODE          VT_ERROR
 *    CY             VT_CY
 *    DATE           VT_DATE
 *    BSTR           VT_BSTR
 *    IUnknown *     VT_UNKNOWN
 *    IDispatch *    VT_DISPATCH
 *    SAFEARRAY *    VT_ARRAY
 *    BYTE *         VT_BYREF|VT_UI1
 *    SHORT *        VT_BYREF|VT_I2
 *    LONG *         VT_BYREF|VT_I4
 *    FLOAT *        VT_BYREF|VT_R4
 *    DOUBLE *       VT_BYREF|VT_R8
 *    VARIANT_BOOL * VT_BYREF|VT_BOOL
 *    SCODE *        VT_BYREF|VT_ERROR
 *    CY *           VT_BYREF|VT_CY
 *    DATE *         VT_BYREF|VT_DATE
 *    BSTR *         VT_BYREF|VT_BSTR
 *    IUnknown **    VT_BYREF|VT_UNKNOWN
 *    IDispatch **   VT_BYREF|VT_DISPATCH
 *    SAFEARRAY **   VT_BYREF|VT_ARRAY
 *    VARIANT *      VT_BYREF|VT_VARIANT
 *    PVOID          VT_BYREF (Generic ByRef)
 *    CHAR           VT_I1
 *    USHORT         VT_UI2
 *    ULONG          VT_UI4
 *    INT            VT_INT
 *    UINT           VT_UINT
 *    DECIMAL *      VT_BYREF|VT_DECIMAL
 *    CHAR *         VT_BYREF|VT_I1
 *    USHORT *       VT_BYREF|VT_UI2
 *    ULONG *        VT_BYREF|VT_UI4
 *    INT *          VT_BYREF|VT_INT
 *    UINT *         VT_BYREF|VT_UINT

*/