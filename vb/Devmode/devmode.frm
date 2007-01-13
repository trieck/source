VERSION 5.00
Begin VB.Form frmDevMode 
   BackColor       =   &H8000000C&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "DevMode"
   ClientHeight    =   5865
   ClientLeft      =   1545
   ClientTop       =   1350
   ClientWidth     =   9705
   ClipControls    =   0   'False
   Icon            =   "devmode.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5865
   ScaleWidth      =   9705
   Begin VB.ComboBox cboPrinters 
      BackColor       =   &H80000018&
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   120
      Style           =   2  'Dropdown List
      TabIndex        =   2
      Top             =   120
      Width           =   9375
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   8160
      TabIndex        =   1
      Top             =   5400
      Width           =   1335
   End
   Begin VB.CommandButton cmdGetDevMode 
      Caption         =   "&Get DevMode"
      Height          =   375
      Left            =   6720
      TabIndex        =   0
      Top             =   5400
      Width           =   1335
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   0
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   4
      Top             =   600
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   1
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   6
      Top             =   960
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   2
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   8
      Top             =   1320
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   3
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   16
      Top             =   1680
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   4
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   17
      Top             =   2040
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   5
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   18
      Top             =   2400
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   6
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   19
      Top             =   2760
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   7
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   20
      Top             =   3120
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   8
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   21
      Top             =   3480
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   9
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   22
      Top             =   3840
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   13
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   23
      Top             =   600
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   14
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   24
      Top             =   960
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   15
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   25
      Top             =   1320
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   16
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   26
      Top             =   1680
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   17
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   27
      Top             =   2040
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   18
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   28
      Top             =   2400
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   19
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   29
      Top             =   2760
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   20
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   37
      Top             =   3120
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   21
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   38
      Top             =   3480
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   22
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   39
      Top             =   3840
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   23
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   40
      Top             =   4200
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   24
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   41
      Top             =   4560
      Width           =   3375
      Begin VB.PictureBox sspDevMode 
         Height          =   255
         Index           =   28
         Left            =   0
         ScaleHeight     =   195
         ScaleWidth      =   3315
         TabIndex        =   42
         Top             =   600
         Width           =   3375
      End
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   25
      Left            =   6120
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   43
      Top             =   4920
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   10
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   44
      Top             =   4200
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   11
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   45
      Top             =   4560
      Width           =   3375
   End
   Begin VB.PictureBox sspDevMode 
      Height          =   255
      Index           =   12
      Left            =   1440
      ScaleHeight     =   195
      ScaleWidth      =   3315
      TabIndex        =   46
      Top             =   4920
      Width           =   3375
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Display Freq:"
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
      Index           =   25
      Left            =   4920
      TabIndex        =   55
      Top             =   4920
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Display Flags:"
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
      Index           =   24
      Left            =   4920
      TabIndex        =   54
      Top             =   4560
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Pels Height:"
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
      Index           =   23
      Left            =   4920
      TabIndex        =   53
      Top             =   4200
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Pels Width:"
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
      Index           =   22
      Left            =   4920
      TabIndex        =   52
      Top             =   3840
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Bits Per Pel:"
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
      Index           =   21
      Left            =   4920
      TabIndex        =   51
      Top             =   3480
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Unused Pad:"
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
      Index           =   20
      Left            =   4920
      TabIndex        =   50
      Top             =   3120
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Scale:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   10
      Left            =   240
      TabIndex        =   49
      Top             =   4200
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Copies:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   11
      Left            =   240
      TabIndex        =   48
      Top             =   4560
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Default Source:"
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
      Index           =   12
      Left            =   0
      TabIndex        =   47
      Top             =   4920
      Width           =   1335
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Form Name:"
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
      Index           =   19
      Left            =   4920
      TabIndex        =   36
      Top             =   2760
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Collate:"
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
      Index           =   18
      Left            =   4920
      TabIndex        =   35
      Top             =   2400
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "TTOption:"
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
      Index           =   17
      Left            =   4920
      TabIndex        =   34
      Top             =   2040
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Y Resolution:"
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
      Index           =   16
      Left            =   4920
      TabIndex        =   33
      Top             =   1680
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Duplex:"
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
      Index           =   15
      Left            =   4920
      TabIndex        =   32
      Top             =   1320
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Color:"
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
      Index           =   14
      Left            =   4920
      TabIndex        =   31
      Top             =   960
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Print Quality:"
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
      Index           =   13
      Left            =   4920
      TabIndex        =   30
      Top             =   600
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Paper Width:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   9
      Left            =   240
      TabIndex        =   15
      Top             =   3840
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Paper Length:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   8
      Left            =   240
      TabIndex        =   14
      Top             =   3480
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Paper Size:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   7
      Left            =   240
      TabIndex        =   13
      Top             =   3120
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Orientation:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   6
      Left            =   240
      TabIndex        =   12
      Top             =   2760
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Fields:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   5
      Left            =   240
      TabIndex        =   11
      Top             =   2400
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Driver Extra:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   4
      Left            =   240
      TabIndex        =   10
      Top             =   2040
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Size:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   3
      Left            =   240
      TabIndex        =   9
      Top             =   1680
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Driver Version:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   2
      Left            =   240
      TabIndex        =   7
      Top             =   1320
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Spec Version:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   1
      Left            =   240
      TabIndex        =   5
      Top             =   960
      Width           =   1095
   End
   Begin VB.Label lblDevMode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FF8080&
      BackStyle       =   0  'Transparent
      Caption         =   "Device Name:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   240
      TabIndex        =   3
      Top             =   600
      Width           =   1095
   End
End
Attribute VB_Name = "frmDevMode"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False



Private Function GetDevMode(Printer$) As DEVMODE
    Dim prt As Printer
    Dim pDefault As PRINTER_DEFAULTS
    Dim phPrinter As Long
    Dim bufSize As Long
    Dim dmOut As DEVMODE
    Dim hMem&
        
    On Error GoTo okError
        
    ' Set Printer
    If (Printer$ <> "") Then
        pDefault.pDatatype = vbNullString
        pDefault.pDevMode = 0&
        pDefault.DesiredAccess = PRINTER_ACCESS_USE
        
        Call OpenPrinter(Printer$, phPrinter&, pDefault)
        
        bufSize = DocumentProperties(Me.hWnd, phPrinter, Printer$, 0, 0, 0)
               
        hMem& = GlobalAlloc(GMEM_FIXED Or GMEM_DISCARDABLE, bufSize)
        If (hMem& <> 0) Then
            Call DocumentProperties(Me.hWnd, phPrinter&, Printer$, hMem&, 0&, DM_OUT_BUFFER)
            Call agCopyData(ByVal hMem&, dmOut, Len(dmOut))
            Call GlobalFree(hMem&)
        End If
        
        Call ClosePrinter(phPrinter&)
    End If
    GetDevMode = dmOut
    Exit Function
okError:
    Screen.MousePointer = vbDefault
    MsgBox Error$, vbInformation, App.Title
End Function




Private Sub ShowDevMode(dmOut As DEVMODE)
    sspDevMode(0).Caption = agGetStringFromLPSTR(dmOut.dmDeviceName)
    sspDevMode(1).Caption = dmOut.dmSpecVersion
    sspDevMode(2).Caption = dmOut.dmDriverVersion
    sspDevMode(3).Caption = dmOut.dmSize
    sspDevMode(4).Caption = dmOut.dmDriverExtra
    sspDevMode(5).Caption = dmOut.dmFields
    sspDevMode(6).Caption = dmOut.dmOrientation
    sspDevMode(7).Caption = dmOut.dmPaperSize
    sspDevMode(8).Caption = dmOut.dmPaperLength
    sspDevMode(9).Caption = dmOut.dmPaperWidth
    sspDevMode(10).Caption = dmOut.dmScale
    sspDevMode(11).Caption = dmOut.dmCopies
    sspDevMode(12).Caption = dmOut.dmDefaultSource
    sspDevMode(13).Caption = dmOut.dmPrintQuality
    sspDevMode(14).Caption = dmOut.dmColor
    sspDevMode(15).Caption = dmOut.dmDuplex
    sspDevMode(16).Caption = dmOut.dmYResolution
    sspDevMode(17).Caption = dmOut.dmTTOption
    sspDevMode(18).Caption = dmOut.dmCollate
    sspDevMode(19).Caption = agGetStringFromLPSTR(dmOut.dmFormName)
    sspDevMode(20).Caption = dmOut.dmUnusedPadding
    sspDevMode(21).Caption = dmOut.dmBitsPerPel
    sspDevMode(22).Caption = dmOut.dmPelsWidth
    sspDevMode(23).Caption = dmOut.dmPelsHeight
    sspDevMode(24).Caption = dmOut.dmDisplayFlags
    sspDevMode(25).Caption = dmOut.dmDisplayFrequency
        
    
    
    
End Sub


Private Sub cboPrinters_Click()
    Dim i As Integer
    
    For i = 0 To 25
        sspDevMode(i).Caption = ""
    Next i
    
End Sub


Private Sub cmdExit_Click()
    Unload Me
End Sub


Private Sub cmdGetDevMode_Click()
    Dim dm As DEVMODE
    
    If (cboPrinters.ListIndex > -1) Then
        dm = GetDevMode(cboPrinters.List(cboPrinters.ListIndex))
        Call ShowDevMode(dm)
    End If
End Sub


Private Sub Form_Load()
    Dim c As Collection
    Dim sp As New dwSpool
    Dim obj As Object
    
    Set c = sp.EnumPrinters(PRINTER_ENUM_LOCAL, "", 1)
    For Each obj In c
        cboPrinters.AddItem obj.pName
    Next
End Sub


