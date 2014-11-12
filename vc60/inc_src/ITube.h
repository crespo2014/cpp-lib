// ITube.h: interface for the ITube class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITUBE_H__D92A7DF2_27E8_48B5_8368_E46DAEC70B7F__INCLUDED_)
#define AFX_ITUBE_H__D92A7DF2_27E8_48B5_8368_E46DAEC70B7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bobject.h"

class ITube  
{
public:
	virtual DWORD	Start() = 0;
	virtual DWORD	End() = 0;
	virtual DWORD	Push(BYTE b) = 0;
};

class toStdOut : public ITube
{
public:
	toStdOut() {};
	~toStdOut() {};
	virtual DWORD	Start() { return ERR_OK; };
	virtual DWORD	End()	{ return ERR_OK;};
	virtual DWORD	Push(BYTE b) { putchar(b); return ERR_OK; };
};

class toHex : public ITube
{
public:
	toHex(ITube	*pOutTube) { mpOut = pOutTube; };
	~toHex() {};
	virtual DWORD	Start() { return mpOut->Start(); };
	virtual DWORD	End()	{ return mpOut->End();	 };
	virtual DWORD	Push(BYTE b) 
	{
		const static char *tbl = "0123456789ABCDEF";
		if (mpOut->Push(tbl[b >> 4]) != ERR_OK) return ERR_FATAL;
		return mpOut->Push(tbl[b &0x0F]);
	};
private:
	ITube	*mpOut;
};

class fromHex : public ITube
{
public:
	fromHex(ITube	*pOutTube) { mpOut = pOutTube; };
	~fromHex() {};
	virtual DWORD	Start() 
	{
		mindex = 0;
		return mpOut->Start(); 
	};
	virtual DWORD	End()	
	{
		if (mindex != 0) return ERR_FATAL;
		return mpOut->End();	
	};
	virtual DWORD	Push(BYTE b) 
	{
		BYTE r;
		mcache[mindex++] = b;
		if (mindex == 2)
		{
			if ((mcache[0] >= '0') && (mcache[0] <= '9')) r = (BYTE)((mcache[0] - '0') << 4);
			else if ((mcache[0] >= 'A') && (mcache[0] <= 'F')) r = (BYTE)((mcache[0] - 'A' + 10) << 4);
			else if ((mcache[0] >= 'a') && (mcache[0] <= 'f')) r = (BYTE)((mcache[0] - 'a' + 10) << 4);
			else return ERR_FATAL;
			if ((mcache[1] >= '0') && (mcache[1] <= '9'))      r = (BYTE)(r + mcache[1] - '0');
			else if ((mcache[1] >= 'A') && (mcache[1] <= 'F')) r = (BYTE)(r + mcache[1] - 'A' + 10);
			else if ((mcache[1] >= 'a') && (mcache[1] <= 'f')) r = (BYTE)(r + mcache[1] - 'a' + 10);
			else return ERR_FATAL;
			mindex = 0;
			return mpOut->Push(r);
		}
		return ERR_OK;
	};
private:
	ITube	*mpOut;
	BYTE	mcache[2];
	BYTE	mindex;
};

#endif // !defined(AFX_ITUBE_H__D92A7DF2_27E8_48B5_8368_E46DAEC70B7F__INCLUDED_)
