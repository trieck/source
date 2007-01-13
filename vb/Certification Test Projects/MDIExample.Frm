VERSION 4.00
Begin VB.MDIForm MDIForm1 
   BackColor       =   &H00404040&
   Caption         =   "MDIForm1"
   ClientHeight    =   4080
   ClientLeft      =   1440
   ClientTop       =   2325
   ClientWidth     =   6180
   Height          =   4485
   Left            =   1380
   LinkTopic       =   "MDIForm1"
   LockControls    =   -1  'True
   ScrollBars      =   0   'False
   Top             =   1980
   Width           =   6300
   Begin VB.PictureBox Picture1 
      Align           =   1  'Align Top
      Height          =   540
      Left            =   0
      ScaleHeight     =   480
      ScaleWidth      =   6120
      TabIndex        =   0
      Top             =   0
      Width           =   6180
      Begin VB.CommandButton Command2 
         Caption         =   "&Close"
         BeginProperty Font 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   700
            size            =   8.25
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   960
         TabIndex        =   2
         Top             =   0
         Width           =   975
      End
      Begin VB.CommandButton Command1 
         Caption         =   "&Open"
         BeginProperty Font 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   700
            size            =   8.25
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   0
         TabIndex        =   1
         Top             =   0
         Width           =   975
      End
   End
End
Attribute VB_Name = "MDIForm1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Dim colForms As New Collection
Sub Command1_Click()
    Dim NewClass1 As New MyClass
    With NewClass1
        .XPos = 0
        .YPos = 0
        .TitleBar = "Form1"
        .ShowForm
    End With
    colForms.Add NewClass1
    Dim NewClass2 As New MyClass
    With NewClass2
        .XPos = 2050
        .YPos = 0
        .TitleBar = "Form2"
        .ShowForm
    End With
    colForms.Add NewClass2
    Dim NewClass3 As New MyClass
    With NewClass3
        .TitleBar = "Form3"
        .XPos = 4100
        .YPos = 0
        .ShowForm
    End With
    colForms.Add NewClass3
    Command1.Enabled = False
End Sub


Private Sub Command2_Click()
    Set colForms = Nothing
    Command1.Enabled = True
End Sub


