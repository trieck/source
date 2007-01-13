VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.MDIForm mdiMain 
   BackColor       =   &H8000000C&
   Caption         =   "Tom's Phone Book"
   ClientHeight    =   4695
   ClientLeft      =   1170
   ClientTop       =   2475
   ClientWidth     =   6675
   Icon            =   "frmMDI.frx":0000
   LinkTopic       =   "MDIForm1"
   Begin ComctlLib.StatusBar sbarMain 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   0
      Top             =   4320
      Width           =   6675
      _ExtentX        =   11774
      _ExtentY        =   661
      Style           =   1
      SimpleText      =   ""
      _Version        =   327680
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Object.Width           =   11351
            TextSave        =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuOptions 
      Caption         =   "&Options"
      Begin VB.Menu mnuAddEntry 
         Caption         =   "Add an entry"
      End
      Begin VB.Menu mnuDeleteEntry 
         Caption         =   "Delete an entry"
      End
      Begin VB.Menu mnuSaveEntry 
         Caption         =   "Save an entry"
      End
      Begin VB.Menu mnuLookup 
         Caption         =   "Lookup"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "About Tom's Phone Book"
      End
   End
End
Attribute VB_Name = "mdiMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub MDIForm_Load()
'   create an instance of the DB object
    Set glbPB = New CPBDB
'   open the database
    glbPB.OpenDB ("c:\My Documents\Tom's Database.mdb")
'   show the options
    frmOptions.Show
    Me.WindowState = vbMaximized
End Sub


Private Sub MDIForm_Unload(Cancel As Integer)
    ' cleanup and exit
    Set glbPB = Nothing
End Sub


