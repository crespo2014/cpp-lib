# Microsoft Developer Studio Project File - Name="neurofb" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=neurofb - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "neurofb.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "neurofb.mak" CFG="neurofb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "neurofb - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "neurofb - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "neurofb - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x80a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x80a /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 shlwapi.lib opengl32.lib ddraw.lib glu32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "neurofb - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\inc_src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x80a /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x80a /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib opengl32.lib ddraw.lib glu32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "neurofb - Win32 Release"
# Name "neurofb - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\neurofbdll\App.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ChangePass.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\DataBaseAplication.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\EntradaSistema.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\FileManage.cpp
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

SOURCE=..\G_01\G_01C05.cpp
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

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\Medico.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\neurofb.cpp
# End Source File
# Begin Source File

SOURCE=.\neurofb.rc
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\Paciente.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\TreePaciente.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewAllReports.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewBuscarPaciente.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewCondicion.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewConfigurarSesion.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewMostrarDatos.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewRegistro.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewSenales.cpp
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewTraining.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\neurofbdll\App.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ChangePass.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\DataBaseAplication.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\EntradaSistema.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\FileManage.h
# End Source File
# Begin Source File

SOURCE=..\G_01\G_01C02.h
# End Source File
# Begin Source File

SOURCE=..\G_01\G_01C03.h
# End Source File
# Begin Source File

SOURCE=..\G_01\G_01C04.h
# End Source File
# Begin Source File

SOURCE=..\G_01\G_01C05.h
# End Source File
# Begin Source File

SOURCE=..\G_01\g_01c08.h
# End Source File
# Begin Source File

SOURCE=..\G_01\g_01c09.h
# End Source File
# Begin Source File

SOURCE=..\G_01\G_01def.h
# End Source File
# Begin Source File

SOURCE=..\LFC10\LFC10DEF.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\Medico.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\neurofb.h
# End Source File
# Begin Source File

SOURCE=..\Lfc10\Objetos.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\Paciente.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\TreePaciente.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewAllReports.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewBuscarPaciente.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewCondicion.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewConfigurarSesion.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewMostrarDatos.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewRegistro.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewSenales.h
# End Source File
# Begin Source File

SOURCE=..\neurofbdll\ViewTraining.h
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

SOURCE=.\res\file1.bin
# End Source File
# Begin Source File

SOURCE=.\res\neurofb.ico
# End Source File
# Begin Source File

SOURCE=.\res\neurofb.rc2
# End Source File
# Begin Source File

SOURCE=.\res\session1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Game.ogl
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section neurofb : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section neurofb : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
