// Device.cpp: implementation of the CDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Device.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDevice::CDevice()
{
	ThreadParams.m_Status=0;
	m_hEvent1=NULL;
	m_hEvent2=NULL;
	m_hEvent3=NULL;
	m_DeviceOpen=false;
	m_DeviceAck=false;
}

CDevice::~CDevice()
{
	Close();
}

DWORD CDevice::InitDevice(CWnd* pCWnd)
{
    CListBox* pLB=(CListBox*)pCWnd;
	ThreadParams.m_ListBox=pLB;
	pLB->AddString("Initializing ...");
	if (!m_OnOpen)
	{
		m_TempError=OpenComm();
		if (m_TempError!=0)
		{
			pLB->AddString("Opening Port ...Failed");
			return m_TempError;
		}
	}
	pLB->AddString("Opening Port ...Ok");
	m_TempError=ConfigComm();
	if (m_TempError!=0)
	{
		pLB->AddString("Config Port ...Failed");
		return m_TempError;
	} 
	pLB->AddString("Config Port ...Ok");

	if (!m_DeviceOpen)
	{
		ThreadParams.m_HPort=m_HPort;
		ThreadParams.m_Read_Overlapped=m_Read_Overlapped;
		m_hEvent1=CreateEvent(NULL,false,false,NULL);
		m_hEvent2=CreateEvent(NULL,false,false,NULL);
		m_hEvent3=CreateEvent(NULL,false,false,NULL);
		if ((m_hEvent1==NULL)|(m_hEvent2==NULL)|(m_hEvent3==NULL))
		{
			::CloseHandle(m_hEvent1);
			::CloseHandle(m_hEvent2);
			::CloseHandle(m_hEvent3);
			pLB->AddString("Creating Event ...Failed");
			return m_TempError;
		}
		pLB->AddString("Creating Event ...Ok");
		m_ReadThread=AfxBeginThread(ReadThread,&ThreadParams,THREAD_PRIORITY_TIME_CRITICAL,0,0,NULL);
		if (m_ReadThread==NULL)
		{
			pLB->AddString("Creating Thread ...Failed");
			Close();
			return false;
		}
		pLB->AddString("Creating Thread ...Ok");
	}
	m_DeviceOpen=true;
	
	if (SendString("S\x01\x2c\x20\x8d",5)!=0)
	{
		pLB->AddString("Sending SWXYZ=012C+208D");
		pLB->AddString("(Sample Rate= 300)...Failed");
		return false;
	}
	pLB->AddString("Sending SWXYZ=012C+208D ");
	pLB->AddString("(Sample Rate= 300)...Ok");
	/*
	m_TempError=WaitForSingleObject(ThreadParams.m_Status_Overlapped.hEvent,2000);
	if (m_TempError !=WAIT_OBJECT_0)
	{
		pLB->AddString("Waiting Response ...Failed");
		return false;
	}
	*/
	return true;
}

UINT ReadThread( LPVOID pParam )
{
	//
	// variables utilizadas por el hilo
	//
	Exchange* ThreadParams=(Exchange*)(pParam);

	BYTE m_ReadBuffer[255];
	DWORD m_BytesReads;
	DWORD m_Error;
	HANDLE m_Events[3];
	DWORD i;
	BYTE Counter1=0;
	char m_LastChar=0;
	CWinThread* CurrentThread=AfxGetThread();
	MSG  m_Message;
	// Filtros usados por el hilo
	CMyFilter m_BethaFilter;
	CMyFilter m_ThetaFilter;
	CMyFilter m_AlphaFilter;
	CMyFilter m_MuscleFilter;
	//
	// Indica si lo proximo que viene es un valor o el numero de canal
	// esto ocurre si el ultimo dato que se lee es el numero de canal
	// ademas hay que saber que canal fue el que se quedo
	//
	BOOL IsValue=false;
	BYTE Channel;

	//
	// Buffer que almacena la senal
	// y las senales filtradas
	double m_SignalInput1[256];  // RAW EEG
	double m_SignalInput2[256];  // Temperature 
	double m_SignalBetha[256];  // Betha
	double m_SignalTheta[256];  // Theta
	double m_SignalAlpha[256];  // Alpha
	double m_SignalMuscle[256]; // EMG

	// Punteros para intercambio de informacion
	BYTE m_PtrSignal1=255;
	BYTE m_PtrSignal2=255;
	BYTE m_PtrBetha=255;
	BYTE m_PtrTheta=255;
	BYTE m_PtrAlpha=255;
	BYTE m_PtrMuscle=255;

	//
	// inicializacion de parametros
	//
	m_Events[0]=ThreadParams->m_Read_Overlapped.hEvent;
	
	
//	ThreadParams->m_ListBox->AddString("Thread Running ...");

	//
	// Estado 2 Modo de no comando
	//
	ThreadParams->m_Status=2; 

	while (true)
	{
		if (!ReadFile(ThreadParams->m_HPort,m_ReadBuffer,20,&m_BytesReads,&ThreadParams->m_Read_Overlapped))
		{	
			m_Error=GetLastError();
			if (m_Error != ERROR_IO_PENDING) return m_Error;
			do
			{ // Mientras se reciba un comando
				m_Error=MsgWaitForMultipleObjects(1,m_Events,false,INFINITE,QS_ALLINPUT);
				switch (m_Error)
				{
				case WAIT_OBJECT_0:
					{
						//
						// llego una cadena por el puerto procesarla
						//
						m_BytesReads=ThreadParams->m_Read_Overlapped.InternalHigh;
						break;
					}
				case WAIT_OBJECT_0+1:
					{
						//
						// El hilo recibira un comando
						//
						GetMessage(&m_Message,0,0,0);
						switch(LOWORD(m_Message.wParam))
						{
						case 0: 
							{   // Matar el hilo
								PurgeComm(ThreadParams->m_HPort,PURGE_RXABORT+PURGE_RXCLEAR);
								SetEvent((HANDLE)m_Message.lParam);
								ThreadParams->m_ListBox->AddString("Thread Terminate ...");
								return 0;
							}
						case 1:
							{   // Tomar la ultima muestra
								switch(HIWORD(m_Message.wParam))
								{
								case 1:
									{
										ThreadParams->m_LastValue=m_SignalInput1[255];
										break;
									}
								case 2:
									{
										ThreadParams->m_LastValue=m_SignalInput2[255];
										break;
									}
								case 3:
									{
										ThreadParams->m_LastValue=m_SignalBetha[255];
										break;
									}
								case 4:
									{
										ThreadParams->m_LastValue=m_SignalTheta[255];
										break;
									}
								case 5:
									{
										ThreadParams->m_LastValue=m_SignalAlpha[255];
										break;
									}
								case 6:
									{
										ThreadParams->m_LastValue=m_SignalMuscle[255];
										break;
									}
								}
								break;
							}
						case 2:
							{   // tomar las ultimas muestras
								switch(HIWORD(m_Message.wParam))
								{
								case 1:
									{
										memcpy(ThreadParams->m_OutBuffer,
											&m_SignalInput1[m_PtrSignal1],
											(255-m_PtrSignal1)*sizeof(double));
										ThreadParams->m_OutCant=255-m_PtrSignal1;
										m_PtrSignal1=255;
										break;
									}
								case 2:
									{
									memcpy(ThreadParams->m_OutBuffer,
											&m_SignalInput2[m_PtrSignal2],
											(255-m_PtrSignal2)*sizeof(double));
										ThreadParams->m_OutCant=255-m_PtrSignal2;
										m_PtrSignal2=255;
										break;
									}
								case 3:
									{
										memcpy(ThreadParams->m_OutBuffer,
											&m_SignalBetha[m_PtrBetha],
											(255-m_PtrBetha)*sizeof(double));
										ThreadParams->m_OutCant=255-m_PtrBetha;
										m_PtrBetha=255;
										break;
									}
								case 4:
									{
										memcpy(ThreadParams->m_OutBuffer,
											&m_SignalTheta[m_PtrTheta],
											(255-m_PtrTheta)*sizeof(double));
										ThreadParams->m_OutCant=255-m_PtrTheta;
										m_PtrTheta=255;
										break;
									}
								case 5:
									{
										memcpy(ThreadParams->m_OutBuffer,
											&m_SignalAlpha[m_PtrAlpha],
											(255-m_PtrAlpha)*sizeof(double));
										ThreadParams->m_OutCant=255-m_PtrAlpha;
										m_PtrAlpha=255;
										break;
									}
								case 6:
									{
										memcpy(ThreadParams->m_OutBuffer,
											&m_SignalMuscle[m_PtrMuscle],
											(255-m_PtrMuscle)*sizeof(double));
										ThreadParams->m_OutCant=255-m_PtrMuscle;
										m_PtrMuscle=255;
										break;
									}
								}
								break;
							}
						case 3:
							{ // Asignar los coeficientes al filtro
								switch(HIWORD(m_Message.wParam))
								{
								case 1:
									{
										m_BethaFilter.SetCoef(ThreadParams->m_CoefA,ThreadParams->m_CoefB,ThreadParams->m_Order);
										break;
									}
								case 2:
									{
										m_ThetaFilter.SetCoef(ThreadParams->m_CoefA,ThreadParams->m_CoefB,ThreadParams->m_Order);
										break;
									}
								case 3:
									{
										m_AlphaFilter.SetCoef(ThreadParams->m_CoefA,ThreadParams->m_CoefB,ThreadParams->m_Order);
										break;
									}
								case 4:
									{
										m_MuscleFilter.SetCoef(ThreadParams->m_CoefA,ThreadParams->m_CoefB,ThreadParams->m_Order);
										break;
									}
								}
								break;
							}
						} // end del switch wParam
						SetEvent((HANDLE)m_Message.lParam);
						break;
					}
				default: 
					{
						//
						// Ocurrio un error en la funcion Wait
						//
						PurgeComm(ThreadParams->m_HPort,PURGE_RXABORT+PURGE_RXCLEAR);
						return 0;
					}
				}
			} while (m_Error==WAIT_OBJECT_0+1);
			
		} else
			m_BytesReads=ThreadParams->m_Read_Overlapped.InternalHigh;
		
		//
		// Cuando se llegua aqui es porque se recibieron caracteres
		//
		for (i=0;i<m_BytesReads;i++)
		{
			if (IsValue)
			{ // lo que entro es el valor del canal
				IsValue=false;
				if (Channel== 1)
				{   // filtrado del canal1
					memmove(&m_SignalInput1[0],&m_SignalInput1[1],sizeof(double)*255);
					memmove(&m_SignalBetha[0],&m_SignalBetha[1],sizeof(double)*255);
					memmove(&m_SignalTheta[0],&m_SignalTheta[1],sizeof(double)*255);
					memmove(&m_SignalAlpha[0],&m_SignalAlpha[1],sizeof(double)*255);
					memmove(&m_SignalMuscle[0],&m_SignalMuscle[1],sizeof(double)*255);
					m_SignalInput1[255]=m_ReadBuffer[i];
					m_SignalBetha[255]=m_BethaFilter.GetNext(m_ReadBuffer[i]);
					m_SignalTheta[255]=m_ThetaFilter.GetNext(m_ReadBuffer[i]);
					m_SignalAlpha[255]=m_AlphaFilter.GetNext(m_ReadBuffer[i]);
					m_SignalMuscle[255]=m_MuscleFilter.GetNext(m_ReadBuffer[i]);
					m_PtrSignal1--;
					m_PtrBetha--;
					m_PtrTheta--;
					m_PtrAlpha--;
					m_PtrMuscle--;
				} else
				{   // almacenamiento del canal 2
					memmove(&m_SignalInput2[0],&m_SignalInput2[1],sizeof(double)*255);
					m_SignalInput2[255]=m_ReadBuffer[i];
					m_PtrSignal2--;
				}
			} else
			{ // No era el valor del canal
				if 	(ThreadParams->m_Status==2)
				{ // no esta en modo comando
					if (m_ReadBuffer[i] < 2 )
					{
						Channel=m_ReadBuffer[i];
						IsValue=true;
					} else
					{
						m_LastChar=m_ReadBuffer[i];
						ThreadParams->m_Status=1; // Modo comado
					}
				} else
				{  // esta en modo comando
					if ( ((m_ReadBuffer[i] == 'K')|(m_ReadBuffer[i] == 'k'))&&
						 ((m_LastChar == 'O')|(m_LastChar == 'o')))
					{
						SetEvent(m_Events[1]);
						ThreadParams->m_Status=2; // Modo canal
						m_LastChar=0;
						Counter1=0;
						ThreadParams->m_ListBox->AddString("Receiving ... Ok");
					}
					else
					{
						Counter1++;
						m_LastChar=m_ReadBuffer[i];
						if (Counter1 > 9) 
						{
							ThreadParams->m_ListBox->AddString(" Receiving Invalid comand ...");
							ThreadParams->m_Status=2; // Modo canal
							Counter1=0;
						}
					}
				}
			}
		}
	} // end del while true
}

int CDevice::Close()
{
	if (m_DeviceOpen)
	{
		m_DeviceOpen=false;
		if (!PostThreadMessage(m_ReadThread->m_nThreadID,0,MAKELPARAM(0,0),(DWORD)m_hEvent2))
			m_TempError=GetLastError();
		WaitForSingleObject(m_hEvent2,INFINITE);
		CloseHandle(m_hEvent2);
		CloseHandle(m_hEvent1);
		CloseHandle(m_hEvent3);
	}
	if (m_OnOpen) 
		CloseComm();
	return true;
}

int CDevice::GetBetaData()
{
	return GetData(3);
}

int CDevice::GetPlainData()
{
	return GetData(1);
}

int CDevice::GetData(WORD pSignal)
{
	if (m_DeviceOpen)
	{
		if (!PostThreadMessage(m_ReadThread->m_nThreadID,0,MAKELPARAM(1,pSignal),0))
			return 0;
		/*
		m_TempError=WaitForSingleObject(ThreadParams.m_Status_Overlapped.hEvent,INFINITE);
		ResetEvent(ThreadParams.m_Status_Overlapped.hEvent);
		*/
		if (m_TempError != WAIT_OBJECT_0)
			return 0;
		return (int)ThreadParams.m_LastValue;
	}
	return 0;
}

int CDevice::GetPlainDataBuffer(int *pMaxSize, double *pBuffer)
{
	return GetDataBuffer(pBuffer,1);
}

int CDevice::GetBetaDataBuffer(int *pMaxSize, double *pBuffer)
{
	return GetDataBuffer(pBuffer,3);
}

int CDevice::GetThetaDataBuffer(int *pMaxSize, double *pBuffer)
{
	return GetDataBuffer(pBuffer,4);
}

int CDevice::GetMuscleDataBuffer(int *pMaxSize, double *pBuffer)
{
	return GetDataBuffer(pBuffer,6);
}

int CDevice::GetTemperatureDataBuffer(int *pMaxSize, double *pBuffer)
{
	return GetDataBuffer(pBuffer,2);
}

int CDevice::GetDataBuffer(double *pBuffer,WORD pSignal)
{
	ThreadParams.m_OutBuffer=pBuffer;
	if (m_DeviceOpen)
	{
		if (!PostThreadMessage(m_ReadThread->m_nThreadID,0,MAKELPARAM(2,pSignal),(DWORD)m_hEvent1))
			return false;
		m_TempError=WaitForSingleObject(m_hEvent1,INFINITE);
		if (m_TempError != WAIT_OBJECT_0)
			return false;
		return ThreadParams.m_OutCant;
	}
	return 0;
}

int CDevice::SetBhetaCoef(double *pCoefA, double *pCoefB, DWORD pOrder)
{
	return SetCoef(pCoefA,pCoefB,pOrder,1);
}

int CDevice::SetThetaCoef(double *pCoefA, double *pCoefB, DWORD pOrder)
{
	return SetCoef(pCoefA,pCoefB,pOrder,2);
}

int CDevice::SetAlphaCoef(double *pCoefA, double *pCoefB, DWORD pOrder)
{
	return SetCoef(pCoefA,pCoefB,pOrder,3);
}

int CDevice::SetMuscleCoef(double *pCoefA, double *pCoefB, DWORD pOrder)
{
	return SetCoef(pCoefA,pCoefB,pOrder,4);
}

int CDevice::SetCoef(double *pCoefA, double *pCoefB, DWORD pOrder,WORD pSignal)
{
	ThreadParams.m_CoefA=pCoefA;
	ThreadParams.m_CoefB=pCoefB;
	ThreadParams.m_Order=pOrder;
	if (m_DeviceOpen)
	{
		if (!PostThreadMessage(m_ReadThread->m_nThreadID,0,MAKELPARAM(3,pSignal),(DWORD)m_hEvent2))
			return false;
		m_TempError=WaitForSingleObject(m_hEvent2,INFINITE);
		if (m_TempError != WAIT_OBJECT_0)
			return false;
		return true;
	}
	return true;
}

int CDevice::GetAlphaDataBuffer(int *pMaxSize, double *pBuffer)
{
	return GetDataBuffer(pBuffer,5);
}

int CDevice::StartData()
{
	CListBox* pLB=(CListBox*)AfxGetMainWnd()->GetDlgItem(1003);
	if (SendString("DAT",3)!=0)
	{
		pLB->AddString("Sending DAT ...Failed");
		return false;
	}
	pLB->AddString("Sending DAT ...Ok");
//	m_TempError=WaitForSingleObject(ThreadParams.m_Status_Overlapped.hEvent,2000);
	if (m_TempError !=WAIT_OBJECT_0)
	{
		pLB->AddString("Waiting Response ...Failed");
		return false;
	}
//	ResetEvent(ThreadParams.m_Status_Overlapped.hEvent);
	return true;
}
