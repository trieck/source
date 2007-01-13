VERSION 5.00
Begin VB.Form frmSplash 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   2580
   ClientLeft      =   6045
   ClientTop       =   8355
   ClientWidth     =   6075
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   Icon            =   "splash.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2580
   ScaleWidth      =   6075
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame Frame1 
      Height          =   2475
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   5865
      Begin VB.PictureBox pctLogo 
         AutoRedraw      =   -1  'True
         Height          =   1620
         Left            =   120
         Picture         =   "splash.frx":014A
         ScaleHeight     =   1560
         ScaleWidth      =   2220
         TabIndex        =   6
         Top             =   240
         Width           =   2280
      End
      Begin VB.Label lblCopyright 
         Caption         =   "Copyright ©2003 "
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   3120
         TabIndex        =   2
         Top             =   1920
         Width           =   2415
      End
      Begin VB.Label lblCompany 
         Caption         =   "Rieck Enterprises"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   3120
         TabIndex        =   1
         Top             =   2160
         Width           =   2415
      End
      Begin VB.Label lblVersion 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Version "
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   240
         Left            =   4755
         TabIndex        =   3
         Top             =   1320
         Width           =   795
      End
      Begin VB.Label lblProductName 
         Alignment       =   2  'Center
         AutoSize        =   -1  'True
         Caption         =   "Product Name"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   21.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   525
         Left            =   2400
         TabIndex        =   5
         Top             =   720
         Width           =   3345
      End
      Begin VB.Label lblCompanyProduct 
         AutoSize        =   -1  'True
         Caption         =   "Rieck Enterprises"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   18
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00000080&
         Height          =   435
         Left            =   2520
         TabIndex        =   4
         Top             =   240
         Width           =   3090
      End
   End
End
Attribute VB_Name = "frmSplash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub Form_Activate()
    Me.ZOrder (0)
End Sub

Private Sub Form_Load()
    lblVersion.Caption = "Version " & App.Major & "." & App.Minor & "." & App.Revision
    lblProductName.Caption = App.Title
    Reset
End Sub

Public Property Get Complete() As Boolean
    Complete = TimerHasCompleted(Me.hWnd)
End Property

Public Sub Reset()
    Call CreateTimer(Me.hWnd, 1, 2500)
End Sub

