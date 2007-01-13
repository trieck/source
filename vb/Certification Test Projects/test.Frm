VERSION 4.00
Begin VB.Form frmSQLQuery 
   BackColor       =   &H00404000&
   Caption         =   "SQL Query"
   ClientHeight    =   3525
   ClientLeft      =   2655
   ClientTop       =   1665
   ClientWidth     =   4800
   ForeColor       =   &H00000000&
   Height          =   3960
   Left            =   2595
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   3525
   ScaleWidth      =   4800
   Top             =   1290
   Width           =   4920
   Begin VB.ListBox lstQueryBox 
      Height          =   2010
      Left            =   240
      TabIndex        =   3
      Top             =   720
      Width           =   4215
   End
   Begin VB.CommandButton cmdCDQuery 
      Caption         =   "CD Query"
      Height          =   375
      Left            =   2400
      TabIndex        =   1
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton cmdTapeQuery 
      Caption         =   "Tape Query"
      Height          =   375
      Left            =   1200
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
   Begin VB.Label lblShowStatus 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   18
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   1440
      TabIndex        =   2
      Top             =   3000
      Width           =   1695
   End
End
Attribute VB_Name = "frmSQLQuery"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Dim SQLTapeString As String, SQLCDString As String, MyDB As Database, TapeRecordset As Recordset, _
    CDRecordset As Recordset


Private Sub cmdCDQuery_Click()
    cmdTapeQuery.Enabled = True
    lstQueryBox.Clear
    Do Until CDRecordset.EOF
            lstQueryBox.AddItem CDRecordset("Artist") & " - " & CDRecordset("Album")
        CDRecordset.MoveNext
    Loop
    CDRecordset.MoveFirst
    lblShowStatus.Caption = "CDs"
    cmdCDQuery.Enabled = Not cmdCDQuery.Enabled
End Sub

Private Sub cmdCDQuery_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    lstQueryBox.SetFocus
End Sub


Private Sub cmdTapeQuery_Click()
    cmdCDQuery.Enabled = True
    lstQueryBox.Clear
    Do Until TapeRecordset.EOF
            lstQueryBox.AddItem TapeRecordset("Artist") & " - " & TapeRecordset("Album")
        TapeRecordset.MoveNext
    Loop
    TapeRecordset.MoveFirst
    lblShowStatus.Caption = "Tapes"
    cmdTapeQuery.Enabled = Not cmdTapeQuery.Enabled
End Sub

Private Sub cmdTapeQuery_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    lstQueryBox.SetFocus
End Sub


Private Sub Form_Activate()
    lstQueryBox.SetFocus
End Sub

Private Sub Form_Load()
SQLTapeString = "SELECT DISTINCTROW Albums.Artist," & _
                        "Albums.Album From Albums Where ((([Albums]![Medium]) = False))" & _
                        "ORDER BY Albums.Artist, Albums.Album;"
SQLCDString = "SELECT DISTINCTROW Albums.Artist," & _
                        "Albums.Album From Albums Where ((([Albums]![Medium]) = True))" & _
                        "ORDER BY Albums.Artist, Albums.Album;"

Set MyDB = OpenDatabase("c:\Program Files\Microsoft Visual Basic\Tom's Projects\Albums\albums.mdb")
Set TapeRecordset = MyDB.OpenRecordset(SQLTapeString)
Set CDRecordset = MyDB.OpenRecordset(SQLCDString)
End Sub


