# NAME
#   oci_m.sed 
# DESCRIPTION
# This sed script changes the OCI macro names to long
# names
# MODIFIED
#    10/03/96 - Peter Vasterd - Creation
#    10/04/96 - Sreenivas Gollapudi - Added OCI_STM and OCI_TX stuff
#    10/21/96 - Peter Vasterd - TOPROW -> PREFETCH
#
s/OCI_ATTR_ENVCTXT/OCI_ATTR_ENV/g
s/OCI_ATTR_SRVRCTXT/OCI_ATTR_SERVER/g
s/OCI_ATTR_TXCTXT/OCI_ATTR_TRANS/g
s/OCI_ATTR_USERCTXT/OCI_ATTR_SESSION/g
s/OCI_ATTR_FUNCODE/OCI_ATTR_FNCODE/g
s/OCI_ATTR_NBLMODE/OCI_ATTR_NONBLOCKING_MODE/g
s/OCI_ATTR_ROWCNT/OCI_ATTR_ROW_COUNT/g
s/OCI_ATTR_TOPRCNT/OCI_ATTR_PREFETCH_ROWS/g
s/OCI_ATTR_NSTD_RCNT/OCI_ATTR_NESTED_ROW_COUNT/g
s/OCI_ATTR_TOP_RMSZ/OCI_ATTR_PREFETCH_MEMORY/g
s/OCI_ATTR_NSTD_RMSZ/OCI_ATTR_NESTED_PREFETCH_MEMORY/g
s/OCI_ATTR_CHRCNT/OCI_ATTR_CHAR_COUNT/g
s/OCI_ATTR_PARMCNT/OCI_ATTR_PARAM_COUNT/g
s/OCI_ATTR_STMTYP/OCI_ATTR_STMT_TYPE/g
s/OCI_ATTR_TXLOCK/OCI_ATTR_TRANS_LOCK/g
s/OCI_ATTR_TXNAME/OCI_ATTR_TRANS_NAME/g
s/OCI_ATTR_CHRSETID/OCI_ATTR_CHARSET_ID/g
s/OCI_ATTR_CHRSETFORM/OCI_ATTR_CHARSET_FORM/g
s/OCI_ATTR_CHRSET/OCI_ATTR_CHARSET/g
s/OCI_ATTR_MAXDATASZ/OCI_ATTR_MAXDATA_SIZE/g
s/OCI_ATTR_OPTSIZE/OCI_ATTR_CACHE_OPT_SIZE/g
s/OCI_ATTR_MAXSIZE/OCI_ATTR_CACHE_MAX_SIZE/g
s/OCI_ATTR_ALLOCDUR/OCI_ATTR_ALLOC_DURATION/g
s/OCI_ATTR_PINDUR/ OCI_ATTR_PIN_DURATION/g
s/OCI_ATTR_CORTYP/OCI_ATTR_COMPLEXOBJECTCOMP_TYPE/g
s/OCI_ATTR_CORLVL/OCI_ATTR_COMPLEXOBJECTCOMP_LEVEL/g
s/OCI_HTYPE_BND/OCI_HTYPE_BIND/g
s/OCI_HTYPE_DFN/OCI_HTYPE_DEFINE/g
s/OCI_HTYPE_DSC/OCI_HTYPE_DESCRIBE/g
s/OCI_HTYPE_ENV/OCI_HTYPE_ENV/g
s/OCI_HTYPE_ERR/OCI_HTYPE_ERROR/g
s/OCI_HTYPE_SRV/OCI_HTYPE_SERVER/g
s/OCI_HTYPE_STM/OCI_HTYPE_STMT/g
s/OCI_HTYPE_SVC/OCI_HTYPE_SVCCTX/g
s/OCI_HTYPE_TXN/OCI_HTYPE_TRANS/g
s/OCI_HTYPE_COR/OCI_HTYPE_COMPLEXOBJECT/g
s/OCI_HTYPE_USR/OCI_HTYPE_SESSION/g
s/OCIATCH/OCI_FNCODE_SERVERATTACH/g
s/OCIAUTH/OCI_FNCODE_SESSIONBEGIN/g
s/OCIBDA/OCI_FNCODE_BINDDYNAMIC/g
s/OCIBNDH/OCI_FNCODE_BIND/g
s/OCIBNDN/OCI_FNCODE_STMTBINDBYNAME/g
s/OCIBNDP/OCI_FNCODE_STMTBINDBYPOS/g
s/OCIBNDT/OCI_FNCODE_BINDOBJECT/g
s/OCIBREAK/OCI_FNCODE_SVCCTXBREAK/g
s/OCIBSA/OCI_FNCODE_BINDARRAYOFSTRUCT/g
s/OCIBSVT/OCI_FNCODE_BINDRECORD/g
s/OCICPW/OCI_FNCODE_PASSWORDCHANGE/g
s/OCIDARR/OCI_FNCODE_DEFINEARRAYOFSTRUCT/g
s/OCIDDF/OCI_FNCODE_DEFINEDYNAMIC/g
s/OCIDEFN/OCI_FNCODE_DEFINE/g
s/OCIDNDT/OCI_FNCODE_DEFINEOBJECT/g
s/OCIDSCA/OCI_FNCODE_DESCRIBEANY/g
s/OCIEXEC/OCI_FNCODE_STMTEXECUTE/g
s/OCIFCH/OCI_FNCODE_STMTFETCH/g
s/OCIFCLS/OCI_FNCODE_LOBCLOSEFILE/g
s/OCIFCRT/OCI_FNCODE_LOBCREATEFILE/g
s/OCIFDEL/OCI_FNCODE_LOBDELFILE/g
s/OCIFDESC/OCI_FNCODE_DESCRIPTORFREE/g
s/OCIFHNDL/OCI_FNCODE_HANDLEFREE/g
s/OCIFOPN/OCI_FNCODE_LOBOPENFILE/g
s/OCIFREEM/OCI_FNCODE_MEMORYFREE/g
s/OCIGATTR/OCI_FNCODE_ATTRGET/g
s/OCIGBP/OCI_FNCODE_STMTGETBIND/g
s/OCIGDESC/OCI_FNCODE_DESCRIPTORALLOC/g
s/OCIGDR/OCI_FNCODE_ERRORGET/g
s/OCIGHNDL/OCI_FNCODE_HANDLEALLOC/g
s/OCIGPARM/OCI_FNCODE_PARAMGET/g
s/OCIGPI/OCI_FNCODE_STMTGETPIECEINFO/g
s/OCIINIT/OCI_FNCODE_ENVINIT/g
s/OCILD2SV/OCI_FNCODE_LDATOSVCCTX/g
s/OCILFAP/OCI_FNCODE_LOBAPPEND/g
s/OCILFCP/OCI_FNCODE_LOBCOPY/g
s/OCILFER/OCI_FNCODE_LOBERASE/g
s/OCILFLN/OCI_FNCODE_LOBGETLENGTH/g
s/OCILFRD/OCI_FNCODE_LOBREAD/g
s/OCILFTR/OCI_FNCODE_LOBTRIM/g
s/OCILFWR/OCI_FNCODE_LOBWRITE/g
s/OCIPI/OCI_FNCODE_INITIALIZE/g
s/OCIREQ/OCI_FNCODE_STMTPREPARE/g
s/OCIRS2SH/OCI_FNCODE_RESULTSETTOSTMT/g
s/OCISATTR/OCI_FNCODE_ATTRSET/g
s/OCISPI/OCI_FNCODE_STMTSETPIECEINFO/g
s/OCISV2LD/OCI_FNCODE_SVCCTXTOLDA/g
s/OCITAC/OCI_FNCODE_SESSIONEND/g
s/OCITXCM/OCI_FNCODE_TRANSCOMMIT/g
s/OCITXDT/OCI_FNCODE_TRANSDETACH/g
s/OCITXFGT/OCI_FNCODE_TRANSFORGET/g
s/OCITXPRE/OCI_FNCODE_TRANSPREPARE/g
s/OCITXRL/OCI_FNCODE_TRANSROLLBACK/g
s/OCITXST/OCI_FNCODE_TRANSSTART/g
s/OCIVERS/OCI_FNCODE_SERVERVERSION/g
s/OCI_FILE_RDWR/OCI_FILE_READWRITE/g
s/OCI_FILE_RDONLY/OCI_FILE_READONLY/g
s/SQLT_CFIL/SQLT_CFILE/g
s/SQLT_BFIL/SQLT_BFILE/g
s/OCI_STM_SELECT/OCI_STMT_SELECT/g
s/OCI_STM_UPDATE/OCI_STMT_UPDATE/g
s/OCI_STM_DELETE/OCI_STMT_DELETE/g
s/OCI_STM_INSERT/OCI_STMT_INSERT/g
s/OCI_STM_DROP/OCI_STMT_DROP/g
s/OCI_STM_ALTER/OCI_STMT_ALTER/g
s/OCI_STM_BEGIN/OCI_STMT_BEGIN/g
s/OCI_STM_DEC/OCI_STMT_DECLARE/g
s/OCI_TX_OLD/OCI_TRANS_OLD/g
s/OCI_TX_NEW/OCI_TRANS_NEW/g
s/OCI_TX_JOIN/OCI_TRANS_JOIN/g
s/OCI_TX_RESUME/OCI_TRANS_RESUME/g
s/OCI_TX_STARTMASK/OCI_TRANS_STARTMASK/g
s/OCI_TX_READONLY/OCI_TRANS_READONLY/g
s/OCI_TX_READWRITE/OCI_TRANS_READWRITE/g
s/OCI_TX_SERIALIZABLE/OCI_TRANS_SERIALIZABLE/g
s/OCI_TX_ISOLMASK/OCI_TRANS_ISOLMASK/g
s/OCI_TX_LOOSE/OCI_TRANS_LOOSE/g
s/OCI_TX_TIGHT/OCI_TRANS_TIGHT/g
s/OCI_TX_TYPEMASK/OCI_TRANS_TYPEMASK/g
s/OCI_TX_NOMIGRATE/OCI_TRANS_NOMIGRATE/g
s/OCI_TX_TWOPHASE/OCI_TRANS_TWOPHASE/g
s/OCI_DTYPE_PARM/OCI_DTYPE_PARAM/g
s/OCI_DTYPE_COR/OCI_DTYPE_COMPLEXOBJECTCOMP/g
s/OCI_DTYPE_RDD/OCI_DTYPE_ROWID/g
s/OCI_SB2_INDP/OCI_SB2_IND_PTR/g
s/OCI_IN_PARAMETER/OCI_PARAM_IN/g
s/OCI_OUT_PARAMETER/OCI_PARAM_OUT/g
s/OCISQLSTATESZ/OCI_SQLSTATE_SIZE/g
s/OCIMAXMSGSZ/OCI_ERROR_MAXMSG_SIZE/g
