// AJ_4270.h: interface for the CAJ_4270 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AJ_4270_H__E681FE87_FF42_4603_AF8C_4A6F93515589__INCLUDED_)
#define AFX_AJ_4270_H__E681FE87_FF42_4603_AF8C_4A6F93515589__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\LabDevice.h"

#define MAX_BLOCKSIZE   80

class CAJ_4270 : public CLabDevice
{

	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD _stdcall AddAnalysis();
	DWORD ResetStatus();
	DWORD ProcessBlock();

	bool	m_onPatient;

	BYTE	m_status;			// Estado de la maquina de estados
	char	m_block[MAX_BLOCKSIZE];
	BYTE	m_blockIndex;			// Proxima posicion a escribir en el bloque
	BYTE	m_blockSize;			// Maximo tamaño que debe tomar el bloque

public:
	CAJ_4270();
	virtual ~CAJ_4270();
};

#endif // !defined(AFX_AJ_4270_H__E681FE87_FF42_4603_AF8C_4A6F93515589__INCLUDED_)
