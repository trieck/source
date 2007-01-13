VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "threed32.ocx"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.Form frmPhoneBook2 
   BackColor       =   &H00808000&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Tom's Phone Book"
   ClientHeight    =   4275
   ClientLeft      =   795
   ClientTop       =   2145
   ClientWidth     =   7830
   ForeColor       =   &H00000000&
   Icon            =   "PhoneBook2.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4275
   ScaleWidth      =   7830
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "Z"
      Height          =   375
      Index           =   25
      Left            =   7320
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   39
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "Y"
      Height          =   375
      Index           =   24
      Left            =   6960
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   38
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "X"
      Height          =   375
      Index           =   23
      Left            =   6600
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   37
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "W"
      Height          =   375
      Index           =   22
      Left            =   6240
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   36
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "V"
      Height          =   375
      Index           =   21
      Left            =   5880
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   35
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "U"
      Height          =   375
      Index           =   20
      Left            =   5520
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   34
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "T"
      Height          =   375
      Index           =   19
      Left            =   5160
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   33
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "S"
      Height          =   375
      Index           =   18
      Left            =   4800
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   32
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "R"
      Height          =   375
      Index           =   17
      Left            =   4440
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   31
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "Q"
      Height          =   375
      Index           =   16
      Left            =   4080
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   30
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "P"
      Height          =   375
      Index           =   15
      Left            =   3720
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   29
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "O"
      Height          =   375
      Index           =   14
      Left            =   3360
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   28
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "N"
      Height          =   375
      Index           =   13
      Left            =   3000
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   27
      Top             =   360
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "M"
      Height          =   375
      Index           =   12
      Left            =   7320
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   26
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "L"
      Height          =   375
      Index           =   11
      Left            =   6960
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   25
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "K"
      Height          =   375
      Index           =   10
      Left            =   6600
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   24
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "J"
      Height          =   375
      Index           =   9
      Left            =   6240
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   23
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "I"
      Height          =   375
      Index           =   8
      Left            =   5880
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   22
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "H"
      Height          =   375
      Index           =   7
      Left            =   5520
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   21
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "G"
      Height          =   375
      Index           =   6
      Left            =   5160
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   20
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "F"
      Height          =   375
      Index           =   5
      Left            =   4800
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   19
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "E"
      Height          =   375
      Index           =   4
      Left            =   4440
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   18
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "D"
      Height          =   375
      Index           =   3
      Left            =   4080
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   17
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "C"
      Height          =   375
      Index           =   2
      Left            =   3720
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   16
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "B"
      Height          =   375
      Index           =   1
      Left            =   3360
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   15
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      BackColor       =   &H00808000&
      Caption         =   "A"
      Height          =   375
      Index           =   0
      Left            =   3000
      MaskColor       =   &H00FFFFC0&
      TabIndex        =   14
      Top             =   0
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Index           =   5
      Left            =   4800
      TabIndex        =   5
      Top             =   3570
      Width           =   2895
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Index           =   3
      Left            =   4800
      TabIndex        =   3
      Top             =   2610
      Width           =   1455
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Index           =   2
      Left            =   4800
      TabIndex        =   2
      Top             =   2130
      Width           =   570
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Index           =   1
      Left            =   4800
      TabIndex        =   1
      Top             =   1650
      Width           =   2895
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Index           =   0
      Left            =   4800
      MultiLine       =   -1  'True
      TabIndex        =   0
      Top             =   840
      Width           =   2895
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Index           =   4
      Left            =   4800
      TabIndex        =   4
      Top             =   3090
      Width           =   2895
   End
   Begin VB.ListBox lstOutputWindow 
      BackColor       =   &H00C0FFFF&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2790
      ItemData        =   "PhoneBook2.frx":0442
      Left            =   120
      List            =   "PhoneBook2.frx":0444
      TabIndex        =   6
      Top             =   840
      Width           =   2895
   End
   Begin Threed.SSPanel pnlToolbar 
      Height          =   735
      Left            =   0
      TabIndex        =   40
      Top             =   0
      Width           =   3015
      _Version        =   65536
      _ExtentX        =   5318
      _ExtentY        =   1296
      _StockProps     =   15
      BackColor       =   -2147483633
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelOuter      =   0
      RoundedCorners  =   0   'False
      Begin Threed.SSCommand cmdToolbar 
         Height          =   570
         Index           =   0
         Left            =   0
         TabIndex        =   45
         Tag             =   "New"
         Top             =   0
         Width           =   570
         _Version        =   65536
         _ExtentX        =   1005
         _ExtentY        =   1005
         _StockProps     =   78
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         RoundedCorners  =   0   'False
         Outline         =   0   'False
         MouseIcon       =   "PhoneBook2.frx":0446
         Picture         =   "PhoneBook2.frx":0462
      End
      Begin Threed.SSCommand cmdToolbar 
         Height          =   570
         Index           =   1
         Left            =   600
         TabIndex        =   44
         Tag             =   "Delete"
         Top             =   0
         Width           =   570
         _Version        =   65536
         _ExtentX        =   1005
         _ExtentY        =   1005
         _StockProps     =   78
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         RoundedCorners  =   0   'False
         Outline         =   0   'False
         MouseIcon       =   "PhoneBook2.frx":08B4
         Picture         =   "PhoneBook2.frx":08D0
      End
      Begin Threed.SSCommand cmdToolbar 
         Height          =   600
         Index           =   4
         Left            =   2400
         TabIndex        =   43
         Tag             =   "ExitProgram"
         Top             =   0
         Width           =   600
         _Version        =   65536
         _ExtentX        =   1058
         _ExtentY        =   1058
         _StockProps     =   78
         ForeColor       =   8421376
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         RoundedCorners  =   0   'False
         Outline         =   0   'False
         AutoSize        =   2
         MouseIcon       =   "PhoneBook2.frx":0BEA
         Picture         =   "PhoneBook2.frx":0C06
      End
      Begin Threed.SSCommand cmdToolbar 
         Height          =   570
         Index           =   3
         Left            =   1200
         TabIndex        =   42
         Tag             =   "Dial"
         Top             =   0
         Width           =   570
         _Version        =   65536
         _ExtentX        =   1005
         _ExtentY        =   1005
         _StockProps     =   78
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         RoundedCorners  =   0   'False
         Outline         =   0   'False
         MouseIcon       =   "PhoneBook2.frx":1910
         Picture         =   "PhoneBook2.frx":192C
      End
      Begin Threed.SSCommand cmdToolbar 
         Height          =   570
         Index           =   2
         Left            =   1800
         TabIndex        =   41
         Tag             =   "Save"
         Top             =   0
         Width           =   570
         _Version        =   65536
         _ExtentX        =   1005
         _ExtentY        =   1005
         _StockProps     =   78
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         RoundedCorners  =   0   'False
         Outline         =   0   'False
         MouseIcon       =   "PhoneBook2.frx":1D7E
         Picture         =   "PhoneBook2.frx":1D9A
      End
   End
   Begin ComctlLib.StatusBar sbrOutputBar 
      Align           =   2  'Align Bottom
      Height          =   300
      Left            =   0
      TabIndex        =   13
      Top             =   3975
      Width           =   7830
      _ExtentX        =   13811
      _ExtentY        =   529
      SimpleText      =   ""
      _Version        =   327680
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   3
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Alignment       =   1
            AutoSize        =   2
            Object.Width           =   265
            MinWidth        =   176
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Alignment       =   1
            AutoSize        =   2
            Object.Width           =   265
            MinWidth        =   176
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Alignment       =   1
            AutoSize        =   2
            Object.Width           =   265
            MinWidth        =   176
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      MouseIcon       =   "PhoneBook2.frx":21EC
   End
   Begin VB.Label lblBusPhone 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "Business Phone:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C0FFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   8
      Top             =   3600
      Width           =   1575
   End
   Begin VB.Label lblAddress 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "Address:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C0FFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   12
      Top             =   840
      Width           =   1575
   End
   Begin VB.Label lblCity 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "City:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C0FFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   11
      Top             =   1680
      Width           =   1575
   End
   Begin VB.Label lblState 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "State:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C0FFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   10
      Top             =   2160
      Width           =   1575
   End
   Begin VB.Label lblZipCode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "Zip Code:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C0FFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   9
      Top             =   2640
      Width           =   1575
   End
   Begin VB.Label lblHomePhone 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "Home Phone:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C0FFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   7
      Top             =   3120
      Width           =   1575
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuExit 
         Caption         =   "&Exit"
      End
   End
   Begin VB.Menu mnuData 
      Caption         =   "&Data"
      Begin VB.Menu mnuAddRecord 
         Caption         =   "&Add a New Record"
      End
      Begin VB.Menu mnuDeleteRecord 
         Caption         =   "&Delete Current Record"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuSaveRecord 
         Caption         =   "&Save Current Record"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuTools 
      Caption         =   "&Tools"
      Begin VB.Menu mnuDialRecord 
         Caption         =   "Dia&l Current Record"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "&About"
      End
   End
End
Attribute VB_Name = "frmPhoneBook2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim PhoneRS As Recordset, ReturnRS As Recordset
Dim LetterQuery As QueryDef, FullNameQuery As QueryDef _
    , HalfNameQuery As QueryDef
Dim MyIndex() As IndexType
Dim LetterSQL As String, FullNameSQL As String _
    , NewLast As String, NewFirst As String _
    , NDXNum As Integer, MyID As Integer _
    , CurrentListIndex As Integer _
    , DirtyFlags As Boolean


    Private Sub Show_Record()
        Dim VarIndex(5), i As Integer
        VarIndex(0) = ReturnRS("HOME_STREET")
        VarIndex(1) = ReturnRS("HOME_CITY")
        VarIndex(2) = ReturnRS("HOME_STATE")
        VarIndex(3) = ReturnRS("HOME_POSTAL")
        VarIndex(4) = ReturnRS("HOME_PHONE")
        VarIndex(5) = ReturnRS("BUSINESS_PHONE")
        For i = 0 To 5
            If IsNull(VarIndex(i)) Then
                VarIndex(i) = ""
            End If
            txtOutput(i).Enabled = True
            txtOutput(i).Text = VarIndex(i)
        Next
        txtOutput(0).SetFocus
    End Sub

Private Sub cmdLetter_Click(Index As Integer)
    Dim SearchString As String, MyPanel As Panel
    Dim i As Integer, j As Integer
    
    frmPhoneBook2.MousePointer = 11 'Show Hourglass
    
    NDXNum = Index 'No Bold on all buttons
        For i = 0 To 25
            cmdLetter(i).FontBold = False
        Next i
        For j = 0 To 5 'Clear Text Boxes
            txtOutput(j).Text = ""
        Next j
    For Each MyPanel In sbrOutputBar.Panels 'Clear Status
        MyPanel.Text = ""
    Next MyPanel
    
    SearchString = Chr$(65 + Index) + "*" 'Base Query on a function of the index
    LetterQuery.Parameters![Letter Wanted] = SearchString
    Set ReturnRS = LetterQuery.OpenRecordset() 'Get Return Set
    Show_Output
    cmdLetter(Index).FontBold = True 'Bold the active button
    mnuDeleteRecord.Enabled = False
    mnuDialRecord.Enabled = False
    cmdToolbar(1).Enabled = False   'No Delete
    cmdToolbar(3).Enabled = False   'No Dial
    frmPhoneBook2.MousePointer = 0 'Back to Default pointer
End Sub

Private Sub cmdToolbar_Click(Index As Integer)
    Select Case Index
        Case 0      ' Add
            mnuAddRecord_Click
        Case 1      ' Delete
            mnuDeleteRecord_Click
        Case 2      ' Save
            mnuSaveRecord_Click
        Case 3      ' Dial
            mnuDialRecord_Click
        Case 4      ' Exit
            mnuExit_Click
    End Select
    
End Sub

Private Sub Form_Load()
    On Error GoTo flError
    
    Me.MousePointer = 11
    Set PhoneDB = OpenDatabase("c:\My Documents\Tom's Database", True, False)
    Set LetterQuery = PhoneDB.QueryDefs("Letter Query")
    Set FullNameQuery = PhoneDB.QueryDefs("FullName Query")
    Set HalfNameQuery = PhoneDB.QueryDefs("HalfName Query")
    DirtyFlags = False
    Me.MousePointer = 0
    
    Exit Sub
flError:
    Me.MousePointer = 0
    MsgBox Error$, vbInformation, App.Title
    End
End Sub




Private Sub Show_Output()
    Dim TotalRec As Integer, RecText As String, i As Integer
    
    TotalRec = 0
    lstOutputWindow.Clear
    For i = 0 To 5
        txtOutput(i).Enabled = False
    Next i
    Do Until ReturnRS.EOF
        ReDim Preserve MyIndex(TotalRec)
        MyIndex(TotalRec).LastName = ReturnRS("LAST_NAME")
        MyIndex(TotalRec).FirstName = ReturnRS("FIRST_NAME")
        If MyIndex(TotalRec).FirstName <> "" Then
            lstOutputWindow.AddItem MyIndex(TotalRec).LastName + ", " + MyIndex(TotalRec).FirstName
        Else
            lstOutputWindow.AddItem MyIndex(TotalRec).LastName
        End If
        ReturnRS.MoveNext
        TotalRec = TotalRec + 1
    Loop
    If TotalRec <> 1 Then
        RecText = " Records"
    Else
        RecText = " Record"
    End If
    lstOutputWindow.SetFocus
    sbrOutputBar.Panels(3).Text = Str$(TotalRec) + RecText
End Sub


Private Sub lstOutputWindow_Click()
    Dim CurrRec As Integer, NLast As String, NFirst As String, _
        i As Integer
    
    On Error GoTo Errhandler
    
    If Not DirtyFlags Then
        CurrRec = lstOutputWindow.ListIndex 'Set Record# = ListIndex Property
    Else
        CurrRec = CurrentListIndex 'Set Record# = Last Record Selected
    End If
    NLast = MyIndex(CurrRec).LastName
    If IsNull(MyIndex(CurrRec).FirstName) Or _
    MyIndex(CurrRec).FirstName = "" Then  'No first Name (for Companies)
        NFirst = ""
        HalfNameQuery.Parameters![LastName Wanted] = NLast
        Set ReturnRS = HalfNameQuery.OpenRecordset()
    Else
        NFirst = MyIndex(CurrRec).FirstName 'Full Name
        FullNameQuery.Parameters![LastName Wanted] = NLast
        FullNameQuery.Parameters![FirstName Wanted] = NFirst
        Set ReturnRS = FullNameQuery.OpenRecordset()
    End If
    MyID = ReturnRS("ID")
    If ReturnRS.RecordCount > 0 Then
        Show_Record
    Else
        MsgBox "No Record Found."
        Exit Sub
    End If
    mnuDeleteRecord.Enabled = True
    mnuDialRecord.Enabled = True
    cmdToolbar(1).Enabled = True 'Enable Delete
    cmdToolbar(3).Enabled = True 'Enable Dialing
    sbrOutputBar.Panels(1).Text = Str$(CurrRec + 1)
    sbrOutputBar.Panels(2).Text = "of"
    Exit Sub
Errhandler:
    MsgBox "Error Accessing this Record.", vbOKOnly, "Error#" + Str$(Err)
    For i = 0 To 5
        txtOutput(i).Text = ""
    Next i
End Sub








Private Sub mnuAbout_Click()
    Load frmAbout
    frmAbout.Show vbModal 'vbModal for OLE Servers always
End Sub

Private Sub mnuAddRecord_Click()
    Dim i As Integer, j As Integer, MyPanel As Panel
    
    NewLast = InputBox("Enter a Last Name:", "Add a Record")
    NewLast = Trim(NewLast)
        If NewLast <> "" Then
            NewFirst = InputBox("Enter a First Name:", "Add a Record")
            NewFirst = Trim(NewFirst)
        Else
           lstOutputWindow.SetFocus
           Exit Sub
        End If
    For i = 0 To 25 'Turn off buttons when you add
        cmdLetter(i).FontBold = False
        cmdLetter(i).Enabled = False
        
    Next
    For j = 0 To 5  'And clear Text for new entry
        txtOutput(j).Text = ""
    Next j
    For Each MyPanel In sbrOutputBar.Panels 'And also clear status bar
        MyPanel.Text = ""
    Next MyPanel
    lstOutputWindow.Clear
    If NewFirst <> "" Then
        lstOutputWindow.AddItem NewLast + ", " + NewFirst
    Else
        lstOutputWindow.AddItem NewLast + ""
    End If
    lstOutputWindow.Enabled = False 'Disable the list so user can't type in it
    cmdToolbar(0).Enabled = False   'No New
    cmdToolbar(1).Enabled = False   'No Delete
    cmdToolbar(2).Enabled = True    'Enable Save
    cmdToolbar(3).Enabled = False   'No Dial
    mnuAddRecord.Enabled = False
    mnuDeleteRecord.Enabled = False 'No Delete
    mnuSaveRecord.Enabled = True    'Enable Save
    mnuDialRecord.Enabled = False   'No Dial
    For i = 0 To 5
        txtOutput(i).Enabled = True
    Next i
    txtOutput(0).SetFocus
    NewLast = Chr(34) + NewLast + Chr(34)
    NewFirst = Chr(34) + NewFirst + Chr(34)
    txtOutput(0).SetFocus
End Sub

Private Sub mnuDeleteRecord_Click()
    Dim Reply As Integer
    If Not IsNull(MyIndex(lstOutputWindow.ListIndex).FirstName) Then
        Reply = MsgBox("Are you sure you want to delete" + Chr(13) _
            + MyIndex(lstOutputWindow.ListIndex).FirstName + Chr(32) _
            + MyIndex(lstOutputWindow.ListIndex).LastName + "?", vbQuestion _
            + vbYesNo, "Delete Record")
    Else
        Reply = MsgBox("Are you sure you want to delete" + Chr(13) _
            + MyIndex(lstOutputWindow.ListIndex).LastName _
            + "?", vbQuestion + vbYesNo, "Delete Record")
    End If
    If Reply <> 7 Then
        ReturnRS.Delete
        cmdLetter_Click (NDXNum)
    End If
    lstOutputWindow.SetFocus
End Sub


Private Sub mnuDialRecord_Click()
    ' Dial the current selected record
    frmDialingOptions.Show 1
    lstOutputWindow.SetFocus
End Sub

Private Sub mnuExit_Click()
    Unload frmPhoneBook2
End Sub


Private Sub SaveNewRecord()
    Dim NameString As String, OutputString As String, i As Integer _
        , MidString As String, IndexNum As Integer
        
    On Error GoTo SaveErrHandler
    NameString = "INSERT INTO Names (LAST_NAME, FIRST_NAME, HOME_STREET, HOME_CITY, HOME_STATE, HOME_POSTAL, HOME_PHONE, BUSINESS_PHONE) VALUES "
    NameString = NameString + "(" + NewLast + ", " + NewFirst + ", "
        For i = 0 To 5
            If i < 5 Then
                OutputString = OutputString + Chr(34) + Trim(txtOutput(i).Text) + Chr(34) + ", "
            Else
                OutputString = OutputString + Chr(34) + Trim(txtOutput(i).Text) + Chr(34)
            End If
        Next i
    NameString = NameString + OutputString + ");"
    PhoneDB.Execute NameString, dbFailOnError
    For i = 0 To 25 'Enable buttons after save
        cmdLetter(i).Enabled = True
    Next
    lstOutputWindow.Enabled = True
    cmdToolbar(0).Enabled = True    'Enable New
    cmdToolbar(1).Enabled = True    'Enable Delete
    cmdToolbar(2).Enabled = False   'Disable Save
    cmdToolbar(3).Enabled = True    'Enable Dial
    mnuAddRecord.Enabled = True     'Enable New
    mnuDeleteRecord.Enabled = True  'Enable Delete
    mnuSaveRecord.Enabled = False   'Disable Save
    mnuDialRecord.Enabled = True    'Enable Dial
    For i = 0 To 5
        txtOutput(i).Enabled = False
    Next i
    MidString = Mid(NewLast, 2, 1)
    IndexNum = Asc(UCase(MidString)) - 65 'Get The index Number of the key that matches LastName
    cmdLetter_Click (IndexNum) 'Hit it
    lstOutputWindow.SetFocus
    Exit Sub
SaveErrHandler:
    MsgBox "There was an error writing to Tom's Database"
    lstOutputWindow.SetFocus
    Exit Sub
End Sub






Private Sub mnuSaveRecord_Click()
    ' Save Current and New Records
    ' If this button is selected during
    ' an update, the lost focus event
    ' for the edit controls will take
    ' care of the update, and this control
    ' will mask that work
    
    If lstOutputWindow.Enabled = False Then
        SaveNewRecord
    Else
        lstOutputWindow.SetFocus
    End If
End Sub

Private Sub txtOutput_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
    If lstOutputWindow.ListIndex >= 0 And lstOutputWindow.Enabled Then
        DirtyFlags = True
        mnuSaveRecord.Enabled = True    'Enable saving
        cmdToolbar(2).Enabled = True
        CurrentListIndex = lstOutputWindow.ListIndex
    End If
End Sub


Private Sub txtOutput_LostFocus(Index As Integer)
    Dim Reply As Integer, NLast As String, NFirst As String _
        , i As Integer, MyButton As Button _
        , k As Integer, btnIndex%
        
    On Error GoTo Errhandler
    
    'Allow LostFocus between members of Control Array
    If TypeOf Screen.ActiveControl Is TextBox Then
        Exit Sub
    End If
    
    If DirtyFlags Then 'Check for Edit Mode
    'Jump to Save Routine if that is selected button
    If Screen.ActiveControl.Tag = "Save" Then GoTo DoSave
    
        NLast = MyIndex(CurrentListIndex).LastName
        If Not IsNull(MyIndex(CurrentListIndex).FirstName) Then
            NFirst = MyIndex(CurrentListIndex).FirstName
            Reply = MsgBox("Do you want to save your changes to" _
            + vbCrLf _
            + NFirst _
             + Chr(32) + NLast _
             + "?", (vbYesNo + vbQuestion + vbDefaultButton1), "Record has changed!")
        Else
            NFirst = ""
            Reply = MsgBox("Do you want to save your changes to" _
            + vbCrLf _
            + NLast _
             + "?", (vbYesNo + vbQuestion + vbDefaultButton1), "Record has changed!")
        End If
        
        If Reply = vbYes Then
        'Define a Recordset to Update Names in the Open Database
DoSave:
            Set PhoneRS = PhoneDB.OpenRecordset("NAMES", dbOpenTable)
            With PhoneRS
                .Index = "PrimaryKey"
                .Seek "=", MyID
                .Edit
                .Fields("HOME_STREET") = Trim(txtOutput(0).Text)
                .Fields("HOME_CITY") = Trim(txtOutput(1).Text)
                .Fields("HOME_STATE") = Trim(txtOutput(2).Text)
                .Fields("HOME_POSTAL") = Trim(txtOutput(3).Text)
                .Fields("HOME_PHONE") = Trim(txtOutput(4).Text)
                .Fields("BUSINESS_PHONE") = Trim(txtOutput(5).Text)
                .Update
            End With
        End If
        DirtyFlags = False
        mnuSaveRecord.Enabled = False   'Disable Saving
        cmdToolbar(2).Enabled = False
    End If
    If TypeOf Screen.ActiveControl Is CommandButton Then
        If Screen.ActiveControl.Name = "cmdLetter" Then
            btnIndex = Screen.ActiveControl.Index
            cmdLetter_Click (btnIndex)
        End If
    ElseIf TypeOf Screen.ActiveControl Is SSCommand Then
        If Screen.ActiveControl.Name = "cmdToolbar" Then
            btnIndex = Screen.ActiveControl.Index
            cmdToolbar_Click (btnIndex)
        End If
    ElseIf TypeOf Screen.ActiveControl Is ListBox Then
        lstOutputWindow_Click
    End If
    Exit Sub
Errhandler:
    MsgBox Error$, 64, "Error #" & Err
End Sub


