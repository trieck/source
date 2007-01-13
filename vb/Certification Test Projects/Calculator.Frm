VERSION 4.00
Begin VB.Form frmCalculator 
   BackColor       =   &H00C0FFFF&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Calculator"
   ClientHeight    =   3525
   ClientLeft      =   3885
   ClientTop       =   1455
   ClientWidth     =   2295
   Height          =   3930
   Left            =   3825
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3525
   ScaleWidth      =   2295
   Top             =   1110
   Width           =   2415
   Begin VB.TextBox txtOutputWindow 
      Height          =   375
      Left            =   120
      TabIndex        =   10
      Top             =   240
      Width           =   2055
   End
   Begin Threed.SSCommand cmdEqual 
      Height          =   375
      Left            =   120
      TabIndex        =   15
      Top             =   2760
      Width           =   2055
      _Version        =   65536
      _ExtentX        =   3625
      _ExtentY        =   661
      _StockProps     =   78
      Caption         =   "="
   End
   Begin Threed.SSCommand cmdOperand 
      Height          =   495
      Index           =   3
      Left            =   1680
      TabIndex        =   14
      Top             =   2160
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "/"
   End
   Begin Threed.SSCommand cmdOperand 
      Height          =   495
      Index           =   2
      Left            =   1680
      TabIndex        =   13
      Top             =   1680
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "*"
   End
   Begin Threed.SSCommand cmdOperand 
      Height          =   495
      Index           =   1
      Left            =   1680
      TabIndex        =   12
      Top             =   1200
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "-"
   End
   Begin Threed.SSCommand cmdOperand 
      Height          =   495
      Index           =   0
      Left            =   1680
      TabIndex        =   11
      Top             =   720
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "+"
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   9
      Left            =   1080
      TabIndex        =   9
      Top             =   1680
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "9"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   8
      Left            =   600
      TabIndex        =   8
      Top             =   1680
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "8"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   7
      Left            =   120
      TabIndex        =   7
      Top             =   1680
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "7"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   6
      Left            =   1080
      TabIndex        =   6
      Top             =   1200
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "6"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   5
      Left            =   600
      TabIndex        =   5
      Top             =   1200
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "5"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   4
      Left            =   120
      TabIndex        =   4
      Top             =   1200
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "4"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   3
      Left            =   1080
      TabIndex        =   3
      Top             =   720
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "3"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   2
      Left            =   600
      TabIndex        =   2
      Top             =   720
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "2"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   1
      Left            =   120
      TabIndex        =   1
      Top             =   720
      Width           =   495
      _Version        =   65536
      _ExtentX        =   873
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "1"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
   Begin Threed.SSCommand cmdMathButton 
      Height          =   495
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   2160
      Width           =   1455
      _Version        =   65536
      _ExtentX        =   2566
      _ExtentY        =   873
      _StockProps     =   78
      Caption         =   "0"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Font3D          =   1
   End
End
Attribute VB_Name = "frmCalculator"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Private Sub Form_Activate()
    txtOutputwindow.SetFocus
End Sub

