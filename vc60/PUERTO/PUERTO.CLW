; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPuertoDlg
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "puerto.h"

ClassCount=3
Class1=CPuertoApp
Class2=CPuertoDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PUERTO_DIALOG
Resource4=IDD_ABOUTBOX (Spanish (Modern))
Resource5=IDD_PUERTO_DIALOG (Spanish (Modern))

[CLS:CPuertoApp]
Type=0
HeaderFile=puerto.h
ImplementationFile=puerto.cpp
Filter=N

[CLS:CPuertoDlg]
Type=0
HeaderFile=puertoDlg.h
ImplementationFile=puertoDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CPuertoDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=puertoDlg.h
ImplementationFile=puertoDlg.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_PUERTO_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CPuertoDlg

[DLG:IDD_PUERTO_DIALOG (Spanish (Modern))]
Type=1
Class=CPuertoDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_BUTTON3,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,button,1342178055
Control9=IDC_ESTADO,static,1342308353
Control10=IDC_CURVAS,static,1342308353

[DLG:IDD_ABOUTBOX (Spanish (Modern))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

