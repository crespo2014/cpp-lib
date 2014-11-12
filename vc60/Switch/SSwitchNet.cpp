// SSwitchNet.cpp: implementation of the CSSwitchNet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Switch.h"
#include "SSwitchNet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSSwitchNet::CSSwitchNet(BOOL bDynamic):CUnknown(bDynamic)
{
	
}

CSSwitchNet::~CSSwitchNet()
{
	UnInitialize();
}
