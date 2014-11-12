// LFC10C03.cpp: implementation of the CSignalDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sigC03.h"
#include "sigdef.h" 
#include "..\neurofbdll\app.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define FILTER_4_7_HZ_ORDER 7

double FILTER_4_7_HZ_A1[] = {
	   1.0000000000000000e+000,
	   -5.9234125427462541e+000,
	   1.4658896085810349e+001,
	   -1.9399502411701370e+001,
		1.4479764721753707e+001,
	   -5.7795329447156725e+000,
		9.6378890531529104e-001};
double FILTER_4_7_HZ_B1[] = {
       3.6731211833936897e-003,
  	  -1.4564371353847395e-002,
	   1.8109931047261871e-002,
	  -3.0992676196319782e-017,
	  -1.8109931047261840e-002,
	  1.4564371353847402e-002,
	  -3.6731211833936953e-003};

#define FILTER_8_14_HZ_ORDER 9
double FILTER_8_14_HZ_B1[] = {
		3.1165385134352273e-002,
		-2.4007906586447444e-001,
		8.1797442458319647e-001,
		-1.6098103346414425e+000,
		2.0014993565156867e+000,
		-1.6098103346414416e+000,
		8.1797442458319569e-001,
		-2.4007906586447411e-001,
		3.1165385134352221e-002};
double FILTER_8_14_HZ_A1[] = {
	   1.0000000000000000e+000,
	  -7.7164769151806736e+000,
	   2.6257281550986313e+001,
	  -5.1453208430963201e+001,
	   6.3502315231566634e+001,
	  -5.0544014933683997e+001,
	   2.5337591944747274e+001,
	  -7.3146785620600605e+000,
	   9.3119564811361466e-001};

#define FILTER_15_18_HZ_ORDER 7
double FILTER_15_18_HZ_B1[] = {
	   3.6731211833936905e-003,
	   -1.3794758013584662e-002,
       1.6620568813262234e-002,
	   -1.6311934840168310e-018,
	   -1.6620568813262227e-002,
	   1.3794758013584653e-002,
	   -3.6731211833936866e-003 };
double FILTER_15_18_HZ_A1[] = {
	   1.0000000000000000e+000,
	   -5.6104064265177795e+000,
	   1.3455170963417970e+001,
	   -1.7623592913989597e+001,
	   1.3290752822084357e+001,
	   -5.4741297421554860e+000,
	   9.6378890531529515e-001};

#define FILTER_15_21_HZ_ORDER 9
double FILTER_15_21_HZ_A1[] = {
	   1.0000000000000000e+000,
	   -7.3693038832921598e+000,
	   2.4291679752728598e+001,
	   -4.6720204719748850e+001,
	   5.7306381375759173e+001,
	   -4.5894692167893112e+001,
	   2.3440862978972024e+001,
	   -6.9855828929361783e+000,
	   9.3119564811361355e-001};
	   
double FILTER_15_21_HZ_B1[] = {
	   3.1165385134352273e-002,
	   -2.2927763690857897e-001,
	   7.5670915358430968e-001,
	   -1.4616136745190123e+000,
	   1.8060441707462676e+000,
	   -1.4616136745190118e+000,
	   7.5670915358430912e-001,
	   -2.2927763690857872e-001,
	   3.1165385134352231e-002};

#define FILTER_18_21_HZ_ORDER 7
double FILTER_18_21_HZ_A1[] = {
	  1.0000000000000000e+000,
	 -5.4725068465655120e+000,
	  1.2945584071433071e+001,
	 -1.6880386903375836e+001,
	  1.2787394649014612e+001,
	 -5.3395797408437229e+000,
	  9.6378890531529271e-001};

double FILTER_18_21_HZ_B1[] = {
	  3.6731211833936949e-003,
	 -1.3455693213105127e-002,
	  1.5990059855905698e-002,
	  1.3049547872134663e-017,
	 -1.5990059855905722e-002,
	  1.3455693213105144e-002,
	 -3.6731211833936983e-003};

#define FILTER_22_HZ_ORDER 7
double FILTER_22_HZ_A1[] = {
	  1.0000000000000000e+000,
	 -4.4939973991338684e+000,
	  9.0459866086236733e+000,
	 -1.0310079076439550e+001,
	  7.0547230802964735e+000,
	 -2.7724885463573763e+000,
	  5.0499508471069354e-001};

double FILTER_22_HZ_B1[] = {
	  4.3746408981714874e-001,
	 -2.4249306935974060e+000,
	  5.7895512181276523e+000,
	 -7.6032475837488338e+000,
	  5.7895512181276523e+000,
	 -2.4249306935974069e+000,
	  4.3746408981714902e-001};



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define SIGNAL_TIMEOUT 500 
// Esperar medio segundo por el arribo de la senal

CSignalDevice::CSignalDevice()
{
	InitSignalDevice();
}

CSignalDevice::~CSignalDevice()
{
	// Destruir todos los buffer 
	S_MESSAGE Msg;
	Msg.Msg=UM_COMMAND;
	Msg.wParam=CLEAR_BUFFER;
	SendMessage(&Msg);
	delete Data;
}

int CSignalDevice::OpenDevice()
{
	return OpenPort();
}

int CSignalDevice::IsDevice()
{
	if (!IsOpen())
		return false;
	// Enviar mensaje al hilo indicando el envio de un comando
	S_MESSAGE Msg;
	Msg.Msg=UM_CLEAR_STATE;
	SendMessage(&Msg);
	SendBuffer((BYTE*)"AT\r",3);
	Msg.Msg=UM_WAIT_COMMAND;
	SendMessage(&Msg);
	if (Data->DeviceState !=0 )
	{
		AfxMessageBox("Hay un dispositivo conectado");
	}
	return true;
}

int CSignalDevice::InitSignalDevice()
{
	Data = new S_SIGNALDEVICE;
	if (!Data)
		return false;

	SetBufferLen(5);
	Data->OnNotifyWindow=false;
	Data->NotifyHWND=NULL;

	S_MESSAGE Message;
	Message.Msg=UM_THREAD_INIT;
	SendThreadMessage(&Message);
	
	SetSignalsCant(6);
	SetSignalsBufferLen(600);

	m_game_start=false;
	m_minuto=0;
	m_burst=0;
	m_burst_time=0;
	m_burst_sec=0;
	m_cant_muestras=0;
	m_cant_seconds=0;
	m_prom_ieeg=0;
	m_prom_iemg=0;
	m_prom_reeg=0;
	m_prom_temp=0;
	m_suma_ieeg_sec=0;
	m_suma_iemg_sec=0;
	m_suma_reeg_sec=0;
	m_suma_temp_sec=0;
	m_disparar=true;
	return true;
}

int CSignalDevice::OnReceiveData(BYTE *pBuffer, DWORD pCant)
{
	DWORD i;
	for (i=0;i<pCant;i++)
	{
		if (Data->OnValue)
		{ 
			// Llego el valor del canal
			Data->OnValue=false;
			if (Data->Channel== 1)
			{ 
				// El valor pertenece al canal 1
				NewSample(0,pBuffer[i]);
			}
			else
			{
				// Entro el valor del canal dos
			}
		}
		else
		{
			switch(pBuffer[i])
			{
			case 1:
				{
					Data->OnValue=true;
					Data->Channel=1;
					break;
				}
			case 'K':
			case 'k':
			case 'O':
			case 'o':
				{
					if (Data->LastValue=='O')
					{
						if (Data->DeviceState!=PRESENT)
							SetDeviceStatus(PRESENT);
					}
					Data->LastValue=toupper(pBuffer[i]);
					break;
				}
			default:
				{
					//Data->DeviceState=BAD_DEVICE;
					break;
				}
			}
		}
	}
	if (Data->OnCommand)
	{
		if (Data->DeviceState == GETING_DATA)
		{
			// Replicar el mensaje
			if (Data->CommandMaxBytes < pCant)
			{
				ReplyCommand();
			}
			else
				Data->CommandMaxBytes-=pCant;
		}
		else 
		{
			ReplyCommand();
		}
	}
	return true;
}

int CSignalDevice::OnProcessMessage(S_MESSAGE *pMessage)
{
	switch (pMessage->Msg)
	{
	case UM_THREAD_INIT:
		{
			ThreadInit();
			break;
		}
	case UM_NULL:
		break;
	case UM_CLEAR_STATE:
		{
			Data->DeviceState=UKNOW_STATE;
			SetWaitTimeOut(1000);
			break;
		}
	case UM_WAIT_COMMAND:
		{
			if (Data->DeviceState!=GETING_DATA)
				ReplyCommand();
			else
			{
				Data->OnCommand=true;
				SetWaitTimeOut(5000);
				return false;
			}
			break;
		}
	case UM_GET_BUFFER:
		{
			S_BUFFER* Buffer=(S_BUFFER*)pMessage->ExtraData;
			ReadFromSignal(Buffer->pIndex,Buffer->pBuffer,Buffer->pCant,Buffer->pCantRead);
			break;
		}
	case UM_COMMAND:
		{
			switch(pMessage->wParam)
			{
			case CLEAR_BUFFER:
				{
					ThreadDestroy();
					break;
				}
			}
			break;
		}
	case UM_UPDATE:
		{
			switch (pMessage->wParam)
			{
			case SIGCANT:
				{
					UpDateSignalsCant(pMessage->lParam);
					break;
				}
			case COEF:
				{
					S_COEF* Coef=(S_COEF*)pMessage->ExtraData;
					UpDateCoef(pMessage->lParam,Coef->pCoefA,Coef->pCoefB,Coef->pOrder);
					break;
				}
			case BUFFERLEN:
				{
					UpDateSignalsBufferLen(pMessage->lParam);
					break;
				}
			}
		}
	}
	return true;
}

int CSignalDevice::ReplyCommand()
{
	ReplyMessage(true);
	Data->OnCommand=false;
	SetWaitTimeOut(SIGNAL_TIMEOUT);
	return true;
}

int CSignalDevice::OnWaitTimeOut()
{
	if (Data->OnCommand)
		ReplyCommand();
	else
		if (Data->DeviceState == GETING_DATA)
		{
			// Notificar la falta  de muestras
			SetDeviceStatus(UKNOW_STATE);
			SetWaitTimeOut(INFINITE);
		}
		else
			SetWaitTimeOut(INFINITE);
	return true;
}

/*
	Adiciona un uevo valor al buffer
	de la senal especifica
*/
int CSignalDevice::AddToSignal(DWORD pIndex, float pValue)
{
	if (pIndex > Data->SignalsCant)
		return false;
	if (!Data->Signals[pIndex].Buffer)
		return false;
	Data->Signals[pIndex].Buffer[Data->Signals[pIndex].Write_Ptr]=pValue;
	Data->Signals[pIndex].Write_Ptr++;
	if (Data->Signals[pIndex].Write_Ptr == Data->Signals[pIndex].Buffer_Len)
		Data->Signals[pIndex].Write_Ptr=0;
	if (Data->Signals[pIndex].Write_Ptr == Data->Signals[pIndex].Read_Ptr)
	{
		Data->Signals[pIndex].Read_Ptr++;
		Data->Signals[pIndex].Status=LOSS_DATA;
	}
	if (Data->Signals[pIndex].Read_Ptr == Data->Signals[pIndex].Buffer_Len)
		Data->Signals[pIndex].Read_Ptr=0;

	if (Data->DeviceState != GETING_DATA)
		SetDeviceStatus(GETING_DATA);
	return true;
}

int CSignalDevice::SetSignalsCant(DWORD pCant)
{
	S_MESSAGE Msg;
	Msg.Msg=UM_UPDATE;
	Msg.wParam=SIGCANT;
	Msg.lParam=pCant;
	SendMessage(&Msg);

	SetFilterCoef(2,FILTER_4_7_HZ_A1,FILTER_4_7_HZ_B1,FILTER_4_7_HZ_ORDER);
	SetFilterCoef(4,FILTER_15_18_HZ_A1,FILTER_15_18_HZ_B1,FILTER_15_18_HZ_ORDER);
	SetFilterCoef(5,FILTER_22_HZ_A1,FILTER_22_HZ_B1,FILTER_22_HZ_ORDER);

	return true;
}

/*
	Esta funcion es llamada desde el hilo
*/
int CSignalDevice::ReadFromSignal(DWORD pIndex, float *pBuffer, DWORD pCant, DWORD *pCantRead)
{
	*pCantRead=0;
	while ((Data->Signals[pIndex].Read_Ptr != Data->Signals[pIndex].Write_Ptr) & (*pCantRead < pCant))
	{
		pBuffer[*pCantRead]=Data->Signals[pIndex].Buffer[Data->Signals[pIndex].Read_Ptr];
		Data->Signals[pIndex].Read_Ptr++;
		if (Data->Signals[pIndex].Read_Ptr==Data->Signals[pIndex].Buffer_Len)
			Data->Signals[pIndex].Read_Ptr=0;
		(*pCantRead)++;
	}
	return true;
}
/*
	Esta funcion es llamada desde afuera 
*/
int CSignalDevice::GetSignal(DWORD pIndex, float *pBuffer, DWORD pCant, DWORD *pCantRead)
{
	if (pIndex >= Data->SignalsCant)
		return false;
	if (Data->Signals[pIndex].Read_Ptr == Data->Signals[pIndex].Write_Ptr)
		return false;

	S_BUFFER Buffer;
	Buffer.pBuffer=pBuffer;
	Buffer.pIndex=pIndex;
	Buffer.pCantRead=pCantRead;
	Buffer.pCant=pCant;
	S_MESSAGE Msg;
	Msg.Msg=UM_GET_BUFFER;
	Msg.ExtraData=&Buffer;
	SendMessage(&Msg);
	return true;
}

int CSignalDevice::SetSignalsBufferLen(DWORD pLen)
{
	S_MESSAGE Msg;
	Msg.Msg=UM_UPDATE;
	Msg.wParam=BUFFERLEN;
	Msg.lParam=pLen;
	SendMessage(&Msg);
	return true;	
}

int CSignalDevice::SetNotifyWindow(HWND pHWnd)
{
	Data->NotifyHWND =pHWnd;
	Data->OnNotifyWindow =true;
	return true;
}

int CSignalDevice::SetFilterCoef(DWORD pIndex, double *pCoefA, double *pCoefB, DWORD pOrder)
{
	S_COEF Coef;
	S_MESSAGE Msg;
	Coef.pCoefA=pCoefA;
	Coef.pCoefB=pCoefB;
	Coef.pOrder=pOrder;
	Msg.ExtraData=&Coef;
	Msg.Msg=UM_UPDATE;
	Msg.wParam=COEF;
	Msg.lParam=pIndex;
	SendMessage(&Msg);
	return true;
}
/*
	Esta funcion es invocada por el hilo
*/
int CSignalDevice::UpDateCoef(DWORD pIndex, double *pCoefA, double *pCoefB, DWORD pOrder)
{
	if (pIndex >= Data->SignalsCant)
		return false;
	return Data->Signals[pIndex].Filter.SetCoeficient(pCoefA,pCoefB,pOrder);
}
/*
	Esta funcion es invocada desde el hilo
*/
int CSignalDevice::UpDateSignalsCant(DWORD pCant)
{
	DWORD i;
	if (pCant == Data->SignalsCant)
		return true;

	for(i=0;i<Data->SignalsCant;i++)
	{
		delete Data->Signals[i].Buffer;
	}
	delete Data->Signals;
	Data->SignalsCant=pCant;
	Data->Signals= new S_SIGNALDATA[pCant];
	for(i=0;i<Data->SignalsCant;i++)
	{
		Data->Signals[i].Buffer=NULL;
		Data->Signals[i].Buffer_Len=0;
		Data->Signals[i].Read_Ptr=0;
		Data->Signals[i].Write_Ptr=0;
	}
	return true;
}
/*
	esta funcion es invocada desde el hilo
*/
int CSignalDevice::UpDateSignalsBufferLen(DWORD pLen)
{
	for(DWORD i=0;i<Data->SignalsCant;i++)
	{
		delete Data->Signals[i].Buffer;
		Data->Signals[i].Buffer= new float [pLen];
		Data->Signals[i].Buffer_Len=pLen;
	}
	return true;
}

/*
	LLamada desde el hilo adiciona una muetra al canal 0 o 1
	y si es el uno adicona muestras a los demas canales
*/
int CSignalDevice::NewSample(DWORD pIndex, float pValue)
{
	int Frecuencia_Muestreo; //en herz
    Frecuencia_Muestreo = 300;

	if (!Data->SignalsCant)
		return false;
	
	if (pIndex==1)
		valor[1]=pValue;
	else
		valor[1]=0;

	pValue*=0.117;						// ajuste de escala a multiplicar por 0.115 para llevar a microV
										//30 µV ->255
	AddToSignal(pIndex,pValue);
	
	if (pIndex==1)    //pindex = 0 es señal de entrada pindex = 1 temperatura ahora no se hace nada 
		return false; //con la temperatura

	//aqui se le aplican los filtros a la señal de entrada y se le halla el modulo 
	if (pIndex == 0)
	{
		DWORD i;
		for (i=2;i<Data->SignalsCant;i++)
		{
			valor[i]=Data->Signals[i].Filter.GetOutput(pValue);
			if (valor[i]<0) valor[i]=-valor[i];
			AddToSignal(i,valor[i]);
			
		}
	}
    //a la salida de los filtros en el arreglo valor estan los valores instantaneo de cada señal filtrada
	//con el modulo hallado y la escala lista
	
	//esto se ejecuta si se está jugando Online
	if (m_game_start)
	{
		//estas sumas son para hallar los promedios de cada segundo
		m_suma_temp_sec+=valor[1];
		m_suma_ieeg_sec+=valor[2];
		m_suma_reeg_sec+=valor[4];
		m_suma_iemg_sec+=valor[5];

		//aqui se evalua la condicion y si es valida se incrementa el contador de burst
		if ((valor[2] < m_lpparametros->m_Nivel_I_Eeg)&&
			(valor[4] > m_lpparametros->m_Nivel_R_Eeg)&&
			(valor[5] < m_lpparametros->m_Nivel_I_Musculo))
			m_burst++;
		
		m_cant_muestras++;
		//esto se ejecuta para cada segundo (300 mustras) que es la frecuencia de muestreo
		if (m_cant_muestras == Frecuencia_Muestreo)
		{
			//se incrementa el contador de tiempo de conteo de burst, si este contador es igual
			//al tiempo de conteo de burst seteado se compara la cantidad de burst con el criterio
			m_burst_time++;
			if (m_burst_time == m_lpparametros->m_Tiempo_Conteo_Burst)
			{
				m_burst_sec=m_burst;
				//comparacion de la cantidad de burst si se cumple se permite disparar
				if (m_burst > m_lpparametros->m_Crit_Comp_Burst)
				{
					m_disparar=true;
				}
				else
					m_disparar=false;
				m_burst_time=0;
				m_burst=0;
			}
			
			m_prom_ieeg_sec=m_suma_ieeg_sec/Frecuencia_Muestreo;
			m_prom_iemg_sec=m_suma_iemg_sec/Frecuencia_Muestreo;
			m_prom_reeg_sec=m_suma_reeg_sec/Frecuencia_Muestreo;
            m_prom_temp+=m_suma_temp_sec/Frecuencia_Muestreo;
			
			//estos son los sumadores de los promedios para cada minuto
			m_prom_ieeg+=m_prom_ieeg_sec;
			m_prom_reeg+=m_prom_reeg_sec;
			m_prom_iemg+=m_prom_iemg_sec;
			
			m_suma_temp_sec=0;
			m_suma_ieeg_sec=0;
			m_suma_reeg_sec=0;
			m_suma_iemg_sec=0;
			
			m_cant_seconds++;
			m_cant_muestras=0;
		}
		
		//esto de aqui se hace para cada minuto, se guardan los promedios de las señales filtradas
		//el contador de minutos y los puntos obtenidos en el minuto
        if (m_cant_seconds == 60)
		{
			m_lpdatos[m_minuto]->prom_ieeg_min=m_prom_ieeg/60;
			m_lpdatos[m_minuto]->prom_iemg_min=m_prom_iemg/60;
			m_lpdatos[m_minuto]->prom_reeg_min=m_prom_reeg/60;
			m_lpdatos[m_minuto]->prom_temp_min=m_prom_temp/60;
			m_lpdatos[m_minuto]->minuto=m_minuto+1;
			m_lpdatos[m_minuto]->puntos=m_lpapp->m_3dgame.m_score;
			m_cant_seconds=0;
			m_prom_ieeg=0;
			m_prom_iemg=0;
			m_prom_reeg=0;
			m_prom_temp=0;
			m_minuto++;
		}
		//condicion de terminacion de la condicion
		if (m_minuto == m_lpparametros->m_Duracion_Cond)
			m_game_start=false;
	}
	
	

	SetWaitTimeOut(SIGNAL_TIMEOUT);
	Data->DeviceState = GETING_DATA;
	return true;
}

int CSignalDevice::SendNullMessage()
{
	S_MESSAGE Msg;
	Msg.Msg=UM_NULL;
	SendMessage(&Msg);
	return true;
}

/*
	Inicializacion de todas las variables del hilo
*/
int CSignalDevice::ThreadInit()
{
	Data->Channel=0;
 	Data->OnValue=false;
 	Data->LastValue=0;
 	Data->OnCommand=false;
 	Data->SignalsCant=0;
 	Data->Signals=NULL;
	SetWaitTimeOut(SIGNAL_TIMEOUT);
	m_disparar=false;
 	return true;
}

int CSignalDevice::ThreadDestroy()
{
	// Destrucion de todos los datos del hilo
	for(DWORD i=0;i<Data->SignalsCant;i++)
	{
		delete Data->Signals[i].Buffer;
	}
	delete [] Data->Signals;
	Data->SignalsCant =0;
	Data->Signals =NULL;
	return true;
}

int CSignalDevice::StartData()
{
	OpenPort();
	S_MESSAGE Msg;
	Msg.Msg=UM_CLEAR_STATE;
	SendMessage(&Msg);
	SendBuffer((BYTE*)"DAT",3);
	return true;
}

int CSignalDevice::StopData()
{
	OpenPort();
	S_MESSAGE Msg;
	Msg.Msg=UM_CLEAR_STATE;
	SendMessage(&Msg);
	SendBuffer((BYTE*)"HALT",4);
	return true;
}

int CSignalDevice::SetDeviceStatus(DWORD pStatus)
{
	Data->DeviceState=pStatus;
	if (Data->OnNotifyWindow)
		PostMessage(Data->NotifyHWND,UM_DEVICE_STATE,pStatus,0);
	return true;
}

DWORD CSignalDevice::GameStart()
{
	/*
		actualizacion de los filtros
	*/
	m_minuto=0;
	m_burst=0;
	m_burst_time=0;
	m_burst_sec=0;
	m_cant_muestras=0;
	m_cant_seconds=0;
	m_prom_ieeg=0;
	m_prom_iemg=0;
	m_prom_reeg=0;
	m_prom_temp=0;
	m_suma_ieeg_sec=0;
	m_suma_iemg_sec=0;
	m_suma_reeg_sec=0;
	m_suma_temp_sec=0;
	m_prom_ieeg_sec=0;
	m_prom_iemg_sec=0;
	m_prom_reeg_sec=0;
	m_game_start=true;
	m_disparar=false;
	return 0;
}

DWORD CSignalDevice::SetApp(CApp *lpApp)
{
	m_lpapp=lpApp;
	return 0;
}

DWORD CSignalDevice::SetParameters(S_PARAMETROS* lpparametros, S_DATOS** lpdatos)
{
	m_lpparametros=lpparametros;
	m_lpdatos=lpdatos;
	return 0;
}
