; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=14
ResourceCount=33
NewFileInclude1=#include "stdafx.h"
Resource1=IDD_MOSTRARDATOS
Resource2=IDD_PASSWORD
Resource3=IDD_CONFIGURARSESION
Resource4=IDD_REPORTES
Resource5="FONT_DLGBAR" (English (U.S.))
Class1=CViewRegistro
LastClass=CViewMostrarDatos
LastTemplate=CDialog
Class2=CBuscarPaciente
Class3=CViewMostrarDatos
Class4=CViewConfigurarSesion
Class5=CViewCondicion
Class6=CViewConfigurarJuego
Class7=CEntradaSistema
Class8=CTreePaciente
Class9=CViewAllReports
Resource6=IDD_REGISTRO
Resource7=IDD_CONDICION
Class10=CChangePass
Resource8=IDD_CLINICIANDISPLAY
Class11=CViewSenales
Resource9=IDD_BUSCARPACIENTE
Resource10=PASSWORD
Class12=CViewTraining
Resource11=IDD_TRAINING
Resource12="IDD_MOSTRARDATOS"
Resource13="IDD_CONFIGURARSESION"
Resource14="IDD_CONDICION"
Resource15="IDD_PASSWORD"
Resource16="IDD_REPORTES"
Resource17="IDD_BUSCARPACIENTE"
Resource18="IDD_REGISTRO"
Resource19="PASSWORD"
Resource20="IDD_CLINICIANDISPLAY"
Resource21="IDD_PASSWORD" (Spanish (Mexican))
Resource22="IDD_TRAINING" (Spanish (Mexican))
Resource23="IDD_REGISTRO" (Spanish (Mexican))
Resource24="IDD_CONFIGURARSESION" (Spanish (Mexican))
Resource25="IDD_BUSCARPACIENTE" (Spanish (Mexican))
Resource26="IDD_REPORTES" (Spanish (Mexican))
Resource27="PASSWORD" (Spanish (Mexican))
Resource28="FONT_DLGBAR"
Resource29="IDD_MOSTRARDATOS" (Spanish (Mexican))
Resource30="IDD_CLINICIANDISPLAY" (Spanish (Mexican))
Resource31="IDD_CONDICION" (Spanish (Mexican))
Class13=CPortConf
Class14=CGameDlg
Resource32="PORT_CONFIGURATION" (Spanish (Mexican))
Resource33=PORT_CONFIGURATION (Spanish (Mexican))

[DLG:IDD_MOSTRARDATOS]
Type=1
Class=CViewMostrarDatos
ControlCount=33
Control1=IDCANCEL,button,1342242817
Control2=IDC_GRIDMINUTOS,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TREEPACIENTE,SysTreeView32,1350631424
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDITSESSIONDATE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDITSESSIONREPORT,edit,1350631552
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDITDURACIONCONDICION,edit,1350631552
Control22=IDC_EDITNIVELINHIBICIONEEG,edit,1350631552
Control23=IDC_EDITNIVELREWARDEEG,edit,1350631552
Control24=IDC_EDITNIVELINHIBICIONMUSCULO,edit,1350631552
Control25=IDC_EDITCRITERIOCOMPARACIONBURST,edit,1350631552
Control26=IDC_EDITTIEMPOCONTEOBURST,edit,1350631552
Control27=IDC_EDITBFINHIBICIONEEG,edit,1350631552
Control28=IDC_EDITTEMPERATURA,edit,1350631552
Control29=IDC_EDITAFINHIBICIONEEG,edit,1350631552
Control30=IDC_EDITBFREWARDEEG,edit,1350631552
Control31=IDC_EDITAFREWARDEEG,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_EDITAFMUSCLEFREG,edit,1350631552

[DLG:IDD_CONFIGURARSESION]
Type=1
Class=CViewConfigurarSesion
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_REJILLA,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control4=IDC_ADD,button,1342242816
Control5=IDC_DELETE,button,1342242816
Control6=IDC_UPDATE,button,1342242816

[DLG:IDD_CONDICION]
Type=1
Class=CViewCondicion
ControlCount=26
Control1=IDC_EDITDURACIONCONDICION,edit,1350631552
Control2=IDC_EDITNIVELINHIBICIONEEG,edit,1350631552
Control3=IDC_EDITNIVELREWARDEEG,edit,1350631552
Control4=IDC_EDITNIVELINHIBICIONMUSCULO,edit,1350631552
Control5=IDC_EDITCRITERIOCOMPARACIONBURST,edit,1350631552
Control6=IDC_EDITTIEMPOCONTEOBURST,edit,1350631552
Control7=IDC_EDITTEMPERATURA,edit,1350631552
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_COMBOILOWFREQ,combobox,1344340227
Control23=IDC_COMBORLOWFREQ,combobox,1344340227
Control24=IDC_COMBOIHIGHFREQ,combobox,1344340227
Control25=IDC_COMBORHIGHFREQ,combobox,1344340227
Control26=IDC_COMBOMUSCLEFREQ,combobox,1344340227

[CLS:CViewRegistro]
Type=0
HeaderFile=ViewRegistro.h
ImplementationFile=ViewRegistro.cpp
BaseClass=CDialog
Filter=D
LastObject=CViewRegistro

[CLS:CBuscarPaciente]
Type=0
HeaderFile=BuscarPaciente.h
ImplementationFile=BuscarPaciente.cpp
BaseClass=CDialog
Filter=D
LastObject=CBuscarPaciente

[CLS:CViewMostrarDatos]
Type=0
HeaderFile=ViewMostrarDatos.h
ImplementationFile=ViewMostrarDatos.cpp
BaseClass=CDialog
Filter=D
LastObject=CViewMostrarDatos
VirtualFilter=dWC

[CLS:CViewConfigurarSesion]
Type=0
HeaderFile=ViewConfigurarSesion.h
ImplementationFile=ViewConfigurarSesion.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_REJILLA
VirtualFilter=dWC

[CLS:CViewCondicion]
Type=0
HeaderFile=ViewCondicion.h
ImplementationFile=ViewCondicion.cpp
BaseClass=CDialog
Filter=D
LastObject=CViewCondicion
VirtualFilter=dWC

[CLS:CViewConfigurarJuego]
Type=0
HeaderFile=ViewConfigurarJuego.h
ImplementationFile=ViewConfigurarJuego.cpp
BaseClass=CDialog
Filter=D
LastObject=CViewConfigurarJuego

[DLG:IDD_PASSWORD]
Type=1
Class=CEntradaSistema
ControlCount=3
Control1=IDC_PASSWORD,edit,1350631584
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CEntradaSistema]
Type=0
HeaderFile=EntradaSistema.h
ImplementationFile=EntradaSistema.cpp
BaseClass=CDialog
Filter=D
LastObject=CEntradaSistema
VirtualFilter=dWC

[CLS:CTreePaciente]
Type=0
HeaderFile=TreePaciente.h
ImplementationFile=TreePaciente.cpp
BaseClass=CTreeCtrl
Filter=W
LastObject=CTreePaciente
VirtualFilter=GWC

[DLG:IDD_REPORTES]
Type=1
Class=CViewAllReports
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDITREPORTS,edit,1350631620

[CLS:CViewAllReports]
Type=0
HeaderFile=ViewAllReports.h
ImplementationFile=ViewAllReports.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDITREPORTS

[DLG:IDD_BUSCARPACIENTE]
Type=1
Class=?
ControlCount=15
Control1=IDCANCEL,button,1342242816
Control2=IDC_TODOS,button,1342308361
Control3=IDC_NOMBRE,button,1342177289
Control4=IDC_BUSCA_TODOS,button,1342177289
Control5=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control6=IDC_STATIC,button,1342178055
Control7=IDC_BUSCAR_PACIENTE,button,1342242817
Control8=IDC_ID,edit,1350635648
Control9=IDC_NAME,edit,1350635648
Control10=IDC_STATIC,button,1342178055
Control11=IDC_CARGA_PACIENTE,button,1342242816
Control12=IDC_BORRA_PACIENTE,button,1342242816
Control13=IDC_IMPORTA_PACIENTE,button,1342242816
Control14=IDC_EXPORTA_PACIENTE,button,1342242816
Control15=IDC_ACTUALIZAR_PACIENTE,button,1342242816

[DLG:IDD_REGISTRO]
Type=1
Class=?
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=No_Paciente,edit,1350631552
Control4=Nombre_Paciente,edit,1350631552
Control5=Apellido_Paciente,edit,1350631552
Control6=Fecha_Nacimiento,edit,1350631552
Control7=Telefono,edit,1350631552
Control8=Direccion,edit,1350631552
Control9=Diagnostico,edit,1350631552
Control10=Medicacion_Actual,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,button,1342178055

[DLG:PASSWORD]
Type=1
Class=CChangePass
ControlCount=6
Control1=IDC_EDIT_NUEVA,edit,1350631584
Control2=IDC_EDIT_REESCRIBIR,edit,1350631584
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CChangePass]
Type=0
HeaderFile=ChangePass.h
ImplementationFile=ChangePass.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CChangePass

[DLG:IDD_CLINICIANDISPLAY]
Type=1
Class=CViewSenales
ControlCount=0

[CLS:CViewSenales]
Type=0
HeaderFile=ViewSenales.h
ImplementationFile=ViewSenales.cpp
BaseClass=CDialog
Filter=D
LastObject=CViewSenales
VirtualFilter=dWC

[DLG:"FONT_DLGBAR" (English (U.S.))]
Type=1
Class=?
ControlCount=45
Control1=IDC_CLOSE,button,1342242945
Control2=IDC_STATIC,static,1342308352
Control3=FONT_COMBOBOX,combobox,1344340227
Control4=IDC_STATIC,static,1342308352
Control5=FONT_HEIGHT_COMBOBOX,combobox,1344339971
Control6=ITALIC_CHECK,button,1342242819
Control7=BOLD_CHECK,button,1342242819
Control8=IDC_STATIC,static,1342308352
Control9=IDC_GRAPH_NAME,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_SAMPLES_CANT,combobox,1344339971
Control12=IDC_STATIC,static,1342308352
Control13=VOLT_POR_DIV_COMBO,combobox,1344339971
Control14=IDC_STATIC,static,1342308864
Control15=IDC_EDGE_POS,combobox,1344339971
Control16=IDC_STATIC,static,1342308352
Control17=IDC_FILTER,combobox,1344340227
Control18=IDC_EDGE_COLOR,button,1342242816
Control19=IDC_SIGNAL_COLOR,button,1342242816
Control20=IDC_BACK_COLOR,button,1342242816
Control21=IDC_SHOW,button,1342242819
Control22=IDC_PREV,button,1342242816
Control23=IDC_DEVICESTART,button,1342242816
Control24=IDC_DEVICESTOP,button,1342242816
Control25=IDC_NEXT,button,1342242816
Control26=IDC_STATIC,static,1342308864
Control27=IDC_PORT,combobox,1344339971
Control28=IDC_STATIC,static,1342308864
Control29=IDC_BYTESIZE,combobox,1344339971
Control30=IDC_STATIC,static,1342308864
Control31=IDC_STOPBITS,combobox,1344339971
Control32=IDC_STATIC,static,1342308864
Control33=IDC_PARITY,combobox,1344339971
Control34=IDC_STATIC,static,1342308864
Control35=IDC_BAUDRATE,combobox,1344339971
Control36=IDC_PORT_OPEN,button,1342242816
Control37=IDC_PORT_CLOSE,button,1342242816
Control38=IDC_PORT_APPLY,button,1342242816
Control39=IDC_OPEN_CLOSE,static,1342179598
Control40=IDC_GRAPH,button,1342178055
Control41=IDC_STATIC,button,1342178055
Control42=IDC_STATIC,button,1342178055
Control43=IDC_STATIC,button,1342178055
Control44=IDC_STATIC,static,1342177294
Control45=IDC_OPEN_CLOSE2,button,1342242944

[DLG:IDD_TRAINING]
Type=1
Class=CViewTraining
ControlCount=8
Control1=IDC_TRAININGOFFLINE,button,1342242816
Control2=IDC_STARTTRAINING,button,1342242816
Control3=IDC_CHANGEPARAMETERS,button,1342242816
Control4=IDC_CLINICIANDISPLAY,button,1342242816
Control5=IDC_CANCELSESSION,button,1342242816
Control6=IDOK,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287

[CLS:CViewTraining]
Type=0
HeaderFile=ViewTraining.h
ImplementationFile=ViewTraining.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CViewTraining

[DLG:"IDD_MOSTRARDATOS"]
Type=1
ControlCount=33
Control1=IDCANCEL,button,1342242817
Control2=IDC_GRIDMINUTOS,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TREEPACIENTE,SysTreeView32,1350631424
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDITSESSIONDATE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDITSESSIONREPORT,edit,1350631552
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDITDURACIONCONDICION,edit,1350631552
Control22=IDC_EDITNIVELINHIBICIONEEG,edit,1350631552
Control23=IDC_EDITNIVELREWARDEEG,edit,1350631552
Control24=IDC_EDITNIVELINHIBICIONMUSCULO,edit,1350631552
Control25=IDC_EDITCRITERIOCOMPARACIONBURST,edit,1350631552
Control26=IDC_EDITTIEMPOCONTEOBURST,edit,1350631552
Control27=IDC_EDITBFINHIBICIONEEG,edit,1350631552
Control28=IDC_EDITTEMPERATURA,edit,1350631552
Control29=IDC_EDITAFINHIBICIONEEG,edit,1350631552
Control30=IDC_EDITBFREWARDEEG,edit,1350631552
Control31=IDC_EDITAFREWARDEEG,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_EDITAFMUSCLEFREG,edit,1350631552

[DLG:"IDD_CONFIGURARSESION"]
Type=1
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_REJILLA,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control4=IDC_ADD,button,1342242816
Control5=IDC_DELETE,button,1342242816
Control6=IDC_UPDATE,button,1342242816

[DLG:"IDD_CONDICION"]
Type=1
ControlCount=26
Control1=IDC_EDITDURACIONCONDICION,edit,1350631552
Control2=IDC_EDITNIVELINHIBICIONEEG,edit,1350631552
Control3=IDC_EDITNIVELREWARDEEG,edit,1350631552
Control4=IDC_EDITNIVELINHIBICIONMUSCULO,edit,1350631552
Control5=IDC_EDITCRITERIOCOMPARACIONBURST,edit,1350631552
Control6=IDC_EDITTIEMPOCONTEOBURST,edit,1350631552
Control7=IDC_EDITTEMPERATURA,edit,1350631552
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_COMBOILOWFREQ,combobox,1344340227
Control23=IDC_COMBORLOWFREQ,combobox,1344340227
Control24=IDC_COMBOIHIGHFREQ,combobox,1344340227
Control25=IDC_COMBORHIGHFREQ,combobox,1344340227
Control26=IDC_COMBOMUSCLEFREQ,combobox,1344340227

[DLG:"IDD_PASSWORD"]
Type=1
ControlCount=3
Control1=IDC_PASSWORD,edit,1350631584
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[DLG:"IDD_REPORTES"]
Type=1
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDITREPORTS,edit,1350631620

[DLG:"IDD_BUSCARPACIENTE"]
Type=1
ControlCount=15
Control1=IDCANCEL,button,1342242816
Control2=IDC_TODOS,button,1342308361
Control3=IDC_NOMBRE,button,1342177289
Control4=IDC_BUSCA_TODOS,button,1342177289
Control5=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control6=IDC_STATIC,button,1342178055
Control7=IDC_BUSCAR_PACIENTE,button,1342242817
Control8=IDC_ID,edit,1350635648
Control9=IDC_NAME,edit,1350635648
Control10=IDC_STATIC,button,1342178055
Control11=IDC_CARGA_PACIENTE,button,1342242816
Control12=IDC_BORRA_PACIENTE,button,1342242816
Control13=IDC_IMPORTA_PACIENTE,button,1342242816
Control14=IDC_EXPORTA_PACIENTE,button,1342242816
Control15=IDC_ACTUALIZAR_PACIENTE,button,1342242816

[DLG:"IDD_REGISTRO"]
Type=1
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=No_Paciente,edit,1350631552
Control4=Nombre_Paciente,edit,1350631552
Control5=Apellido_Paciente,edit,1350631552
Control6=Fecha_Nacimiento,edit,1350631552
Control7=Telefono,edit,1350631552
Control8=Direccion,edit,1350631552
Control9=Diagnostico,edit,1350631552
Control10=Medicacion_Actual,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,button,1342178055

[DLG:"PASSWORD"]
Type=1
ControlCount=6
Control1=IDC_EDIT_NUEVA,edit,1350631584
Control2=IDC_EDIT_REESCRIBIR,edit,1350631584
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:"IDD_CLINICIANDISPLAY"]
Type=1
ControlCount=0

[DLG:"IDD_CONFIGURARSESION" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_REJILLA,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control4=IDC_ADD,button,1342242816
Control5=IDC_DELETE,button,1342242816
Control6=IDC_UPDATE,button,1342242816

[DLG:"FONT_DLGBAR"]
Type=1
Class=?
ControlCount=45
Control1=IDC_CLOSE,button,1342242945
Control2=IDC_STATIC,static,1342308352
Control3=FONT_COMBOBOX,combobox,1344340227
Control4=IDC_STATIC,static,1342308352
Control5=FONT_HEIGHT_COMBOBOX,combobox,1344339971
Control6=ITALIC_CHECK,button,1342242819
Control7=BOLD_CHECK,button,1342242819
Control8=IDC_STATIC,static,1342308352
Control9=IDC_GRAPH_NAME,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_SAMPLES_CANT,combobox,1344339971
Control12=IDC_STATIC,static,1342308352
Control13=VOLT_POR_DIV_COMBO,combobox,1344339971
Control14=IDC_STATIC,static,1342308864
Control15=IDC_EDGE_POS,combobox,1344339971
Control16=IDC_STATIC,static,1342308352
Control17=IDC_FILTER,combobox,1344340227
Control18=IDC_EDGE_COLOR,button,1342242816
Control19=IDC_SIGNAL_COLOR,button,1342242816
Control20=IDC_BACK_COLOR,button,1342242816
Control21=IDC_SHOW,button,1342242819
Control22=IDC_PREV,button,1342242816
Control23=IDC_DEVICESTART,button,1342242816
Control24=IDC_DEVICESTOP,button,1342242816
Control25=IDC_NEXT,button,1342242816
Control26=IDC_STATIC,static,1342308864
Control27=IDC_PORT,combobox,1344339971
Control28=IDC_STATIC,static,1342308864
Control29=IDC_BYTESIZE,combobox,1344339971
Control30=IDC_STATIC,static,1342308864
Control31=IDC_STOPBITS,combobox,1344339971
Control32=IDC_STATIC,static,1342308864
Control33=IDC_PARITY,combobox,1344339971
Control34=IDC_STATIC,static,1342308864
Control35=IDC_BAUDRATE,combobox,1344339971
Control36=IDC_PORT_OPEN,button,1342242816
Control37=IDC_PORT_CLOSE,button,1342242816
Control38=IDC_PORT_APPLY,button,1342242816
Control39=IDC_OPEN_CLOSE,static,1342179598
Control40=IDC_GRAPH,button,1342178055
Control41=IDC_STATIC,button,1342178055
Control42=IDC_STATIC,button,1342178055
Control43=IDC_STATIC,button,1342178055
Control44=IDC_STATIC,static,1342177294
Control45=IDC_OPEN_CLOSE2,button,1342242944

[DLG:"IDD_MOSTRARDATOS" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=33
Control1=IDCANCEL,button,1342242817
Control2=IDC_GRIDMINUTOS,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TREEPACIENTE,SysTreeView32,1350631424
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDITSESSIONDATE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDITSESSIONREPORT,edit,1350631552
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDITDURACIONCONDICION,edit,1350631552
Control22=IDC_EDITNIVELINHIBICIONEEG,edit,1350631552
Control23=IDC_EDITNIVELREWARDEEG,edit,1350631552
Control24=IDC_EDITNIVELINHIBICIONMUSCULO,edit,1350631552
Control25=IDC_EDITCRITERIOCOMPARACIONBURST,edit,1350631552
Control26=IDC_EDITTIEMPOCONTEOBURST,edit,1350631552
Control27=IDC_EDITBFINHIBICIONEEG,edit,1350631552
Control28=IDC_EDITTEMPERATURA,edit,1350631552
Control29=IDC_EDITAFINHIBICIONEEG,edit,1350631552
Control30=IDC_EDITBFREWARDEEG,edit,1350631552
Control31=IDC_EDITAFREWARDEEG,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_EDITAFMUSCLEFREG,edit,1350631552

[DLG:"IDD_CONDICION" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=26
Control1=IDC_EDITDURACIONCONDICION,edit,1350631552
Control2=IDC_EDITNIVELINHIBICIONMUSCULO,edit,1350631552
Control3=IDC_EDITNIVELINHIBICIONEEG,edit,1350631552
Control4=IDC_EDITNIVELREWARDEEG,edit,1350631552
Control5=IDC_EDITCRITERIOCOMPARACIONBURST,edit,1350631552
Control6=IDC_EDITTIEMPOCONTEOBURST,edit,1350631552
Control7=IDC_EDITTEMPERATURA,edit,1350631552
Control8=IDC_COMBOILOWFREQ,combobox,1344340227
Control9=IDC_COMBOIHIGHFREQ,combobox,1344340227
Control10=IDC_COMBORLOWFREQ,combobox,1344340227
Control11=IDC_COMBORHIGHFREQ,combobox,1344340227
Control12=IDC_COMBOMUSCLEFREQ,combobox,1344340227
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352

[DLG:"IDD_REPORTES" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDITREPORTS,edit,1350631620

[DLG:"IDD_BUSCARPACIENTE" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=15
Control1=IDCANCEL,button,1342242816
Control2=IDC_TODOS,button,1342308361
Control3=IDC_NOMBRE,button,1342177289
Control4=IDC_BUSCA_TODOS,button,1342177289
Control5=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control6=IDC_STATIC,button,1342178055
Control7=IDC_BUSCAR_PACIENTE,button,1342242817
Control8=IDC_ID,edit,1350635648
Control9=IDC_NAME,edit,1350635648
Control10=IDC_STATIC,button,1342178055
Control11=IDC_CARGA_PACIENTE,button,1342242816
Control12=IDC_BORRA_PACIENTE,button,1342242816
Control13=IDC_IMPORTA_PACIENTE,button,1342242816
Control14=IDC_EXPORTA_PACIENTE,button,1342242816
Control15=IDC_ACTUALIZAR_PACIENTE,button,1342242816

[DLG:"IDD_REGISTRO" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=No_Paciente,edit,1350631552
Control4=Nombre_Paciente,edit,1350631552
Control5=Apellido_Paciente,edit,1350631552
Control6=Fecha_Nacimiento,edit,1350631552
Control7=Telefono,edit,1350631552
Control8=Direccion,edit,1350631552
Control9=Diagnostico,edit,1350631552
Control10=Medicacion_Actual,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,button,1342178055

[DLG:"PASSWORD" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=6
Control1=IDC_EDIT_NUEVA,edit,1350631584
Control2=IDC_EDIT_REESCRIBIR,edit,1350631584
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:"IDD_CLINICIANDISPLAY" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=0

[DLG:"IDD_TRAINING" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=9
Control1=IDC_TRAININGOFFLINE,button,1342242816
Control2=IDC_STARTTRAINING,button,1342242816
Control3=IDC_CHANGEPARAMETERS,button,1342242816
Control4=IDC_CLINICIANDISPLAY,button,1342242816
Control5=IDC_CANCELSESSION,button,1342242816
Control6=IDOK,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_SAVE_AND_EXIT,button,1342242816

[CLS:CPortConf]
Type=0
HeaderFile=PortConf.h
ImplementationFile=PortConf.cpp
BaseClass=CDialog
Filter=D
LastObject=CPortConf
VirtualFilter=dWC

[CLS:CGameDlg]
Type=0
HeaderFile=GameDlg.h
ImplementationFile=GameDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_MSFLEXGRID1

[DLG:"IDD_PASSWORD" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=3
Control1=IDC_PASSWORD,edit,1350631584
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[DLG:"PORT_CONFIGURATION" (Spanish (Mexican))]
Type=1
Class=?
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_PORT,combobox,1344339971
Control5=IDC_STATIC,static,1342308864
Control6=IDC_BYTESIZE,combobox,1344339971
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STOPBITS,combobox,1344339971
Control9=IDC_STATIC,static,1342308864
Control10=IDC_PARITY,combobox,1344339971
Control11=IDC_STATIC,static,1342308864
Control12=IDC_BAUDRATE,combobox,1344339971

[DLG:PORT_CONFIGURATION (Spanish (Mexican))]
Type=1
Class=?
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_PORT,combobox,1344339971
Control5=IDC_STATIC,static,1342308864
Control6=IDC_BYTESIZE,combobox,1344339971
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STOPBITS,combobox,1344339971
Control9=IDC_STATIC,static,1342308864
Control10=IDC_PARITY,combobox,1344339971
Control11=IDC_STATIC,static,1342308864
Control12=IDC_BAUDRATE,combobox,1344339971

