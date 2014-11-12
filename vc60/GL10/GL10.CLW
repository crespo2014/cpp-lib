; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=11
ResourceCount=4
NewFileInclude1=#include "stdafx.h"
Class1=CGLView
LastClass=CTree3DObject
LastTemplate=generic CWnd
Resource1=IDD_DIALOGBAR (English (U.S.))
Class2=CDlgCilinder
Resource2=IDD_VAR_INST_DLG
Class3=CDlg3DObject
Resource3=IDR_TREE_MENU
Class4=CTree3DObject
Class5=CDlgSelectObject
Class6=CEscenaTree
Class7=CDlgAddVar
Class8=CVariableDlg
Class9=CVariableInstanceDlg
Class10=CMemDCView
Class11=CGraphWnd
Resource4=IDD_VARIABLE

[CLS:CGLView]
Type=0
HeaderFile=class4.h
ImplementationFile=class4.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CGLView

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CDlgCilinder]
Type=0
HeaderFile=Dlg1.h
ImplementationFile=Dlg1.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgCilinder
VirtualFilter=dWC

[CLS:CDlg3DObject]
Type=0
HeaderFile=Dlg2.h
ImplementationFile=Dlg2.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlg3DObject

[CLS:CDlgSelectObject]
Type=0
HeaderFile=gl10d3.h
ImplementationFile=gl10d3.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgSelectObject
VirtualFilter=dWC

[CLS:CTree3DObject]
Type=0
HeaderFile=gl10c2.h
ImplementationFile=gl10c2.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC
LastObject=CTree3DObject

[CLS:CEscenaTree]
Type=0
HeaderFile=gl10c7.h
ImplementationFile=gl10c7.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC
LastObject=ID_ESCENA_WIREFRAME

[CLS:CDlgAddVar]
Type=0
HeaderFile=gl10d4.h
ImplementationFile=gl10d4.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgAddVar
VirtualFilter=dWC

[DLG:IDD_VARIABLE]
Type=1
Class=CVariableDlg
ControlCount=7
Control1=IDOK,button,1342242816
Control2=IDC_POS,msctls_trackbar32,1342242840
Control3=IDC_MAX,edit,1350631552
Control4=IDC_STATIC,static,1342308864
Control5=IDC_VALOR,edit,1342244864
Control6=IDC_STATIC,static,1342308864
Control7=IDC_EDIT1,edit,1350631552

[CLS:CVariableDlg]
Type=0
HeaderFile=gl10d5.h
ImplementationFile=gl10d5.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CVariableDlg

[MNU:IDR_TREE_MENU]
Type=1
Class=CEscenaTree
Command1=ID_ESCENA_READ3DS
Command2=ID_ESCENA_NEWVARIABLE
Command3=ID_ESCENA_SAVE
Command4=ID_ESCENA_READ
Command5=ID_ESCENA_WIREFRAME
Command6=ID_MATERIAL_CHANGE
Command7=ID_MESH_READ
Command8=ID_MESGROUP_DELETE
Command9=ID_MESGROUP_NEW
Command10=ID_VARIABLE_PROPIEDADES
Command11=ID_MESHINSTANCE_DELETE
Command12=ID_VARIABLEINSTANCE_DELETE
Command13=ID_VARIABLEINSTANCE_PROPIEDADES
CommandCount=13

[DLG:IDD_VAR_INST_DLG]
Type=1
Class=CVariableInstanceDlg
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_MINIMO,edit,1350631552
Control5=IDC_STATIC,static,1342308864
Control6=IDC_PENDIENTE,edit,1350631552
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STATIC,static,1342308864
Control10=IDC_STATIC,static,1342308864
Control11=IDC_ROTCENX,edit,1350631552
Control12=IDC_ROTCENY,edit,1350631552
Control13=IDC_ROTCENZ,edit,1350631552
Control14=IDC_STATIC,static,1342308864
Control15=IDC_ROTVECTX,edit,1350631552
Control16=IDC_ROTVECY,edit,1350631552
Control17=IDC_ROTVECZ,edit,1350631552
Control18=IDC_STATIC,static,1342308864
Control19=IDC_POSX,edit,1350631552
Control20=IDC_POSY,edit,1350631552
Control21=IDC_POSZ,edit,1350631552
Control22=IDC_STATIC,button,1342178055
Control23=IDC_STATIC,button,1342178055
Control24=IDC_MODIFICAR,button,1342242816

[CLS:CVariableInstanceDlg]
Type=0
HeaderFile=gl10d6.h
ImplementationFile=gl10d6.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CVariableInstanceDlg

[CLS:CMemDCView]
Type=0
HeaderFile=gl10c12.h
ImplementationFile=gl10c12.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

[CLS:CGraphWnd]
Type=0
HeaderFile=gl10c13.h
ImplementationFile=gl10c13.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

