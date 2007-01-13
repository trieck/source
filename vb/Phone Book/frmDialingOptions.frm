VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Begin VB.Form frmDialingOptions 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Tom's Phone Book"
   ClientHeight    =   2550
   ClientLeft      =   3015
   ClientTop       =   2370
   ClientWidth     =   3465
   Icon            =   "frmDialingOptions.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2550
   ScaleWidth      =   3465
   ShowInTaskbar   =   0   'False
   Begin Threed.SSFrame fmeDialOptions 
      Height          =   1815
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3255
      _Version        =   65536
      _ExtentX        =   5741
      _ExtentY        =   3201
      _StockProps     =   14
      Caption         =   "Dialing Options"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Begin Threed.SSOption optDial 
         Height          =   375
         Index           =   1
         Left            =   240
         TabIndex        =   4
         Top             =   1080
         Width           =   975
         _Version        =   65536
         _ExtentX        =   1720
         _ExtentY        =   661
         _StockProps     =   78
         Caption         =   "Business"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin Threed.SSOption optDial 
         Height          =   375
         Index           =   0
         Left            =   240
         TabIndex        =   3
         Top             =   480
         Width           =   735
         _Version        =   65536
         _ExtentX        =   1296
         _ExtentY        =   661
         _StockProps     =   78
         Caption         =   "Home"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Value           =   -1  'True
      End
   End
   Begin Threed.SSCommand cmdCancel 
      Height          =   375
      Left            =   2160
      TabIndex        =   2
      Top             =   2040
      Width           =   1215
      _Version        =   65536
      _ExtentX        =   2143
      _ExtentY        =   661
      _StockProps     =   78
      Caption         =   "&Cancel"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin Threed.SSCommand cmdDial 
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   2040
      Width           =   1215
      _Version        =   65536
      _ExtentX        =   2143
      _ExtentY        =   661
      _StockProps     =   78
      Caption         =   "&Dial"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
End
Attribute VB_Name = "frmDialingOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdDial_Click()
    Dim Number$
    
    If optDial(0).Value = True Then
        Number$ = frmPhoneBook2!txtOutput(4).Text
    Else
        Number$ = frmPhoneBook2!txtOutput(5).Text
    End If
    DialNumber Number$, App.Title, frmPhoneBook2!lstOutputWindow.Text
    
    Unload Me
End Sub


