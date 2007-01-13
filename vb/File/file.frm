VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "APIFile"
   ClientHeight    =   5010
   ClientLeft      =   3090
   ClientTop       =   1590
   ClientWidth     =   3945
   ForeColor       =   &H00000000&
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5010
   ScaleWidth      =   3945
   Begin VB.CommandButton cmdCommProperties 
      Caption         =   "Comm Properties"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2040
      TabIndex        =   24
      Top             =   4080
      Width           =   1815
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   4560
      Width           =   3735
   End
   Begin VB.CommandButton cmdOpenFile 
      Caption         =   "Open File"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   4080
      Width           =   1815
   End
   Begin VB.Label lblwPacketLength 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   35
      Top             =   120
      Width           =   1575
   End
   Begin VB.Label lblwPacketVersion 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   34
      Top             =   480
      Width           =   1575
   End
   Begin VB.Label lbldwServiceMask 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   33
      Top             =   840
      Width           =   1575
   End
   Begin VB.Label lbldwReserved1 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   32
      Top             =   1200
      Width           =   1575
   End
   Begin VB.Label lbldwMaxTxQue 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   31
      Top             =   1560
      Width           =   1575
   End
   Begin VB.Label lbldwMaxRxQue 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   30
      Top             =   1920
      Width           =   1575
   End
   Begin VB.Label lbldwMaxBaud 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   29
      Top             =   2280
      Width           =   1575
   End
   Begin VB.Label lbldwProvSubType 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   28
      Top             =   2640
      Width           =   1575
   End
   Begin VB.Label lbldwProvCapabilities 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   27
      Top             =   3000
      Width           =   1575
   End
   Begin VB.Label lbldwSettableParams 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   26
      Top             =   3360
      Width           =   1575
   End
   Begin VB.Label lbldwSettableBaud 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   5040
      TabIndex        =   25
      Top             =   3720
      Width           =   1575
   End
   Begin VB.Label lblEVTChar 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   23
      Top             =   3720
      Width           =   1575
   End
   Begin VB.Label lblEVTCharCaption 
      Caption         =   "EVT Char:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   22
      Top             =   3720
      Width           =   1095
   End
   Begin VB.Label lblEOFChar 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   21
      Top             =   3360
      Width           =   1575
   End
   Begin VB.Label lblEOFCharCaption 
      Caption         =   "EOF Char:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   20
      Top             =   3360
      Width           =   1095
   End
   Begin VB.Label lblErrorChar 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   19
      Top             =   3000
      Width           =   1575
   End
   Begin VB.Label lblErrorCharCaption 
      Caption         =   "Error Char:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   18
      Top             =   3000
      Width           =   1095
   End
   Begin VB.Label lblStopBitsCaption 
      Caption         =   "Stop Bits:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   17
      Top             =   2640
      Width           =   1095
   End
   Begin VB.Label lblParityCaption 
      Caption         =   "Parity:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   16
      Top             =   2280
      Width           =   1095
   End
   Begin VB.Label lblByteSizeCaption 
      Caption         =   "Byte Size:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   15
      Top             =   1920
      Width           =   1095
   End
   Begin VB.Label lblStopBits 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   14
      Top             =   2640
      Width           =   1575
   End
   Begin VB.Label lblParity 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   13
      Top             =   2280
      Width           =   1575
   End
   Begin VB.Label lblByteSize 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   12
      Top             =   1920
      Width           =   1575
   End
   Begin VB.Label lblXOFFLim 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   11
      Top             =   1560
      Width           =   1575
   End
   Begin VB.Label lblXOFFLimitCaption 
      Caption         =   "XOFF Limit:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   10
      Top             =   1560
      Width           =   1095
   End
   Begin VB.Label lblXOnLim 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   9
      Top             =   1200
      Width           =   1575
   End
   Begin VB.Label lblXONLimCaption 
      Caption         =   "XON Limit:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   8
      Top             =   1200
      Width           =   1095
   End
   Begin VB.Label lblBits1 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   7
      Top             =   840
      Width           =   1575
   End
   Begin VB.Label lblBits1Caption 
      Caption         =   "Bits1:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   6
      Top             =   840
      Width           =   975
   End
   Begin VB.Label lblBaudRate 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   5
      Top             =   480
      Width           =   1575
   End
   Begin VB.Label lblBaudRateCaption 
      Caption         =   "Baud Rate:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   4
      Top             =   480
      Width           =   855
   End
   Begin VB.Label lblDCBLengthCaption 
      Caption         =   "DCB Length:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   600
      TabIndex        =   3
      Top             =   120
      Width           =   975
   End
   Begin VB.Label lblDCBLength 
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   2
      Top             =   120
      Width           =   1575
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim hFile&

Private Sub cmdCommProperties_Click()
    Dim rtn&
    If Me.Width = 6810 Then Me.Width = 4065: Exit Sub
    
    rtn& = GetCommProperties(hFile&, MyCommProp)
    If (rtn&) Then
        Me.Width = 6810
        DisplayCommProperties
    End If
End Sub


Private Sub cmdExit_Click()
    Unload Me
    End
End Sub


Private Sub cmdOpenFile_Click()
    Dim rtn&
    
    With MySecurity
        .nLength = LenB(MySecurity)
        .lpSecurityDescriptor = 0
        .bInheritHandle = True
    End With
    If Not (hFile& > 0) Then
        hFile& = CreateFile("\\.\COM1", _
                        GENERIC_READ, _
                        0, _
                        MySecurity, _
                        OPEN_EXISTING, _
                        FILE_ATTRIBUTE_NORMAL, _
                        0)
        If (hFile& > 0) Then
            rtn& = GetCommState(hFile&, MyDCB)
            If (rtn&) Then
                DisplayData
                cmdCommProperties.Enabled = True
            End If
        End If
    End If
    
    
End Sub


Private Sub Form_Unload(Cancel As Integer)
    CloseHandle hFile&
End Sub



Private Sub DisplayData()
    With MyDCB
        lblDCBLength.Caption = .DCBlength
        lblBaudRate.Caption = .BaudRate
        lblBits1.Caption = .Bits1
        lblXOnLim.Caption = .XonLim
        lblxofflim.Caption = .XoffLim
        lblByteSize.Caption = .ByteSize
        lblParity.Caption = .Parity
        lblStopBits.Caption = .StopBits
        lblErrorChar.Caption = .ErrorChar
        lblEOFChar.Caption = .EofChar
        lblEVTChar.Caption = .EvtChar
    End With
End Sub


Private Sub DisplayCommProperties()
    With MyCommProp
        lblwPacketLength = .wPacketLength
        lblwPacketVersion = .wPacketVersion
        lbldwServiceMask = .dwServiceMask
        lbldwReserved1 = .dwReserved1
        lbldwMaxTxQue = .dwMaxTxQueue
        lbldwMaxRxQue = .dwMaxRxQueue
        lbldwMaxBaud = .dwMaxBaud
        lbldwProvSubType = .dwProvSubType
        lbldwProvCapabilities = .dwProvCapabilities
        lbldwSettableParams = .dwSettableParams
        lbldwSettableBaud = .dwSettableBaud
        'lblwSettableData = .wSettableData
        'lblwSettableStopParity = .wSettableStopParity
        'lbldwCurrentTxQueue = .dwCurrentTxQueue
        'lbldwCurrentRxQueue = .dwCurrentRxQueue
        'lbldwProvSpec1 = .dwProvSpec1
        'dwProvSpec2 = .dwProvSpec2
        'lblwcProvChar(1) = .wcProvChar(1)
    End With
End Sub

