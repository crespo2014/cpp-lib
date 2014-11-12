; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=2
ResourceCount=2
NewFileInclude1=#include "stdafx.h"
Class1=CInputDlg
LastClass=CSQLDlg
LastTemplate=CDialog
Resource1=IDD_SQL_DLG
Class2=CSQLDlg
Resource2=IDR_MAINFRAME (Spanish (Modern))

[CLS:CInputDlg]
Type=0
HeaderFile=db11d1.h
ImplementationFile=db11d1.cpp
BaseClass=CDialog
Filter=D
LastObject=CInputDlg
VirtualFilter=dWC

[DB:CCartasRecordset]
DB=1
DBType=DAO
ColumnCount=15
Column1=[NUMERO], 4, 4
Column2=[ORGANISMO], 4, 4
Column3=[NOMBRE], 12, 50
Column4=[APELLIDO1], 12, 50
Column5=[APELLIDO2], 12, 50
Column6=[ENTRADA], 12, 11
Column7=[MUNICIPIO], 4, 4
Column8=[TEMA], 4, 4
Column9=[TIPO], -6, 1
Column10=[SINTESIS], -1, 0
Column11=[SINDICATO], 4, 4
Column12=[ENVIAR1], 4, 4
Column13=[ENVIAR2], 4, 4
Column14=[RESPUESTA], 12, 11
Column15=[CLASIFICACION], -6, 1

[DLG:IDD_SQL_DLG]
Type=1
Class=CSQLDlg
ControlCount=36
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BNUMERO,button,1342245891
Control4=IDC_BNOMBRE,button,1342242819
Control5=IDC_B1APELLIDO,button,1342242819
Control6=IDC_B2APELLIDO,button,1342242819
Control7=IDC_BORGANISMO,button,1342242819
Control8=IDC_BMUNICIPIO,button,1342242819
Control9=IDC_BTEMA,button,1342242819
Control10=IDC_BCLASIFICACION,button,1342242819
Control11=IDC_BDESDE,button,1342242819
Control12=IDC_BHASTA,button,1342242819
Control13=IDC_BSINDICATO,button,1342242819
Control14=IDC_BORDENAR,button,1342242819
Control15=IDC_NUMERO,edit,1350631552
Control16=IDC_NOMBRE,edit,1350631552
Control17=IDC_1APELLIDO,edit,1350631552
Control18=IDC_2APELLIDO,edit,1350631552
Control19=IDC_ORGANISMO,combobox,1344340226
Control20=IDC_MUNICIPIO,combobox,1344340226
Control21=IDC_TEMA,combobox,1344340226
Control22=IDC_SINDICATO,combobox,1344340226
Control23=IDC_DESDE,SysDateTimePick32,1342242848
Control24=IDC_HASTA,SysDateTimePick32,1342242848
Control25=IDC_TPROVINCIA,combobox,1344340226
Control26=IDC_TDEPARTAMENTO,combobox,1344340226
Control27=IDC_TSINDICATO,combobox,1344340226
Control28=IDC_CLASIFICACION,combobox,1344340226
Control29=IDC_ORDENAR,combobox,1344340226
Control30=IDC_BTPROVINCIA,button,1342242819
Control31=IDC_BTDEPARTAMENTO,button,1342242819
Control32=IDC_BTSINDICATO,button,1342242819
Control33=IDC_CHECK1,button,1342242819
Control34=IDC_CHECK2,button,1342242819
Control35=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control36=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242848

[CLS:CSQLDlg]
Type=0
HeaderFile=db11d2.h
ImplementationFile=db11d2.cpp
BaseClass=CDialog
Filter=D
LastObject=CSQLDlg
VirtualFilter=dWC

[TB:IDR_MAINFRAME (Spanish (Modern))]
Type=1
Class=?
Command1=ID_ABRIR_BASEDATO
Command2=ID_PRIMERA
Command3=ID_ANTERIOR
Command4=ID_SIGUIENTE
Command5=ID_ULTIMA
Command6=ID_NUEVA_CARTA
Command7=ID_SALVAR_CARTA
Command8=ID_BORRAR_CARTA
Command9=ID_BUSCAR_CARTA
CommandCount=9

