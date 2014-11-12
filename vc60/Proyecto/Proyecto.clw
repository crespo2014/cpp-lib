; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProyectoView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Proyecto.h"
LastPage=0

ClassCount=13
Class1=CProyectoApp
Class2=CProyectoDoc
Class3=CProyectoView
Class4=CMainFrame

ResourceCount=9
Resource1=IDD_GRAFICO
Resource2=IDD_SIMULACION
Class5=CAboutDlg
Resource3=IDD_CONFIG_CR
Resource4=IDD_CONFIG_CT
Resource5=IDD_CD
Resource6=IDR_MAINFRAME
Resource7=IDD_CONFIG_SUP
Class6=T_CD
Class7=T_CR_DLG
Class8=T_CT_DLG
Class9=T_CS_DLG
Class10=T_S_DLG
Resource8=IDD_ABOUTBOX
Class11=T_MSG_DLG
Class12=TGrafica
Class13=T_G_DLG
Resource9=IDD_MSG

[CLS:CProyectoApp]
Type=0
HeaderFile=Proyecto.h
ImplementationFile=Proyecto.cpp
Filter=N

[CLS:CProyectoDoc]
Type=0
HeaderFile=ProyectoDoc.h
ImplementationFile=ProyectoDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CProyectoDoc

[CLS:CProyectoView]
Type=0
HeaderFile=ProyectoView.h
ImplementationFile=ProyectoView.cpp
Filter=C
LastObject=ID_CERRAR
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=Proyecto.cpp
ImplementationFile=Proyecto.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_NUEVO
Command2=ID_ABRIR
Command3=ID_CERRAR
Command4=ID_GUARDAR
Command5=ID_APP_EXIT
Command6=ID_SIMULACION
Command7=ID_CONFIGURAR_TRANSMISOR
Command8=ID_CONFIGURAR_RECEPTOR
Command9=ID_CONFIGURAR_SUPERFICIE
Command10=ID_CONFIGURAR_DIMENSIONES
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:]
Type=1
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,static,1342308864
Control6=IDC_LARGO,edit,1350631552
Control7=IDC_ANCHO,edit,1350631552
Control8=IDC_ALTURA,edit,1350631552

[DLG:IDD_CD]
Type=1
Class=T_CD
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,static,1342308864
Control6=IDC_LARGO,edit,1350631552
Control7=IDC_ANCHO,edit,1350631552
Control8=IDC_ALTURA,edit,1350631552

[DLG:IDD_CONFIG_CR]
Type=1
Class=T_CR_DLG
ControlCount=30
Control1=65535,button,1342177287
Control2=65535,static,1342308864
Control3=VOX,edit,1350631552
Control4=65535,static,1342308864
Control5=65535,static,1342308864
Control6=VOY,edit,1350631552
Control7=VOZ,edit,1350631552
Control8=65535,button,1342177287
Control9=65535,static,1342308864
Control10=VPX,edit,1350631552
Control11=65535,static,1342308864
Control12=65535,static,1342308864
Control13=VPY,edit,1350631552
Control14=VPZ,edit,1350631552
Control15=IDC_POS,static,1342308352
Control16=IDOK,button,1342242817
Control17=IDCANCEL,button,1342242816
Control18=IDC_GRAFICAR,button,1342242816
Control19=IDC_ANTERIOR,button,1342242816
Control20=IDC_SIGUIENTE,button,1342242816
Control21=IDC_ADICIONAR,button,1342242816
Control22=65535,static,1342308864
Control23=AS,edit,1350631552
Control24=65535,static,1342308864
Control25=AC,edit,1350631552
Control26=65535,static,1342308864
Control27=CV,edit,1350631552
Control28=65535,static,1342308864
Control29=65535,static,1342308864
Control30=65535,static,1342308864

[DLG:IDD_CONFIG_CT]
Type=1
Class=T_CT_DLG
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308864
Control5=VOX,edit,1350631552
Control6=IDC_STATIC,static,1342308864
Control7=IDC_STATIC,static,1342308864
Control8=VOY,edit,1350631552
Control9=VOZ,edit,1350631552
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308864
Control12=VPX,edit,1350631552
Control13=IDC_STATIC,static,1342308864
Control14=IDC_STATIC,static,1342308864
Control15=VPY,edit,1350631552
Control16=VPZ,edit,1350631552
Control17=IDC_STATIC,static,1342308864
Control18=IDC_STATIC,static,1342308864
Control19=PERRAD,edit,1350631552
Control20=POTRAD,edit,1350631552
Control21=IDC_T_GRAFICAR,button,1342242816
Control22=IDC_T_ANTERIOR,button,1342242816
Control23=IDC_T_SIGUIENTE,button,1342242816
Control24=IDC_T_POS,static,1342308352
Control25=IDC_T_ADICIONAR,button,1342242816
Control26=IDC_STATIC,static,1342308864

[DLG:IDD_CONFIG_SUP]
Type=1
Class=T_CS_DLG
ControlCount=23
Control1=65535,button,1342177287
Control2=65535,static,1342308864
Control3=VOX,edit,1350631552
Control4=65535,static,1342308864
Control5=65535,static,1342308864
Control6=VOY,edit,1350631552
Control7=VOZ,edit,1350631552
Control8=65535,button,1342177287
Control9=65535,static,1342308864
Control10=VPX,edit,1350631552
Control11=65535,static,1342308864
Control12=65535,static,1342308864
Control13=VPY,edit,1350631552
Control14=VPZ,edit,1350631552
Control15=IDC_S_POS,static,1342308352
Control16=65535,static,1342308864
Control17=CR,edit,1350631552
Control18=IDOK,button,1342242817
Control19=IDCANCEL,button,1342242816
Control20=IDC_S_GRAFICAR,button,1342242816
Control21=IDC_S_ANTERIOR,button,1342242816
Control22=IDC_S_SIGUIENTE,button,1342242816
Control23=IDC_S_ADICONAR,button,1342242816

[DLG:IDD_GRAFICO]
Type=1
Class=T_G_DLG
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GRAFICO,static,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_X,edit,1350631552
Control8=IDC_Y,edit,1350631552
Control9=IDC_Z,edit,1350631552
Control10=IDC_STATIC,static,1342308864
Control11=IDC_STATIC,static,1342308864
Control12=IDC_STATIC,static,1342308864
Control13=IDC_APLICAR,button,1342242816

[DLG:IDD_SIMULACION]
Type=1
Class=T_S_DLG
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816

[CLS:T_CD]
Type=0
HeaderFile=T_CD.h
ImplementationFile=T_CD.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_ANCHO

[CLS:T_CR_DLG]
Type=0
HeaderFile=T_CR_DLG.h
ImplementationFile=T_CR_DLG.cpp
BaseClass=CDialog
Filter=D
LastObject=VPX
VirtualFilter=dWC

[CLS:T_CT_DLG]
Type=0
HeaderFile=T_CT_DLG.h
ImplementationFile=T_CT_DLG.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ABRIR
VirtualFilter=dWC

[CLS:T_CS_DLG]
Type=0
HeaderFile=T_CS_DLG.h
ImplementationFile=T_CS_DLG.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:T_S_DLG]
Type=0
HeaderFile=T_S_DLG.h
ImplementationFile=T_S_DLG.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_MSG]
Type=1
Class=T_MSG_DLG
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LABEL,static,1342308865
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_STATIC,static,1342177283

[CLS:T_MSG_DLG]
Type=0
HeaderFile=T_MSG_DLG.h
ImplementationFile=T_MSG_DLG.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:TGrafica]
Type=0
HeaderFile=TGrafica.h
ImplementationFile=TGrafica.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

[CLS:T_G_DLG]
Type=0
HeaderFile=T_G_DLG.h
ImplementationFile=T_G_DLG.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

