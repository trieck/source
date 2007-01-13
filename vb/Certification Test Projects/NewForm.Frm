VERSION 4.00
Begin VB.Form Form1 
   BackColor       =   &H00404040&
   Caption         =   "Form1"
   ClientHeight    =   2835
   ClientLeft      =   3735
   ClientTop       =   2550
   ClientWidth     =   2745
   ForeColor       =   &H800F0012&
   Height          =   3255
   Left            =   3675
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   2835
   ScaleWidth      =   2745
   Top             =   2190
   Width           =   2865
   Begin VB.VScrollBar vsbBackColor 
      Height          =   2415
      LargeChange     =   5
      Left            =   120
      Max             =   30
      TabIndex        =   0
      Top             =   120
      Width           =   375
   End
   Begin VB.Label lblhWnd 
      Alignment       =   2  'Center
      BackColor       =   &H00404040&
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   600
      TabIndex        =   1
      Top             =   120
      Width           =   855
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Click()
    lblhWnd.Caption = Me.hDC
End Sub

Private Sub vsbBackColor_Change()
   Dim MyLong1 As Long, MyLong2 As Long
   MyLong1 = "&H" & Hex(vsbBackColor.Value ^ 2)
   MyLong2 = "&H" & Hex(vsbBackColor.Value ^ 2)
   Me.BackColor = MyLong1 & MyLong2
End Sub


Private Sub vsbBackColor_Scroll()
    vsbBackColor_Change
End Sub


