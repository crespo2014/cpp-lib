// ROBOT.h - include file for VxD ROBOT

#include <vtoolsc.h>

#define ROBOT_Major		1
#define ROBOT_Minor		0
#define ROBOT_DeviceID		UNDEFINED_DEVICE_ID
#define ROBOT_Init_Order	UNDEFINED_INIT_ORDER

BOOL __stdcall RTCInt_Handler(VMHANDLE hVM, IRQHANDLE hIRQ);

typedef struct StructCommand
{ 
	DWORD Message[5];  // incluye OnComand,OnRun
					  //Message,MotorNum,NewValue
	int Pos[6];
	DWORD dPos[6];
	BYTE dir[6];
	BYTE TablePtr[6];
	BYTE Moving[6];


} Command;

