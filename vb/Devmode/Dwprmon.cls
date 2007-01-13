VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "dwPrintMonitor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
' Desaware API Class library
' Copyright (c) 1996 by Desaware
' All rights reserved

' Preliminary demonstration edition


Option Explicit

Public pName$           ' Print monitor name
Public pEnvironment$    ' Environment for monitor
Public pDLLName$        ' DLL name of print monitor
Public Level&

Private Type MONITOR_INFO_1
        pName As Long
End Type

Private Type MONITOR_INFO_2
        pName As Long
        pEnvironment As Long
        pDLLName As Long
End Type

Public Sub LoadInfo(Buf As Byte, pLevel&, x&)
    Level = pLevel
    Select Case Level
        Case 1
            LoadMonitorInfo1 Buf, x&
        Case 2
            LoadMonitorInfo2 Buf, x&
    End Select
End Sub

Public Sub LoadMonitorInfo1(Buf As Byte, x&)
    Dim pi As MONITOR_INFO_1
    Dim offset&
    Dim useaddr&
    offset& = x * Len(pi)
    useaddr& = agGetAddressForObject(Buf) + offset
    Call agCopyData(ByVal useaddr, pi, Len(pi))
    If (pi.pName <> 0) Then pName = agGetStringFromPointer(pi.pName)
End Sub

Public Sub LoadMonitorInfo2(Buf As Byte, x&)
    Dim pi As MONITOR_INFO_2
    Dim offset&
    Dim useaddr&
    offset& = x * Len(pi)
    useaddr& = agGetAddressForObject(Buf) + offset
    Call agCopyData(ByVal useaddr, pi, Len(pi))
    If (pi.pName <> 0) Then pName = agGetStringFromPointer(pi.pName)
    If (pi.pEnvironment <> 0) Then pEnvironment = agGetStringFromPointer(pi.pEnvironment)
    If (pi.pDLLName <> 0) Then pDLLName = agGetStringFromPointer(pi.pDLLName)
End Sub

