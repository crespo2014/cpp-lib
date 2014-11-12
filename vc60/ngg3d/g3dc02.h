// g3dc02.h: interface for the C3DDXViewGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G3DC02_H__8C2D2A86_0033_11D5_8D3A_00D0093D4380__INCLUDED_)
#define AFX_G3DC02_H__8C2D2A86_0033_11D5_8D3A_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "g3d.h" 

class G3D_API C3DDXViewGame  
{
public:
	DWORD CreateWnd();
	LRESULT WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	DWORD CreateDirectX();
	DWORD RegisterClass();
	DWORD Release();
	DWORD Initialize();
	C3DDXViewGame();
	virtual ~C3DDXViewGame();

};

#endif // !defined(AFX_G3DC02_H__8C2D2A86_0033_11D5_8D3A_00D0093D4380__INCLUDED_)
