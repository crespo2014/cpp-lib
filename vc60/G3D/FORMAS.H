// Formas.h: interface for the Formas class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMAS_H__FAEECCE1_1CC7_11D3_9A2B_000021B01127__INCLUDED_)
#define AFX_FORMAS_H__FAEECCE1_1CC7_11D3_9A2B_000021B01127__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "math.h"

void FillSin();
double Seno(int pAngulo);
double Coseno(int pAngulo);
double Tangente(int pAngulo);

void SetResolution(int param);
int GetResolution();


class CEngraneXZ
{
public:
	Paint();
	CEngraneXZ();
	CEngraneXZ(double pradio1,double pradio2,double paltura,int pdientes);
	Set(double pradio1,double pradio2,double paltura,int pdientes);
	Enabled(int param);

	// Variables
public:
	double radio1,radio2,altura;
	int dientes;
	BOOL Tape0,Tape1;
};

class CCilindroXZ
{
public:
	Paint();
	CCilindroXZ(double pradio,double paltura); 
	CCilindroXZ();
	Set(double pradio,double paltura);
	Enabled(int param);
public:
	double radio,altura;
	BOOL Tape0,Tape1;

};

class CConoXZ
{
public:
    Paint();
	CConoXZ(double pRadio,double pHaltura);
	CConoXZ();
	Set(double pRadio,double pHaltura);
	Enabled(int param);
public:
	double m_Haltura,m_Radio;
	BOOL m_Tape0;

};


class CEngraneYZ : public CEngraneXZ
{
public:
	Paint();
	CEngraneYZ();
	CEngraneYZ(double pradio1,double pradio2,double paltura,int pdientes);
};


class CEngraneXY : public CEngraneXZ
{
public:
	Paint();
	CEngraneXY();
	CEngraneXY(double pradio1,double pradio2,double paltura,int pdientes);

};

class CCilindroXY : public CCilindroXZ
{
public:
	CCilindroXY(double pradio,double paltura); 
	CCilindroXY();
	Paint();
};

class CCilindroYZ : public CCilindroXZ
{
public:
	Paint();
	CCilindroYZ(double pradio,double paltura); 
	CCilindroYZ();
};

class CCaja
{
public:
	void Set(double pHeight, double pWidth,double pDepth);
	Paint();
	CCaja();
	CCaja(double pHeight, double pWidth,double pDepth);
private:
	double Depth;
	double Width;
	double Height;
};

class CEsfera
{
public:
	CEsfera();
	CEsfera( double pradio);
	Set(double pradio);
	Paint();
public:
	double radio;
};

class CPoleaXZ : public CCilindroXZ
{
public:
	CPoleaXZ();
	CPoleaXZ(double pradioExt, double pradioInt, double phExt, double phInt);
	Enabled(int param);
	Set(double pradioExt, double pradioInt, double phExt, double phInt);
	Paint();
public:
	BOOL Tapa0,Tapa1;
	BOOL Cilindro0,Cilindro1;
	double radioExt,radioInt,hExt,hInt;
};

class CPoleaXY : public CPoleaXZ
{
public:
	CPoleaXY();
	CPoleaXY(double pradioExt, double pradioInt, double phExt, double phInt);
	Paint();
};

class CPoleaZY : public CPoleaXZ
{
public:
	CPoleaZY();
	CPoleaZY(double pradioExt, double pradioInt, double phExt, double phInt);
	Paint();
};

class CAnilloXZ
{
public:
	void Enable (int param);
	void Set(double pradioInt, double pradioExt, double paltura);
	BOOL Tape0,Tape1,TapeInt,TapeExt;
	double altura;
	double RadioInt;
	double RadioExt;
	CAnilloXZ();
	void Paint();
	virtual ~CAnilloXZ();
};

class CConoXY : public CConoXZ
{
public:
	CConoXY();
	CConoXY(double pRadio,double pHaltura);
	Paint();
};


#endif // !defined(AFX_FORMAS_H__FAEECCE1_1CC7_11D3_9A2B_000021B01127__INCLUDED_)
