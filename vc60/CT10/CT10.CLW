; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCT10Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CT10.h"

ClassCount=3
Class1=CCT10App
Class2=CCT10Dlg

ResourceCount=3
Resource2=IDD_CT10_DIALOG
Resource1=IDR_MAINFRAME
Class3=CConfigDlg
Resource3=IDD_CT10_DIALOG (Spanish (Modern))

[CLS:CCT10App]
Type=0
HeaderFile=CT10.h
ImplementationFile=CT10.cpp
Filter=N

[CLS:CCT10Dlg]
Type=0
HeaderFile=CT10Dlg.h
ImplementationFile=CT10Dlg.cpp
Filter=D
LastObject=CCT10Dlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_CT10_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CCT10Dlg

[DLG:IDD_CT10_DIALOG (Spanish (Modern))]
Type=1
Class=CCT10Dlg
ControlCount=17
Control1=IDC_STATIC,static,1342308864
Control2=IDC_RECEIVEDBYTESEDIT,edit,1352730756
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_BUTTON3,button,1342242817
Control6=IDC_STATIC,static,1342308864
Control7=IDC_SEND,edit,1350631424
Control8=IDC_BUTTON4,button,1342242816
Control9=IDC_BUTTON5,button,1342242816
Control10=IDC_RECEIVEDBYTESCANT,static,1342308864
Control11=IDC_COMBO2,combobox,1344339971
Control12=IDC_SENDMESSAGE,static,1342308864
Control13=IDC_BUTTON6,button,1342242816
Control14=IDC_SENTBYTESEDIT,edit,1352730628
Control15=IDC_STATIC,static,1342308864
Control16=IDC_STATIC,static,1342308864
Control17=IDC_SENTBYTES,static,1342308864

[CLS:CConfigDlg]
Type=0
HeaderFile=CDlg.h
ImplementationFile=CDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CConfigDlg

