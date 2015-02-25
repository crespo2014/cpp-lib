#
# Example for building demo OCI programs:
#
# 1. All OCI demos (including extdemo2, extdemo4 and extdemo5):
#
#    make -f demo_rdbms.mk demos
#
# 2. A single OCI demo:
#
#    make -f demo_rdbms.mk build EXE=demo OBJS="demo.o ..."
#    e.g. make -f demo_rdbms.mk build EXE=oci02 OBJS=oci02.o
#
# 3. A single OCI demo with static libraries:
#
#    make -f demo_rdbms.mk build_static EXE=demo OBJS="demo.o ..."
#    e.g. make -f demo_rdbms.mk build_static EXE=oci02 OBJS=oci02.o
#
# 4. To re-generate shared library:
#
#    make -f demo_rdbms.mk generate_sharedlib
#
# 5. All OCCI demos
#
#    make -f demo_rdbms.mk occidemos
#
# 6. A single OCCI demo:
#
#    make -f demo_rdbms.mk <demoname>
#    e.g. make -f demo_rdbms.mk occidml
#    OR
#    make -f demo_rdbms.mk buildocci EXE=demoname OBJS="demoname.o ..."
#    e.g. make -f demo_rdbms.mk buildocci EXE=occidml OBJS=occidml.o
#
# 7. A single OCCI demo with static libraries:
#
#    make -f demo_rdbms.mk buildocci_static EXE=demoname OBJS="demoname.o ..."
#    e.g. make -f demo_rdbms.mk buildocci_static EXE=occiblob OBJS=occiblob.o
#
# 8. All OCI Connection Pooling, Session Pooling and Statement Cache demos
#
#    make -f demo_rdbms.mk cpdemos
#
# 9. A single OCI Connection Pooling demo:
#
#    make -f demo_rdbms.mk <demoname>
#    e.g. make -f demo_rdbms.mk cdemocp
#    OR
#    make -f demo_rdbms.mk buildcp EXE=demoname OBJS="demoname.o ..."
#    e.g. make -f demo_rdbms.mk buildcp EXE=cdemocp OBJS=cdemocp.o
#
# 10. A single OCI Connection Pooling demo with static libraries:
#
#    make -f demo_rdbms.mk buildcp_static EXE=demoname OBJS="demoname.o ..."
#    e.g. make -f demo_rdbms.mk buildcp_static EXE=cdemocp OBJS=cdemocp.o
#
# 11. A single OCI Session Pooling demo:
#
#    make -f demo_rdbms.mk <demoname>
#    e.g. make -f demo_rdbms.mk cdemosp
#    OR
#    make -f demo_rdbms.mk buildcp EXE=demoname OBJS="demoname.o ..."
#    e.g. make -f demo_rdbms.mk buildcp EXE=cdemosp OBJS=cdemosp.o
#
# 12. A single OCI Session Pooling demo with static libraries:
#
#    make -f demo_rdbms.mk buildcp_static EXE=demoname OBJS="demoname.o ..."
#    e.g. make -f demo_rdbms.mk buildcp_static EXE=cdemosp OBJS=cdemosp.o
#
# 13. A single OCI Statement Cache demo:
#
#    make -f demo_rdbms.mk <demoname>
#    e.g. make -f demo_rdbms.mk cdemostc
#    OR
#    make -f demo_rdbms.mk buildcp EXE=demoname OBJS="demoname.o ..."
#    e.g. make -f demo_rdbms.mk buildcp EXE=cdemostc OBJS=cdemostc.o
#
# 14. A single OCI Statement Cache demo with static libraries:
#
#    make -f demo_rdbms.mk buildcp_static EXE=demoname OBJS="demoname.o ..."
#    e.g. make -f demo_rdbms.mk buildcp_static EXE=cdemostc OBJS=cdemostc.o
#
# Example for building demo DIRECT PATH API programs:
#
# 1. All DIRECT PATH API demos:
#
#    make -f demo_rdbms.mk demos_dp
#
# 2. A single DIRECT PATH API demo:
#
#    make -f demo_rdbms.mk build_dp EXE=demo OBJS="demo.o ..."
#    e.g. make -f demo_rdbms.mk build_dp EXE=cdemdplp OBJS=cdemdplp.o
#
#
# Example for building external procedures demo programs:
#
# 1. All external procedure demos:
#
# 2. A single external procedure demo whose 3GL routines do not use the 
#    "with context" argument:
#
#    make -f demo_rdbms.mk extproc_no_context SHARED_LIBNAME=libname 
#                                             OBJS="demo.o ..."
#    e.g. make -f demo_rdbms.mk extproc_no_context SHARED_LIBNAME=epdemo.so
#                                             OBJS="epdemo1.o epdemo2.o"
#
# 3. A single external procedure demo where one or more 3GL routines use the 
#    "with context" argument:
#
#    make -f demo_rdbms.mk extproc_with_context SHARED_LIBNAME=libname 
#                                             OBJS="demo.o ..."
#    e.g. make -f demo_rdbms.mk extproc_with_context SHARED_LIBNAME=epdemo.so
#                                             OBJS="epdemo1.o epdemo2.o"
#    e.g. make -f demo_rdbms.mk extproc_with_context 
#                       SHARED_LIBNAME=extdemo2.so OBJS="extdemo2.o"
#    e.g. or For EXTDEMO2 DEMO ONLY: make -f demo_rdbms.mk demos
#
# 4. To link C++ demos:
#
#    make -f demo_rdbms.mk c++demos
#
#
# NOTE: 1. ORACLE_HOME must be either:
#		   . set in the user's environment
#		   . passed in on the command line
#		   . defined in a modified version of this makefile
#
#       2. If the target platform support shared libraries (e.g. Solaris)
#          look in the platform specific documentation for information
#          about environment variables that need to be properly
#          defined (e.g. LD_LIBRARY_PATH in Solaris).
#

include $(ORACLE_HOME)/rdbms/lib/env_rdbms.mk

# flag for linking with non-deferred option (default is deferred mode)
NONDEFER=false

DEMO_DIR=$(ORACLE_HOME)/rdbms/demo
DEMO_MAKEFILE = $(DEMO_DIR)/demo_rdbms.mk

DEMOS = cdemo1 cdemo2 cdemo3 cdemo4 cdemo5 cdemo81 cdemo82 \
        cdemobj cdemolb cdemodsc cdemocor cdemolb2 cdemolbs \
        cdemodr1 cdemodr2 cdemodr3 cdemodsa obndra \
        cdemoext cdemothr cdemofil cdemofor \
        oci02 oci03 oci04 oci05 oci06 oci07 oci08 oci09 oci10 \
        oci11 oci12 oci13 oci14 oci15 oci16 oci17 oci18 oci19 oci20 \
        oci21 oci22 oci23 oci24 oci25 readpipe cdemosyev \
	ociaqdemo00 ociaqdemo01 ociaqdemo02 cdemoucb nchdemo1

DEMOS_DP = cdemdpco cdemdpin cdemdpit cdemdplp cdemdpno cdemdpro cdemdpss 

C++DEMOS = cdemo6
OCCIDEMOS = occiblob occiclob occicoll occidesc occidml occipool occiproc \
            occistre
OCCIOTTDEMOS = occiobj occiinh occipobj
# OTT Markers Support
OCCIOTTDEMOSWITHMARKER = mdemo1
OTTUSR = scott
OTTPWD = tiger
CPDEMOS = cdemocp cdemocpproxy cdemosp cdemostc

.SUFFIXES: .o .cob .for .c .pc .cc .cpp

demos: $(DEMOS) extdemo2 extdemo4 extdemo5

demos_dp: $(DEMOS_DP) 

generate_sharedlib:
	$(SILENT)$(ECHO) "Building client shared library ..."
	$(SILENT)$(ECHO) "Calling script $$ORACLE_HOME/bin/genclntsh ..."
	$(GENCLNTSH)
	$(SILENT)$(ECHO) "The library is $$ORACLE_HOME/lib/libclntsh.so... DONE"

BUILD=build
$(DEMOS):
	$(MAKE) -f $(DEMO_MAKEFILE) $(BUILD) EXE=$@ OBJS=$@.o

$(DEMOS_DP): cdemodp.c cdemodp0.h cdemodp.h
	$(MAKE) -f $(DEMO_MAKEFILE) build_dp EXE=$@ OBJS=$@.o

c++demos: $(C++DEMOS)

$(C++DEMOS):
	$(MAKE) -f $(DEMO_MAKEFILE) buildc++ EXE=$@ OBJS=$@.o

buildc++: $(OBJS)
	$(MAKECPLPLDEMO)

occidemos:	$(OCCIDEMOS) $(OCCIOTTDEMOS) $(OCCIOTTDEMOSWITHMARKER)

$(OCCIDEMOS):
	$(MAKE) -f $(DEMO_MAKEFILE) buildocci EXE=$@ OBJS=$@.o

$(OCCIOTTDEMOS):
	$(MAKE) -f $(DEMO_MAKEFILE) ott OTTFILE=$@
	$(MAKE) -f $(DEMO_MAKEFILE) buildocci EXE=$@ OBJS="$@.o $@o.o $@m.o"

# OTT Markers Support
$(OCCIOTTDEMOSWITHMARKER):
	$(MAKE) -f $(DEMO_MAKEFILE) ott_mrkr OTTFILE=$@
	$(MAKE) -f $(DEMO_MAKEFILE) buildocci EXE=$@ OBJS="$@.o $@o.o $@m.o"


buildocci: $(OBJS)
	$(MAKEOCCISHAREDDEMO)

buildocci_static: $(OBJS)
	$(MAKEOCCISTATICDEMO)

ott:
	$(ORACLE_HOME)/bin/ott \
		userid=$(OTTUSR)/$(OTTPWD) \
		intype=$(OTTFILE).typ \
		outtype=$(OTTFILE)out.type \
		code=cpp \
		hfile=$(OTTFILE).h \
		cppfile=$(OTTFILE)o.cpp \
		attraccess=private

# OTT Markers Suppport
ott_mrkr:
	$(ORACLE_HOME)/bin/ott \
                userid=$(OTTUSR)/$(OTTPWD) \
                intype=$(OTTFILE).typ \
                outtype=$(OTTFILE)out.type \
                code=cpp \
                hfile=$(OTTFILE).h \
                cppfile=$(OTTFILE)o.cpp \
                use_marker=true

cpdemos:	$(CPDEMOS)
$(CPDEMOS):
	$(MAKE) -f $(DEMO_MAKEFILE) buildcp EXE=$@ OBJS=$@.o
buildcp: $(OBJS)
	$(MAKECPSHAREDDEMO)
buildcp_static: $(OBJS)
	$(MAKECPSTATICDEMO)

# Pro*C rules
# SQL Precompiler macros

pc1:
	$(PCC2C)

.pc.c:
	$(MAKE) -f $(DEMO_MAKEFILE) PCCSRC=$* I_SYM=include= pc1

.pc.o:
	$(MAKE) -f $(DEMO_MAKEFILE) PCCSRC=$* I_SYM=include= pc1
	$(PCCC2O)

.cc.o:
	$(CCC2O)

.cpp.o:
	$(CCC2O)

build: $(LIBCLNTSH) $(OBJS)
	$(BUILDEXE)

extdemo2:
	$(MAKE) -f $(DEMO_MAKEFILE) extproc_with_context SHARED_LIBNAME=extdemo2.so OBJS="extdemo2.o"

extdemo4:
	$(MAKE) -f $(DEMO_MAKEFILE) extproc_with_context SHARED_LIBNAME=extdemo4.so OBJS="extdemo4.o"

extdemo5:
	$(MAKE) -f $(DEMO_MAKEFILE) extproc_with_context SHARED_LIBNAME=extdemo5.so OBJS="extdemo5.o"

.c.o:
	$(C2O)

build_dp: $(LIBCLNTSH) $(OBJS) cdemodp.o
	$(DPTARGET)

build_static: $(OBJS)
	$(O2STATIC)

# extproc_no_context and extproc_with_context are the current names of these
# targets.  The old names, extproc_nocallback and extproc_callback are
# preserved for backward compatibility.

extproc_no_context extproc_nocallback: $(OBJS)
	$(BUILDLIB_NO_CONTEXT)

extproc_with_context extproc_callback: $(OBJS) $(LIBCLNTSH)
	$(BUILDLIB_WITH_CONTEXT)

clean:
	$(RM) -f $(DEMOS) $(CPDEMOS) extdemo2 extdemo4 extdemo5 *.o *.so
	$(RM) -f $(OCCIDEMOS)  $(OCCIOTTDEMOS) $(OCCIOTTDEMOSWITHMARKER) occi*m.cpp occi*o.cpp occi*.type occiobj*.h occiinh*.h occipobj*.h
	$(RM) -f $(DEMOS_DP)