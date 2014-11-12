// jniJVM.h: interface for the CjniJVM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JNIJVM_H__F64828C0_FD7A_41D8_A49F_1FBDF02692DB__INCLUDED_)
#define AFX_JNIJVM_H__F64828C0_FD7A_41D8_A49F_1FBDF02692DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "jdk\v1.5.0_07\jni.h"
#include "bobject.h"
#include "utils.h"

class CjniJVM  : public CbObject
{
public:
	DWORD CheckException();
	DWORD NewObjectArray(jsize len, jclass jvc, jobject jvo_init,jobjectArray  *pjobj);
	DWORD CreateJVM(JavaVMOption* opt,WORD opt_count);
	DWORD GetUTFStringObj(char *cstr,jstring* pjstring);
	DWORD NewObject(jclass* pjclass,jmethodID fnc_const,jobject* pjobj);
	DWORD FindClass(char* class_name,jclass* pjclass);
	DWORD AttachCurrentThread();
	DWORD GetStaticMethodID(jclass jvclass, jmethodID *mID, char *name, char *signature);
	DWORD GetMethodID(jclass jvclass,jmethodID *mID, char *name, char *signature);
	DWORD GetCharString(jstring cjstring,char* str,WORD max_size);
	DWORD GetStringObj(char* cstr,jstring* pjstring);
	DWORD UnLoadJVM();
	DWORD LoadJVM(char *jarpath);

	void Release();
	void Clear();
	CjniJVM();
	virtual ~CjniJVM();

	JNIEnv *m_env;
	BOOL	m_descException;
	BOOL	m_jniDebug;

private:
	JavaVM *m_jvm;
	
};

extern CjniJVM JVM;

#endif // !defined(AFX_JNIJVM_H__F64828C0_FD7A_41D8_A49F_1FBDF02692DB__INCLUDED_)
