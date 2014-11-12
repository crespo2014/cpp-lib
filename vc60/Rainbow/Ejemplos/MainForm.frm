VERSION 5.00
Begin VB.Form MainForm 
   Caption         =   "SuperPro VB Sample Program"
   ClientHeight    =   4410
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5955
   LinkTopic       =   "Form1"
   ScaleHeight     =   4410
   ScaleWidth      =   5955
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton QueryButton 
      Caption         =   "Query"
      Height          =   375
      Left            =   2040
      TabIndex        =   2
      Top             =   3960
      Width           =   1695
   End
   Begin VB.TextBox StatusEdit 
      Height          =   3495
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   360
      Width           =   5655
   End
   Begin VB.Label Label1 
      Caption         =   "Results:"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   100
      Width           =   1335
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Const DevID = &H28A9

Private Sub Form_Load()

' Initialize the Query Table
InitQueryTable

' Format the declared API Packet.
result% = RNBOsproFormatPacket(MyAPIPacket, Len(MyAPIPacket))

' handle errors
If result% <> 0 Then
    MsgBox ("Unable To Format Packet!")
    Unload (MainForm)
End If

'Initialize the API packet
result% = RNBOsproInitialize(MyAPIPacket)

' handle errors
If result% <> 0 Then
    MsgBox ("Unable To Initialize Packet!")
    Unload (MainForm)
End If

AddLine ("Successfully formatted and initialized packet.")

Randomize

End Sub

Private Sub QueryButton_Click()

AddLine ("")

' Try to find the key
result% = RNBOsproFindFirstUnit(MyAPIPacket, DevID)

' Handle any errors searching for the key
If result% <> 0 Then
    AddLine ("Error " + Str$(result%) + " on FindFirstUnit!")
    Exit Sub
End If
AddLine ("Successfully Found Key!")

' Query the key to make sure it is the right key and
' and the user is licensed to use the product.
QueryKey

End Sub

Private Sub QueryKey()

Dim QueryStr As DATAQUERY
Dim ExpectedResponse As DATAQUERY
Dim ResponseStr As DATAQUERY
Dim unused As Long
Dim TableIndex As Integer
Dim CompIndex As Integer
Dim Compare As Boolean

' Randomly choose an item from the Query Table
TableIndex = Int(Rnd(1) * QueryTableLength) + 1
AddLine ("Query using Table entry " + Str$(TableIndex))

' Get the Query and expected response from the table
QueryStr = GetQueryData(TableIndex)
ExpectedResponse = GetResponseData(TableIndex)

' Query the SuperPro
result% = RNBOsproQuery(MyAPIPacket, &H8, QueryStr, ResponseStr, unused, QueryLength)

' Handle any errors from the API call.
If result% <> 0 Then
    AddLine ("Error " + Str$(result%) + " on Query!")
    Exit Sub
End If

' Compare the Expected Response and the actual Response
Compare = True
For CompIndex = 0 To QueryLength - 1
    Compare = Compare And (ResponseStr.Data(CompIndex) = ExpectedResponse.Data(CompIndex))
Next CompIndex

' Decide What to do depending on the results.
If Compare Then
    AddLine ("Good Query Response!")
Else: AddLine ("Bad Query Response!")
End If

End Sub

Public Sub AddLine(S As String)

' Purpose is to add a line of text to the end of the StatusEdit TextBox

If StatusEdit.Text = "" Then
     StatusEdit.Text = S
 Else: StatusEdit.Text = StatusEdit.Text + Chr(13) + Chr(10) + S
End If

StatusEdit.SelStart = Len(StatusEdit.Text)

End Sub
