Attribute VB_Name = "basSysWAPI"
Option Explicit

Declare Function OpenPrinter Lib "winspool.drv" Alias "OpenPrinterA" (ByVal pPrinterName As String, phPrinter As Long, pDefault As PRINTER_DEFAULTS) As Long
Declare Function ClosePrinter Lib "winspool.drv" (ByVal hPrinter As Long) As Long
Declare Function DocumentProperties Lib "winspool.drv" Alias "DocumentPropertiesA" (ByVal hWnd As Long, ByVal hPrinter As Long, ByVal pDeviceName As String, ByVal pDevModeOutput As Long, ByVal pDevModeInput As Long, ByVal fMode As Long) As Long
Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long
Declare Function agGetAddressForObject Lib "apigid32.dll" (object As Any) As Long
Declare Function agGetStringFromLPSTR Lib "apigid32.dll" (ByVal lpstr As String) As String
Declare Function agGetStringFromPointer$ Lib "apigid32.dll" Alias "agGetStringFromLPSTR" (ByVal ptr&)
Declare Sub agCopyData Lib "apigid32.dll" (Source As Any, dest As Any, ByVal nCount&)

Public Const PRINTER_ACCESS_USE = &H8
Public Const CCHDEVICENAME = 32
Public Const CCHFORMNAME = 32
Public Const DM_MODIFY = 8
Public Const DM_PROMPT = 4
Public Const DM_IN_PROMPT = DM_PROMPT
Public Const DM_IN_BUFFER = DM_MODIFY
Public Const DM_COPY = 2
Public Const DM_OUT_BUFFER = DM_COPY

Public Const GMEM_DISCARDABLE = &H100
Public Const GMEM_FIXED = &H0
Public Const GMEM_ZEROINIT = &H40

Public Const PRINTER_ENUM_LOCAL = &H2

Type ACL
        AclRevision As Byte
        Sbz1 As Byte
        AclSize As Integer
        AceCount As Integer
        Sbz2 As Integer
End Type

Type SECURITY_DESCRIPTOR
        Revision As Byte
        Sbz1 As Byte
        Control As Long
        Owner As Long
        Group As Long
        Sacl As ACL
        Dacl As ACL
End Type

Type DEVMODE
        dmDeviceName As String * CCHDEVICENAME
        dmSpecVersion As Integer
        dmDriverVersion As Integer
        dmSize As Integer
        dmDriverExtra As Integer
        dmFields As Long
        dmOrientation As Integer
        dmPaperSize As Integer
        dmPaperLength As Integer
        dmPaperWidth As Integer
        dmScale As Integer
        dmCopies As Integer
        dmDefaultSource As Integer
        dmPrintQuality As Integer
        dmColor As Integer
        dmDuplex As Integer
        dmYResolution As Integer
        dmTTOption As Integer
        dmCollate As Integer
        dmFormName As String * CCHFORMNAME
        dmUnusedPadding As Integer
        dmBitsPerPel As Integer
        dmPelsWidth As Long
        dmPelsHeight As Long
        dmDisplayFlags As Long
        dmDisplayFrequency As Long
End Type

Type PRINTER_DEFAULTS
        pDatatype As String
        pDevMode As Long
        DesiredAccess As Long
End Type

