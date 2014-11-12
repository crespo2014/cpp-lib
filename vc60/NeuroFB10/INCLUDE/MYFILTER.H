// MyFilter.h: interface for the CMyFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFILTER_H__C02818A4_8C4D_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_MYFILTER_H__C02818A4_8C4D_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyFilter  
{
public:
	void SetCoef(double* pCoefA, double* pCoefB,DWORD pOrder);
	DWORD m_FilterOrder;
	double* CoefA;
	double* CoefB;
	double* TempIn;
	double* TempOut;
	DWORD m_VarCicle;  // variable de siclo
	double GetNext( double pInSignal);
	CMyFilter();
	virtual ~CMyFilter();

};

void FftDouble(unsigned int NumSamples, int InverseTransform, double *RealIn, double *ImagIn, double *RealOut, double *ImagOut);
int IsPowerOfTwo ( unsigned x );
unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo );
unsigned ReverseBits ( unsigned index, unsigned NumBits );

#endif // !defined(AFX_MYFILTER_H__C02818A4_8C4D_11D3_A036_0000E8DE4B3B__INCLUDED_)

/*

// Procedimiento para graficar la senal

	DWORD Center=150;
	
	CDC* pDC=GetDC();
	CRect Window1(10,Center-30,10+MaxPoint+10,Center+30);
	pDC->Rectangle(Window1);
	pDC->MoveTo(10,Center);
	for (i=0;i<MaxPoint;i++)
	{
		pDC->LineTo(i+10,(int)(InputSignal[i]+Center));
		pDC->MoveTo(i+10,(int)(InputSignal[i]+Center));
	}

	CRect Window2(10,Center+40,10+MaxPoint+10,Center+100);
	pDC->Rectangle(Window2);
	pDC->MoveTo(10,Center+70);
	for (i=0;i<MaxPoint;i++)
	{
		pDC->LineTo(i+10,(int)(Signal4_7[i])+Center+70);
		pDC->MoveTo(i+10,(int)(Signal4_7[i])+Center+70);
	}
	

	FftDouble(MaxPoint,0,InputSignal,Imag_1,Real_2,Imag_2);
	CRect Window3(10,Center+110,10+(MaxPoint*4)/2+10,Center+160);
	pDC->Rectangle(Window3);
	pDC->MoveTo(10,Center+150);
	double temp;
	for (i=0; i < MaxPoint/2; i++)
	{
		temp=sqrt((Real_2[i]*Real_2[i])+(Imag_2[i]*Imag_2[i]))/30;
		if (temp> 30) temp =38; 
		pDC->LineTo(i*4+10,(Center+150-temp));
		pDC->MoveTo(i*4+10,(Center+150-temp));
	}

	FftDouble(MaxPoint,0,Signal4_7,Imag_1,Real_2,Imag_2);
	CRect Window4(10,Center+170,10+(MaxPoint*4)/2+10,Center+220);
	pDC->Rectangle(Window4);
	pDC->MoveTo(10,Center+210);
	for (i=0; i < MaxPoint/2; i++)
	{
		temp=sqrt((Real_2[i]*Real_2[i])+(Imag_2[i]*Imag_2[i]))/30;
		if (temp > 30) temp = 38; 
		pDC->LineTo(i*4+10,(Center+210-temp));
		pDC->MoveTo(i*4+10,(Center+210-temp));
	}
	
  
    // Subrutina para obtener el proximo pto del grafico

	// mover los ptos que saldran en pantalla
	memmove(&InputSignal[0],&InputSignal[1],(MaxPoint-1)*sizeof(double));
	// Mover ptos de la senal filtrada
	memmove(&Signal4_7[0],&Signal4_7[1],(MaxPoint-1)*sizeof(double));

	// incrementar el tiempo

	t[0]++;
	t[1]++;
	if (frec[0] !=0)
		if (t[0]==m_fs/frec[0]) t[0]=0;
	if (frec[1] !=0)
		if (t[1]==m_fs/frec[1]) t[1]=0;
	double Signal1=10*cos(2*3.14*frec[0]*t[0]/m_fs)+10*cos(2*3.14*frec[1]*t[1]/m_fs);
	double Signal2=MyFilter.GetNext(Signal1);

	InputSignal[MaxPoint-1]=Signal1;
	Signal4_7[MaxPoint-1]=Signal2;

	// Analisis espectral
	for (i=0; i < MaxPoint; i++)
		Imag_1[i]=0;

	Grafica();
	

// Coeficientes utilizados para los distintos filtros

void CSignalDlg::OnSelect100() 
{
	m_CoefA[0]= 1.0000000000000000e+000;
	m_CoefA[1]=-4.5656830734242639e+000;
	m_CoefA[2]=9.8701680998329397e+000;
	m_CoefA[3]=-1.2426247234221336e+001;
	m_CoefA[4]=9.6304667684354097e+000;
	m_CoefA[5]=-4.3465379223331677e+000;
	m_CoefA[6]=9.2888664910492702e-001;
	
	m_CoefB[0]=7.2583550576423329e-003;
	m_CoefB[1]=-2.2183210160259925e-002;
	m_CoefB[2]=2.4084549718688820e-002;
	m_CoefB[3]=-6.4467143247191787e-018; 
	m_CoefB[4]=-2.4084549718688817e-002;
	m_CoefB[5]=2.2183210160259932e-002;
	m_CoefB[6]=-7.2583550576423381e-003;

	MyFilter.SetCoef(m_CoefA,m_CoefB,7);
	
}

void CSignalDlg::OnSelect300() 
{
	m_CoefA[0]=1.0000000000000000e+000;
	m_CoefA[1]=-4.5656830734242639e+000;
	m_CoefA[2]=9.8701680998329397e+000;
	m_CoefA[3]=-1.2426247234221336e+001;
	m_CoefA[4]=9.6304667684354097e+000;
	m_CoefA[5]=-4.3465379223331677e+000;
	m_CoefA[6]=9.2888664910492702e-001;
	
	m_CoefB[0]=7.2583550576423329e-003;
	m_CoefB[1]=-2.2183210160259925e-002;
	m_CoefB[2]=2.4084549718688820e-002;
	m_CoefB[3]=-6.4467143247191787e-018;
	m_CoefB[4]=-2.4084549718688817e-002;
	m_CoefB[5]=2.2183210160259932e-002;
	m_CoefB[6]=-7.2583550576423381e-003;

	MyFilter.SetCoef(m_CoefA,m_CoefB,7);   
}

	// Start Signal
	UpdateData(true);
	t[0]=0;
	t[1]=0;
	frec[0]=m_Signal1;
	frec[1]=m_Signal2;
	if (!OnStartSignal)
	{
		m_Timer_ID=SetTimer(1,1,NULL);
		AfxBeginThread(PaintThread,this);
	}
	OnStartSignal=true;
	
void CSignalDlg::OnStop() 
{
	KillTimer(m_Timer_ID);
	OnStartSignal=false;
}



variables a incluir en el dialogo para poder dibujar
y generar las senales

	DWORD MaxPoint;
	
	// frecuecias a usar y tiempo de muestreo para ellas
	DWORD frec[2];
	DWORD t[2];

	// Coeficientes utilizados
	double m_CoefA[7];
	double m_CoefB[7];
	// senales utilizadas
	double InputSignal[256];
	double Signal4_7[256];

	// variable de ciclo
	DWORD i;

	UINT m_Timer_ID;
	BOOL OnStartSignal;

	// variables para el espectro de frecuencia
	double Real_1[256];
	double Imag_1[256];
	double Real_2[256];
	double Imag_2[256];

	CDevice Device;  // Clase para el manejo del equipo

Hilo de ejecucion 
UINT PaintThread( LPVOID pParam )
{
	CSignalDlg* Dialogo=(CSignalDlg*)pParam;
	while (Dialogo->OnStartSignal)
	{
		Dialogo->NextSample();
	};
	return 0;
}

*/