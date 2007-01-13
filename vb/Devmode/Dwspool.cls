VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "dwSpool"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
' Desaware API Class library
' Copyright (c) 1995 by Desaware
' All rights reserved

' Preliminary demonstration edition

Option Explicit

Private Declare Function apiEnumPrinters Lib "winspool.drv" Alias "EnumPrintersA" (ByVal Flags As Long, ByVal Name As String, ByVal Level As Long, pPrinterEnum As Byte, ByVal cdBuf As Long, pcbNeeded As Long, pcReturned As Long) As Long
Private Declare Function apiEnumPorts Lib "winspool.drv" Alias "EnumPortsA" (ByVal pName As String, ByVal Level As Long, lpbPorts As Byte, ByVal cbBuf As Long, pcbNeeded As Long, pcReturned As Long) As Long
Private Declare Function apiEnumMonitors Lib "winspool.drv" Alias "EnumMonitorsA" (ByVal pName As String, ByVal Level As Long, pMonitors As Byte, ByVal cbBuf As Long, pcbNeeded As Long, pcReturned As Long) As Long

Private Declare Function GetLastError Lib "kernel32" () As Long




' Retrieves a collection of printer objects
Public Function EnumPrinters(Flags As Long, Name As String, Level As Long) As Collection
    Dim needed&
    Dim returned&
    Dim res&
    Dim tbt As Byte
    Dim usename$
    Dim cprinters As New Collection
    Dim x&
    Dim ppi As dwPrinterInfo
    If Name$ = "" Then usename$ = vbNullString Else usename$ = Name
    res& = apiEnumPrinters(Flags, usename$, Level, tbt, 0, needed, returned)
    If needed& = 0 Then
        Set EnumPrinters = cprinters
        Exit Function
    End If
    ReDim ResultBuffer(needed) As Byte
    res& = apiEnumPrinters(Flags, usename$, Level, ResultBuffer(0), needed, needed, returned)
    
    ' Now enumerate create an object for each printer structure
    For x = 1 To returned
        Set ppi = New dwPrinterInfo
        Call ppi.LoadInfo(ResultBuffer(0), Level, x - 1)
        cprinters.Add ppi
    Next x
    Set EnumPrinters = cprinters
End Function

' Retrieves a collection of printer objects
Public Function EnumPorts(Server As String, Level As Long) As Collection
    Dim needed&
    Dim returned&
    Dim res&
    Dim tbt As Byte
    Dim useserver$
    Dim cports As New Collection
    Dim x&
    Dim ppi As dwPortInfo
    If Server$ = "" Then useserver$ = vbNullString Else useserver$ = Server
    res& = apiEnumPorts(useserver, Level, tbt, 0, needed, returned)
    If needed& = 0 Then
        Set EnumPorts = cports
        Exit Function
    End If
    ReDim ResultBuffer(needed) As Byte
    res& = apiEnumPorts(useserver, Level, ResultBuffer(0), needed, needed, returned)
    Debug.Print GetLastError()
    ' Now enumerate create an object for each printer structure
    For x = 1 To returned
        Set ppi = New dwPortInfo
        Call ppi.LoadInfo(ResultBuffer(0), Level, x - 1)
        cports.Add ppi
    Next x
    Set EnumPorts = cports
End Function

' Retrieves a collection of monitor objects
Public Function EnumMonitors(Server As String, Level As Long) As Collection
    Dim needed&
    Dim returned&
    Dim res&
    Dim tbt As Byte
    Dim useserver$
    Dim cmonitors As New Collection
    Dim x&
    Dim ppi As dwPrintMonitor
    If Server$ = "" Then useserver$ = vbNullString Else useserver$ = Server
    res& = apiEnumPorts(useserver, Level, tbt, 0, needed, returned)
    If needed& = 0 Then
        Set EnumMonitors = cmonitors
        Exit Function
    End If
    ReDim ResultBuffer(needed) As Byte
    res& = apiEnumMonitors(useserver, Level, ResultBuffer(0), needed, needed, returned)
    Debug.Print GetLastError()
    ' Now enumerate create an object for each printer structure
    For x = 1 To returned
        Set ppi = New dwPrintMonitor
        Call ppi.LoadInfo(ResultBuffer(0), Level, x - 1)
        cmonitors.Add ppi
    Next x
    Set EnumMonitors = cmonitors
End Function

