
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SIALDAP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SIALDAP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SIALDAP_EXPORTS
#define SIALDAP_API __declspec(dllexport)
#else
#define SIALDAP_API __declspec(dllimport)
#endif

// Header file for class C_Entry
#include "Entry.hpp"


// Header file for class C_Directory
#include "Directory.hpp" 

/////////////////////////////////////////////////////////
// EXAMPLES
/////////////////////////////////////////////////////////

// This class is exported from the SIALDAP.dll
//class SIALDAP_API CSIALDAP {
//public:
//	CSIALDAP(void);
//	// TODO: add your methods here.
//};

//extern SIALDAP_API int nSIALDAP;

//SIALDAP_API int fnSIALDAP(void);