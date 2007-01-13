VERSION 5.00
Begin VB.Form frmList 
   Caption         =   "Component Client"
   ClientHeight    =   3360
   ClientLeft      =   3690
   ClientTop       =   2940
   ClientWidth     =   4110
   ClipControls    =   0   'False
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "list.frx":0000
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   168
   ScaleMode       =   2  'Point
   ScaleWidth      =   205.5
   Begin VB.ListBox lstMain 
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   3150
      IntegralHeight  =   0   'False
      Left            =   60
      TabIndex        =   0
      Top             =   120
      Width           =   3975
   End
End
Attribute VB_Name = "frmList"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    ' Don't Allow closing from the system menu
    If (UnloadMode = vbFormControlMenu) Then Cancel = True
End Sub


Private Sub Form_Resize()
    lstMain.Left = Me.ScaleLeft
    lstMain.Width = Me.ScaleWidth
    lstMain.Top = Me.ScaleTop
    lstMain.Height = Me.ScaleHeight
End Sub



