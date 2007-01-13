Attribute VB_Name = "basPrinters"
Option Explicit
Declare Function GetProfileString Lib "kernel32" Alias "GetProfileStringA" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long) As Long
Declare Function GetPrinter Lib "winspool.drv" Alias "GetPrinterA" (ByVal hPrinter As Long, ByVal Level As Long, pPrinter As Byte, ByVal cbBuf As Long, pcbNeeded As Long) As Long
Declare Function OpenPrinter Lib "winspool.drv" Alias "OpenPrinterA" (ByVal pPrinterName As String, phPrinter As Long, pDefault As PRINTER_DEFAULTS) As Long
Declare Function DocumentProperties Lib "winspool.drv" Alias "DocumentPropertiesA" (ByVal hwnd As Long, ByVal hPrinter As Long, ByVal pDeviceName As String, ByVal pDevModeOutput As Long, ByVal pDevModeInput As Long, ByVal fMode As Long) As Long
Declare Sub agCopyData Lib "apigid32.dll" (source As Any, dest As Any, ByVal nCount&)
Declare Function agGetStringFromPointer$ Lib "apigid32.dll" Alias "agGetStringFromLPSTR" (ByVal ptr&)
Declare Function agGetStringFromLPSTR$ Lib "apigid32.dll" (ByVal src$)
Declare Function agGetAddressForObject& Lib "apigid32.dll" (object As Any)

Declare Function EnumDesktopWindows Lib "user32" (ByVal hDesktop As Long, ByVal lpfn As Long, ByVal lParam As Long) As Long

Type PRINTER_DEFAULTS
        pDatatype As String
        pDevMode As Long
        DesiredAccess As Long
End Type

Type PRINTER_INFO_5
        pPrinterName As Long
        pPortName As Long
        Attributes As Long
        DeviceNotSelectedTimeout As Long
        TransmissionRetryTimeout As Long
End Type

Public Const CCHDEVICENAME = 32
Public Const CCHFORMNAME = 32
Public Const DM_PROMPT = 4
Public Const DM_COPY = 2
Public Const DM_IN_PROMPT = DM_PROMPT
Public Const DM_OUT_BUFFER = DM_COPY
Public Const DMORIENT_PORTRAIT = 1
Public Const DM_YRESOLUTION = &H2000&



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
        dmICMMethod As Long
        dmICMIntent As Long
        dmMediaType As Long
        dmDitherType As Long
        dmReserved1 As Long
        dmReserved2 As Long
End Type

