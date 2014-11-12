// StoreImage.cpp: implementation of the CStoreImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StoreImage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStoreImage::CStoreImage()
{

}

CStoreImage::~CStoreImage()
{

}

void CStoreImage::SaveSubImage(CString filename, CPoint Store[255], int contfind, CVisByteImage *m_gray)
{
    
	
	CPoint inicio;
	CPoint fin;
    int i;
    char temporal[10];
    CString file;

	x_size =30; 
	y_size =30; 

	in = (char *) malloc(x_size*y_size);
	
	for(i=0;i<contfind;i++)
	{

	inicio.x=Store[i].x;
	inicio.y=Store[i].y;
	fin.x=Store[i].x+30;
	fin.y=Store[i].y+30;
	
	if (fin.y>=m_gray->Height())
		fin.y=m_gray->Height()-1;

	if (fin.x>=m_gray->Width())
		fin.x=m_gray->Width()-1;

	int t=0;
	
	  for (int y=inicio.y;y<fin.y;y++)
	  for(int x=inicio.x;x<fin.x;x++)
		{
	    in[t]=m_gray->Pixel(x,y);
		t++;
		}
	  _itoa(i,temporal,10);
	 
	 
     file=filename;
	 file=file+temporal+".pgm";           
	 PutImage(file);

	}
     free(in); 
}

void CStoreImage::PutImage(CString filename)
{
     FILE  *fd;


  if ((fd=fopen(filename,"wb")) == NULL) 
      AfxMessageBox("Can't output image");
  
  fprintf(fd,"P5\n");
  fprintf(fd,"%d %d\n",x_size,y_size);
  fprintf(fd,"255\n");
  
  if (fwrite(in,x_size*y_size,1,fd) != 1)
    AfxMessageBox("Can't write image");

  fclose(fd);
}

void CStoreImage::SaveImage(CString filename, CVisByteImage *m_gray)
{
  
	x_size=m_gray->Width();
	y_size=m_gray->Height();
	in = (char *) malloc(x_size*y_size);
	
	int t=0;
	for (int y = m_gray->Top();y < m_gray->Bottom();y++)
    for (int x = m_gray->Left();x < m_gray->Right();x++)
	{
        in[t]=m_gray->Pixel(x,y);
		t++;
	}
	 
	 PutImage(filename);
	 free(in);
}

CVisByteImage* CStoreImage::LoadImage(CString filename)
{
  
  GetImage(filename);
  
  CVisByteImage* m_gray = new CVisByteImage(x_size,y_size);
  
  int cont=0;
  for (int y = m_gray->Top();y < m_gray->Bottom();y++)
		   for ( int x = m_gray->Left();x < m_gray->Right();x++)
              m_gray->Pixel(x,y)=in[cont++];
			  
  return m_gray;
}

void CStoreImage::GetImage(CString filename)
{
  
char header [100];
int  tmp;
FILE *fd;

if ((fd=fopen(filename,"rb")) == NULL)

    AfxMessageBox("No se pudo abrir");
   else
   {

  /* {{{ read header */

  header[0]=fgetc(fd);
  header[1]=fgetc(fd);
  if(!(header[0]=='P' && header[1]=='5'))
    AfxMessageBox("Image does not have binary PGM header");

  x_size = GetInt(fd);
  y_size = GetInt(fd);
  tmp = GetInt(fd);

/* }}} */
  
  in = (char *) malloc(x_size * y_size);

  if (fread(in,1,x_size * y_size,fd) == 0)
    AfxMessageBox("Image is wrong size");

  fclose(fd);

   }
}

int CStoreImage::GetInt(FILE *fd)
{
 
  int c, i;
  char dummy[10000];

  c = getc(fd);
  while (1) // find next integer 
  {
    if (c=='#')    // if we're at a comment, read to end of line 
      fgets(dummy,9000,fd);
    if (c==EOF)
      AfxMessageBox("Image is not binary PGM");
    if (c>='0' && c<='9')
      break;   // found what we were looking for 
    c = getc(fd);
  }
  
  i = 0;
  while (1) {
    i = (i*10) + (c - '0');
    c = getc(fd);
    if (c==EOF) return (i);
    if (c<'0' || c>'9') break;
  }

  return (i);
}

CVisByteImage* CStoreImage::DevImage(int x,int y)
{
  
  CVisByteImage* m_gray = new CVisByteImage(x,y);
  
  int cont=0;
  for (y = m_gray->Top();y < m_gray->Bottom();y++)
		   for ( int x = m_gray->Left();x < m_gray->Right();x++)
              m_gray->Pixel(x,y)=in[cont++];
			  
  return m_gray;
}
