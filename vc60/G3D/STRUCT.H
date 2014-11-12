#if !defined( _ESTRUCTURAS_HEADER_FILE_ )
#define _ESTRUCTURAS_HEADER_FILE_

#if _MSC_VER > 1000
#pragma once
#endif

#define UM_ACK     (WM_USER+1)
#define UM_COMMAND (WM_USER+2)
#define MAX_FIRE   10
#define MAX_OBJECT 5

#define UC_BEGIN    1
#define UC_PAUSE    2
#define UC_END      3
#define UC_FIRE     4

typedef struct S_FireParams
{
	BOOL     m_OnValid;
	double   m_distz;
	double   m_LastY;
	double   m_LastX;
	double   m_angXZ;
	double   m_angYZ1;
	double   m_angYZ2;
} FireParams;
typedef struct S_ObjectParams
{
	double m_MaxZ;
	double m_PosZ;
	double m_Vel;
	double m_PosY;
	double m_PosX;
	BOOL   m_OnValid;
	BOOL   m_Dir;
	int    m_List;
	DWORD  m_ID;

} ObjectParams;

typedef struct S_GameParams
{
	// Intercambio de informacion
	HANDLE  m_hEvent;
	// posicion del lente en coordenadas de la pantalla
	int     m_MouseX;
	int		m_MouseY;
	
	// posicion del jostick en cada instante de tiempo coordenadas normalizadas
	BOOL m_IsJoystick;
	double m_JoystickX;
	double m_JoystickY;
	double m_JoystickZ;

	// coordenadas sin normalizar
	int m_JX;
	int m_JY;
	
	// OpenGl
	GLuint m_ListBase;
	// Disparos
	double   m_FireY;
	double   m_FireX;
	double   m_FireFarZ;
	double   m_FireVel;
	double   m_FirePosX1;
	double   m_FirePosX2;
	double   m_FirePosY;
	// Colimador
	double m_PosX;
	double m_PosY;
	double m_PosZ;
	double m_dPos;
	double m_ImpactDist;
	int m_Points;

	// Objetos Impactados
	DWORD m_PointID[10];
	// Tiempo de la condicion
    SYSTEMTIME  m_STime;
	DWORD       m_CondMin;

} GameParams;

#endif