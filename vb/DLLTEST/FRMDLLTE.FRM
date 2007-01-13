VERSION 5.00
Begin VB.Form frmDllTest 
   Appearance      =   0  'Flat
   BackColor       =   &H00E0E0E0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "DllTest"
   ClientHeight    =   3225
   ClientLeft      =   3495
   ClientTop       =   1650
   ClientWidth     =   3000
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3225
   ScaleWidth      =   3000
   ShowInTaskbar   =   0   'False
   Begin VB.PictureBox Picture4 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   585
      Left            =   1800
      ScaleHeight     =   585
      ScaleWidth      =   945
      TabIndex        =   6
      Top             =   3240
      Visible         =   0   'False
      Width           =   945
   End
   Begin VB.PictureBox Picture6 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   1800
      ScaleHeight     =   585
      ScaleWidth      =   945
      TabIndex        =   5
      Top             =   3960
      Visible         =   0   'False
      Width           =   975
   End
   Begin VB.PictureBox Picture5 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   240
      ScaleHeight     =   585
      ScaleWidth      =   945
      TabIndex        =   4
      Top             =   3960
      Visible         =   0   'False
      Width           =   975
   End
   Begin VB.PictureBox Picture3 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   585
      Left            =   240
      ScaleHeight     =   585
      ScaleWidth      =   945
      TabIndex        =   3
      Top             =   3240
      Visible         =   0   'False
      Width           =   945
   End
   Begin VB.PictureBox Picture2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   1800
      ScaleHeight     =   585
      ScaleWidth      =   945
      TabIndex        =   2
      Top             =   2520
      Width           =   975
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   240
      ScaleHeight     =   585
      ScaleWidth      =   945
      TabIndex        =   1
      Top             =   2520
      Width           =   975
   End
   Begin VB.ListBox List1 
      BackColor       =   &H00E0E0E0&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   2085
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   2535
   End
End
Attribute VB_Name = "frmDllTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False



Private Sub Picture1_Click()
    Dim Buffer(255) As String, rtn%, i As Integer
    List1.Clear
    rtn% = GrabData(Buffer)
    For i = 0 To 90
        List1.AddItem Buffer(i)
    Next i
End Sub

Private Sub Picture1_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Picture1.Picture = Picture3.Picture
End Sub


Private Sub Picture1_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Picture1.Picture = Picture5.Picture
End Sub


Private Sub Picture2_Click()
    End
End Sub

Private Sub Picture2_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Picture2.Picture = Picture4.Picture
End Sub


Private Sub Picture2_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Picture2.Picture = Picture6.Picture
End Sub


