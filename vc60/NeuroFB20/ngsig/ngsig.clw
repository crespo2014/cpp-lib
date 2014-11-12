; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=2
ResourceCount=5
NewFileInclude1=#include "stdafx.h"
Resource1="IDD_SETTINGS"
Class1=CSignalFrame
LastClass=CSignalFrame
LastTemplate=CDialog
Resource2=PORT_CONFIGURATION (Spanish (Mexican))
Resource3=IDR_MENU_CLINICIAN_DISPLAY
Class2=CGraphicsSettings
Resource4=IDR_TOOLBAR1
Resource5=IDR_TOOLBAR_CLINICIAN_DISPLAY

[CLS:CSignalFrame]
Type=0
HeaderFile=sigc07.h
ImplementationFile=sigc07.cpp
BaseClass=CFrameWnd
Filter=T
VirtualFilter=fWC
LastObject=ID_VIEW_FREC

[MNU:IDR_MENU_CLINICIAN_DISPLAY]
Type=1
Class=?
Command1=ID_CONFIGURATION_GRAPHICSSETTINGS
CommandCount=1

[DLG:PORT_CONFIGURATION (Spanish (Mexican))]
Type=1
Class=?
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PORT_OPEN,button,1342242816
Control4=IDC_PORT_CLOSE,button,1342242816
Control5=IDC_PORT_APPLY,button,1342242816
Control6=IDC_STATIC,static,1342308864
Control7=IDC_PORT,combobox,1344339971
Control8=IDC_STATIC,static,1342308864
Control9=IDC_BYTESIZE,combobox,1344339971
Control10=IDC_STATIC,static,1342308864
Control11=IDC_STOPBITS,combobox,1344339971
Control12=IDC_STATIC,static,1342308864
Control13=IDC_PARITY,combobox,1344339971
Control14=IDC_STATIC,static,1342308864
Control15=IDC_BAUDRATE,combobox,1344339971

[TB:IDR_TOOLBAR1]
Type=1
Command1=ID_BUTTON32778
CommandCount=1

[CLS:CGraphicsSettings]
Type=0
HeaderFile=GraphicsSettings.h
ImplementationFile=GraphicsSettings.cpp
BaseClass=CDialog
Filter=D
LastObject=CGraphicsSettings
VirtualFilter=dWC

[TB:IDR_TOOLBAR_CLINICIAN_DISPLAY]
Type=1
Class=?
Command1=ID_TB_SHOW_ALL_GRAPHICS
Command2=ID_TB_SHOW_RAW
Command3=ID_TB_SHOW_REEG
Command4=ID_TB_SHOW_IEEG
Command5=ID_TB_SHOW_IEMG
Command6=ID_VIEW_FREC
CommandCount=6

[DLG:"IDD_SETTINGS"]
Type=1
Class=CGraphicsSettings
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SAMPLES_CANT,combobox,1344339971
Control4=IDC_STATIC,static,1342308352
Control5=IDC_VOLT_POR_DIV,combobox,1344339971
Control6=IDC_STATIC,static,1342308864
Control7=IDC_AXIS_POSITION,combobox,1344339971
Control8=IDC_GRID_COLOR,button,1342242816
Control9=IDC_SIGNAL_COLOR,button,1342242816
Control10=IDC_BACK_COLOR,button,1342242816
Control11=IDC_STATIC,button,1342178055

