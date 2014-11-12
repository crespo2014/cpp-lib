; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPage
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "P02.h"

ClassCount=5
Class1=CP02App
Class2=CDialog01
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_P02_DIALOG (English (U.S.))
Resource4=IDD_ABOUTBOX (English (U.S.))
Class4=CReGrid
Class5=CPage
Resource5=IDD_DIALOG1

[CLS:CP02App]
Type=0
HeaderFile=P02.h
ImplementationFile=P02.cpp
Filter=N

[CLS:CAboutDlg]
Type=0
HeaderFile=P02Dlg.h
ImplementationFile=P02Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CReGrid]
Type=0
HeaderFile=ReGrid.h
ImplementationFile=ReGrid.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

[DLG:IDD_P02_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG1]
Type=1
Class=CDialog01
ControlCount=1
Control1=IDC_PRINT,button,1342242816

[CLS:CDialog01]
Type=0
HeaderFile=Dialog01.h
ImplementationFile=Dialog01.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDialog01

[CLS:CPage]
Type=0
HeaderFile=Page.h
ImplementationFile=Page.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

