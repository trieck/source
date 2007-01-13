VERSION 4.00
Begin VB.Form Form1 
   BackColor       =   &H00E0E0E0&
   Caption         =   "Form1"
   ClientHeight    =   4410
   ClientLeft      =   2235
   ClientTop       =   1560
   ClientWidth     =   5535
   Height          =   4830
   Left            =   2175
   LinkTopic       =   "Form1"
   ScaleHeight     =   4410
   ScaleWidth      =   5535
   Top             =   1200
   Width           =   5655
   Begin VB.CommandButton cmdMsgBoxAPI 
      Caption         =   "Message Box via Win API"
      Height          =   615
      Left            =   3840
      TabIndex        =   6
      Top             =   1920
      Width           =   1215
   End
   Begin Threed.SSCommand SScmdCloseComm 
      Height          =   615
      Left            =   2160
      TabIndex        =   8
      Top             =   720
      Width           =   1455
      _version        =   65536
      _extentx        =   2566
      _extenty        =   1085
      _stockprops     =   78
      caption         =   "Close Comm1"
      bevelwidth      =   7
   End
   Begin Threed.SSCommand SScmdOpenComm 
      Height          =   615
      Left            =   2160
      TabIndex        =   7
      Top             =   120
      Width           =   1455
      _version        =   65536
      _extentx        =   2566
      _extenty        =   1085
      _stockprops     =   78
      caption         =   "Open Comm1"
      bevelwidth      =   7
   End
   Begin Threed.SSCommand SSCommand1 
      Height          =   375
      Index           =   4
      Left            =   3720
      TabIndex        =   5
      Top             =   1440
      Width           =   1575
      _version        =   65536
      _extentx        =   2778
      _extenty        =   661
      _stockprops     =   78
      caption         =   "Question"
      bevelwidth      =   4
      font3d          =   3
   End
   Begin Threed.SSCommand SSCommand1 
      Height          =   375
      Index           =   3
      Left            =   3720
      TabIndex        =   4
      Top             =   1080
      Width           =   1575
      _version        =   65536
      _extentx        =   2778
      _extenty        =   661
      _stockprops     =   78
      caption         =   "System Hand"
      bevelwidth      =   4
      font3d          =   3
   End
   Begin Threed.SSCommand SSCommand1 
      Height          =   375
      Index           =   2
      Left            =   3720
      TabIndex        =   3
      Top             =   720
      Width           =   1575
      _version        =   65536
      _extentx        =   2778
      _extenty        =   661
      _stockprops     =   78
      caption         =   "System Asterisk"
      bevelwidth      =   4
      font3d          =   3
   End
   Begin Threed.SSCommand SSCommand1 
      Height          =   375
      Index           =   1
      Left            =   3720
      TabIndex        =   2
      Top             =   360
      Width           =   1575
      _version        =   65536
      _extentx        =   2778
      _extenty        =   661
      _stockprops     =   78
      caption         =   "Exclamation"
      bevelwidth      =   4
      font3d          =   3
   End
   Begin Threed.SSCommand SSCommand1 
      Height          =   375
      Index           =   0
      Left            =   3720
      TabIndex        =   1
      Top             =   0
      Width           =   1575
      _version        =   65536
      _extentx        =   2778
      _extenty        =   661
      _stockprops     =   78
      caption         =   "Default Sound"
      bevelwidth      =   4
      font3d          =   3
   End
   Begin VB.Label lblOutputWindow 
      Alignment       =   2  'Center
      BackColor       =   &H00808080&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   400
         size            =   13.5
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   1215
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Dim idComDev As Integer

Private Sub cmdMsgBoxAPI_Click()
    Dim HWnd As Integer, lptext As String, lpcaption As String, WType As Integer, i As Integer
    HWnd = 0
    lptext = "Hi."
    lpcaption = "Message Box WinAPI"
    i = MessageBox(HWnd, lptext, lpcaption, MB_OK)
End Sub


Private Sub SScmdCloseComm_Click()
    Dim RetNum As Integer, nCID As Integer
    nCID = idComDev
    RetNum = CloseComm(nCID)
    If RetNum <> 0 Then
        lblOutputWindow.Caption = "COM1 already Closed!"
    Else
        lblOutputWindow.Caption = "COM1 Closed"
    End If
End Sub


Private Sub SScmdOpenComm_Click()

    Dim idComDev As Integer, err As Integer, dcb As dcb
    lblOutputWindow.Caption = ""
    idComDev = OpenComm("COM1", 1024, 128)
    If idComDev = -2 Then
       lblOutputWindow.Caption = "COM1 already Open!"
    ElseIf idComDev >= 0 Then
        lblOutputWindow.Caption = "COM1 Open"
        err = BuildCommDCB("COM1:9600,n,8,1", dcb)
            If err < 0 Then
                lblOutputWindow.Caption = "Error"
            End If
    End If
End Sub

Private Sub SSCommand1_Click(Index As Integer)
    Select Case SSCommand1(Index).Index
        Case 0
            MessageBeep (MB_OK)
        Case 1
            MessageBeep (MB_ICONEXCLAMATION)
        Case 2
            MessageBeep (MB_ICONASTERISK)
        Case 3
            MessageBeep (MB_ICONHAND)
        Case 4
            MessageBeep (MB_ICONQUESTION)
    End Select
End Sub


