VERSION 5.00
Begin VB.Form frmNBO 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Network Byte Order Converter"
   ClientHeight    =   1545
   ClientLeft      =   2400
   ClientTop       =   2700
   ClientWidth     =   4245
   Icon            =   "frmNBO.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   1545
   ScaleWidth      =   4245
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   2880
      TabIndex        =   3
      Top             =   1080
      Width           =   1215
   End
   Begin VB.CommandButton cmdConvert 
      Caption         =   "&Convert"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   1080
      Width           =   1215
   End
   Begin VB.TextBox txtPortNumber 
      Height          =   285
      Left            =   2880
      TabIndex        =   1
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label lblConvertedPortCaption 
      Caption         =   "Converted  Number:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   480
      Width           =   1575
   End
   Begin VB.Label lblConvertedPort 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   2880
      TabIndex        =   4
      Top             =   480
      Width           =   1215
   End
   Begin VB.Label lblPortNumber 
      Caption         =   "Enter Port Number:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1575
   End
End
Attribute VB_Name = "frmNBO"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' starts winsock services
Private Declare Function WSAStartup Lib "wsock32.dll" (ByVal wVersion As Integer, wd As WSADAta) As Integer

' converts to network byte order
Private Declare Function htons Lib "wsock32.dll" (ByVal hostshort As Integer) As Integer

' converts from network byte order
Private Declare Function ntohs Lib "wsock32.dll" (ByVal netshort As Integer) As Integer

Private Declare Function WSACleanup Lib "wsock32.dll" () As Long

Private Const WSADESCRIPTION_LEN = 256 + 1
Private Const WSASYS_STATUS_LEN = 128 + 1

Private Const SOCKET_ERROR = -1

Private Type WSADAta
    wVersion As Integer
    wHighVersion As Integer
    szDescription As String * WSADESCRIPTION_LEN
    szSystemStatus As String * WSASYS_STATUS_LEN
    iMaxSockets As Integer
    lpVendorInfo As Long
End Type
Private Sub cmdConvert_Click()
    If (Not IsNumeric(txtPortNumber)) Then
        MsgBox "Please enter a numeric value.", vbInformation, App.Title
        Exit Sub
    Else
        ' make sure value entered is within range of integer
        If (Val(txtPortNumber) > 32767 Or Val(txtPortNumber) < -32767) Then
            MsgBox "Value is not in range.", vbInformation, App.Title
            Exit Sub
        End If

        ' convert
        lblConvertedPort = htons(txtPortNumber)
        
    End If
End Sub

Private Sub cmdExit_Click()
    Unload Me
End Sub

Private Sub optNBO_Click(Index As Integer)
    lblConvertedPort.Caption = ""
End Sub

Private Sub txtPortNumber_Change()
    lblConvertedPort.Caption = ""
End Sub


