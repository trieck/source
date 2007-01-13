VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "dwPortInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
' Desaware API Class library
' Copyright (c) 1996 by Desaware
' All rights reserved

' Preliminary demonstration edition

Option Explicit

Private Type PORT_INFO_1
        pName As Long
End Type

Private Type PORT_INFO_2
        pPortName As Long
        pMonitorName As Long
        pDescription As Long
        fPortType As Long
        Reserved As Long
End Type

Public pName$
Public pMonitorName$
Public fPortType&
Public Level&



Public Sub LoadInfo(Buf As Byte, pLevel&, x&)
    Level = pLevel
    Select Case Level
        Case 1
            LoadPortInfo1 Buf, x&
        Case 2
            LoadPortInfo2 Buf, x&
    End Select
End Sub

Public Sub LoadPortInfo1(Buf As Byte, x&)
    Dim pi As PORT_INFO_1
    Dim offset&
    Dim useaddr&
    offset& = x * Len(pi)
    useaddr& = agGetAddressForObject(Buf) + offset
    Call agCopyData(ByVal useaddr, pi, Len(pi))
    If (pi.pName <> 0) Then pName = agGetStringFromPointer(pi.pName)
End Sub
Public Sub LoadPortInfo2(Buf As Byte, x&)
    Dim pi As PORT_INFO_2
    Dim offset&
    Dim useaddr&
    offset& = x * Len(pi)
    useaddr& = agGetAddressForObject(Buf) + offset
    Call agCopyData(ByVal useaddr, pi, Len(pi))
    pName = agGetStringFromPointer(pi.pPortName)
    pMonitorName = agGetStringFromPointer(pi.pMonitorName)
    fPortType = pi.fPortType
End Sub

' pPortName is an alias for pName
Public Property Get pPortName() As String
    pPortName = pName
End Property

Public Property Let pPortName(ByVal vNewValue$)
    pName = vNewValue
End Property
