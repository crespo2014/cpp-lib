// Codec.h: interface for the CCodec class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODEC_H__4068BBC5_6BB3_11D3_A767_0000E856599A__INCLUDED_)
#define AFX_CODEC_H__4068BBC5_6BB3_11D3_A767_0000E856599A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  <vfw.h>
#include  <math.h>

class AFX_EXT_CLASS CCodec   
{
public:
	void PintaBmp(CClientDC *dc, CPoint org, LPVOID buffer, LPBITMAPINFO bih);
	LPVOID state;
	void FindDecompress(HWND hwndApp);
	void GetParamDecomp();
	void DeCompress(LPVOID BufferIn );
	void GetBitmapInfoHeader(LPBITMAPINFOHEADER binfo);
	
	DWORD dwCompressBufferSize;
	DWORD dwFormatSize;
	LPBITMAPINFOHEADER bihIn;
	LPBITMAPINFOHEADER bihOut;
	LPBITMAPINFO biIn;
	LPBITMAPINFO biOut;

	DWORD dwKeyFrameRate, dwQuality;
	LPVOID OutputBuffer;
	HIC hIC;
	
	void Compress(LPVOID BufferIn);
	void GetParamComp();
	void FindCompress(HWND hwndApp,DWORD quality);
	CCodec();
	virtual ~CCodec();

};

#endif // !defined(AFX_CODEC_H__4068BBC5_6BB3_11D3_A767_0000E856599A__INCLUDED_)
