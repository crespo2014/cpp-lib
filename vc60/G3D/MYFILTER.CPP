// MyFilter.cpp: implementation of the CMyFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyFilter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyFilter::CMyFilter()
{
	m_FilterOrder=0;
	CoefA=NULL;
	CoefB=NULL;
	TempIn=NULL;
	TempOut=NULL;
}

CMyFilter::~CMyFilter()
{
	delete CoefA;
	delete CoefB;
	delete TempIn;
	delete TempOut;
}

//
// Calculo del proximo valor de salida 
// filtraje de la senal de entrada
//
double CMyFilter::GetNext(double pInSignal)
{
	double OutValue=0.0;
	if (m_FilterOrder==0)
		return 0.0;

	OutValue=CoefB[0]*pInSignal;
	for (m_VarCicle=1;m_VarCicle<m_FilterOrder;m_VarCicle++)
	{
		OutValue+=CoefB[m_VarCicle]*TempIn[m_FilterOrder-m_VarCicle]-
			CoefA[m_VarCicle]*TempOut[m_FilterOrder-m_VarCicle];
	}
	memmove(&TempIn[0],&TempIn[1],(m_FilterOrder-1)*sizeof(double));
	memmove(&TempOut[0],&TempOut[1],(m_FilterOrder-1)*sizeof(double));
	TempIn[m_FilterOrder-1]=pInSignal;
	TempOut[m_FilterOrder-1]=OutValue;
	return OutValue;
}

void CMyFilter::SetCoef(double *pCoefA, double* pCoefB, DWORD pOrder)
{
	if (m_FilterOrder != pOrder)
	{
		delete CoefA;
		delete CoefB;
		delete TempIn;
		delete TempOut;
		m_FilterOrder=pOrder;
		CoefA=new double[pOrder];
		CoefB=new double[pOrder];
		TempIn=new double[pOrder];
		TempOut=new double[pOrder];
	}
	memcpy(CoefA,pCoefA,pOrder*sizeof(double));
	memcpy(CoefB,pCoefB,pOrder*sizeof(double));
	for (m_VarCicle=0;m_VarCicle<pOrder;m_VarCicle++)
	{
		TempIn[m_VarCicle]=0.0;
		TempOut[m_VarCicle]=0.0;
	}
}

void FftDouble(unsigned int NumSamples, int InverseTransform, double *RealIn, double *ImagIn, double *RealOut, double *ImagOut)
{

	double PI=3.14;
    unsigned int NumBits;    /* Number of bits needed to store indices */
    unsigned int i, j, k, n;
    unsigned int BlockSize, BlockEnd;

    double angle_numerator = 2.0 * PI;
    double tr, ti;     /* temp real, temp imaginary */

    if ( !IsPowerOfTwo(NumSamples) )
    {
        fprintf (
            stderr,
            "Error in fft():  NumSamples=%u is not power of two\n",
            NumSamples );

        exit(1);
    }

    if ( InverseTransform )
        angle_numerator = -angle_numerator;

    
NumBits = NumberOfBitsNeeded ( NumSamples );

    /*
    **   Do simultaneous data copy and bit-reversal ordering into outputs...
    */

    for ( i=0; i < NumSamples; i++ )
    {
        j = ReverseBits ( i, NumBits );
        RealOut[j] = RealIn[i];
        ImagOut[j] = (ImagIn == NULL) ? 0.0 : ImagIn[i];
    }

    /*
    **   Do the FFT itself...
    */

    BlockEnd = 1;
    for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
    {
        double delta_angle = angle_numerator / (double)BlockSize;
        double sm2 = sin ( -2 * delta_angle );
        double sm1 = sin ( -delta_angle );
        double cm2 = cos ( -2 * delta_angle );
        double cm1 = cos ( -delta_angle );
        double w = 2 * cm1;
        double ar[3], ai[3];

        for ( i=0; i < NumSamples; i += BlockSize )
        {
            ar[2] = cm2;
            ar[1] = cm1;

            ai[2] = sm2;
            ai[1] = sm1;

            for ( j=i, n=0; n < BlockEnd; j++, n++ )
            {
                ar[0] = w*ar[1] - ar[2];
                ar[2] = ar[1];
                ar[1] = ar[0];

                ai[0] = w*ai[1] - ai[2];
                ai[2] = ai[1];
                ai[1] = ai[0];

                k = j + BlockEnd;
                tr = ar[0]*RealOut[k] - ai[0]*ImagOut[k];
                ti = ar[0]*ImagOut[k] + ai[0]*RealOut[k];

                RealOut[k] = RealOut[j] - tr;
                ImagOut[k] = ImagOut[j] - ti;

                RealOut[j] += tr;
                ImagOut[j] += ti;
            }
        }

        BlockEnd = BlockSize;
    }

    /*
    **   Need to normalize if inverse transform...
    */

    if ( InverseTransform )
    {
        double denom = (double)NumSamples;

        for ( i=0; i < NumSamples; i++ )
        {
            RealOut[i] /= denom;
            ImagOut[i] /= denom;
        }
    }
	
}

int IsPowerOfTwo ( unsigned x )
{
    if ( x < 2 )
        return FALSE;

    if ( x & (x-1) )        // Thanks to 'byang' for this cute trick!
        return FALSE;

    return TRUE;
}

unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo )
{
    unsigned i;

    if ( PowerOfTwo < 2 )
    {
        fprintf (
            stderr,
            ">>> Error in fftmisc.c: argument %d to NumberOfBitsNeeded is too small.\n",
            PowerOfTwo );

        exit(1);
    }

    for ( i=0; ; i++ )
    {
        if ( PowerOfTwo & (1 << i) )
            return i;
    }
}

unsigned ReverseBits ( unsigned index, unsigned NumBits )
{
    unsigned i, rev;

    for ( i=rev=0; i < NumBits; i++ )
    {
        rev = (rev << 1) | (index & 1);
        index >>= 1;
    }

    return rev;
}