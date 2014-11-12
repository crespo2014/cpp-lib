// Piezas.h: interface for the Pieza_01 class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_PIEZAS_H__72DE4BC1_1CAC_11D3_9A2B_000021B01127__INCLUDED_)
#define AFX_PIEZAS_H__72DE4BC1_1CAC_11D3_9A2B_000021B01127__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Formas.h"

class CPieza_01  
{
public:
	void Paint();
	CPieza_01();
	virtual ~CPieza_01();

};

class CPieza_02  
{
public:
	void Paint();
	CPieza_02();
	virtual ~CPieza_02();

};

class CPieza_03  
{
public:
	void Paint();
	CPieza_03();
	virtual ~CPieza_03();

};

class CPieza_04  
{
public:
	int Direccion;
	void Paint();
	CPieza_04();
	virtual ~CPieza_04();

};

class CPieza_04_YZ : public CPieza_04
{

public:
	void Paint();
	CPieza_04_YZ();
	virtual ~CPieza_04_YZ();
};

class CMotorXZ : public CCilindroXZ
{
public:
	void SetDir(BOOL param);
	int Direccion;
	void Paint();
	CMotorXZ();
	virtual ~CMotorXZ();

};

class CMotorXY : public CMotorXZ
{
public:
	void Paint();
	CMotorXY();
	virtual ~CMotorXY();

};

class CMotorZY : public CMotorXZ
{
public:
	void Paint();
	CMotorZY();
	virtual ~CMotorZY();

};


// Cabeza de los tornillos
class CCabezaXZ
{
public:
	CCabezaXZ();
	void SetDir(BOOL param);
	int Direccion;
	void Paint();
	virtual ~CCabezaXZ();
};

class CCabezaYZ : public CCabezaXZ
{
public:
	CCabezaYZ();
	void Paint();
	virtual ~CCabezaYZ();
};

class CPieza_05_01
{
public:
	float ang;
	void Paint();
	CPieza_05_01();
	virtual ~CPieza_05_01();

};

class CPieza_05 : public CPieza_05_01
{
public:

	void Paint();
	CPieza_05();
	virtual ~CPieza_05();
};



#endif // !defined(AFX_PIEZAS_H__72DE4BC1_1CAC_11D3_9A2B_000021B01127__INCLUDED_)
