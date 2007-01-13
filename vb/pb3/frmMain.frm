VERSION 5.00
Object = "{A3AFC613-B347-11D0-97F7-444553540000}#1.0#0"; "COLOR BUTTON.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Phone Book"
   ClientHeight    =   4710
   ClientLeft      =   1785
   ClientTop       =   2070
   ClientWidth     =   5145
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   4710
   ScaleWidth      =   5145
   Begin VB.TextBox txtFirstName 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00400000&
      Height          =   285
      Left            =   120
      TabIndex        =   6
      Top             =   720
      Width           =   3135
   End
   Begin VB.TextBox txtLastName 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00400000&
      Height          =   285
      Left            =   120
      TabIndex        =   5
      Top             =   360
      Width           =   3135
   End
   Begin VB.Frame fmeBtnContainer 
      Height          =   2655
      Left            =   3360
      TabIndex        =   7
      Top             =   120
      Width           =   1695
      Begin COLORBUTTONLib.ColorButton cmdAddEntry 
         Height          =   375
         Left            =   120
         TabIndex        =   0
         Top             =   240
         Width           =   1455
         _Version        =   65536
         _ExtentX        =   2566
         _ExtentY        =   661
         _StockProps     =   68
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.24
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BackColor       =   8388736
         ForeColor       =   12648447
         Caption         =   "Add Entry"
      End
      Begin COLORBUTTONLib.ColorButton cmdSaveEntry 
         Height          =   375
         Left            =   120
         TabIndex        =   2
         Top             =   1200
         Width           =   1455
         _Version        =   65536
         _ExtentX        =   2566
         _ExtentY        =   661
         _StockProps     =   68
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.24
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BackColor       =   16761024
         ForeColor       =   4194368
         Caption         =   "Save Entry"
      End
      Begin COLORBUTTONLib.ColorButton cmdDeleteEntry 
         Height          =   375
         Left            =   120
         TabIndex        =   3
         Top             =   1680
         Width           =   1455
         _Version        =   65536
         _ExtentX        =   2566
         _ExtentY        =   661
         _StockProps     =   68
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.24
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BackColor       =   12648384
         ForeColor       =   4194368
         Caption         =   "Delete Entry"
      End
      Begin COLORBUTTONLib.ColorButton cmdExit 
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   2160
         Width           =   1455
         _Version        =   65536
         _ExtentX        =   2566
         _ExtentY        =   661
         _StockProps     =   68
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.24
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BackColor       =   128
         ForeColor       =   12648447
         Caption         =   "Exit"
      End
      Begin COLORBUTTONLib.ColorButton cmdLookup 
         Height          =   375
         Left            =   120
         TabIndex        =   1
         Top             =   720
         Width           =   1455
         _Version        =   65536
         _ExtentX        =   2566
         _ExtentY        =   661
         _StockProps     =   68
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.24
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BackColor       =   8438015
         ForeColor       =   8388608
         Caption         =   "Lookup"
      End
   End
   Begin VB.Label lblName 
      BackStyle       =   0  'Transparent
      Caption         =   "Name:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   120
      Width           =   2175
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private pb As Object
Public Sub ClearText()
    Dim ctrl As Control
    
    For Each ctrl In Me.Controls
        If TypeOf ctrl Is TextBox Then
            ctrl.Text = ""
        End If
    Next
End Sub






Private Sub cmdExit_Click()
    If (MsgBox("Are you sure you wish to exit?", vbYesNo + vbQuestion + vbDefaultButton2, "Exit Phone Book") = vbYes) Then
        End
    End If
End Sub



Private Sub cmdLookup_Click()
    Dim vArray As Variant
 
'   Do lookup
    vArray = pb.DoLookup()
    If (IsArray(vArray)) Then
        Dim i As Long, msg$
        For i = 0 To UBound(vArray, 2)
            frmEntries!lstEntries.AddItem vArray(1, i)
            frmEntries!lstEntries.ItemData(frmEntries!lstEntries.NewIndex) = vArray(0, i)
        Next
    Else: Exit Sub
    End If
    frmEntries.Show vbModal
End Sub



Private Sub Form_Load()
'   create an instance of the DB object
    Set pb = New CPBDB
'   open the database
    pb.OpenDB ("c:\My Documents\Tom's Database.mdb")
End Sub


Private Sub Form_Unload(Cancel As Integer)
' cleanup and exit
    Set pb = Nothing
End Sub


