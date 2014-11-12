// Pipe.cpp: implementation of the CPipe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Pipe.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPipe::CPipe()
{
	m_hpipe = NULL;
}

CPipe::~CPipe()
{

}

DWORD CPipe::Create(char *pipe_name)
{
	if (m_hpipe != NULL) return Error(ERR_FATAL,"CPipe::Create ... failed, pipe already created");
	if ((pipe_name == NULL) ||
		(pipe_name[0] == 0))	return Error(ERR_PARAM,"CPipe::Create ... failed, invalid pipe name");
	sprintf(m_pipe_name,"\\\\.\\pipe\\%s",pipe_name);

	return ERR_OK;
}
