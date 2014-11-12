# Microsoft Developer Studio Project File - Name="ROBOT1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=ROBOT1 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ROBOT1.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ROBOT1.MAK" CFG="ROBOT1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ROBOT1 - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "ROBOT1 - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "ROBOT1 - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f ROBOT.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "ROBOT.exe"
# PROP BASE Bsc_Name "ROBOT.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f ROBOT.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "ROBOT1.EXE"
# PROP Bsc_Name "ROBOT1.BSC"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "ROBOT1 - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f ROBOT.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "ROBOT.exe"
# PROP BASE Bsc_Name "ROBOT.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f ROBOT.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "ROBOT1.vxd"
# PROP Bsc_Name "ROBOT1.BSC"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "ROBOT1 - Win32 Release"
# Name "ROBOT1 - Win32 Debug"

!IF  "$(CFG)" == "ROBOT1 - Win32 Release"

!ELSEIF  "$(CFG)" == "ROBOT1 - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\Cmosio.c
# End Source File
# Begin Source File

SOURCE=.\Cmosio.h
# End Source File
# Begin Source File

SOURCE=.\ROBOT.c
# End Source File
# Begin Source File

SOURCE=.\ROBOT.h
# End Source File
# Begin Source File

SOURCE=.\ROBOT.mak
# End Source File
# End Target
# End Project
