// jniObject.h: interface for the CjniObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JNIOBJECT_H__C661C4F0_ED06_40E2_A230_4CE7830436E5__INCLUDED_)
#define AFX_JNIOBJECT_H__C661C4F0_ED06_40E2_A230_4CE7830436E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "jnijvm.h"

class CjniObject : public CbObject  
{
public:
	void Delete();
	CjniObject();
	virtual ~CjniObject();
	void Attach(jobject	pjobj)	{ Delete(); m_jobj = pjobj; }
	void Detach()				{ m_jobj = NULL; }
	jobject		get_jo()		{ return m_jobj; };
protected:
	jobject		m_jobj;		// ya es un puntero a un objeto

};

class CjniObjArray	: public CjniObject
{
public:
	CjniObjArray() {};
	virtual ~CjniObjArray() {};
	jobjectArray* get_optr() 
	{ 
		Delete(); 
		return (jobjectArray*)m_jobj; 
	};
	jobjectArray get_o() 
	{ 
		return (jobjectArray)m_jobj; 
	};
};

class CjniString  : public CjniObject
{
public:
	CjniString() {};
	virtual ~CjniString()  {};
	jstring* get_optr() 
	{ 
		Delete(); 
		return (jstring*)m_jobj; 
	};
	jstring get_o() 
	{ 
		return (jstring)m_jobj; 
	};
};



#endif // !defined(AFX_JNIOBJECT_H__C661C4F0_ED06_40E2_A230_4CE7830436E5__INCLUDED_)
