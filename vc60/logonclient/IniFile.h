// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__2AC75F10_28D1_4183_9D47_B9D3D6F82E34__INCLUDED_)
#define AFX_INIFILE_H__2AC75F10_28D1_4183_9D47_B9D3D6F82E34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_inifile.h"

class CIniFile  
{
public:
	DWORD Release();
	DWORD GetKeyValue(char* section,char* key,char** value);
	DWORD SaveToFile(char* filepath);
	DWORD ReadFromFile(char* filepath) {return _inifileReadFromFile(&m_keys,filepath);}
	CIniFile(){};
	virtual ~CIniFile(){};
private:
	_INIFILE	m_keys;

};

#endif // !defined(AFX_INIFILE_H__2AC75F10_28D1_4183_9D47_B9D3D6F82E34__INCLUDED_)
