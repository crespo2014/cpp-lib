// jniJVM.h: interface for the CjniJVM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JNIJVM_H__F64828C0_FD7A_41D8_A49F_1FBDF02692DB__INCLUDED_)
#define AFX_JNIJVM_H__F64828C0_FD7A_41D8_A49F_1FBDF02692DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "C:\j2sdk1.4.2_12\include\jni.h"
#include "bobject.h"
#include "utils.h"

class CjniJVM  
{
public:
	void Release();
	BOOL	GetStaticMethodID(jclass jvclass, jmethodID *mID, char *name, char *signature);
	BOOL	GetMethodID(jclass jvclass,jmethodID *mID, char *name, char *signature);
	char*	GetErrorStr(){return m_err_msg;};
	DWORD GetCharString(jstring cjstring,char* str,WORD max_size);
	jstring GetStringObj(char* cstr);
	void Clear();
	DWORD UnLoadJVM();
	DWORD LoadJVM(char *jarpath);
	CjniJVM();
	virtual ~CjniJVM();

	JNIEnv *m_env;

private:
	JavaVM *m_jvm;
	char	m_err_msg[500];
};

extern CjniJVM JVM;

#endif // !defined(AFX_JNIJVM_H__F64828C0_FD7A_41D8_A49F_1FBDF02692DB__INCLUDED_)
