#if !defined(AFX_COMMON_H__8A25A337_736D_448E_9A46_B3DD966441BF__INCLUDED_)
#define AFX_COMMON_H__8A25A337_736D_448E_9A46_B3DD966441BF__INCLUDED_

#include "unknwn.h."
#include "oledb.h"
#include "errorcodes.h"

struct _VARIANT{
	union {
		BYTE				bVal;		// VT_UI1.
		short				iVal;		// VT_I2.
		long				lVal;		// VT_I4.
		float				fltVal;		// VT_R4.
		double				dblVal;		// VT_R8.
		VARIANT_BOOL		boolVal;	// VT_BOOL.
		SCODE				scode;		// VT_ERROR.
		CY					cyVal;		// VT_CY.
		DATE				date;		// VT_DATE.
		BSTR				bstrVal;	// VT_BSTR.
		DECIMAL *			pdecVal;	// VT_BYREF|VT_DECIMAL.
		IUnknown *			punkVal;	// VT_UNKNOWN.
		IDispatch *			pdispVal;	// VT_DISPATCH.
		SAFEARRAY *			parray;		// VT_ARRAY|*.
		BYTE *				pbVal;		// VT_BYREF|VT_UI1.
		short *				piVal;		// VT_BYREF|VT_I2.
		long *				plVal;		// VT_BYREF|VT_I4.
		float *				pfltVal;	// VT_BYREF|VT_R4.
		double *			pdblVal;	// VT_BYREF|VT_R8.
		VARIANT_BOOL *		pboolVal;	// VT_BYREF|VT_BOOL.
		SCODE *				pscode;		// VT_BYREF|VT_ERROR.
		CY *				pcyVal;		// VT_BYREF|VT_CY.
		DATE *				pdate;		// VT_BYREF|VT_DATE.
		BSTR *				pbstrVal;	// VT_BYREF|VT_BSTR.
		IUnknown * *		ppunkVal;	// VT_BYREF|VT_UNKNOWN.
		IDispatch * *		ppdispVal;	// VT_BYREF|VT_DISPATCH.
		SAFEARRAY * *		pparray;	// VT_ARRAY|*.
		VARIANT *			pvarVal;	// VT_BYREF|VT_VARIANT.
		void *				byref;		// Generic ByRef.
		char				cVal;		// VT_I1.
		unsigned short		uiVal;		// VT_UI2.
		unsigned long		ulVal;		// VT_UI4.
		int					intVal;		// VT_INT.
		unsigned int		uintVal;	// VT_UINT.
		char *				pcVal;		// VT_BYREF|VT_I1.
		unsigned short *	puiVal;		// VT_BYREF|VT_UI2.
		unsigned long *     pulVal;		// VT_BYREF|VT_UI4.
		int *               pintVal;	// VT_BYREF|VT_INT.
		unsigned int *      puintVal;	// VT_BYREF|VT_UINT.
		DB_NUMERIC			numeric;	// DBTYPE_NUMERIC
		DBDATE				dbdate;		// DBTYPE_DBDATE
		DBTIME				dbtime;		// DBTYPE_DBTIME
		char				pzsVal[1];	// DBTYPE_STR
		
		};
};

class IIniFile
{
public:
	virtual DWORD _stdcall OnProcessParam(char* name,double val,void* lpParam)=0;
};

class IinfProcess  
{
public:
	virtual DWORD _stdcall OnStart()=0;
	virtual DWORD _stdcall OnNewSection(char* name)=0;	
	virtual DWORD _stdcall OnNewValue(char* name,char* value)=0;
	virtual DWORD _stdcall OnFinish()=0;
};

DWORD LoadIniFile(char* filename,IIniFile* lpIIniFile,void* lpParam);
DWORD ProcessInfBuffer(char* buffer,IinfProcess* lpInfProcess);
DWORD FileSizeToString(DWORD dwSize,char* str);
DWORD InitializeWinSock();
void* GetResource(char* lpName);
DWORD _stdcall From0x20To0x00(char *lpBuffer, DWORD dwIndex, BOOL bForward = false);
DWORD _stdcall GetIntValue(char* lpszStringVal,int* lpiVal);
DWORD _stdcall ProcessInfResource(char* lpszResorceName,IinfProcess* lpInfProcess);

#endif