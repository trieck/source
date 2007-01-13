VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Begin VB.Form Form1 
   BackColor       =   &H00E0FEFB&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Albums"
   ClientHeight    =   2985
   ClientLeft      =   2610
   ClientTop       =   1845
   ClientWidth     =   5220
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2985
   ScaleWidth      =   5220
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3165
      TabIndex        =   9
      Top             =   2040
      Visible         =   0   'False
      Width           =   975
   End
   Begin VB.CommandButton cmdSave 
      Caption         =   "Save"
      Height          =   375
      Left            =   3180
      TabIndex        =   5
      Top             =   1560
      Visible         =   0   'False
      Width           =   975
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "Delete"
      Height          =   375
      Left            =   4200
      TabIndex        =   11
      Top             =   2040
      Width           =   975
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "Add"
      Height          =   375
      Left            =   4200
      TabIndex        =   7
      Top             =   1560
      Width           =   975
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      Height          =   375
      Left            =   4185
      TabIndex        =   13
      Top             =   2520
      Width           =   975
   End
   Begin VB.TextBox txtRelease 
      BackColor       =   &H00C0C0C0&
      Height          =   375
      Left            =   165
      TabIndex        =   2
      Text            =   " "
      Top             =   2505
      Width           =   855
   End
   Begin VB.OptionButton optCD 
      BackColor       =   &H00E0FEFB&
      Caption         =   "CD"
      Height          =   375
      Left            =   3360
      TabIndex        =   3
      Top             =   825
      Width           =   1335
   End
   Begin VB.OptionButton optCassette 
      BackColor       =   &H00E0FEFB&
      Caption         =   "Cassette"
      Height          =   375
      Left            =   3345
      TabIndex        =   4
      Top             =   375
      Width           =   1335
   End
   Begin VB.TextBox txtAlbum 
      BackColor       =   &H00C0C0C0&
      Height          =   405
      Left            =   120
      TabIndex        =   1
      Text            =   " "
      Top             =   1530
      Width           =   2895
   End
   Begin VB.TextBox txtArtist 
      BackColor       =   &H00C0C0C0&
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
      TabIndex        =   0
      Text            =   " "
      Top             =   570
      Width           =   2895
   End
   Begin VB.Frame fraMedium 
      BackColor       =   &H00E0FEFB&
      Caption         =   "Medium"
      Height          =   1215
      Left            =   3240
      TabIndex        =   6
      Top             =   120
      Width           =   1575
   End
   Begin Threed.SSCommand cmdPrevious 
      Height          =   375
      Left            =   1680
      TabIndex        =   18
      Top             =   2520
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   661
      _StockProps     =   78
      Caption         =   "<<<"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   4
      Font3D          =   3
   End
   Begin Threed.SSCommand cmdNext 
      Height          =   375
      Left            =   2760
      TabIndex        =   17
      Top             =   2520
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   661
      _StockProps     =   78
      Caption         =   ">>>"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   4
      Font3D          =   3
   End
   Begin VB.Label lblDate 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H00C0FFFF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Release Date:"
      BeginProperty Font 
         Name            =   "Book Antiqua"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   12
      Top             =   2040
      Width           =   2295
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H00C0FFFF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Album:"
      BeginProperty Font 
         Name            =   "Book Antiqua"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   120
      TabIndex        =   10
      Top             =   1080
      Width           =   1455
   End
   Begin VB.Label lblArtist 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H00C0FFFF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Artist:"
      BeginProperty Font 
         Name            =   "Book Antiqua"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   8
      Top             =   120
      Width           =   1335
   End
   Begin VB.Label Label4 
      BackColor       =   &H00808080&
      Caption         =   "Label4"
      Height          =   375
      Left            =   120
      TabIndex        =   14
      Top             =   2085
      Width           =   2370
   End
   Begin VB.Label Label5 
      BackColor       =   &H00808080&
      Caption         =   "Label4"
      Height          =   375
      Left            =   120
      TabIndex        =   15
      Top             =   1125
      Width           =   1530
   End
   Begin VB.Label Label6 
      BackColor       =   &H00808080&
      Caption         =   "Label4"
      Height          =   375
      Left            =   120
      TabIndex        =   16
      Top             =   165
      Width           =   1395
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim Database As Database
Dim AlbumTable As Recordset
Dim med As Boolean
Dim Path As String




Private Sub cmdAdd_Click()
    txtArtist = ""
    txtAlbum = ""
    txtRelease = ""
    optCD = False
    optCassette = False
    cmdSave.Visible = True
    cmdCancel.Visible = True
    cmdAdd.Enabled = False
    cmdDelete.Enabled = False
    cmdExit.Enabled = False
    cmdNext.Enabled = False
    cmdPrevious.Enabled = False
    txtArtist.SetFocus
    AlbumTable.AddNew
End Sub


Private Sub cmdCancel_Click()
    cmdSave.Visible = False
    cmdCancel.Visible = False
    cmdAdd.Enabled = True
    cmdDelete.Enabled = True
    cmdExit.Enabled = True
    cmdNext.Enabled = True
    cmdPrevious.Enabled = True
    AlbumTable.MoveFirst
    Refresh_Display
End Sub

Private Sub cmdDelete_Click()
    Dim Reply As Integer
    Reply = MsgBox("Are you sure you want to delete this record", 292, "Delete Record")
    If Reply = 6 Then
        AlbumTable.Delete
        AlbumTable.MoveFirst
        Refresh_Display
    End If
End Sub


Private Sub cmdExit_Click()
    End
End Sub

Private Sub cmdNext_Click()
    AlbumTable.MoveNext
     If AlbumTable.EOF Then
        AlbumTable.MoveLast
    End If
    txtArtist.SetFocus
    Refresh_Display
End Sub

Private Sub cmdPrevious_Click()
    AlbumTable.MovePrevious
    If AlbumTable.BOF Then
        AlbumTable.MoveFirst
    End If
    txtArtist.SetFocus
    Refresh_Display
End Sub

Private Sub cmdSave_Click()
    If optCD = True Then
        med = True
    Else
        med = False
    End If
    If Trim(txtArtist) = "" Or Trim(txtAlbum) = "" Then
        MsgBox "You cannot have an empty Artist or Album Field."
        txtArtist.SetFocus
        Exit Sub
    End If
    AlbumTable("artist") = txtArtist
    AlbumTable("Album") = txtAlbum
    AlbumTable("Release Date") = txtRelease
    AlbumTable("Medium") = med
    AlbumTable.Update
    Refresh_Display
    cmdSave.Visible = False
    cmdCancel.Visible = False
    cmdAdd.Enabled = True
    cmdDelete.Enabled = True
    cmdExit.Enabled = True
    cmdNext.Enabled = True
    cmdPrevious.Enabled = True
End Sub

Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
    If KeyCode = 34 Then
        cmdNext_Click
    End If
    If KeyCode = 33 Then
        cmdPrevious_Click
    End If
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
If KeyAscii = 13 Then
    KeyAscii = 0
End If
End Sub


Sub Form_Load()
    #If Win16 Then
        Path = "D:\tom'sp~1\albums"
    #ElseIf Win32 Then
        Path = "D:\Tom's Projects\Albums"
    #End If
    Set Database = OpenDatabase(Path, False, False, "FoxPro 2.6;")
    Set AlbumTable = Database.OpenRecordset("albums.dbf")
    AlbumTable.Index = "Artist"
    Refresh_Display
End Sub



Private Sub Refresh_Display()
    txtArtist = AlbumTable!ARTIST
    txtAlbum = AlbumTable!ALBUM
    If IsNull(AlbumTable!RELEASE_DA) Then
        txtRelease = "???"
    Else
        txtRelease = AlbumTable!RELEASE_DA
    End If
    med = AlbumTable!MEDIUM
    If med = True Then
        optCD = True
        optCassette = False
    Else
        optCassette = True
        optCD = False
    End If
End Sub




