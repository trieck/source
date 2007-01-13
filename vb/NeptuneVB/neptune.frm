VERSION 5.00
Object = "{38911DA0-E448-11D0-84A3-00DD01104159}#1.1#0"; "COMCT332.OCX"
Begin VB.Form frmNeptune 
   BackColor       =   &H00C0E0FF&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Neptune"
   ClientHeight    =   5580
   ClientLeft      =   4935
   ClientTop       =   4290
   ClientWidth     =   6585
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "neptune.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5580
   ScaleWidth      =   6585
   Begin VB.TextBox txtOutput 
      Enabled         =   0   'False
      Height          =   2655
      Left            =   840
      TabIndex        =   1
      Top             =   2400
      Width           =   4695
   End
   Begin VB.TextBox txtInput 
      Height          =   285
      Left            =   840
      TabIndex        =   0
      Top             =   1560
      Width           =   4695
   End
   Begin ComCtl3.CoolBar cbNeptune 
      Height          =   765
      Left            =   -120
      TabIndex        =   4
      Top             =   0
      Width           =   6735
      _ExtentX        =   11880
      _ExtentY        =   1349
      BandCount       =   1
      VariantHeight   =   0   'False
      _CBWidth        =   6735
      _CBHeight       =   765
      _Version        =   "6.7.8862"
      BandBackColor1  =   -2147483636
      MinHeight1      =   705
      Width1          =   6675
      NewRow1         =   0   'False
      Begin VB.CommandButton cmdExit 
         Caption         =   "E&xit"
         Height          =   495
         Left            =   4080
         TabIndex        =   6
         Top             =   120
         Width           =   1575
      End
      Begin VB.CommandButton cmdFormat 
         Caption         =   "&Format..."
         Height          =   495
         Left            =   960
         TabIndex        =   5
         Top             =   120
         Width           =   1575
      End
   End
   Begin VB.Label lblInput 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Input:"
      Height          =   255
      Left            =   840
      TabIndex        =   3
      Top             =   1200
      Width           =   1695
   End
   Begin VB.Label lblOutput 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Output:"
      Height          =   255
      Left            =   840
      TabIndex        =   2
      Top             =   2040
      Width           =   1695
   End
End
Attribute VB_Name = "frmNeptune"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Option Base 0

Private Function FormatString(ByVal str As String) As String
    Dim objNeptune As Neptune
    
    On Error GoTo errHandler
    
    Set objNeptune = New Neptune
    
    Dim fmt As String
    Dim output As String
        
    objNeptune.FormatString str, output, "Mamma", "Dadda", "Poppa"
    
    FormatString = output
    
    Exit Function
    
errHandler:
    Debug.Print Err.Description
    On Error GoTo 0
End Function



Private Sub cmdExit_Click()
    Unload Me
End Sub


Private Sub cmdFormat_Click()
    txtOutput.Text = FormatString(txtInput.Text)
End Sub


Private Sub Form_Load()
    Dim x As String
    Dim c As IComputer
    Dim obj As New Neptune
    
    Set c = obj
    
    x = c.SystemDirectory
    
End Sub


