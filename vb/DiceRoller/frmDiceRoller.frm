VERSION 5.00
Begin VB.Form frmDiceRoller 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Dice Roller"
   ClientHeight    =   3345
   ClientLeft      =   2910
   ClientTop       =   2265
   ClientWidth     =   5235
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "frmDiceRoller.frx":0000
   MaxButton       =   0   'False
   ScaleHeight     =   3345
   ScaleWidth      =   5235
   Begin VB.Timer tmrRandomize 
      Interval        =   1000
      Left            =   120
      Top             =   2880
   End
   Begin VB.Frame fmeSides 
      Caption         =   "Sides"
      Height          =   2055
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   5055
      Begin VB.OptionButton optSides 
         Caption         =   "20"
         Height          =   375
         Index           =   5
         Left            =   4080
         TabIndex        =   10
         Top             =   1440
         Width           =   855
      End
      Begin VB.OptionButton optSides 
         Caption         =   "12"
         Height          =   375
         Index           =   4
         Left            =   4080
         TabIndex        =   9
         Top             =   840
         Width           =   855
      End
      Begin VB.OptionButton optSides 
         Caption         =   "10"
         Height          =   375
         Index           =   3
         Left            =   4080
         TabIndex        =   8
         Top             =   240
         Width           =   855
      End
      Begin VB.OptionButton optSides 
         Caption         =   "8"
         Height          =   375
         Index           =   2
         Left            =   240
         TabIndex        =   7
         Top             =   1440
         Width           =   855
      End
      Begin VB.OptionButton optSides 
         Caption         =   "6"
         Height          =   375
         Index           =   1
         Left            =   240
         TabIndex        =   6
         Top             =   840
         Width           =   855
      End
      Begin VB.OptionButton optSides 
         Caption         =   "4"
         Height          =   375
         Index           =   0
         Left            =   240
         TabIndex        =   5
         Top             =   240
         Value           =   -1  'True
         Width           =   855
      End
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   4080
      TabIndex        =   1
      Top             =   2880
      Width           =   1095
   End
   Begin VB.CommandButton cmdRoll 
      Caption         =   "&Roll 'em"
      Height          =   375
      Left            =   2880
      TabIndex        =   0
      Top             =   2880
      Width           =   1095
   End
   Begin VB.Label lblResult 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   4320
      TabIndex        =   3
      Top             =   2280
      Width           =   855
   End
   Begin VB.Label lblResultCap 
      Caption         =   "Result:"
      Height          =   255
      Left            =   3600
      TabIndex        =   2
      Top             =   2280
      Width           =   615
   End
End
Attribute VB_Name = "frmDiceRoller"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Label2_Click()

End Sub


Private Sub Command1_Click()

End Sub

Private Sub cmdExit_Click()
    Unload Me
End Sub


Private Sub cmdRoll_Click()
    Dim vArray As Variant
    Dim nIndex As Integer
    Dim nRandom As Integer
    Dim i As Integer
    
    Screen.MousePointer = vbHourglass
    
    vArray = Array(4, 6, 8, 10, 12, 20)
    
    For i = 0 To optSides.UBound
        If optSides(i).Value Then
            Exit For
        End If
    Next i
             
    ' Generate random value between 1 and number of sides
    nRandom = Int((vArray(i) * Rnd) + 1)
        
    lblResult = nRandom
    
    Screen.MousePointer = vbDefault
End Sub


Private Sub tmrRandomize_Timer()
    ' Seed the Random Number Generator
    Randomize (Time)
End Sub


