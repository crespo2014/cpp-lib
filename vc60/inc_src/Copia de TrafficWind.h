// TrafficWind.h: interface for the CTrafficWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAFFICWIND_H__0FCA989C_4129_432B_AC74_48EE90EB280F__INCLUDED_)
#define AFX_TRAFFICWIND_H__0FCA989C_4129_432B_AC74_48EE90EB280F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wind.h"
#include "LockEvent.h"
#include "VirtualMem.h"

#define SP0		7	// Cantidad de caracteres del tipo de bloque
#define SP1		1   // Cantidad de caracteres entre el tipo de bloque y el primer valor
#define SP2		1   // Cantidad de caracteres despues de cada valor
#define SP3		1	// Cantidad de espacios entre el ultimo byte y el primer ascii

#define SND_BUF 1	// Tipo de buffer
#define RCV_BUF 2
#define COM_BUF 3	//Comentario
#define END_BUF 4	//Tipo de buffer que todavia no se ha puesto

class CTrafficWind : public CWind,
					 private CLockEvent  
{
public:
	DWORD SaveBIN(HANDLE hFile);
	DWORD Release();
	DWORD AddComment(char* comment);
	DWORD AddReadBuffer(BYTE* buffer,DWORD dwsize);
	DWORD AddSendBuffer(BYTE* buffer,DWORD dwsize);
	DWORD Clear();
	DWORD Create_Window(int x,int y,int nWidth,int nHeight,HWND hWndParent);
	DWORD ShowLastBuffer();
	DWORD Initialize();
	CTrafficWind();
	~CTrafficWind();
private:
	DWORD GetBufferMetrics(BYTE bType,BYTE* bBytesRow,BYTE* bCharsByte);
	DWORD RowsToSize(BYTE btype,DWORD dwRows,DWORD* dwSize);
	DWORD Paint_Window(HDC hdc,PAINTSTRUCT Paint);
	DWORD GetBufferInfo(BYTE* lpbType,DWORD* lpdwSize);
	DWORD CalcRows(BYTE bType,DWORD dwSize,DWORD* dwRows);
	LRESULT OnVerticalScroll(WPARAM wParam, LPARAM lParam);
	DWORD GetWindowMetrics(WINDOW_METRICS *lpwindowmetrics);
	DWORD UpdateScroll();
	virtual LRESULT _stdcall OnWindProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);


//	CVirtualMemory	m_Buffer;
private:
	DWORD Paint();
	BYTE  m_bpr;
	DWORD m_Rows;		//Cantidad de columnas
	DWORD m_TopRow;
	BOOL	m_OnUpdateScrolls;	//Indica que los scroll deben ser actualizados
	
	// Medidas de las letras.
	long	m_fontHeight;
	long	m_fontWidth;
	HFONT	m_hFont;

	DWORD	m_MemIndex;
	
	CVirtualMem	m_Buffer;

};

#endif // !defined(AFX_TRAFFICWIND_H__0FCA989C_4129_432B_AC74_48EE90EB280F__INCLUDED_)
