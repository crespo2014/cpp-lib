# Microsoft Developer Studio Project File - Name="GL10" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GL10 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GL10.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GL10.mak" CFG="GL10 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GL10 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GL10 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GL10 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x80a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x80a /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 opengl32.lib glu32.lib ftkvc40.lib /nologo /subsystem:windows /dll /machine:I386 /out:"c:\windows\system\GL10.dll"

!ELSEIF  "$(CFG)" == "GL10 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x80a /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x80a /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib ftkvc40d.lib glu32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:".\GL10.def" /out:"c:\windows\system\GL10.dll" /implib:"c:\windows\system\GL10.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "GL10 - Win32 Release"
# Name "GL10 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\GL10.cpp
# End Source File
# Begin Source File

SOURCE=.\GL10.def

!IF  "$(CFG)" == "GL10 - Win32 Release"

!ELSEIF  "$(CFG)" == "GL10 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GL10.rc
# End Source File
# Begin Source File

SOURCE=.\gl10c10.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c11.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c12.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c13.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c14.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c3.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c4.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c5.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c6.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c7.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c8.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10c9.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10d5.cpp
# End Source File
# Begin Source File

SOURCE=.\gl10d6.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\gl10c10.h
# End Source File
# Begin Source File

SOURCE=.\gl10c11.h
# End Source File
# Begin Source File

SOURCE=.\gl10c12.h
# End Source File
# Begin Source File

SOURCE=.\gl10c13.h
# End Source File
# Begin Source File

SOURCE=.\gl10c14.h
# End Source File
# Begin Source File

SOURCE=.\gl10c3.h
# End Source File
# Begin Source File

SOURCE=.\gl10c4.h
# End Source File
# Begin Source File

SOURCE=.\gl10c5.h
# End Source File
# Begin Source File

SOURCE=.\gl10c6.h
# End Source File
# Begin Source File

SOURCE=.\gl10c7.h
# End Source File
# Begin Source File

SOURCE=.\gl10c8.h
# End Source File
# Begin Source File

SOURCE=.\gl10c9.h
# End Source File
# Begin Source File

SOURCE=.\gl10d5.h
# End Source File
# Begin Source File

SOURCE=.\gl10d6.h
# End Source File
# Begin Source File

SOURCE=.\gl10s.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\cilindro.ico
# End Source File
# Begin Source File

SOURCE=.\folder.ico
# End Source File
# Begin Source File

SOURCE=.\res\folder.ico
# End Source File
# Begin Source File

SOURCE=.\res\GL10.rc2
# End Source File
# Begin Source File

SOURCE=.\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\ico3dobj.ico
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\material.ico
# End Source File
# Begin Source File

SOURCE=.\res\material.ico
# End Source File
# Begin Source File

SOURCE=.\nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\res\nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\primitiv.ico
# End Source File
# Begin Source File

SOURCE=.\res\vista.ico
# End Source File
# Begin Source File

SOURCE=.\vista.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
