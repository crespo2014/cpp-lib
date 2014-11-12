// Fft.h: interface for the CFft class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FFT_H__BED07993_03E6_11D5_9041_0000E83D722B__INCLUDED_)
#define AFX_FFT_H__BED07993_03E6_11D5_9041_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFft  
{
public:
	CFft();
	virtual ~CFft();
	unsigned ReverseBits ( unsigned index, unsigned NumBits );
	void FftDouble(unsigned int NumSamples, int InverseTransform, double *RealIn, double *ImagIn, double *RealOut, double *ImagOut);
	int IsPowerOfTwo ( unsigned x );
	unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo );

};

#endif // !defined(AFX_FFT_H__BED07993_03E6_11D5_9041_0000E83D722B__INCLUDED_)
