// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LFC20_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LFC20_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LFC20_EXPORTS
// Se compila la DLL
#define LFC20_API __declspec(dllexport) 
#else
// Se compila el programa principal
#define LFC20_API __declspec(dllimport)
#endif

LFC20_API DWORD LFC20Init();