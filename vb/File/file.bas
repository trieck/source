Attribute VB_Name = "Module1"
Option Explicit
Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, lpSecurityAttributes As SECURITY_ATTRIBUTES, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Declare Sub CloseHandle Lib "kernel32" (ByVal hObject As Long)
Declare Function GetCommState Lib "kernel32" (ByVal nCid As Long, lpDCB As DCB) As Long
Declare Function GetCommProperties Lib "kernel32" (ByVal hFile As Long, lpCommProp As COMMPROP) As Long

Type SECURITY_ATTRIBUTES
        nLength As Long
        lpSecurityDescriptor As Long
        bInheritHandle As Long
End Type
Public MySecurity As SECURITY_ATTRIBUTES

Type DCB
        DCBlength As Long
        BaudRate As Long
        Bits1 As Long
        wReserved As Integer
        XonLim As Integer
        XoffLim As Integer
        ByteSize As Byte
        Parity As Byte
        StopBits As Byte
        XonChar As Byte
        XoffChar As Byte
        ErrorChar As Byte
        EofChar As Byte
        EvtChar As Byte
        wReserved2 As Integer
End Type

Public MyDCB As DCB

Type COMMPROP
        wPacketLength As Integer
        wPacketVersion As Integer
        dwServiceMask As Long
        dwReserved1 As Long
        dwMaxTxQueue As Long
        dwMaxRxQueue As Long
        dwMaxBaud As Long
        dwProvSubType As Long
        dwProvCapabilities As Long
        dwSettableParams As Long
        dwSettableBaud As Long
        wSettableData As Integer
        wSettableStopParity As Integer
        dwCurrentTxQueue As Long
        dwCurrentRxQueue As Long
        dwProvSpec1 As Long
        dwProvSpec2 As Long
        wcProvChar(1) As Integer
End Type

Public MyCommProp As COMMPROP


Public Const GENERIC_READ = &H80000000
Public Const OPEN_EXISTING = 3
Public Const FILE_ATTRIBUTE_NORMAL = &H80

