# Microsoft Developer Studio Project File - Name="G30" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=G30 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "G30.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "G30.mak" CFG="G30 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "G30 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "G30 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "G30 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "G30_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "G30_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib opengl32.lib glu32.lib /nologo /dll /machine:I386 /out:"..\prog\Release\G30.dll" /implib:"c:/lib/G30.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "G30 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "G30_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\inc_src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "G30_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib lfc30.lib opengl32.lib glu32.lib lfc30.lib ddraw.lib /nologo /dll /debug /machine:I386 /out:"..\prog\debug\G30.dll" /implib:"c:/lib/G30.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "G30 - Win32 Release"
# Name "G30 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\G30.cpp
# End Source File
# Begin Source File

SOURCE=.\g30c02.cpp
# End Source File
# Begin Source File

SOURCE=.\g30c03.cpp
# End Source File
# Begin Source File

SOURCE=.\g30c04.cpp
# End Source File
# Begin Source File

SOURCE=.\g30c05.cpp
# End Source File
# Begin Source File

SOURCE=.\g30c06.cpp
# End Source File
# Begin Source File

SOURCE=.\G_01C02.CPP
# End Source File
# Begin Source File

SOURCE=.\G_01C03.CPP
# End Source File
# Begin Source File

SOURCE=.\G_01C04.CPP
# End Source File
# Begin Source File

SOURCE=.\G_01C06.CPP
# End Source File
# Begin Source File

SOURCE=.\G_01c07.cpp
# End Source File
# Begin Source File

SOURCE=.\G_01C08.CPP
# End Source File
# Begin Source File

SOURCE=.\G_01C09.CPP
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\G30c02.h
# End Source File
# Begin Source File

SOURCE=.\g30c03.h
# End Source File
# Begin Source File

SOURCE=.\g30c04.h
# End Source File
# Begin Source File

SOURCE=.\g30c05.h
# End Source File
# Begin Source File

SOURCE=.\g30c06.h
# End Source File
# Begin Source File

SOURCE=.\G30DEF.H
# End Source File
# Begin Source File

SOURCE=.\G_01C01.H
# End Source File
# Begin Source File

SOURCE=.\G_01C02.H
# End Source File
# Begin Source File

SOURCE=.\G_01C03.H
# End Source File
# Begin Source File

SOURCE=.\G_01C04.H
# End Source File
# Begin Source File

SOURCE=.\G_01C06.H
# End Source File
# Begin Source File

SOURCE=.\G_01C07.H
# End Source File
# Begin Source File

SOURCE=.\G_01C08.H
# End Source File
# Begin Source File

SOURCE=.\G_01C09.H
# End Source File
# Begin Source File

SOURCE=.\G_01def.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
