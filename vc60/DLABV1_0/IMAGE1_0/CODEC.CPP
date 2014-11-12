// Codec.cpp: implementation of the CCodec class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Codec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCodec::CCodec()
{

}

CCodec::~CCodec()
{

}

void CCodec::FindCompress(HWND hwndApp,DWORD quality)
{

biIn = (LPBITMAPINFO)malloc(sizeof(BITMAPINFO));
biIn->bmiHeader = *bihIn;
dwQuality = quality;
//---------------------------------------------------------
/*DWORD fccType;
fccType=ICTYPE_VIDEO;
ICINFO icinfo;
int size=0;


for (DWORD i=0; ICInfo(fccType, i, &icinfo); i++) 
{ 

   hIC = ICOpen(icinfo.fccType, icinfo.fccHandler, ICMODE_QUERY);     
	if (hIC) 
    {         // Skip this compressor if it can't handle the format. 
        if (//fccType != ICTYPE_VIDEO  biIn == NULL && 
            ICDecompressQuery(hIC,biIn, NULL) != ICERR_OK)                              
		{ 
          ICClose(hIC);             
			continue;         
		}  
        // Find out the compressor name. 
        ICGetInfo(hIC, &icinfo, sizeof(icinfo));  
        // Add it to the combo box. 
        icinfo.szDescription; 
       if (icinfo.dwFlags!=VIDCF_CRUNCH)
	   {
	      ICClose(hIC);             
		  continue;
	   }       
		
     } 
} 	


	
*/	
	
//----------------------------------------------------------	
//Esta funcion es para buscar el codec que sirve para comprimir
// el formato correspondiente
hIC = ICLocate (ICTYPE_VIDEO, 0L, bihIn, NULL, ICMODE_FASTCOMPRESS ); 
//aqui se encuesta si el codec tiene ventana de configuracion y se
//muestra
if (ICQueryConfigure(hIC)) ICConfigure(hIC, hwndApp);

    DWORD size;
    COMPVARS* state;

	size = ICGetStateSize(hIC);
	state = (COMPVARS*) malloc(sizeof(COMPVARS));
	ICGetState(hIC,state,size);
	state->lQ=quality;
    ICSetState(hIC,state,size);

	
}

void CCodec::GetParamComp()
{
    //con esta funcion se obtiene la cantidad de cuadros entre
	//frame llaves
	dwKeyFrameRate = ICGetDefaultKeyFrameRate(hIC); 
    
	//esta funcion retorna el valor de la calidad de compresion
	//variando este valor se puede comprimir mas o menos
	//dwQuality = ICGetDefaultQuality(hIC);
    
	//aqui se obtiene el tamaño para la estructura del 
	//formato de salida teniendo el cuenta el formato de entrada
	

	dwFormatSize = ICCompressGetFormatSize(hIC, biIn);
	
	biOut =(LPBITMAPINFO)malloc(dwFormatSize);
	bihOut = &biOut->bmiHeader;
	//aqui se obtiene el formato de salida
	ICCompressGetFormat(hIC, biIn, biOut);
	
	//tamaño del buffer de salida comprimido
	dwCompressBufferSize = ICCompressGetSize(hIC, biIn, biOut);  
    
	// reservar memoria para el buffer de salida
	OutputBuffer = calloc(dwCompressBufferSize,1);

}

void CCodec::Compress(LPVOID BufferIn)
{
    DWORD dwCkID; 
	DWORD dwCompFlags; 
	 
	if (ICCompressBegin(hIC, biIn, biOut) == ICERR_OK)
	{ 
	if (ICCompress(hIC, 0, bihOut, OutputBuffer, bihIn, BufferIn, 
				&dwCkID, &dwCompFlags, 1, 
				0, dwQuality, NULL, NULL) == ICERR_OK)        
			{ 
				
			   //hace algo con los datos comprimidos            
			}
			else         
			{             
				// manejar error de compresion 
			}     
		     
		ICCompressEnd(hIC);    
	 } 
	else 
	{ 
		// manejar error de formato 
	}
	
}

void CCodec::GetBitmapInfoHeader(LPBITMAPINFOHEADER binfo)
{
   bihIn = binfo;
}

void CCodec::DeCompress(LPVOID BufferIn)
{
  if (ICDecompressBegin(hIC, biIn, biOut) == ICERR_OK)
  {
   if (ICDecompress(hIC, 0, bihIn, BufferIn, bihOut,OutputBuffer) == ICERR_OK) 
        { 
            // Frame decompressed OK so we can process it as required. 
        }         
   else         
   { 
            // Handle the decompression error that occurred.         
   } 
   ICDecompressEnd(hIC); 
   }
}

void CCodec::GetParamDecomp()
{
    dwFormatSize = ICDecompressGetFormatSize(hIC, biIn); 
	biOut =(LPBITMAPINFO)malloc(dwFormatSize);
	ICDecompressGetFormat(hIC, biIn, biOut); 
	bihOut=&biOut->bmiHeader;
	OutputBuffer = malloc(bihOut->biSizeImage);

}

void CCodec::FindDecompress(HWND hwndApp)
{
  biIn = (LPBITMAPINFO)malloc(sizeof(BITMAPINFO));
  biIn->bmiHeader = *bihIn;
  
  hIC = ICLocate (ICTYPE_VIDEO, 0L, bihIn, NULL,ICMODE_FASTDECOMPRESS ); 
  if (ICQueryConfigure(hIC)) ICConfigure(hIC, hwndApp);

}



void CCodec::PintaBmp(CClientDC *dc, CPoint org, LPVOID buffer, LPBITMAPINFO bih)
{
    CRect rect(0,0,192,142);
    
    SetDIBitsToDevice(dc->GetSafeHdc(), org.x, org.y,
					rect.Width(), rect.Height(),
					rect.left, 142 - rect.bottom,
					0, rect.Height(), buffer,
					bih,
					DIB_RGB_COLORS);
}   
