Attribute VB_Name = "GLOBAL"
' (C) Copyright 1986-1997 Rainbow Technologies, Inc. All rights reserved.

DefLng A-Z

Type APIPACKET
 Data(4096) As Byte
End Type

Type DATAQUERY
 Data(16) As Byte
End Type

Global MyAPIPacket As APIPACKET

Declare Function RNBOsproFormatPacket% Lib "sx32w.dll" (ApiPack As APIPACKET, ByVal ApiPackSize As Integer)
Declare Function RNBOsproInitialize% Lib "sx32w.dll" (ApiPack As APIPACKET)
Declare Function RNBOsproGetFullStatus% Lib "sx32w.dll" (ApiPack As APIPACKET)
Declare Function RNBOsproGetVersion% Lib "sx32w.dll" (ApiPack As APIPACKET, majv As Integer, minv As Integer, rev As Integer, ostype As Integer)
Declare Function RNBOsproFindFirstUnit% Lib "sx32w.dll" (ApiPack As APIPACKET, ByVal developerID As Integer)
Declare Function RNBOsproFindNextUnit% Lib "sx32w.dll" (ApiPack As APIPACKET)
Declare Function RNBOsproRead% Lib "sx32w.dll" (ApiPack As APIPACKET, ByVal address As Integer, datum As Integer)
Declare Function RNBOsproExtendedRead% Lib "sx32w.dll" (ApiPack As APIPACKET, ByVal address As Integer, datum As Integer, accessCode As Integer)
Declare Function RNBOsproWrite% Lib "sx32w.dll" (ApiPack As APIPACKET, ByVal wPass As Integer, ByVal address As Integer, ByVal datum As Integer, ByVal accessCode As Integer)
Declare Function RNBOsproOverwrite% Lib "sx32w.dll" (ApiPack As APIPACKET, ByVal wPass As Integer, ByVal oPass1 As Integer, ByVal oPass2 As Integer, ByVal address As Integer, ByVal datum As Integer, ByVal accessCode As Integer)
Declare Function RNBOsproDecrement% Lib "sx32w.dll" (ApiPack As APIPACKET, ByVal wPass As Integer, ByVal address As Integer)
Declare Function RNBOsproActivate% Lib "sx32w.dll" (ApiPack As APIPACKET, ByVal wPass As Integer, ByVal aPass1 As Integer, ByVal aPass2 As Integer, ByVal address As Integer)
Declare Function RNBOsproQuery% Lib "sx32w.dll" (ApiPack As APIPACKET, ByVal address As Integer, Query As DATAQUERY, Response As DATAQUERY, unused As Long, ByVal length As Integer)

Private Type TQueryPair
  Query As String
  Response As String
End Type

Public Const QueryTableLength = 10
Public Const QueryLength = 4

Dim QueryTable(1 To QueryTableLength) As TQueryPair

Public Sub InitQueryTable()

QueryTable(1).Query = "4F64565D"
QueryTable(1).Response = "3259CE00"
QueryTable(2).Query = "64ECB2B4"
QueryTable(2).Response = "65D3225D"
QueryTable(3).Query = "5C49A4F2"
QueryTable(3).Response = "1A9F792C"
QueryTable(4).Query = "9E040131"
QueryTable(4).Response = "54B2DACA"
QueryTable(5).Query = "182EF72C"
QueryTable(5).Response = "186AA526"
QueryTable(6).Query = "CF4E07F0"
QueryTable(6).Response = "108B1C07"
QueryTable(7).Query = "EEF54CB7"
QueryTable(7).Response = "B461502E"
QueryTable(8).Query = "1453035E"
QueryTable(8).Response = "BA93B629"
QueryTable(9).Query = "FA4E4A19"
QueryTable(9).Response = "E2818E59"
QueryTable(10).Query = "55D62866"
QueryTable(10).Response = "1785655B"


End Sub

Public Function GetQueryData(Index As Integer) As DATAQUERY

Dim I As Integer
Dim Answer As DATAQUERY

For I = 0 To (Len(QueryTable(Index).Query) / 2 - 1)
    Answer.Data(I) = Val("&H" + Mid$(QueryTable(Index).Query, I * 2 + 1, 2))
Next I

GetQueryData = Answer

End Function

Public Function GetResponseData(Index As Integer) As DATAQUERY

Dim I As Integer
Dim Answer As DATAQUERY

For I = 0 To (Len(QueryTable(Index).Response) / 2 - 1)
    Answer.Data(I) = Val("&H" + Mid$(QueryTable(Index).Response, I * 2 + 1, 2))
Next I

GetResponseData = Answer

End Function


