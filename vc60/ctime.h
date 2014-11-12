// ctime.h: interface for the ctime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTIME_H__3BF661F4_BC12_4337_BB9E_7DE71EB00B5E__INCLUDED_)
#define AFX_CTIME_H__3BF661F4_BC12_4337_BB9E_7DE71EB00B5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h"
#include "itext.h"
#include "iformat.h"

#define tfmt_max 	35		// maxima canidad de item a almacenar

class ctime;

// estructura de parseo
struct _tfmt_item
{
	BYTE idx;		// indice en la tabal
	BYTE scount;	// cantidad de caracteres estaticos que le precede
};


class ctime
{
public:
	void getf(struct _char_buff * buffer,IFormat *pformat);
	void updatetime();
	DWORD set_format(const char* fmt,IFormat *pformat);
	ctime();
	~ctime();
	
private:
	static DWORD getTickCount() { return GetTickCount(); };

	BYTE	mstext_start;	// cuanto texto estatico hay antes del primer formato
	char	mfmt_stext[50];	// texto estatico
	WORD	mfmt_count;		// cantidad de items de formato
	struct _tfmt_item	mfmt_item[tfmt_max];	// lista de patrones a aplicar
	SYSTEMTIME mdate;
};

#endif // !defined(AFX_CTIME_H__3BF661F4_BC12_4337_BB9E_7DE71EB00B5E__INCLUDED_)
