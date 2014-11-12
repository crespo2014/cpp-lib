
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the G30_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// G30_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef G30_EXPORTS
#define G30_API __declspec(dllexport)
#else
#define G30_API __declspec(dllimport)
#endif

// This class is exported from the G30.dll
class G30_API CG30 {
public:
	CG30(void);
	// TODO: add your methods here.
};

extern G30_API int nG30;

G30_API int fnG30(void);

