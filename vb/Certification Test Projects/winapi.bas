Attribute VB_Name = "Module1"
Declare Sub MessageBeep Lib "User" (ByVal WType As Integer)
Public Const MB_OK = &H0
Public Const MB_ICONEXCLAMATION = &H30
Public Const MB_ICONASTERISK = &H40
Public Const MB_ICONHAND = &H10
Public Const MB_ICONQUESTION = &H20
Declare Function MessageBox Lib "User" (ByVal HWnd As Integer, ByVal lptext As String, ByVal lpcaption As String, ByVal WType As Integer) As Integer
Declare Function OpenComm Lib "User" (ByVal lpComName As String, ByVal wInQueue As Integer, ByVal wOutQueue As Integer) As Integer
Declare Function CloseComm Lib "User" (ByVal nCID As Integer) As Integer
Declare Function BuildCommDCB Lib "User" (ByVal lpDef As String, lpDCB As dcb) As Integer

Type dcb
    Id As String * 1
    BaudRate As Integer
    ByteSize As String * 1
    Parity As String * 1
    StopBits As String * 1
    RlsTimeout As Integer
    CtsTimeout As Integer
    DsrTimeout As Integer
    Bits1 As String * 1 ' The fifteen actual DCB bit-sized data fields
    Bits2 As String * 1 ' within these two bytes can be manipulated by
                        ' bitwise logical And/Or operations.  Refer to
                        ' SDKWIN.HLP for location/meaning of specific bits
    XonChar As String * 1
    XoffChar As String * 1
    XonLim As Integer
    XoffLim As Integer
    PeChar As String * 1
    EofChar As String * 1
    EvtChar As String * 1
    TxDelay As Integer
End Type

