VERSION 5.00
Begin VB.Form frmBM 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "BM Test"
   ClientHeight    =   4635
   ClientLeft      =   1950
   ClientTop       =   1890
   ClientWidth     =   6900
   Icon            =   "bm.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4635
   ScaleWidth      =   6900
   Begin VB.FileListBox File1 
      Height          =   3405
      Left            =   3480
      Pattern         =   "*.bmp"
      TabIndex        =   3
      Top             =   600
      Width           =   3255
   End
   Begin VB.DirListBox Dir1 
      Height          =   3465
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   3255
   End
   Begin VB.DriveListBox Drive1 
      Height          =   315
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   3255
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   435
      Left            =   5760
      TabIndex        =   0
      Top             =   4080
      Width           =   975
   End
End
Attribute VB_Name = "frmBM"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private szFileName$




Private Sub cmdExit_Click()
    Unload Me
End Sub


Private Sub Dir1_Change()
    File1.Path = Dir1.Path
End Sub

Private Sub Drive1_Change()
    On Error Resume Next
    Dir1.Path = Drive1.Drive
End Sub

Private Sub File1_DblClick()
    Call ShowBitmapInfo(Me.hwnd, File1.Path & "\" & File1)
End Sub


Private Sub Form_Load()
    If (App.PrevInstance) Then End
    Drive1.Drive = "d:\"
    Dir1.Path = "d:\userfile\bmp"
    Me.Icon = LoadResPicture(101, vbResIcon)
End Sub



