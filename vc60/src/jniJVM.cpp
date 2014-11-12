// jniJVM.cpp: implementation of the CjniJVM class.
//
//////////////////////////////////////////////////////////////////////

#include "jniJVM.h"
#include "bstr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CjniJVM JVM;

#define JVM_HANDLE_CHECK if (m_jvm == NULL) return LOG_TERROR ERR_HANDLE,"Invalid handle jvm is null");

CjniJVM::CjniJVM()
{
	m_ver = "Class CjniJVM " CLASS_VER;
	m_descException = false;
	m_jniDebug = false;
	Clear();
}

CjniJVM::~CjniJVM()
{
	Release();
}

/*
	sprintf(classpath, "-Djava.class.path=%s", getenv("CLASSPATH"));
		options[0].optionString = classpath;
		options[1].optionString = "-Djava.compiler=NONE";

		sprintf(OrbBuffPort,"-DgaRoot=%s",JNIRSSData.agentePath);
		options[2].optionString = OrbBuffPort;

		sprintf(library, "-Djava.library.path=%s", getenv("Path"));
		options[3].optionString = library;
		options[4].optionString = "-Xms128M -Xmx128M";
		
		writeLog(0,fname,library);
		vm_args.version = JNI_VERSION_1_2;
		vm_args.options = options;
		vm_args.nOptions = 4; 
		vm_args.ignoreUnrecognized = TRUE;//JNI_FALSE;
		*/

DWORD CjniJVM::LoadJVM(char *jarpath)
{
	if (m_jvm != NULL) return ERR_OK;	// ya esta creada la clase
	char	path[1024];
	char	*fnc_name = "CjniJVM::LoadJVM";
	WORD	count;

	JavaVMOption options[5];
	memset(options,0,sizeof(options));

	_snprintf(path,sizeof(path)-1,"-Djava.class.path=%s",jarpath);
	options[0].optionString = path;
	options[1].optionString = "-verbose:jni";		//muestra trazas en consola
	options[2].optionString = "-Djava.compiler=NONE";
	options[3].optionString = "-Xcheck:jni";		// print JNI-related messages
	options[4].optionString = "-Xdebug";
	if (m_jniDebug) 
		count = 5;
	else
		count = 1;
	return CreateJVM(options,count);
	/*

	

#ifdef JNI_VERSION_1_4
		JavaVMInitArgs vm_args;

	options[0].optionString = path;
	options[1].optionString = "-verbose:jni";		//muestra trazas en consola
	options[2].optionString = "-Djava.compiler=NONE";
	options[3].optionString = "-Xcheck:jni";		// print JNI-related messages
	options[4].optionString = "-Xdebug";
	vm_args.nOptions = 1;
	if (m_jniDebug) vm_args.nOptions = 5;
	vm_args.options = options;
	vm_args.version = JNI_VERSION_1_4;
	vm_args.ignoreUnrecognized = JNI_FALSE;
	res = JNI_CreateJavaVM(&m_jvm, (void**)&m_env, &vm_args);

	
	// options[1].optionString = "-Djava.classpath=.";
	// options[2].optionString = "-verbose:jni";
	

#elif defined JNI_VERSION_1_2
	JavaVMInitArgs vm_args;
	JavaVMOption options[5];

		_snprintf(path,sizeof(path)-1,"%s%s","-Djava.class.path=",jarpath);
		options[0].optionString = path;
	options[1].optionString = "-verbose:jni";
	vm_args.nOptions = 1;
	vm_args.options = options;
		vm_args.version = JNI_VERSION_1_2;
	vm_args.ignoreUnrecognized = JNI_FALSE;
		res = JNI_CreateJavaVM(&m_jvm, (void**)&m_env, &vm_args);
	#else
		JDK1_1InitArgs vm_args;

		vm_args.version = 0x00010001;
		JNI_GetDefaultJavaVMInitArgs(&vm_args);
	_snprintf(path,sizeof(path)-1, "%s%c%s",vm_args.classpath, PATH_SEPARATOR, jarpath);
		vm_args.classpath = path;
	res = JNI_CreateJavaVM(&m_jvm, &m_env, &vm_args);
#endif

	LOG_TINFO "Starting JVM (%s)",path);
	if (res < 0) return LOG_TERROR ERR_FATAL,"Failed to load JVM ver = %X with jarpath = <%s>",vm_args.version,jarpath);
	return ERR_OK;
	*/
}

DWORD CjniJVM::UnLoadJVM()
{
	char	*fnc_name = "CjniJVM::UnLoadJVM";

	if (m_jvm == NULL) return ERR_OK;
	FNC_START
	//m_jvm->DestroyJavaVM();
	Clear();
	FNC_END
	return ERR_OK;
}

void CjniJVM::Clear()
{
	m_env = NULL;
	m_jvm = NULL;
}

DWORD CjniJVM::GetStringObj(char *cstr,jstring* pjstring)
{
	char	*fnc_name = "CjniJVM::GetStringObj";
	CbBSTR	bstr;

	JVM_HANDLE_CHECK

	bstr.setLog(getLog());
	if (bstr.SetCharString(cstr) != ERR_OK) 
	{ 
		LOG_TSTACK
		return NULL;
	}
	*pjstring = JVM.m_env->NewString(bstr._BSTR(),strlen(cstr));
	if ((CheckException() != ERR_OK) || (*pjstring == NULL)) return LOG_TERROR ERR_FATAL,"NewString failed ");

	return ERR_OK;
}

DWORD CjniJVM::GetCharString(jstring cjstring, char *str, WORD max_size)
{
	jint len;
	jchar* u_str;
	char	*fnc_name = "CjniJVM::GetCharString";

	JVM_HANDLE_CHECK

	CUtils	gutils;
	gutils.setLog(getLog());

	str[0] = 0;
	
	len = m_env->GetStringLength(cjstring); 
	if (CheckException() != ERR_OK)  return LOG_TERROR ERR_FATAL," GetStringLength failed ");
	
	if (len + 1 > max_size)
	{
		_snprintf(str,max_size,"##TRUNCATE##");
		return LOG_TERROR ERR_FATAL,"%s ... char string has been truncate",fnc_name);
	}
	
	u_str = (jchar*)m_env->GetStringChars(cjstring,NULL);
	if (CheckException() != ERR_OK)  return LOG_TERROR ERR_FATAL," GetStringChars failed ");

	gutils.Char_Get(u_str,str,max_size,len);

	m_env->ReleaseStringChars(cjstring,u_str);
	if (CheckException() != ERR_OK)  return LOG_TERROR ERR_FATAL," ReleaseStringChars failed ");
	return ERR_OK;
	
}

DWORD CjniJVM::GetMethodID(jclass jvclass, jmethodID *mID, char *name, char *signature)
{
	char	*fnc_name = "CjniJVM::GetMethodID";

	JVM_HANDLE_CHECK

	*mID = m_env->GetMethodID(jvclass,name,signature);

	if ((CheckException() != ERR_OK) || (*mID == NULL))  	return LOG_TERROR ERR_FATAL," Failed to get method = '%s' Signature = '%s'",name,signature);
	return ERR_OK;
}

DWORD CjniJVM::GetStaticMethodID(jclass jvclass, jmethodID *mID, char *name, char *signature)
{
	char	*fnc_name = "CjniJVM::GetStaticMethodID";

	JVM_HANDLE_CHECK

	*mID = m_env->GetStaticMethodID(jvclass,name,signature);

	if ((CheckException() != ERR_OK) || (*mID == NULL)) return LOG_TERROR ERR_FATAL,"failed to get static method = '%s' Signature = '%s'",name,signature);
	return ERR_OK;;
}

void CjniJVM::Release()
{
	UnLoadJVM();
}

DWORD CjniJVM::AttachCurrentThread()
{
	char	*fnc_name = "CjniJVM::AttachCurrentThread";
	int	ir;
	ir = m_jvm->AttachCurrentThread((void**)&m_env,NULL);

	if ((CheckException() != ERR_OK) || (ir != 0))  return LOG_TERROR ERR_FATAL,"AttachCurrentThread ... failed");
	return ERR_OK;
}

DWORD CjniJVM::FindClass(char *class_name, jclass *pjclass)
{
	char	*fnc_name = "CjniJVM::FindClass";

	JVM_HANDLE_CHECK
	
	*pjclass = JVM.m_env->FindClass(class_name);

	if ((CheckException() != ERR_OK) || (*pjclass == NULL)) return LOG_TERROR ERR_FATAL," failed to get class '%s'",class_name);
	return ERR_OK;
}


 //NewObjectArray(jsize len, jclass jvc, jobject jvo_init,jobjectArray  *pjobj);


DWORD CjniJVM::NewObject(jclass* pjclass, jmethodID fnc_const,jobject* pjobj)
{
	char *fnc_name = "CjniJVM::NewObject";

	JVM_HANDLE_CHECK

	*pjobj = m_env->NewObject(*pjclass,fnc_const);

	if ((CheckException() != ERR_OK) || (*pjobj == NULL)) return LOG_TERROR ERR_FATAL,"NewObject failed ");

	return ERR_OK;
}

DWORD CjniJVM::GetUTFStringObj(char *cstr,jstring* pjstring)
{
	char	*fnc_name = "CjniJVM::GetUTFStringObj";

	JVM_HANDLE_CHECK

	*pjstring = m_env->NewStringUTF(cstr);

	if ((CheckException() != ERR_OK) || (*pjstring == NULL)) return LOG_TERROR ERR_FATAL,"NewStringUTF failed for '%s'",cstr);
	return ERR_OK;
}

DWORD CjniJVM::CreateJVM(JavaVMOption *opt, WORD opt_count)
{
	if (m_jvm != NULL) return ERR_OK;	// ya esta creada la clase
	jint	res;
	int		i;
	char	*fnc_name = "CjniJVM::CreateJVM";

	FNC_START

	JavaVMInitArgs vm_args;

#ifdef JNI_VERSION_1_4

	vm_args.nOptions = opt_count;
	vm_args.options = opt;
	vm_args.version = JNI_VERSION_1_4;
	vm_args.ignoreUnrecognized = JNI_FALSE;
	res = JNI_CreateJavaVM(&m_jvm, (void**)&m_env, &vm_args);

#elif defined JNI_VERSION_1_2

	vm_args.nOptions = opt_count;
	vm_args.options = opt;
	vm_args.version = JNI_VERSION_1_2;
	vm_args.ignoreUnrecognized = JNI_FALSE;
	res = JNI_CreateJavaVM(&m_jvm, (void**)&m_env, &vm_args);
#else
	/*
	JDK1_1InitArgs vm_args;
	vm_args.version = 0x00010001;
	JNI_GetDefaultJavaVMInitArgs(&vm_args);
	_snprintf(path,sizeof(path)-1, "%s%c%s",vm_args.classpath, PATH_SEPARATOR, jarpath);
	vm_args.classpath = path;
	res = JNI_CreateJavaVM(&m_jvm, &m_env, &vm_args);
	*/
	res = -1;
#endif
	if (res < 0) 
	{
		LOG_TERROR ERR_FATAL,"Options values");
		for (i=0;i<opt_count;i++)
		{
			LOG_TERROR ERR_FATAL,"[%d] = '%s'",i,opt[i].optionString);
		}
		return LOG_TERROR ERR_FATAL,"Failed to load JVM ver = %X",vm_args.version);
	}
	LOG_TINFO "Started JVM");
	return ERR_OK;

}

DWORD CjniJVM::NewObjectArray(jsize len, jclass jvc, jobject jvo_init, jobjectArray *pjobj)
{
	char *fnc_name = "CjniJVM::NewObjectArray";

	JVM_HANDLE_CHECK

	*pjobj = m_env->NewObjectArray(len,jvc,jvo_init);

	if ((CheckException() != ERR_OK) || (*pjobj == NULL)) return LOG_TERROR ERR_FATAL,"NewObjectArray failed ");

	return ERR_OK;

}

DWORD CjniJVM::CheckException()
{
	char *fnc_name = "CjniJVM::CheckException";

	JVM_HANDLE_CHECK

	if (m_env->ExceptionOccurred())
	{
		if (m_descException) JVM.m_env->ExceptionDescribe();
		m_env->ExceptionClear();
		return ERR_FATAL;
	}
	return ERR_OK;
}
