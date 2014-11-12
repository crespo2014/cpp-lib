#if !defined(OCIDB_H_INCLUDED_)
#define OCIDB_H_INCLUDED_

#include <oci.h>
#include "log.h"

struct _OCIDB
{
		// parametros de conexion del oci
	int			oci_init;			// indica si esta inicializado el entorno OCI
	OCIEnv 		*oci_env;    
	OCISvcCtx	*oci_srvctx;		// handle de contexto de servidor                                                                                                         
	OCIError 	*oci_err;			// handle de errores                                                                                                                      
	OCIServer 	*oci_srv;                                                                                                                                                     
	OCIStmt 	*oci_stmt;    
};

DWORD oci_initialize(struct _OCIDB*	pthis,const char *oci_admin, const char *oci_adminpwd, const char *oci_servicio);
DWORD oci_log_error(struct _OCIDB* pthis, sword sw,char* fmt, ...);

#endif
