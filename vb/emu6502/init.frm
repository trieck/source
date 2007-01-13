VERSION 5.00
Begin VB.Form frmInit 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "emu6502"
   ClientHeight    =   510
   ClientLeft      =   5790
   ClientTop       =   7560
   ClientWidth     =   2430
   Icon            =   "init.frx":0000
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   510
   ScaleWidth      =   2430
   ShowInTaskbar   =   0   'False
   Begin VB.Label lblWait 
      Alignment       =   2  'Center
      Caption         =   "Please Wait, Initializing..."
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2175
   End
End
Attribute VB_Name = "frmInit"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    Me.ZOrder (0)
End Sub


