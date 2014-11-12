// ROBOT.c - main module for VxD ROBOT

#define   DEVICE_MAIN
#include  "robot.h"
#undef    DEVICE_MAIN

#include  "cmosio.h"
// Variables globales

VPICD_HWInt_THUNK RTCInt_Thunk;	// Thunk para la interrupcion

IRQHANDLE RTCIRQHandle;			// Handle for virtual IRQ
BYTE SavedStatusRegisterA;		// Saved RTC configuration register
BYTE SavedStatusRegisterB;		// Saved RTC configuration register

// Variables usadas para el movimiento del Robot
BYTE Tabla[9]={10,8,9,1,5,4,6,2,0};
BYTE Value[6];
Command Operacion;             // estructura para transferencia de comandos
BYTE i;

Declare_Virtual_Device(ROBOT)

VOID __cdecl PM_Api_Handler(VMHANDLE hVM, PCLIENT_STRUCT pcrs)
{
}

DefineControlHandler(SYS_DYNAMIC_DEVICE_INIT, OnSysDynamicDeviceInit);
DefineControlHandler(SYS_DYNAMIC_DEVICE_EXIT, OnSysDynamicDeviceExit);
DefineControlHandler(W32_DEVICEIOCONTROL, OnW32Deviceiocontrol);

BOOL __cdecl ControlDispatcher(
	DWORD dwControlMessage,
	DWORD EBX,
	DWORD EDX,
	DWORD ESI,
	DWORD EDI,
	DWORD ECX)
{
	START_CONTROL_DISPATCH

		ON_SYS_DYNAMIC_DEVICE_INIT(OnSysDynamicDeviceInit);
		ON_SYS_DYNAMIC_DEVICE_EXIT(OnSysDynamicDeviceExit);
		ON_W32_DEVICEIOCONTROL(OnW32Deviceiocontrol);

	END_CONTROL_DISPATCH

	return TRUE;
}
BOOL OnSysDynamicDeviceInit()
{
	// Variables temporales
	BYTE statreg;
	// Estructura a transferir para virtuallizar la IRQ
	struct VPICD_IRQ_Descriptor IRQdesc;	

	memset(&Operacion.Pos,0,6*sizeof(int));
	memset(&Operacion.Moving,0,6);
	memset(&Operacion.dir,1,6);
	memset(&Operacion.dPos,0,6*sizeof(DWORD));
	memset(&Operacion.TablePtr,0,6);

	// Llenado de la estructura
	IRQdesc.VID_IRQ_Number = 8;	    // IRQ8 CMOS
	IRQdesc.VID_Options = 0;		// reserved

	IRQdesc.VID_Hw_Int_Proc =		// Habilitacion y transferencia del Thunk
		(DWORD)VPICD_Thunk_HWInt(RTCInt_Handler, &RTCInt_Thunk);

	IRQdesc.VID_EOI_Proc = 0;
	IRQdesc.VID_Virt_Int_Proc = 0;
	IRQdesc.VID_Mask_Change_Proc = 0;
	IRQdesc.VID_IRET_Proc = 0;

	// Sin informacion
	IRQdesc.VID_IRET_Time_Out = 500;

	// Virtualizar IRQ y recoger handle
	RTCIRQHandle = VPICD_Virtualize_IRQ(&IRQdesc);
	if (RTCIRQHandle == 0)
		return FALSE;			// failed to virtualize

    // Salvar registros de la CMOS
	SavedStatusRegisterA = ReadCMOS(STATREG_A);
	SavedStatusRegisterB = ReadCMOS(STATREG_B);

	// Desmarcar la IRQ para que funcione
	VPICD_Physically_Unmask(RTCIRQHandle);
	return TRUE;
}

BOOL OnSysDynamicDeviceExit()
{
	
	// Recuperacion de registros
	WriteCMOS(STATREG_A, SavedStatusRegisterA);
	WriteCMOS(STATREG_B, SavedStatusRegisterB);

	// Marcar IRQ para que otros la usen
	VPICD_Physically_Mask(RTCIRQHandle);

	// Desvirtualizacion de la IRQ
	if (RTCIRQHandle) 
	  VPICD_Force_Default_Behavior(RTCIRQHandle);
	
	return TRUE;
}

DWORD OnW32Deviceiocontrol(PIOCTLPARAMS p)
{
	BYTE statreg;
	PVOID  *temp;
	switch(p->dioc_IOCtlCode)
	{
	case 0x8000:
		{
			Operacion.Message[1]=TRUE;  //OnRun
			temp=p->dioc_InBuf;
			temp[0]=Operacion.dPos;
			temp[1]=Operacion.Pos;
			temp[2]=Operacion.Message;

     		// Frecuencia de tiempo
			statreg = (SavedStatusRegisterA & ~0xF) | (p->dioc_cbInBuf & 0xF);
			WriteCMOS(STATREG_A, statreg);
			// Habilitar generacion de interrupciones
			statreg = ReadCMOS(STATREG_B);
			statreg |= ENABLE_INTERRUPT;
			WriteCMOS(STATREG_B, statreg);
			ReadCMOS(STATREG_C);
			break;
		}
	}
	return 0;
}

BOOL __stdcall RTCInt_Handler(VMHANDLE hVM, IRQHANDLE hIRQ)
{
	if (Operacion.Message[0])
	{
		switch (Operacion.Message[2])
		{
		case 1:
			{
				Operacion.Pos[Operacion.Message[3]]=Operacion.Message[4];
				break;
			}
		case 2:
			{
				Operacion.dir[Operacion.Message[3]]=Operacion.Message[4];
				break;
			}
		case 3:
			{
				Operacion.dPos[Operacion.Message[3]]=Operacion.Message[4];
				break;
			}
		case 4:
			{
				switch (Operacion.Message[4])
				{
				case 0:
					{
						Operacion.Moving[Operacion.Message[3]]=0;
						break;
					}
				case 1:
					{
						Operacion.Moving[Operacion.Message[3]]=1;
						Operacion.dir[Operacion.Message[3]]=0;
						break;
					}
				case 2:
					{
						Operacion.Moving[Operacion.Message[3]]=1;
						Operacion.dir[Operacion.Message[3]]=1;
						break;
					}
				}
				break;
			}
		}  // find del switch 
		Operacion.Message[0]=FALSE;
	}
	
	for (i=0;i<6;i++)
	{
		if (Operacion.Moving[i] | !(Operacion.dPos[i] ==0) )
		{
			if (Operacion.dir[i]) 
			{   // Direccion positiva
				if (Operacion.TablePtr[i]==7) 
				{   // Se llego al tope de la tabla
					Operacion.TablePtr[i]=0;
					Operacion.Pos[i]++;
				}
				else Operacion.TablePtr[i]++;
			}
			else 
			{   // Direccion negativa
				if (Operacion.TablePtr[i]==0)
				{
					Operacion.TablePtr[i]=7;
					Operacion.Pos[i]--;
				}
				else Operacion.TablePtr[i]--;
			}
			Value[i]=Tabla[Operacion.TablePtr[i]];
			if (!Operacion.Moving[i])
				if (Operacion.TablePtr[i]==0)
					Operacion.dPos[i]--;
		} else
			Value[i]=0;
	} // fin del ciclo 
	// Salidas de los datos a la tarjeta
	i=Value[0]+Value[1]*16;
	_asm
	{
		mov dx,0x378;
		mov al,i;
		out dx,al;
		out dx,al;
		mov dx,0x37A;
		mov al,0x0b;
		out dx,al;
		out dx,al;
		mov al,0x04;
		out dx,al;
		out dx,al;
	};
	
	i=Value[2]+Value[3]*16;
	_asm
	{
		mov dx,0x378;
		mov al,i;
		out dx,al;
		out dx,al;
		mov dx,0x37A;
		mov al,0x0f;
		out dx,al;
		out dx,al;
		mov al,0x07;
		out dx,al;
		out dx,al;
	};
	
	
	i=Value[4]+Value[5]*16;
	_asm
	{
		mov dx,0x378;
		mov al,i;
		out dx,al;
		out dx,al;
		mov dx,0x37A;
		mov al,0x03;
		out dx,al;
		out dx,al;
		mov al,0x07;
		out dx,al;
		out dx,al;
	};
	ReadCMOS(STATREG_C);		   // Desmarcar la IRQ 
	VPICD_Phys_EOI(hIRQ);  // tell VPICD to clear the interrupt
	return TRUE;	       // thunk will clear carry
}

