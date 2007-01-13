VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Begin VB.Form frmAbout 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "About Tom's Phone Book"
   ClientHeight    =   2460
   ClientLeft      =   3270
   ClientTop       =   2115
   ClientWidth     =   4110
   ControlBox      =   0   'False
   Icon            =   "frmAbout.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2460
   ScaleWidth      =   4110
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   1440
      TabIndex        =   0
      Top             =   2040
      Width           =   1335
   End
   Begin Threed.SSPanel pnlAbout 
      Height          =   1455
      Left            =   360
      TabIndex        =   1
      Top             =   240
      Width           =   3375
      _Version        =   65536
      _ExtentX        =   5953
      _ExtentY        =   2566
      _StockProps     =   15
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelInner      =   1
      Begin VB.Label lblCaption3 
         Alignment       =   2  'Center
         Caption         =   "Copyright (c) 1996"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   1080
         Width           =   3135
      End
      Begin VB.Label lblCaption2 
         Alignment       =   2  'Center
         Caption         =   "Written By: Thomas A. Rieck "
         Height          =   375
         Left            =   120
         TabIndex        =   3
         Top             =   600
         Width           =   3135
      End
      Begin VB.Label lblCaption1 
         Alignment       =   2  'Center
         Caption         =   "Tom's Phone Book"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   120
         TabIndex        =   2
         Top             =   120
         Width           =   3135
      End
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdOK_Click()
    Unload Me
End Sub


Private Sub Label1_Click()

End Sub


