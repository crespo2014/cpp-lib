#if !defined(AFX_DB11S_H__244C9632_EFBE_11D3_BC40_0000E8DE4B3B__INCLUDED_)
#define AFX_DB11S_H__244C9632_EFBE_11D3_BC40_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
// esta estructura almacena el id y el nombre del elemento
//

typedef struct
{
	long	id;
	char	nombre[50];
}S_CAMPO;

typedef struct
{
	long		cantidad;
	S_CAMPO*	valor;
}S_RECORDINFO;



#endif // !defined(AFX_DB11S_H__244C9632_EFBE_11D3_BC40_0000E8DE4B3B__INCLUDED_)