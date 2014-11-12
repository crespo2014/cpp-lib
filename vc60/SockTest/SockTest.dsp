# Microsoft Developer Studio Project File - Name="SockTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SockTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SockTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SockTest.mak" CFG="SockTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SockTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SockTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SockTest - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SockTest - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SockTest - Win32 Release"
# Name "SockTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\SRC\BridgeSvr.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CircularBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\LockEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\MemPage.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\MessageEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\Sock.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\SockBridge.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\SockCommon.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\SockSvr.cpp
# End Source File
# Begin Source File

SOURCE=.\SockTest.cpp
# End Source File
# Begin Source File

SOURCE=.\SockTest.rc
# End Source File
# Begin Source File

SOURCE=.\SockTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\SRC\TcpIpServer.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\TcpIpSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\TrafficFile.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\Unknown.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BridgeSvr.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CircularBuffer.h
# End Source File
# Begin Source File

SOURCE=..\Interfaces\ICommunicationEvents.h
# End Source File
# Begin Source File

SOURCE=..\Interfaces\ISocketEvents.h
# End Source File
# Begin Source File

SOURCE=..\Interfaces\itcpipserverevents.h
# End Source File
# Begin Source File

SOURCE=..\Clases\LockEvent.h
# End Source File
# Begin Source File

SOURCE=.\MemPage.h
# End Source File
# Begin Source File

SOURCE=..\Clases\MessageEvent.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\Sock.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\SockBridge.h
# End Source File
# Begin Source File

SOURCE=.\SockBridge.h
# End Source File
# Begin Source File

SOURCE=.\SockSvr.h
# End Source File
# Begin Source File

SOURCE=.\SockTest.h
# End Source File
# Begin Source File

SOURCE=.\SockTestDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\Clases\TcpIpServer.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\TcpIpServer.h
# End Source File
# Begin Source File

SOURCE=..\Clases\TcpIpSocket.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\TcpIpSocket.h
# End Source File
# Begin Source File

SOURCE=.\TrafficFile.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\SockTest.ico
# End Source File
# Begin Source File

SOURCE=.\res\SockTest.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\SvrCnf.txt
# End Source File
# End Target
# End Project
