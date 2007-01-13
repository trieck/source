VERSION 5.00
Begin VB.Form frmBreakdown 
   BackColor       =   &H80000001&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Key/Value Breakdown"
   ClientHeight    =   1830
   ClientLeft      =   1890
   ClientTop       =   2235
   ClientWidth     =   6840
   Icon            =   "FRMBREAK.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   NegotiateMenus  =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1830
   ScaleWidth      =   6840
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   5520
      TabIndex        =   6
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton cmdSave 
      Caption         =   "&Save"
      Enabled         =   0   'False
      Height          =   375
      Left            =   5520
      TabIndex        =   5
      Top             =   240
      Width           =   1215
   End
   Begin VB.Frame fmeBreakdown 
      BackColor       =   &H80000001&
      Height          =   1455
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5295
      Begin VB.TextBox txtKey 
         Height          =   375
         Left            =   840
         TabIndex        =   4
         Top             =   240
         Width           =   4095
      End
      Begin VB.TextBox txtValue 
         Height          =   375
         Left            =   840
         TabIndex        =   1
         Top             =   840
         Width           =   4095
      End
      Begin VB.Label lblKey 
         Alignment       =   1  'Right Justify
         BackColor       =   &H80000001&
         Caption         =   "Key:"
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   240
         TabIndex        =   3
         Top             =   360
         Width           =   495
      End
      Begin VB.Label lblValue 
         Alignment       =   1  'Right Justify
         BackColor       =   &H80000001&
         Caption         =   "Value:"
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   960
         Width           =   495
      End
   End
End
Attribute VB_Name = "frmBreakdown"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim DirtyFlags As Boolean, HaveSaved As Boolean


Private Sub cmdExit_Click()
    Unload frmBreakdown
End Sub

Private Sub cmdSave_Click()
    Dim Success%, Msg$, Di%
    If DirtyFlags Then 'If in EDIT Mode
        HaveSaved = True
        If frmGetProfile!mnuWIN_INI.Checked Then  'if WIN.INI
            Success% = WriteProfileString _
                (frmGetProfile!lstGetProfile.Text _
                , txtKey.Text, txtValue.Text)
        Else    'If SYSTEM.INI
            Success% = WritePrivateProfileString _
                (frmGetProfile!lstGetProfile.Text _
                , txtKey.Text, txtValue.Text _
                , "SYSTEM.INI")
        End If
        If Success% > 0 And frmGetProfile!mnuWIN_INI.Checked Then
        'Post Message re: Update to WIN.INI
            #If Win32 Then
                Di% = PostMessageByString(HWND_BROADCAST _
                , WM_WININICHANGE, 0, frmGetProfile!lstGetProfile.Text)
            #Else
                Di% = PostMessage(HWND_BROADCAST _
            , WM_WININICHANGE, 0, frmGetProfile!lstGetProfile.Text)
            #End If
        ElseIf Success% = 0 Then 'Error
            Msg$ = "There was a problem writing"
            Msg$ = Msg$ + "to the specified Key."
            MsgBox Msg$
        End If
        DirtyFlags = False
        Unload frmBreakdown
    End If
End Sub

Private Sub Form_Activate()
    Me.Caption = "[" + frmGetProfile!lstGetProfile.Text + "]"
    txtKey.Enabled = False
    txtValue.SetFocus
End Sub

Private Sub Form_Load()
    DirtyFlags = False
    HaveSaved = False
End Sub





Private Sub Form_Unload(Cancel As Integer)
    If HaveSaved Then
        frmGetProfile.lstGetProfile_Click
        HaveSaved = False
    End If
End Sub

Private Sub txtValue_KeyDown(KeyCode As Integer, Shift As Integer)
    DirtyFlags = True
    cmdSave.Enabled = True
End Sub


