VERSION 5.00
Object = "{A3AFC613-B347-11D0-97F7-444553540000}#1.0#0"; "cb.ocx"
Begin VB.Form frmOptions 
   AutoRedraw      =   -1  'True
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Options"
   ClientHeight    =   2175
   ClientLeft      =   2040
   ClientTop       =   2580
   ClientWidth     =   1590
   Icon            =   "frmOptions.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   2175
   ScaleWidth      =   1590
   ShowInTaskbar   =   0   'False
   Begin COLORBUTTONLib.ColorButton cbtnSaveEntry 
      Height          =   375
      Left            =   0
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   720
      Width           =   1575
      _Version        =   65536
      _ExtentX        =   2778
      _ExtentY        =   661
      _StockProps     =   68
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   3
      BackColor       =   16711935
      Caption         =   "Save an entry"
   End
   Begin COLORBUTTONLib.ColorButton cbtnAddEntry 
      Height          =   375
      Left            =   0
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   0
      Width           =   1575
      _Version        =   65536
      _ExtentX        =   2778
      _ExtentY        =   661
      _StockProps     =   68
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   3
      BackColor       =   16761087
      Caption         =   "Add an entry"
   End
   Begin COLORBUTTONLib.ColorButton cbtnDialEntry 
      Height          =   375
      Left            =   0
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   1080
      Width           =   1575
      _Version        =   65536
      _ExtentX        =   2778
      _ExtentY        =   661
      _StockProps     =   68
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   3
      BackColor       =   12583104
      ForeColor       =   12640511
      Caption         =   "Dial an entry"
   End
   Begin COLORBUTTONLib.ColorButton cbtnLookup 
      Height          =   375
      Left            =   0
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   1440
      Width           =   1575
      _Version        =   65536
      _ExtentX        =   2778
      _ExtentY        =   661
      _StockProps     =   68
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   3
      BackColor       =   8388736
      ForeColor       =   12640511
      Caption         =   "Lookup"
   End
   Begin COLORBUTTONLib.ColorButton cbtnExit 
      Height          =   375
      Left            =   0
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   1800
      Width           =   1575
      _Version        =   65536
      _ExtentX        =   2778
      _ExtentY        =   661
      _StockProps     =   68
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   3
      BackColor       =   4194368
      ForeColor       =   12640511
      Caption         =   "Exit"
   End
   Begin COLORBUTTONLib.ColorButton cbtnDeleteEntry 
      Height          =   375
      Left            =   0
      TabIndex        =   5
      TabStop         =   0   'False
      Top             =   360
      Width           =   1575
      _Version        =   65536
      _ExtentX        =   2778
      _ExtentY        =   661
      _StockProps     =   68
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   3
      BackColor       =   16744703
      Caption         =   "Delete an entry"
   End
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Sub ColorButton1_Click()
    MsgBox "Oh"
End Sub


Private Sub ColorButton2_Click(Index As Integer)
    
End Sub


Private Sub cbtnExit_Click()
    Set glbPB = Nothing
    End
End Sub

Private Sub cbtnLookup_Click()
    Dim vArray As Variant
 
    '   Do lookup
    vArray = glbPB.DoLookup()
    If (IsArray(vArray)) Then
        Dim i As Long, msg$
        frmEntries!lstEntries.Clear
        For i = 0 To UBound(vArray, 2)
            frmEntries!lstEntries.AddItem vArray(1, i)
            frmEntries!lstEntries.ItemData(frmEntries!lstEntries.NewIndex) = vArray(0, i)
        Next
    Else: Exit Sub
    End If
    frmEntries.Show
End Sub


