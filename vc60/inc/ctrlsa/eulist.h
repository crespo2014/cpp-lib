#if !defined(EULIST_HEADER)
#define EULIST_HEADER

#include "memstack.h"

struct _EU_APPLY
{
	char	*user_id;
	char	*bs_direccion_mail;

	struct PRF_INFO*	p_prfinfo;
	struct _EU_APPLY	*next;
};

struct _EU_LIST
{
	struct _EU_APPLY*	first;
	struct _EU_APPLY*	last;
	struct _MEM_STACK*	stack;		//la memoria a utilizar se define en tiempo de ejecucion
};

#endif
