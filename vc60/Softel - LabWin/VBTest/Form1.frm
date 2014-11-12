VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Form1"
   ClientHeight    =   7620
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   9135
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   134.409
   ScaleMode       =   0  'User
   ScaleWidth      =   161.132
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   0
      Top             =   5040
   End
   Begin VB.Frame Frame3 
      Caption         =   "Fichero a procesar"
      Height          =   735
      Left            =   0
      TabIndex        =   12
      Top             =   840
      Width           =   6135
      Begin VB.TextBox Text3 
         Height          =   285
         Left            =   840
         TabIndex        =   14
         Text            =   "C:\windows\system\04070005.ACS"
         Top             =   240
         Width           =   3855
      End
      Begin VB.CommandButton Command2 
         Caption         =   "Procesar"
         Height          =   375
         Left            =   4800
         TabIndex        =   13
         Top             =   240
         Width           =   1215
      End
      Begin VB.Label Label5 
         AutoSize        =   -1  'True
         Caption         =   "Fichero : "
         Height          =   195
         Left            =   120
         TabIndex        =   15
         Top             =   240
         Width           =   660
      End
   End
   Begin VB.Frame fDispositivo 
      Caption         =   "Equipo : "
      Height          =   735
      Left            =   0
      TabIndex        =   8
      Top             =   0
      Width           =   6135
      Begin VB.CommandButton Command5 
         Caption         =   "Descargar"
         Height          =   375
         Left            =   4800
         TabIndex        =   16
         Top             =   240
         Width           =   1215
      End
      Begin VB.CommandButton Command1 
         Caption         =   "Cargar"
         Height          =   375
         Left            =   3360
         TabIndex        =   10
         Top             =   240
         Width           =   1215
      End
      Begin VB.TextBox Text2 
         Height          =   285
         Left            =   840
         TabIndex        =   9
         Text            =   "acs180.dll"
         Top             =   240
         Width           =   2415
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "DLL :"
         Height          =   195
         Left            =   240
         TabIndex        =   11
         Top             =   255
         Width           =   390
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Parámetros de Comunicación"
      Height          =   1335
      Left            =   0
      TabIndex        =   3
      Top             =   1680
      Width           =   8175
      Begin VB.CommandButton btnConfigurar 
         Caption         =   "Configurar"
         Height          =   375
         Left            =   6720
         TabIndex        =   23
         Top             =   360
         Width           =   1215
      End
      Begin VB.ComboBox cmbStopBits 
         Height          =   315
         ItemData        =   "Form1.frx":0000
         Left            =   3600
         List            =   "Form1.frx":000D
         Style           =   2  'Dropdown List
         TabIndex        =   22
         Top             =   720
         Width           =   1695
      End
      Begin VB.ComboBox cmbParidad 
         Height          =   315
         ItemData        =   "Form1.frx":001C
         Left            =   960
         List            =   "Form1.frx":002F
         Style           =   2  'Dropdown List
         TabIndex        =   20
         Top             =   720
         Width           =   1695
      End
      Begin VB.ComboBox cmbVelocidad 
         Height          =   315
         ItemData        =   "Form1.frx":0051
         Left            =   3600
         List            =   "Form1.frx":00AF
         Style           =   2  'Dropdown List
         TabIndex        =   18
         Top             =   360
         Width           =   1695
      End
      Begin VB.ComboBox cmbPuerto 
         Height          =   315
         ItemData        =   "Form1.frx":0140
         Left            =   960
         List            =   "Form1.frx":0150
         Style           =   2  'Dropdown List
         TabIndex        =   17
         Top             =   360
         Width           =   1695
      End
      Begin VB.CommandButton Command3 
         Caption         =   "Conectar"
         Height          =   375
         Left            =   5400
         TabIndex        =   6
         Top             =   360
         Width           =   1215
      End
      Begin VB.CommandButton Command6 
         Caption         =   "Desconectar"
         Height          =   375
         Left            =   6720
         TabIndex        =   5
         Top             =   840
         Width           =   1215
      End
      Begin VB.Label Label3 
         Caption         =   "Stop bits"
         Height          =   255
         Left            =   2760
         TabIndex        =   21
         Top             =   720
         Width           =   855
      End
      Begin VB.Label Label1 
         Caption         =   "Paridad"
         Height          =   255
         Left            =   120
         TabIndex        =   19
         Top             =   720
         Width           =   735
      End
      Begin VB.Label Label7 
         Caption         =   "Velocidad"
         Height          =   255
         Left            =   2760
         TabIndex        =   7
         Top             =   360
         Width           =   855
      End
      Begin VB.Label Label6 
         Caption         =   "Puerto"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   360
         Width           =   735
      End
   End
   Begin MSFlexGridLib.MSFlexGrid MSFlexGrid1 
      Height          =   3735
      Left            =   0
      TabIndex        =   2
      Top             =   3120
      Width           =   9135
      _ExtentX        =   16113
      _ExtentY        =   6588
      _Version        =   393216
      Cols            =   9
      FixedCols       =   0
      AllowUserResizing=   1
   End
   Begin VB.CommandButton Command7 
      Caption         =   "Clear Values"
      Height          =   375
      Left            =   7800
      TabIndex        =   1
      Top             =   6960
      Width           =   1215
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Timer OFF"
      Height          =   375
      Left            =   6480
      TabIndex        =   0
      Top             =   6960
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Handle As Long

Private Sub btnConfigurar_Click()
    If CheckError(LabDevice_SetPortConfiguration(Handle, _
                            cmbVelocidad.ItemData(cmbVelocidad.ListIndex), _
                            cmbParidad.ItemData(cmbParidad.ListIndex), _
                            cmbStopBits.ItemData(cmbStopBits.ListIndex)), _
                            "Configurando el puerto de comunicacion") = True Then Exit Sub
End Sub

Private Sub Command1_Click()
Dim Name As String
Dim length As Long
    If CheckError(LabDevice_Load(Text2.Text, Handle), "Loading device Dll") = True Then Exit Sub
    Name = Space$(255)
    length = 255
    If CheckError(LabDevice_GetName(Handle, Name, length), "Getting Device Name") = True Then Exit Sub
    fDispositivo.Caption = " Equipo : " & Name
    If CheckError(LabDevice_Initialize(Handle), "Initializing device") = True Then Exit Sub
End Sub

Private Sub Command2_Click()
    If CheckError(LabDevice_ProcessFile(Handle, Text3.Text), "Procesando el fichero") = True Then Exit Sub
End Sub

Private Sub Command3_Click()
    If CheckError(LabDevice_SetPort(Handle, cmbPuerto.ItemData(cmbPuerto.ListIndex)), "Setting port") = True Then Exit Sub
    If CheckError(LabDevice_Connect(Handle), "Solicitando el puerto de comunicacion") = True Then Exit Sub
    If CheckError(LabDevice_SetPortConfiguration(Handle, _
                            cmbVelocidad.ItemData(cmbVelocidad.ListIndex), _
                            cmbParidad.ItemData(cmbParidad.ListIndex), _
                            cmbStopBits.ItemData(cmbStopBits.ListIndex)), _
                            "Configurando el puerto de comunicacion") = True Then Exit Sub
End Sub

Private Sub Command4_Click()
    Timer1.Enabled = Not Timer1.Enabled
    If Timer1.Enabled Then
        Command4.Caption = "Timer OFF"
    Else
        Command4.Caption = "Timer ON"
    End If
End Sub

Private Sub Command5_Click()
    If CheckError(LabDevice_UnLoad(Handle), "UnLoading device Dll") = True Then Exit Sub
    Handle = -1
    fDispositivo.Caption = "Equipo :"
    
End Sub

Private Sub Command6_Click()
    If CheckError(LabDevice_Disconnect(Handle), "Disconnecting from Comunication resource") = True Then Exit Sub
End Sub

Private Sub Command7_Click()
    If CheckError(LabDevice_ClearResults(Handle), "Clearing results") = True Then Exit Sub
End Sub

Private Sub Form_Load()
    cmbPuerto.ListIndex = 0
    cmbVelocidad.ListIndex = 0
    cmbParidad.ListIndex = 0
    cmbStopBits.ListIndex = 0
    Handle = -1
    MSFlexGrid1.Col = 0
    MSFlexGrid1.Row = 0
    MSFlexGrid1.Text = "Paciente"
    MSFlexGrid1.Col = MSFlexGrid1.Col + 1
    MSFlexGrid1.Text = "Consecutivo"
    MSFlexGrid1.Col = MSFlexGrid1.Col + 1
    MSFlexGrid1.Text = "Analisis"
    MSFlexGrid1.Col = MSFlexGrid1.Col + 1
    MSFlexGrid1.Text = "Criterio"
    MSFlexGrid1.Col = MSFlexGrid1.Col + 1
    MSFlexGrid1.Text = "Valor"
    MSFlexGrid1.Col = MSFlexGrid1.Col + 1
    MSFlexGrid1.Text = "Criterio"
    MSFlexGrid1.Col = MSFlexGrid1.Col + 1
  '  MSFlexGrid1.Text = "Unidad"
  '  MSFlexGrid1.Col = MSFlexGrid1.Col + 1
    MSFlexGrid1.Text = "Fecha"
    MSFlexGrid1.Col = MSFlexGrid1.Col + 1
    MSFlexGrid1.Text = "Hora"
End Sub



Private Sub Timer1_Timer()
    If Handle = -1 Then Exit Sub
    Dim result(0 To 100) As Analysis
    Dim count As Long
    Dim str As String
    count = 100
    If CheckError(LabDevice_GetResults(Handle, VarPtr(result(0)), count), "Getting results") = True Then Exit Sub
    MSFlexGrid1.Rows = 1
        '  GetStr(result(i).Unit) & vbTab &
    For i = 0 To count - 1
        str = GetStr(result(i).Paciente) & vbTab & _
        GetStr(result(i).Consecutivo) & vbTab & _
        GetStr(result(i).Analisis) & vbTab & _
        GetStr(result(i).EstadoMuestra) & vbTab & _
        result(i).Valor & " " & GetStr(result(i).Unit) & vbTab & _
        GetStr(result(i).EstadoValor) & vbTab & _
        result(i).Dia & "/" & result(i).Mes & "/" & result(i).Ano & vbTab & _
        result(i).Hora & ":" & result(i).Minuto & ":" & result(i).Segundo
        MSFlexGrid1.AddItem (str)
    Next
    
End Sub

