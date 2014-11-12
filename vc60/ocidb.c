#include "ocidb.h"

DWORD oci_log_error(struct _OCIDB* pthis, sword sw,char* fmt, ...)
{
	char	err_str[1024];
	char	*cptr;
	va_list arg_ptr;
	sb4 errcode = 0;
	
	int i,len;
	const char	*fnc_name = "oci_log_error";
	cptr = err_str;
	len = sizeof(err_str) - 1;
	
	va_start(arg_ptr, fmt);
	i = vsnprintf(cptr,len,fmt,arg_ptr);
	if ((i<0) || (i > len)) return LOG_TERROR ERR_FATAL,"Buffer overflow");
	cptr += (i-1);
	len -= i;
	va_end(arg_ptr);
    
	i = snprintf(cptr,len," failed sw code = %d ",sw);
	if ((i<0) || (i > len)) return LOG_TERROR ERR_FATAL,"Buffer overflow");
	cptr += i;
	len -= i;
    	
	switch (sw)
	{
		case OCI_SUCCESS:	return ERR_OK;
		case OCI_SUCCESS_WITH_INFO:
		case OCI_ERROR:
			if (pthis->oci_err != NULL)
			{ 
				OCIErrorGet((dvoid *)pthis->oci_err,(ub4)1,(text *)NULL,&errcode,(OraText*)cptr,(ub4)len,OCI_HTYPE_ERROR);
				i = strlen(cptr);
				cptr += i;
				len -= i;
				
				i = snprintf(cptr,len," ecode = %u",errcode);
				if ((i<0) || (i > len)) return LOG_TERROR ERR_FATAL,"Buffer overflow");
				cptr += i;
				len -= i;
			}
			break;
		case OCI_NEED_DATA:
			i = snprintf(cptr,len," OCI_NEED_DATA");
			if ((i<0) || (i > len)) return LOG_TERROR ERR_FATAL,"Buffer overflow");
			cptr += i;
			len -= i;
			break;
		case OCI_NO_DATA:
			i = snprintf(cptr,len," OCI_NODATA");
			if ((i<0) || (i > len)) return LOG_TERROR ERR_FATAL,"Buffer overflow");
			cptr += i;
			len -= i;
			break;
		case OCI_INVALID_HANDLE:
			i = snprintf(cptr,len," OCI_INVALID_HANDLE");
			if ((i<0) || (i > len)) return LOG_TERROR ERR_FATAL,"Buffer overflow");
			cptr += i;
			len -= i;
			break;
		case OCI_STILL_EXECUTING:
			i = snprintf(cptr,len," OCI_STILL_EXECUTE");
			if ((i<0) || (i > len)) return LOG_TERROR ERR_FATAL,"Buffer overflow");
			cptr += i;
			len -= i;
			break;
		case OCI_CONTINUE:
			i = snprintf(cptr,len," OCI_CONTINUE");
			if ((i<0) || (i > len)) return LOG_TERROR ERR_FATAL,"Buffer overflow");
			cptr += i;
			len -= i;
			break;
		default:
			i = snprintf(cptr,len," Unknown OCI error");
			if ((i<0) || (i > len)) return LOG_TERROR ERR_FATAL,"Buffer overflow");
			cptr += i;
			len -= i;
			break;
	}   
	LOG_TERROR ERR_FATAL,"%s",err_str);
	if (sw == OCI_SUCCESS_WITH_INFO) return ERR_OK;
	return ERR_FATAL;	
}


/*
	Inicializacion de oci
*/

DWORD oci_initialize(struct _OCIDB*	pthis,const char *oci_admin, const char *oci_adminpwd, const char *oci_servicio)
{
	sword	sw;
	const char	*fnc_name = "oci_initialize";
	
	if (pthis->oci_init == 1) return ERR_OK;
	
	FNC_START
		
	sw = OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0,  /* Initialize OCI */
           (dvoid * (*)(dvoid *, size_t)) 0,
           (dvoid * (*)(dvoid *, dvoid *, size_t))0,
           (void (*)(dvoid *, dvoid *)) 0 );
	if (sw != OCI_SUCCESS) return oci_log_error(pthis,sw,"%s->OCIInitialize",fnc_name);

	sw = OCIEnvInit( (OCIEnv **) &pthis->oci_env, OCI_DEFAULT, (size_t) 0, (dvoid **) 0 );
	if (sw != OCI_SUCCESS) return  LOG_TERROR ERR_FATAL,"OCIEnvInit for OCIEnv failed with ecode = %u",sw);

	sw = OCIHandleAlloc( (dvoid *) pthis->oci_env, (dvoid **) &pthis->oci_err, OCI_HTYPE_ERROR,(size_t) 0, (dvoid **) 0);
	if (sw != OCI_SUCCESS) return  LOG_TERROR ERR_FATAL,"OCIHandleAlloc for OCI_HTYPE_ERROR failed with ecode = %u",sw);
	
	sw = OCIHandleAlloc( (dvoid *) pthis->oci_env, (dvoid **) &pthis->oci_srvctx, OCI_HTYPE_SVCCTX,0,0);
	if (sw != OCI_SUCCESS) return  oci_log_error(pthis,sw,"%s->OCIHandleAlloc for OCI_HTYPE_SVCCTX",fnc_name);
		
	// conectar con la base de datos y crear un stament
	sw = OCILogon(pthis->oci_env , pthis->oci_err, &pthis->oci_srvctx, 
					(text *)oci_admin	,(ub4)strlen(oci_admin),
					(text *)oci_adminpwd,(ub4)strlen(oci_adminpwd),
					(text *)oci_servicio,(ub4)strlen(oci_servicio));
					
	if (sw != OCI_SUCCESS) 	return oci_log_error(pthis,sw,"%s->OCILogon",fnc_name);
	
	sw = OCIHandleAlloc((dvoid*)pthis->oci_env,(dvoid **)&pthis->oci_stmt,OCI_HTYPE_STMT, 0, 0);
	if (sw != OCI_SUCCESS) return  oci_log_error(pthis,sw,"%s->OCIHandleAlloc for OCI_HTYPE_STMT ",fnc_name);

	pthis->oci_init = 1;
	return ERR_OK;
}
