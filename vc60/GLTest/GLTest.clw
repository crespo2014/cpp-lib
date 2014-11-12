; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGLWind
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GLTest.h"

ClassCount=4
Class1=CGLTestApp
Class2=CGLTestDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_GLTEST_DIALOG
Resource4=IDD_GLTEST_DIALOG (Spanish (Modern))
Class4=CGLWind
Resource5=IDD_ABOUTBOX (Spanish (Modern))

[CLS:CGLTestApp]
Type=0
HeaderFile=GLTest.h
ImplementationFile=GLTest.cpp
Filter=N

[CLS:CGLTestDlg]
Type=0
HeaderFile=GLTestDlg.h
ImplementationFile=GLTestDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CGLTestDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=GLTestDlg.h
ImplementationFile=GLTestDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_GLTEST_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CGLTestDlg

[DLG:IDD_GLTEST_DIALOG (Spanish (Modern))]
Type=1
Class=CGLTestDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_OPENGL,button,1073807360
Control4=IDC_TREE_3DOBJECT,SysTreeView32,1350631563

[DLG:IDD_ABOUTBOX (Spanish (Modern))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CGLWind]
Type=0
HeaderFile=GLWind.h
ImplementationFile=GLWind.cpp
BaseClass=CMemDCView
Filter=W
VirtualFilter=WC
LastObject=CGLWind

