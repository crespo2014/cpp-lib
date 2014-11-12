# Microsoft Developer Studio Project File - Name="dependencias" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=dependencias - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dependencias.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dependencias.mak" CFG="dependencias - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dependencias - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "dependencias - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dependencias - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\inc" /I "D:\home\projects\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "LOTUS8" /D "NT" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib notes.lib /nologo /subsystem:console /machine:I386 /out:"C:\Archivos de programa\IBM\Lotus\Notes\ngid.exe" /libpath:"D:\home\projects\inc\lotus\v8\lib" /libpath:"..\bin"

!ELSEIF  "$(CFG)" == "dependencias - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\Debug"
# PROP Intermediate_Dir "..\..\..\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W4 /Zi /Od /I "..\inc" /I "D:\home\projects\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "LOTUS8" /D "NT" /FR /FD /GF /c
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winhttp.lib Comdlg32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"comsupp.lib libcd.lib oldnames.lib" /out:"debug\app.exe" /pdbtype:sept /libpath:"D:\home\projects\inc\lotus\v8\lib" /libpath:"..\bin" /verbose:lib
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "dependencias - Win32 Release"
# Name "dependencias - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\inc\b64.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\bApp.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\bDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\BlockMem.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\bObject.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\BSTR.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\cmdLineParser.cpp
# End Source File
# Begin Source File

SOURCE=.\CodePage.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\ConfigParser.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\Crypter.cpp
# End Source File
# Begin Source File

SOURCE=.\dependencias.cpp

!IF  "$(CFG)" == "dependencias - Win32 Release"

!ELSEIF  "$(CFG)" == "dependencias - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HtmlCoder.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\HttpReq.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\LogClient.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\memarray.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\StaticMem.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\Tube.cpp
# End Source File
# Begin Source File

SOURCE=..\inc\Utils.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\inc\b64.h
# End Source File
# Begin Source File

SOURCE=..\inc\bApp.h
# End Source File
# Begin Source File

SOURCE=..\inc\bDlg.h
# End Source File
# Begin Source File

SOURCE=..\inc\BlockMem.h
# End Source File
# Begin Source File

SOURCE=..\inc\bObject.h
# End Source File
# Begin Source File

SOURCE=..\inc\BSTR.h
# End Source File
# Begin Source File

SOURCE=..\inc\cmdLineParser.h
# End Source File
# Begin Source File

SOURCE=.\CodePage.h
# End Source File
# Begin Source File

SOURCE=..\inc\ConfigParser.h
# End Source File
# Begin Source File

SOURCE=..\inc\Crypter.h
# End Source File
# Begin Source File

SOURCE=.\HtmlCoder.h
# End Source File
# Begin Source File

SOURCE=.\IConfig.h
# End Source File
# Begin Source File

SOURCE=..\inc\IMem.h
# End Source File
# Begin Source File

SOURCE=..\inc\ITube.h
# End Source File
# Begin Source File

SOURCE=..\inc\LNotesError.h
# End Source File
# Begin Source File

SOURCE=..\inc\LogClient.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=..\inc\LotusDB.h
# End Source File
# Begin Source File

SOURCE=..\inc\LotusNote.h
# End Source File
# Begin Source File

SOURCE=..\inc\LotusSection.h
# End Source File
# Begin Source File

SOURCE=.\ncfParser.h
# End Source File
# Begin Source File

SOURCE=.\notesapp.h
# End Source File
# Begin Source File

SOURCE=.\PwdDialog.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=..\inc\StaticMem.h
# End Source File
# Begin Source File

SOURCE=..\inc\Tube.h
# End Source File
# Begin Source File

SOURCE=.\User.h
# End Source File
# Begin Source File

SOURCE=..\inc\Utils.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\carrefour.bmp
# End Source File
# Begin Source File

SOURCE=.\Logo.bmp
# End Source File
# Begin Source File

SOURCE=.\Notes.ico
# End Source File
# Begin Source File

SOURCE=.\text1.bin
# End Source File
# End Group
# Begin Source File

SOURCE=.\en.ini
# End Source File
# Begin Source File

SOURCE=.\es.ini
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\recurs
# End Source File
# End Target
# End Project
