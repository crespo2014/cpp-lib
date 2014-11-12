; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFileFilterDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FileFilter.h"

ClassCount=3
Class1=CFileFilterApp
Class2=CFileFilterDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FILEFILTER_DIALOG

[CLS:CFileFilterApp]
Type=0
HeaderFile=FileFilter.h
ImplementationFile=FileFilter.cpp
Filter=N

[CLS:CFileFilterDlg]
Type=0
HeaderFile=FileFilterDlg.h
ImplementationFile=FileFilterDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CFileFilterDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=FileFilterDlg.h
ImplementationFile=FileFilterDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FILEFILTER_DIALOG]
Type=1
Class=CFileFilterDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BTN_OPEN,button,1342242816
Control4=IDC_ST_FILENAME,static,1342308352
Control5=IDC_BTN_CLOSE,button,1342242816
Control6=IDC_BTN_PORTFILTER,button,1342242816

