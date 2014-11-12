// jniJVM.cpp: implementation of the CjniJVM class.
//
//////////////////////////////////////////////////////////////////////

#include "jniJVM.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CjniJVM JVM;

CjniJVM::CjniJVM()
{
	Clear();
}

CjniJVM::~CjniJVM()
{
	Release();
}

DWORD CjniJVM::LoadJVM(char *jarpath)
{
	if (m_jvm != NULL) return ERR_OK;	// ya esta creada la clase
	char	path[1024];
	jint	res;

	#ifdef JNI_VERSION_1_2
		JavaVMInitArgs vm_args;
		JavaVMOption options[1];
		sprintf(path,"%s%s","-Djava.class.path=",jarpath);
		options[0].optionString = path;
	//	glog.Log(path);
		//options[0].optionString ="-Djava.class.path=" jarpath;
		vm_args.version = JNI_VERSION_1_2;
		vm_args.options = options;
		vm_args.nOptions = 1;
		vm_args.ignoreUnrecognized = JNI_TRUE;
	/* Create the Java VM */
		res = JNI_CreateJavaVM(&m_jvm, (void**)&m_env, &vm_args);
	#else
		JDK1_1InitArgs vm_args;
		char classpath[1024];
		vm_args.version = 0x00010001;
		JNI_GetDefaultJavaVMInitArgs(&vm_args);
		sprintf(classpath, "%s%c%s",
		vm_args.classpath, PATH_SEPARATOR, USER_CLASSPATH);
		vm_args.classpath = classpath;
	/* Create the Java VM */
		res = JNI_CreateJavaVM(&jvm, &m_env, &vm_args);
	#endif /* JNI_VERSION_1_2 */
	if (res < 0) 
	{
		_snprintf(SSIZE(m_err_msg),"CjniJVM::LoadJVM .. failed to load JVM with jarpath = <%s>",jarpath);
		return ERR_FATAL;
	}
	return ERR_OK;
}

DWORD CjniJVM::UnLoadJVM()
{
	if (m_jvm == NULL) return ERR_OK;
	glog._log(LOG_ERROR,"CjniJVM::UnLoadJVM");
	m_jvm->DestroyJavaVM();
	Clear();
	return ERR_OK;
}

void CjniJVM::Clear()
{
	m_env = NULL;
	m_jvm = NULL;
}

jstring CjniJVM::GetStringObj(char *cstr)
{
	jstring	jni_string;
	BSTR bstr;
	bstr = glog.GetBSTR(cstr);
	if (bstr == NULL) return NULL;
	jni_string = JVM.m_env->NewString(bstr,strlen(cstr));
	SysFreeString(bstr);
	return jni_string;
}

DWORD CjniJVM::GetCharString(jstring cjstring, char *str, WORD max_size)
{
	jint len;
	jchar* u_str;
	char	*msg;

	str[0] = 0;
	for (;;)
	{
		msg = "m_env->GetStringLength(cjstring)";
		len = m_env->GetStringLength(cjstring); if (m_env->ExceptionOccurred()) break;
		if (len + 1 > max_size)
		{
			glog.log_strings(LOG_ERROR,"CjniJVM::GetCharString ... char string has been truncate");
			_snprintf(str,max_size,"##TRUNCATE##");
			return ERR_FATAL;				
		}
		msg = "m_env->GetStringChars(cjstring,NULL)";
		u_str = (jchar*)m_env->GetStringChars(cjstring,NULL);if (m_env->ExceptionOccurred()) break;
		gutils.Char_Get(u_str,str,max_size,len);
		msg = "m_env->ReleaseStringChars(u_str);";
		m_env->ReleaseStringChars(cjstring,u_str);if (m_env->ExceptionOccurred()) break;
		return ERR_OK;
	}
	if (JVM.m_env->ExceptionOccurred()) JVM.m_env->ExceptionDescribe();
	_snprintf(SSIZE(m_err_msg),"CjniJVM::GetCharString ... failed <%s>",msg);
	return ERR_FATAL;
}

BOOL CjniJVM::GetMethodID(jclass jvclass, jmethodID *mID, char *name, char *signature)
{
	*mID = m_env->GetMethodID(jvclass,name,signature);
	if (*mID != NULL) return true;
	_snprintf(SSIZE(m_err_msg),"CjniJVM::GetMethodID ... failed for method = '%s' Signature = '%s'",name,signature);
	return false;
}

BOOL CjniJVM::GetStaticMethodID(jclass jvclass, jmethodID *mID, char *name, char *signature)
{
	*mID = m_env->GetStaticMethodID(jvclass,name,signature);
	if (*mID != NULL) return true;
	_snprintf(SSIZE(m_err_msg),"CjniJVM::GetStaticMethodID ... failed for method = '%s' Signature = '%s'",name,signature);
	return false;
}

void CjniJVM::Release()
{
	UnLoadJVM();
}
