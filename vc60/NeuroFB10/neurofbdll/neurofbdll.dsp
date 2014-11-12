# Microsoft Developer Studio Project File - Name="neurofbdll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=neurofbdll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "neurofbdll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "neurofbdll.mak" CFG="neurofbdll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "neurofbdll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "neurofbdll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "neurofbdll - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
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
# ADD LINK32 shlwapi.lib opengl32.lib ddraw.lib glu32.lib /nologo /subsystem:windows /dll /machine:I386 /def:".\neurofbdll.def" /out:"c:\windows\system\neurofbdll.dll" /implib:"c:\windows\system\neurofbdll.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "neurofbdll - Win32 Debug"

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
# ADD LINK32 shlwapi.lib opengl32.lib ddraw.lib glu32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:".\neurofbdll.def" /out:"c:\windows\system\neurofbdll.dll" /implib:"..\lib\neurofbdll.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "neurofbdll - Win32 Release"
# Name "neurofbdll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\App.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangePass.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBaseAplication.cpp
# End Source File
# Begin Source File

SOURCE=.\EntradaSistema.cpp
# End Source File
# Begin Source File

SOURCE=.\FileManage.cpp
# End Source File
# Begin Source File

SOURCE=..\G_01\G_01C02.cpp
# End Source File
# Begin Source File

SOURCE=..\G_01\G_01C03.cpp
# End Source File
# Begin Source File

SOURCE=..\G_01\G_01C04.cpp
# End Source File
# Begin Source File

SOURCE=..\G_01\g_01c06.cpp
# End Source File
# Begin Source File

SOURCE=..\G_01\g_01c07.cpp
# End Source File
# Begin Source File

SOURCE=..\G_01\g_01c08.cpp
# End Source File
# Begin Source File

SOURCE=..\G_01\g_01c09.cpp
# End Source File
# Begin Source File

SOURCE=..\Lfc10\LFC10C01.cpp
# End Source File
# Begin Source File

SOURCE=..\Lfc10\LFC10C02.cpp
# End Source File
# Begin Source File

SOURCE=..\Lfc10\LFC10C03.cpp
# End Source File
# Begin Source File

SOURCE=..\Lfc10\lfc10c04.cpp
# End Source File
# Begin Source File

SOURCE=..\Lfc10\LFC10C05.cpp
# End Source File
# Begin Source File

SOURCE=..\Lfc10\LFC10C06.cpp
# End Source File
# Begin Source File

SOURCE=.\Medico.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\neurofbdll.cpp
# End Source File
# Begin Source File

SOURCE=.\neurofbdll.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\neurofbdll.rc
# End Source File
# Begin Source File

SOURCE=.\Paciente.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TreePaciente.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewAllReports.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewBuscarPaciente.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewCondicion.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewConfigurarSesion.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewMostrarDatos.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewRegistro.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewSenales.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewTraining.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\App.h
# End Source File
# Begin Source File

SOURCE=.\ChangePass.h
# End Source File
# Begin Source File

SOURCE=.\DataBaseAplication.h
# End Source File
# Begin Source File

SOURCE=.\EntradaSistema.h
# End Source File
# Begin Source File

SOURCE=.\FileManage.h
# End Source File
# Begin Source File

SOURCE=.\Medico.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\Paciente.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TreePaciente.h
# End Source File
# Begin Source File

SOURCE=.\ViewAllReports.h
# End Source File
# Begin Source File

SOURCE=.\ViewBuscarPaciente.h
# End Source File
# Begin Source File

SOURCE=.\ViewCondicion.h
# End Source File
# Begin Source File

SOURCE=.\ViewConfigurarSesion.h
# End Source File
# Begin Source File

SOURCE=.\ViewMostrarDatos.h
# End Source File
# Begin Source File

SOURCE=.\ViewRegistro.h
# End Source File
# Begin Source File

SOURCE=.\ViewSenales.h
# End Source File
# Begin Source File

SOURCE=.\ViewTraining.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\neurofbdll.rc2
# End Source File
# Begin Source File

SOURCE=.\res\session1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
