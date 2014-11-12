// JavaFromC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "..\inc_src\logclient.h"
#include "C:\j2sdk1.4.2_12\include\jni.h"

#define PATH_SEPARATOR ';' /* define it to be ':' on Solaris */
//#define USER_CLASSPATH "." /* where Prog.class is */
#define USER_CLASSPATH "c:\\jar" /* where Prog.class is */

int main(int argc, char* argv[])
{
	JNIEnv *env;
	JavaVM *jvm;
	jint res;
	jclass cls;
	jmethodID mid;
	jstring jstr;
	jclass stringClass;
	jobjectArray args;
	jobject	test;

	#ifdef JNI_VERSION_1_2
		JavaVMInitArgs vm_args;
		JavaVMOption options[1];
		options[0].optionString ="-Djava.class.path=" USER_CLASSPATH;
		vm_args.version = JNI_VERSION_1_2;
		vm_args.options = options;
		vm_args.nOptions = 1;
		vm_args.ignoreUnrecognized = JNI_TRUE;
	/* Create the Java VM */
		res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	#else
		JDK1_1InitArgs vm_args;
		char classpath[1024];
		vm_args.version = 0x00010001;
		JNI_GetDefaultJavaVMInitArgs(&vm_args);
		sprintf(classpath, "%s%c%s",
		vm_args.classpath, PATH_SEPARATOR, USER_CLASSPATH);
		vm_args.classpath = classpath;
	/* Create the Java VM */
		res = JNI_CreateJavaVM(&jvm, &env, &vm_args);
	#endif /* JNI_VERSION_1_2 */
	if (res < 0) {fprintf(stderr, "Can't create Java VM\n");return 0;}
	
	for (;;)
	{
		jmethodID init_id;
		jmethodID gn_id;

		
		char	*s="lester crespo";
		char	c_s[40];
		int		len = strlen(s);
		jchar	s1[30];
		jcharArray	carray;
		jcharArray 	carray1;

		cls = env->FindClass("CTest");
		if (cls == NULL) break;
		
		init_id = env->GetMethodID(cls,"<init>","()V");
		if (init_id == NULL) break;

		test = env->NewObject(cls,init_id);
		if (test == NULL) break;
		
		//env->CallVoidMethod(cls, init_id);

		mid = env->GetMethodID(cls,"PutName","([C)V");
		if (mid == NULL) break;

		gn_id = env->GetMethodID(cls,"Paco","([C)[C");
		if (gn_id == NULL) break;

		MultiByteToWideChar(CP_ACP,0,s,len,s1,sizeof(s1));
		carray = env->NewCharArray(len);
		env->SetCharArrayRegion(carray,0,len,s1);
		env->CallObjectMethod(test,mid, carray);
		
		carray1 = (jcharArray)env->CallObjectMethod(cls, gn_id,carray);
		int i = env->GetArrayLength(carray1);
		env->GetCharArrayRegion(carray1,0,i,s1);
		s1[i] = 0;

		WideCharToMultiByte(CP_ACP,0,s1,-1,SSIZE(c_s),NULL,NULL);


		env->DeleteLocalRef(test);
		env->DeleteLocalRef(carray1);
		env->DeleteLocalRef(carray1);

		/*
		mid = env->GetStaticMethodID(cls, "main","([Ljava/lang/String;)V");
		if (mid == NULL) break;
		
		jstr = env->NewStringUTF(" from C!");
		if (jstr == NULL) break;
		
		stringClass = env->FindClass("java/lang/String");
		args = env->NewObjectArray(1, stringClass, jstr);
		if (args == NULL) break;
		env->CallStaticVoidMethod(cls, mid, args);
		*/
		break;
	}
	if (env->ExceptionOccurred()) env->ExceptionDescribe();
	
	jvm->DestroyJavaVM();
	return 0;
}

