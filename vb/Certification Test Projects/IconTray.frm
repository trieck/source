VERSION 5.00
Begin VB.Form frmIconTray 
   Caption         =   "Form1"
   ClientHeight    =   3855
   ClientLeft      =   1845
   ClientTop       =   2325
   ClientWidth     =   4590
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3855
   ScaleWidth      =   4590
   Visible         =   0   'False
   Begin VB.PictureBox Picture2 
      Height          =   1095
      Left            =   1560
      Picture         =   "IconTray.frx":0000
      ScaleHeight     =   1035
      ScaleWidth      =   1275
      TabIndex        =   1
      Top             =   240
      Width           =   1335
   End
   Begin VB.PictureBox Picture1 
      Height          =   1095
      Left            =   120
      Picture         =   "IconTray.frx":0442
      ScaleHeight     =   1035
      ScaleWidth      =   1275
      TabIndex        =   0
      Top             =   240
      Width           =   1335
   End
   Begin VB.Menu mnuShell 
      Caption         =   "Shell_Menu"
      Begin VB.Menu mnuOn 
         Caption         =   "On"
      End
      Begin VB.Menu mnuOff 
         Caption         =   "Off"
      End
      Begin VB.Menu mnuSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuClose 
         Caption         =   "Close"
      End
   End
End
Attribute VB_Name = "frmIconTray"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Form_Load()
    t.cbSize = Len(t)
    t.hWnd = Picture1.hWnd
    t.uID = 1&
    t.uFlags = NIF_MESSAGE Or _
        NIF_ICON Or _
        NIF_TIP
    t.uCallBackMessage = WM_MOUSEMOVE
    t.hIcon = Picture1.Picture
    t.szTip = "Shell_NotifyIcon Test" & Chr$(0)
    Shell_NotifyIcon NIM_ADD, t
    
End Sub

Private Sub mnuClose_Click()
    Shell_NotifyIcon NIM_DELETE, t
    End
End Sub


Private Sub mnuOff_Click()
    mnuOff.Checked = True
    mnuOn.Checked = False
    t.hIcon = Picture2.Picture
    t.szTip = "Shell_NotifyIcon is off" & _
        Chr$(0)
    Shell_NotifyIcon NIM_MODIFY, t
    
End Sub


Private Sub mnuOn_Click()
    mnuOn.Checked = True
    mnuOff.Checked = False
    Call NotifyIcon_Change(, " ")
    t.hIcon = Picture1.Picture
    t.szTip = " Shell_NotifyIcon is On " & _
        Chr$(0)
    Shell_NotifyIcon NIMMODIFY, t
End Sub


Private Sub Picture1_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Hex(X) = "1e2d" Then
        frmIconTray.PopupMenu frmIconTray.mnuShell
    End If
    
End Sub


