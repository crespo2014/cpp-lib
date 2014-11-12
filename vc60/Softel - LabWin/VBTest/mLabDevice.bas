Attribute VB_Name = "LabDevice"
Const AN_PATIENT_SIZE = 50
Const AN_NO_SIZE = 10
Const AN_NAME_SIZE = 10
Const AN_UNIT_SIZE = 10
Const AN_AN_ST_SIZE = 12
Const AN_VAL_ST_SIZE = 12

Public Type Analysis
    Bandera As Long
    Paciente(1 To AN_PATIENT_SIZE) As Byte
    Sexo As Byte
    Consecutivo(1 To AN_NO_SIZE) As Byte
    Analisis(1 To AN_NAME_SIZE) As Byte
    Unit(1 To AN_UNIT_SIZE) As Byte
    EstadoMuestra(1 To AN_AN_ST_SIZE) As Byte
    EstadoValor(1 To AN_VAL_ST_SIZE) As Byte
    Valor As Single
    Dia As Byte
    Mes As Byte
    Ano As Integer
    Hora As Byte
    Minuto As Byte
    Segundo As Byte
End Type

Public Declare Function Init Lib "labdevice.dll" () As Long
Public Declare Function LabDevice_Load Lib "labdevice.dll" (ByVal dllName As String, ByRef Handle As Long) As Long
Public Declare Function LabDevice_UnLoad Lib "labdevice.dll" (ByVal Handle As Long) As Long
Public Declare Function LabDevice_Initialize Lib "labdevice.dll" (ByVal Handle As Long) As Long
Public Declare Function LabDevice_GetName Lib "labdevice.dll" (ByVal Handle As Long, ByVal Name As String, ByRef length As Long) As Long
Public Declare Function LabDevice_SetPort Lib "labdevice.dll" (ByVal Handle As Long, ByVal port As Byte) As Long
Public Declare Function LabDevice_SetPortConfiguration Lib "labdevice.dll" (ByVal Handle As Long, ByVal dwBaudRate As Long, ByVal bParity As Byte, ByVal bStopBits As Byte) As Long
Public Declare Function LabDevice_GetPortConfiguration Lib "labdevice.dll" (ByVal Handle As Long, ByRef dwBaudRate As Long, ByRef bParity As Byte, ByRef bStopBits As Byte) As Long
Public Declare Function LabDevice_Connect Lib "labdevice.dll" (ByVal Handle As Long) As Long
Public Declare Function LabDevice_Disconnect Lib "labdevice.dll" (ByVal Handle As Long) As Long
Public Declare Function LabDevice_GetResults Lib "labdevice.dll" (ByVal Handle As Long, ByVal results As Long, ByRef count As Long) As Long
Public Declare Function LabDevice_ClearResults Lib "labdevice.dll" (ByVal Handle As Long) As Long
Public Declare Function LabDevice_ProcessFile Lib "labdevice.dll" (ByVal Handle As Long, ByVal FileName As String) As Long
   
Public Function GetStr(ByteStr() As Byte) As String
Dim str As String
    str = ""
    i = 1
    While ByteStr(i) <> 0
        str = str + Chr(ByteStr(i))
        i = i + 1
    Wend
    GetStr = str
End Function

Public Function CheckError(error As Long, progress As String) As Boolean
    If error <> 0 Then
        MsgBox "Codigo de Error " & error & vbCrLf & progress
        CheckError = True
    Else
        CheckError = False
    End If
End Function

