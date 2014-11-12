// GrafSig.cpp: implementation of the CGrafSig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GrafSig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrafSig::CGrafSig()
{
//	m_IsThread=true;
	m_OnInit=false;

	pixelDesc.nSize =sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion=1;
	pixelDesc.dwFlags= PFD_DRAW_TO_WINDOW|
						PFD_SUPPORT_OPENGL|
						PFD_DOUBLEBUFFER;
	pixelDesc.iPixelType =PFD_TYPE_RGBA;
	pixelDesc.cColorBits=24;
	pixelDesc.cRedBits=8;
	pixelDesc.cRedShift=16;
	pixelDesc.cGreenBits=8;
	pixelDesc.cGreenShift=8;
	pixelDesc.cBlueBits=8;
	pixelDesc.cBlueShift=0;
	pixelDesc.cAlphaBits		= 0;
	pixelDesc.cAlphaShift		= 0;
	pixelDesc.cAccumBits		= 0;	
	pixelDesc.cAccumRedBits		= 0;
	pixelDesc.cAccumGreenBits	= 0;
	pixelDesc.cAccumBlueBits	= 0;
	pixelDesc.cAccumAlphaBits	= 0;
	pixelDesc.cDepthBits		= 0;
	pixelDesc.cStencilBits		= 0;
	pixelDesc.cAuxBuffers		= 0;
	pixelDesc.iLayerType		= PFD_MAIN_PLANE;
	pixelDesc.bReserved		= 0;
	pixelDesc.dwLayerMask		= 0;
	pixelDesc.dwVisibleMask		= 0;
	pixelDesc.dwDamageMask		= 0;

	
}

CGrafSig::~CGrafSig()
{

}

BEGIN_MESSAGE_MAP(CGrafSig, COpenGl10)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// 
//  Aspectos del hilo
//  mensage WM_USER+
//

UINT GrafSignalThread(LPVOID pParam)
{
	GrafExchange* m_ThreadData=(GrafExchange*)pParam;
	MSG m_msg;
	
	// Se genero un mensage OnPaint
	BOOL m_OnPaint=false;
	// Se esta muestreando
	BOOL m_OnSampling=false;
	// No se esta graficando
	BOOL m_OnVisible=true;

	WORD m_Height;
	WORD m_Width;
	BOOL m_OnSize=false;  // Indica que ya se recibio el tamano de la ventana

	
	// Proyeccion ortogonal en OpenGL
	int m_GrafMinX=0;
	int m_GrafMaxX=0;
	int m_GrafMinY=0;
	int m_GrafMaxY=0;
	int m_GrafMinZ=0;
	int m_GrafMaxZ=1;
	

	// Barras de desplazamiento
	int   m_LineHeight=3;
	int   m_LineWidth=3;
	int   m_LinePosY[6+2];
	BOOL  m_OnLineMov=false;
	int   m_LineMov;
//	DWORD m_LineUp;
	int m_LineDown;

	BYTE m_GrafCant=6;	
	// Buffer para el almacenamiento de la senal;
	double m_SignalInput1[256];  // RAW EEG
	double m_SignalInput2[256];  // Temperature 
	double m_SignalBetha[256];  // Betha
	double m_SignalTheta[256];  // Theta
	double m_SignalAlpha[256];  // Alpha
	double m_SignalMuscle[256]; // EMG

	int m_CantRead;
	double m_TempBuffer[256];

	WORD i;

	// Garficos de senales y sus parametros
	int m_GrafUp=14;   // Separacion o altura respecto a la divisoria inferior
	int m_GrafDown=8; //  "           "      "                "     superior 
	int m_GrafLeft=27;
	int m_GrafRight=27;
	int m_GrafHeight;
	int m_GrafWidth;

	int m_GrafOut;    // Valor a mostrar acotamiento;

	// Mouse
	HCURSOR m_hCursor[2]=
	{
		LoadCursor(NULL,IDC_ARROW),
		LoadCursor(NULL,IDC_SIZENS) 
	};
	short m_MouseX;
	short m_MouseY;
	DWORD m_MousefwKeys;
	int m_MouseGrafX;
	int m_MouseGrafY;

	m_ThreadData->m_CursorType=m_hCursor[0];

	// Numeracion
	CGlNumber m_Number1;
	
	// Cadenas
	CGlString m_String1,m_String2,m_String3,m_String4,m_String5,m_String6;

	m_String1.m_Buffer="Raw EEG";
	m_String2.m_Buffer="Temp";
	m_String3.m_Buffer="Theta";
	m_String4.m_Buffer="Alpha";
	m_String5.m_Buffer="Betha";
	m_String6.m_Buffer="EMG";

	for (i=0;i<256;i++)
	{
		m_SignalInput1[i]=0;  // RAW EEG
		m_SignalInput2[i]=0;  // Temperature 
		m_SignalBetha[i]=0;  // Betha
		m_SignalTheta[i]=0;  // Theta
		m_SignalAlpha[i]=0;  // Alpha
		m_SignalMuscle[i]=0; // EMG
	}



	// Seleccionar en RC
	if (!wglMakeCurrent(m_ThreadData->m_hDC,m_ThreadData->m_GLContext))
		return 56;	
	// Inizializacion de las openGl
	
	glClearColor(0,0,0,1);
	glColor3ub(255,255,255);

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
    glDisable(GL_DITHER);
    glDisable(GL_FOG);
	glDisable(GL_LIGHTING);
	glDisable(GL_LOGIC_OP); 
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_TEXTURE_1D); 
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_LINE_STIPPLE);
	glDisable(GL_LOGIC_OP);
	glDisable(GL_NORMALIZE);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	glDisable(GL_POLYGON_STIPPLE);
	glDisable(GL_TEXTURE_1D);
	glDisable(GL_TEXTURE_2D);
	glPixelStorei(GL_PACK_ALIGNMENT,20);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS,0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS,0); 
	
	while (true)
	{
		if ((!m_OnSampling)|(!m_OnSize))
		{
			// Esperar por un mensaje
			if (!PeekMessage(&m_msg,NULL,NULL,NULL,PM_NOREMOVE))
				WaitMessage();
		}
		if (PeekMessage(&m_msg,NULL,NULL,NULL,PM_REMOVE))
		{
			switch(m_msg.message)
			{
			case WM_PAINT:
				{
					m_OnPaint=true;
					SetEvent(m_ThreadData->m_hEvent1);
					break;
				}
			case WM_SIZE:
				{
					m_OnSize=true;
					m_Width=LOWORD(m_msg.lParam);
					m_Height=HIWORD(m_msg.lParam);

					glViewport(0,0,m_Width,m_Height);
					glMatrixMode(GL_PROJECTION);
					glLoadIdentity();
					glOrtho(0,m_Width,0,m_Height,0,1);	
					m_GrafMinX=0;
					m_GrafMaxX=m_Width;
					m_GrafMinY=0;
					m_GrafMaxY=m_Height;
					
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glDrawBuffer(GL_BACK);

					// Ubicacion de las lineas
					for (i=0;i<m_GrafCant+1;i++)
					{
						m_LinePosY[i]=(m_GrafMaxY-m_GrafMinY)/m_GrafCant*i;
					}

					//SetEvent(m_ThreadData->m_hEvent1);
					break;
				}
			case WM_CLOSE:
				{
					wglMakeCurrent(NULL,NULL);
					wglDeleteContext(m_ThreadData->m_GLContext);
					SetEvent(m_ThreadData->m_hEvent1);
					return 0;
				}
			case WM_MOUSEMOVE:
				{
					m_MouseX=LOWORD(m_msg.lParam);
					m_MouseY=HIWORD(m_msg.lParam);
					m_MousefwKeys=m_msg.wParam;
					
					m_MouseGrafY=m_Height-m_MouseY;
					m_MouseGrafX=m_MouseX;

					if ((m_OnLineMov) &(m_MousefwKeys & MK_LBUTTON))
					{
						if (m_MouseGrafY > m_GrafMaxY-m_LineHeight)
							m_MouseGrafY=m_GrafMaxY-m_LineHeight;
						if (m_MouseGrafY < m_GrafMinX+m_LineHeight*(m_LineMov)*2)
							m_MouseGrafY = m_GrafMinX+m_LineHeight*(m_LineMov)*2;

						// Subir o bajar a los qu estan arriba
						m_LineDown=m_LinePosY[m_LineMov]-m_MouseGrafY; 
						//if (m_LineDown > 0)
						{
							for (i=m_LineMov+1;i<m_GrafCant;i++)
								m_LinePosY[i]-=m_LineDown;
						}
						m_LinePosY[m_LineMov]=m_MouseGrafY; 

						/*
						// Si estoy subiendo y hay superposicion los subo a todos
						m_LineUp=m_LinePosY[m_LineMov+1]-m_LinePosY[m_LineMov]-m_LineHeight*2;
						if (m_LineUp < 0)
						{
							// Subir todas la lineas
							for (i=m_LineMov+1;i<m_GrafCant;i++)
								m_LinePosY[i]-=m_LineUp;
						}
						*/
						// Si estoy bajando y hay superposicion
						for (i=m_LineMov-1;i>0;i--)
						{
							if (m_LinePosY[i+1]-m_LinePosY[i] <	m_LineHeight*2)
								m_LinePosY[i]=m_LinePosY[i+1]-m_LineHeight*2;
						}
						m_OnPaint=true;
						break;
					}
					for (i=1;i<m_GrafCant+1;i++)
					{
						if ((m_MouseGrafY-m_LinePosY[i] < m_LineHeight)
							& (m_MouseGrafY-m_LinePosY[i] > -m_LineHeight))
						{
							if (m_LinePosY[i]>m_GrafMaxY)
								break;
							m_ThreadData->m_CursorType=m_hCursor[1];
							break;							
						}
						m_ThreadData->m_CursorType=m_hCursor[0];
					}
					break;
				}
			case WM_LBUTTONDOWN:
				{
					for (i=1;i<m_GrafCant+1;i++)
					{
						if ((m_MouseGrafY-m_LinePosY[i] < m_LineHeight)
							& (m_MouseGrafY-m_LinePosY[i] > -m_LineHeight))
						{
							if (m_LinePosY[i]>m_GrafMaxY)
								break;
							m_ThreadData->m_CursorType=m_hCursor[1];
							m_OnLineMov=true;
							m_LineMov=i;
							break;							
						}
					}
					break;
				}
			case WM_LBUTTONUP:
				{
					m_OnLineMov=false;
					break;
				}
			case WM_USER+1:
				{
					switch(m_msg.wParam)
					{
					case 0:
						{
							SetEvent(m_ThreadData->m_hEvent1);
							break;
						}
					case 2:
						{
							m_OnSampling=true;
							SetEvent(m_ThreadData->m_hEvent1);
							break;
						}
					case 3:
						{
							m_OnSampling=false;
							SetEvent(m_ThreadData->m_hEvent1);
							break;
						}
					}
					break;
				}
			} // end de switch message
		} // end of PeekMessage
		
		if (m_OnSampling)
		{
		    m_CantRead=m_ThreadData->m_Device->GetPlainDataBuffer(&m_CantRead,m_TempBuffer);
			memmove(&m_SignalInput1[0],&m_SignalInput1[m_CantRead],(256-m_CantRead)*sizeof(double));
			memcpy(&m_SignalInput1[256-m_CantRead],m_TempBuffer,m_CantRead*sizeof(double));	

			m_CantRead=m_ThreadData->m_Device->GetAlphaDataBuffer(&m_CantRead,m_TempBuffer);
			memmove(&m_SignalAlpha[0],&m_SignalAlpha[m_CantRead],(256-m_CantRead)*sizeof(double));
			memcpy(&m_SignalAlpha[256-m_CantRead],m_TempBuffer,m_CantRead*sizeof(double));	

			m_CantRead=m_ThreadData->m_Device->GetThetaDataBuffer(&m_CantRead,m_TempBuffer);
			memmove(&m_SignalTheta[0],&m_SignalTheta[m_CantRead],(256-m_CantRead)*sizeof(double));
			memcpy(&m_SignalTheta[256-m_CantRead],m_TempBuffer,m_CantRead*sizeof(double));	

			m_CantRead=m_ThreadData->m_Device->GetBetaDataBuffer(&m_CantRead,m_TempBuffer);
			memmove(&m_SignalBetha[0],&m_SignalBetha[m_CantRead],(256-m_CantRead)*sizeof(double));
			memcpy(&m_SignalBetha[256-m_CantRead],m_TempBuffer,m_CantRead*sizeof(double));

			m_CantRead=m_ThreadData->m_Device->GetMuscleDataBuffer(&m_CantRead,m_TempBuffer);
			memmove(&m_SignalMuscle[0],&m_SignalMuscle[m_CantRead],(256-m_CantRead)*sizeof(double));
			memcpy(&m_SignalMuscle[256-m_CantRead],m_TempBuffer,m_CantRead*sizeof(double));

			m_CantRead=m_ThreadData->m_Device->GetTemperatureDataBuffer(&m_CantRead,m_TempBuffer);
			memmove(&m_SignalInput2[0],&m_SignalInput2[m_CantRead],(256-m_CantRead)*sizeof(double));
			memcpy(&m_SignalInput2[256-m_CantRead],m_TempBuffer,m_CantRead*sizeof(double));
		}
			
		if ((m_OnPaint|m_OnSampling)& (m_OnSize))
		{
		// 
		// A partir de aqui es que se dibuja
		//
			m_OnPaint=false;
			
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glTranslated(0.0,0.0,-0.5);
		glColor3ub(0,255,0);

		for (i=0;i<m_GrafCant;i++)
		{
			if (m_LinePosY[i]> m_GrafMaxY)
				break;
			if (m_LinePosY[i+1]-m_LinePosY[i]-m_GrafUp-m_GrafDown > 2)
			{
				// Grafico 1
				glColor3ub(255,0,0);
				glBegin(GL_LINE_STRIP);
				  glVertex3d(m_GrafMinX+m_GrafLeft,m_LinePosY[i+1]-m_GrafUp,0);
				  glVertex3d(m_GrafMinX+m_GrafLeft,m_LinePosY[i]+m_GrafDown,0);
				  glVertex3d(m_GrafMaxX-m_GrafRight,m_LinePosY[i]+m_GrafDown,0);
				 glEnd();
				glRasterPos3d(m_GrafMinX+2,m_LinePosY[i]+m_GrafDown,0.5);
				m_Number1.m_Number=0;
				m_Number1.Paint();
				glRasterPos3d(m_GrafMinX+2,m_LinePosY[i+1]-m_GrafUp-10,0.5);
				m_Number1.m_Number=255;
				m_Number1.Paint();
			}
			
			if (i!=0)
			{
			// Linea Divisora
			glColor3ub(0,0,255);
			glBegin(GL_LINES);
			glVertex3d(m_GrafMinX,m_LinePosY[i],0);
			glVertex3d(m_GrafMaxX,m_LinePosY[i],0);
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex3d(m_GrafMinX,m_LinePosY[i]+m_LineHeight,0);
			glVertex3d(m_GrafMinX,m_LinePosY[i]-m_LineHeight,0);
			glVertex3d(m_GrafMinX+m_LineWidth,m_LinePosY[i],0);
			
			glVertex3d(m_GrafMaxX,m_LinePosY[i]+m_LineHeight,0);
			glVertex3d(m_GrafMaxX,m_LinePosY[i]-m_LineHeight,0);
			glVertex3d(m_GrafMaxX-m_LineWidth,m_LinePosY[i],0);
			glEnd();
			}
			
		}

		//
		// Graficacion de senales
		//

		m_GrafWidth=m_Width-m_GrafLeft-m_GrafRight-2;

		// Senal del musculo
		// Ver si estan pegadas las lineas divisorias
		if (m_LinePosY[1] > m_LineHeight*2)
		{
			m_GrafHeight=m_LinePosY[1];
			// Ver si Cabe el cartel
			if (m_GrafHeight>11)
			{
				// Dejar un espacio
				glColor3ub(255,255,255);
				glRasterPos3d(m_LineWidth,m_LinePosY[1]-11,0.5);
				m_String6.Paint();
				m_GrafHeight=m_GrafHeight-m_GrafUp-m_GrafDown-2;

				if (m_GrafHeight > 2)
				{
					// Divbujar el grafico
					glColor3ub(255,255,255);
					glBegin(GL_LINE_STRIP);
					for (i=0;i<256;i++)
					{
						m_GrafOut=(int)m_SignalMuscle[i]/256*m_GrafHeight/2+m_GrafHeight/2;
						if (m_GrafOut > m_GrafHeight)
							m_GrafOut=m_GrafHeight;
						glVertex3d((double)i*m_GrafWidth/256+m_GrafLeft+1,m_GrafOut+m_GrafDown,0.0);
					}
					glEnd();
				}
			}
		}

		// Senal 2 Betha
		if (m_LinePosY[2]-m_LinePosY[1] > m_LineHeight*2)
		{
			m_GrafHeight=m_LinePosY[2]-m_LinePosY[1];
			// Ver si Cabe el cartel
			if (m_GrafHeight>11)
			{
				// Dejar un espacio
				glColor3ub(255,255,255);
				glRasterPos3d(m_LineWidth,m_LinePosY[2]-11,0.5);
				m_String5.Paint();
				m_GrafHeight=m_GrafHeight-m_GrafUp-m_GrafDown-2;

				if (m_GrafHeight > 2)
				{
					// Divbujar el grafico
					glColor3ub(255,255,255);
					glBegin(GL_LINE_STRIP);
					for (i=0;i<256;i++)
					{
						m_GrafOut=(int)m_SignalBetha[i]/256*m_GrafHeight/2+m_GrafHeight/2;
						if (m_GrafOut > m_GrafHeight)
							m_GrafOut=m_GrafHeight;
						glVertex3d((double)i*m_GrafWidth/256+m_GrafLeft+1,m_LinePosY[1]+m_GrafOut+m_GrafDown,0.0);
					}
					glEnd();
				}
			}
		}

		// Senal alpha
		m_GrafHeight=m_LinePosY[3]-m_LinePosY[2];
		if (m_GrafHeight > m_LineHeight*2)
		{
			// Ver si Cabe el cartel
			if (m_GrafHeight>11)
			{
				// Dejar un espacio
				glColor3ub(255,255,255);
				glRasterPos3d(m_LineWidth,m_LinePosY[3]-11,0.5);
				m_String4.Paint();
				m_GrafHeight=m_GrafHeight-m_GrafUp-m_GrafDown-2;

				if (m_GrafHeight > 2)
				{
					// Divbujar el grafico
					glColor3ub(255,255,255);
					glBegin(GL_LINE_STRIP);
					for (i=0;i<256;i++)
					{
						m_GrafOut=(int)m_SignalBetha[i]/256*m_GrafHeight/2+m_GrafHeight/2;
						if (m_GrafOut > m_GrafHeight)
							m_GrafOut=m_GrafHeight;
						glVertex3d((double)i*m_GrafWidth/256+m_GrafLeft+1,m_LinePosY[2]+m_GrafOut+m_GrafDown,0.0);
					}
					glEnd();
				}
			}
		}

		// Senal tetha
		m_GrafHeight=m_LinePosY[4]-m_LinePosY[3];
		if (m_GrafHeight > m_LineHeight*2)
		{
			// Ver si Cabe el cartel
			if (m_GrafHeight>11)
			{
				// Dejar un espacio
				glColor3ub(255,255,255);
				glRasterPos3d(m_LineWidth,m_LinePosY[4]-11,0.5);
				m_String3.Paint();
				m_GrafHeight=m_GrafHeight-m_GrafUp-m_GrafDown-2;

				if (m_GrafHeight > 2)
				{
					// Divbujar el grafico
					glColor3ub(255,255,255);
					glBegin(GL_LINE_STRIP);
					for (i=0;i<256;i++)
					{
						m_GrafOut=(int)m_SignalBetha[i]/256*m_GrafHeight/2+m_GrafHeight/2;
						if (m_GrafOut > m_GrafHeight)
							m_GrafOut=m_GrafHeight;
						glVertex3d((double)i*m_GrafWidth/256+m_GrafLeft+1,m_LinePosY[3]+m_GrafOut+m_GrafDown,0.0);
					}
					glEnd();
				}
			}
		}

		// Temperatura
		m_GrafHeight=m_LinePosY[5]-m_LinePosY[4];
		if (m_GrafHeight > m_LineHeight*2)
		{
			// Ver si Cabe el cartel
			if (m_GrafHeight>11)
			{
				// Dejar un espacio
				glColor3ub(255,255,255);
				glRasterPos3d(m_LineWidth,m_LinePosY[5]-11,0.5);
				m_String3.Paint();
				m_GrafHeight=m_GrafHeight-m_GrafUp-m_GrafDown-2;

				if (m_GrafHeight > 2)
				{
					// Divbujar el grafico
					glColor3ub(255,255,255);
					glBegin(GL_LINE_STRIP);
					for (i=0;i<256;i++)
					{
						m_GrafOut=(int)m_SignalBetha[i]/256*m_GrafHeight/2+m_GrafHeight/2;
						if (m_GrafOut > m_GrafHeight)
							m_GrafOut=m_GrafHeight;
						glVertex3d((double)i*m_GrafWidth/256+m_GrafLeft+1,m_LinePosY[4]+m_GrafOut+m_GrafDown,0.0);
					}
					glEnd();
				}
			}
		}

		// Senal de entrada
		m_GrafHeight=m_LinePosY[6]-m_LinePosY[5];
		if (m_GrafHeight > m_LineHeight*2)
		{
			// Ver si Cabe el cartel
			if (m_GrafHeight>11)
			{
				// Dejar un espacio
				glColor3ub(255,255,255);
				glRasterPos3d(m_LineWidth,m_LinePosY[6]-11,0.5);
				m_String1.Paint();
				m_GrafHeight=m_GrafHeight-m_GrafUp-m_GrafDown-2;

				if (m_GrafHeight > 2)
				{
					// Divbujar el grafico
					glColor3ub(255,255,255);
					glBegin(GL_LINE_STRIP);
					for (i=0;i<256;i++)
					{
						m_GrafOut=(int)m_SignalBetha[i]/256*m_GrafHeight+1;
						if (m_GrafOut > m_GrafHeight)
							m_GrafOut=m_GrafHeight;
						glVertex3d((double)i*m_GrafWidth/256+m_GrafLeft+1,m_LinePosY[5]+m_GrafOut+m_GrafDown,0.0);
					}
					glEnd();
				}
			}
		}

		glPopMatrix();
		glFlush();
		SwapBuffers(m_ThreadData->m_hDC);
		m_OnPaint=false;
		}

	}  // end del while(true)
	return 0;
}

int CGrafSig::BeginPaint()
{
	m_ThreadData.m_hEvent1=CreateEvent(NULL,false,false,NULL);
	if (!m_ThreadData.m_hEvent1)
	{
		TRACE0("Creating Event Failed");
		return false;
	}

	m_ThreadData.m_GLContext=m_hGLContext;
	m_ThreadData.m_hDC=m_hDC;
	m_ThreadData.m_hWnd=GetSafeHwnd();


	m_RenderThread=AfxBeginThread(GrafSignalThread,&m_ThreadData,THREAD_PRIORITY_ABOVE_NORMAL);
	PostThreadMessage(m_RenderThread->m_nThreadID,WM_USER+1,0,0);
	if (WaitForSingleObject(m_ThreadData.m_hEvent1,INFINITE)!=WAIT_OBJECT_0)
	{
		TRACE0("Wait Failed");
		return false;
	}
	m_OnInit=true;
	return true;
}

int CGrafSig::GlInit()
{
	return BeginPaint();
	
}

void CGrafSig::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	PostThreadMessage(m_RenderThread->m_nThreadID,WM_SIZE,nType,MAKELPARAM(cx,cy));
//	WaitForSingleObject(m_ThreadData.m_hEvent1,INFINITE);
}

int CGrafSig::Close()
{
	if (!m_OnInit)
		return true;
	while (true)
	{
		PostThreadMessage(m_RenderThread->m_nThreadID,WM_CLOSE,0,0);
		if (WaitForSingleObject(m_ThreadData.m_hEvent1,5000)==WAIT_OBJECT_0)
			break;
	}
	WaitForSingleObject(m_RenderThread->m_hThread,INFINITE);
	CloseHandle(m_ThreadData.m_hEvent1);
	m_OnInit=false;
	return true;
}

int CGrafSig::SetDevice(CDevice *pDevice)
{
	m_ThreadData.m_Device=pDevice;
	return true;
}

void CGrafSig::OnPaint()
{
	CPaintDC dc(this);
	PostThreadMessage(m_RenderThread->m_nThreadID,WM_PAINT,0,0);
//	WaitForSingleObject(m_ThreadData.m_hEvent1,INFINITE);
}

int CGrafSig::BeginSampling()
{
	PostThreadMessage(m_RenderThread->m_nThreadID,WM_USER+1,2,0);
	WaitForSingleObject(m_ThreadData.m_hEvent1,INFINITE);
	return true;
}

int CGrafSig::StopSampling()
{
	PostThreadMessage(m_RenderThread->m_nThreadID,WM_USER+1,3,0);
	WaitForSingleObject(m_ThreadData.m_hEvent1,INFINITE);
	return true;
}

void CGrafSig::OnDestroy()
{
	Close();
}

BOOL CGrafSig::PreTranslateMessage( MSG* pMsg )
{
	MyWindowProc(pMsg->message,pMsg->wParam,pMsg->lParam);
	return CWnd::PreTranslateMessage(pMsg);
}

LRESULT CGrafSig::MyWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message > (WM_MOUSEFIRST-1))
		if (message < (WM_MOUSELAST+1))
	{
		PostThreadMessage(m_RenderThread->m_nThreadID,message,wParam,lParam);
		return true;
	}
	return false;
}

BOOL CGrafSig::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	SetCursor(m_ThreadData.m_CursorType);
	return false;
}

void CGrafSig::OnLButtonDown( UINT nFlags, CPoint point )
{
	SetCapture();
}

void CGrafSig::OnLButtonUp( UINT nFlags, CPoint point )
{
	ReleaseCapture();
}

BOOL CGrafSig::OnEraseBkgnd( CDC* pDC )
{
	return true;
}
