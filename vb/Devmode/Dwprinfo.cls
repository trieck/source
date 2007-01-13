VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "dwPrinterInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
' Desaware API Class library
' Copyright (c) 1996 by Desaware
' All rights reserved

' Preliminary demonstration edition

Option Explicit
Private Type PRINTER_INFO_1
        Flags As Long
        pDescription As Long
        pName As Long
        pComment As Long
End Type

Private Type PRINTER_INFO_2
        pServerName As Long
        pPrinterName As Long
        pShareName As Long
        pPortName As Long
        pDriverName As Long
        pComment As Long
        pLocation As Long
        pDevMode As Long    ' Pointer to DEVMODE
        pSepFile As String
        pPrintProcessor As Long
        pDatatype As Long
        pParameters As Long
        pSecurityDescriptor As Long ' Pointer to SECURITY_DESCRIPTOR
        Attributes As Long
        Priority As Long
        DefaultPriority As Long
        StartTime As Long
        UntilTime As Long
        Status As Long
        cJobs As Long
        AveragePPM As Long
End Type

Private Type PRINTER_INFO_3
        pSecurityDescriptor As Long ' Pointer to SECURITY_DESCRIPTOR
End Type

Private Type PRINTER_INFO_4
    pPrinterName As Long
    pServerName As Long
    Attributes As Long
End Type

Private Type PRINTER_INFO_5
        pPrinterName As Long
        pPortName As Long
        Attributes As Long
        DeviceNotSelectedTimeout As Long
        TransmissionRetryTimeout As Long
End Type

Public Flags&
Public pDescription$
Public pName$
Public pComment$
Public pServerName$
Public pPrinterName$
Public pShareName$
Public pPortName$
Public pDriverName$
Public pLocation$
Private pDevMode As DEVMODE
Public pSepFile$
Public pPrintProcessor$
Public pDatatype$
Public pParameters$
Public Attributes&
Public Priority&
Public DefaultPriority&
Public StartTime&
Public UntilTime&
Public Status&
Public cJobs&
Public AveragePPM&
Public DeviceNotSelectedTimeout&
Public TransmissionRetryTimeout&
Private pSecurityDescriptor As SECURITY_DESCRIPTOR
Public Level&   ' Level for which this object was created

Public Sub ResetContents()
    Flags = 0
    pDescription$ = ""
    pName$ = ""
    pComment$ = ""
    pServerName$ = ""
    pPrinterName$ = ""
    pShareName$ = ""
    pPortName$ = ""
    pDriverName$ = ""
    pLocation$ = ""
    pSepFile$ = ""
    pPrintProcessor$ = ""
    pDatatype$ = ""
    pParameters$ = ""
    Attributes& = 0
    Priority& = 0
    DefaultPriority& = 0
    StartTime& = 0
    UntilTime& = 0
    Status& = 0
    cJobs& = 0
    AveragePPM& = 0
    DeviceNotSelectedTimeout& = 0
    TransmissionRetryTimeout& = 0
End Sub

' Load information from a byte structure
Public Sub LoadInfo(Buf As Byte, pLevel&, x&)
    Level = pLevel
    Select Case Level
        Case 1
            LoadPrinterInfo1 Buf, x&
        Case 2
            LoadPrinterInfo2 Buf, x&
        Case 4
            LoadPrinterInfo4 Buf, x&
        Case 5
            LoadPrinterInfo5 Buf, x&
    End Select
End Sub
' Load from PRINTER_INFO_1
Public Sub LoadPrinterInfo1(Buf As Byte, x&)
    Dim pi As PRINTER_INFO_1
    Dim offset&
    Dim useaddr&
    offset& = x * Len(pi)
    useaddr& = agGetAddressForObject(Buf) + offset
    Call agCopyData(ByVal useaddr, pi, Len(pi))
    Flags = pi.Flags
    pDescription = agGetStringFromPointer(pi.pDescription)
    pName = agGetStringFromPointer(pi.pName)
    pComment = agGetStringFromPointer(pi.pComment)
End Sub

' Load from PRINTER_INFO_2
Public Sub LoadPrinterInfo2(Buf As Byte, x&)
    Dim pi As PRINTER_INFO_2
    Dim offset&
    Dim useaddr&
    offset& = x * Len(pi)
    useaddr& = agGetAddressForObject(Buf) + offset
    Call agCopyData(ByVal useaddr, pi, Len(pi))
    
    pServerName = agGetStringFromPointer(pi.pServerName)
    pPrinterName = agGetStringFromPointer(pi.pPrinterName)
    pShareName = agGetStringFromPointer(pi.pShareName)
    pPortName = agGetStringFromPointer(pi.pPortName)
    pDriverName = agGetStringFromPointer(pi.pDriverName)
    pComment = agGetStringFromPointer(pi.pComment)
    pLocation = agGetStringFromPointer(pi.pLocation)
    agCopyData ByVal pi.pDevMode, pDevMode, Len(pDevMode)
    agCopyData ByVal pi.pSecurityDescriptor, pSecurityDescriptor, Len(pSecurityDescriptor)
    pSepFile = agGetStringFromPointer(pi.pSepFile)
    pPrintProcessor = agGetStringFromPointer(pi.pPrintProcessor)
    pDatatype = agGetStringFromPointer(pi.pDatatype)
    pParameters = agGetStringFromPointer(pi.pParameters)
    Attributes = pi.Attributes
    Priority = pi.Priority
    DefaultPriority = pi.DefaultPriority
    StartTime = pi.StartTime
    UntilTime = pi.UntilTime
    Status = pi.Status
    cJobs = pi.cJobs
    AveragePPM = pi.AveragePPM
End Sub
' Load from PRINTER_INFO_4
Public Sub LoadPrinterInfo4(Buf As Byte, x&)
    Dim pi As PRINTER_INFO_4
    Dim offset&
    Dim useaddr&
    offset& = x * Len(pi)
    useaddr& = agGetAddressForObject(Buf) + offset
    Call agCopyData(ByVal useaddr, pi, Len(pi))
    Attributes = pi.Attributes
End Sub

Public Sub LoadPrinterInfo5(Buf As Byte, x&)
    Dim pi As PRINTER_INFO_5
    Dim offset&
    Dim useaddr&
    offset& = x * Len(pi)
    useaddr& = agGetAddressForObject(Buf) + offset
    Call agCopyData(ByVal useaddr, pi, Len(pi))
    pPrinterName = agGetStringFromPointer(pi.pPrinterName)
    pPortName = agGetStringFromPointer(pi.pPortName)
    Attributes = pi.Attributes
    DeviceNotSelectedTimeout = pi.DeviceNotSelectedTimeout
    TransmissionRetryTimeout = pi.TransmissionRetryTimeout
End Sub

