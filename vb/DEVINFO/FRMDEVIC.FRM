VERSION 5.00
Begin VB.Form frmDeviceInfo 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Device Information"
   ClientHeight    =   3780
   ClientLeft      =   2895
   ClientTop       =   1815
   ClientWidth     =   4995
   ForeColor       =   &H00404040&
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3780
   ScaleWidth      =   4995
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   495
      Left            =   3720
      TabIndex        =   2
      Top             =   3240
      Width           =   1215
   End
   Begin VB.CommandButton cmdPrinterInfo 
      Caption         =   "&Printer"
      Height          =   735
      Left            =   3720
      TabIndex        =   1
      Top             =   960
      Width           =   1215
   End
   Begin VB.CommandButton cmdVideoInfo 
      Caption         =   "&Video"
      Height          =   735
      Left            =   3720
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label lblNumberColorsOutput 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
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
      Left            =   2280
      TabIndex        =   10
      Top             =   2160
      Width           =   1215
   End
   Begin VB.Label lblNumberColors 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00C0C0C0&
      BackStyle       =   0  'Transparent
      Caption         =   "Colort Table Entries:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   720
      TabIndex        =   9
      Top             =   2160
      Width           =   1455
   End
   Begin VB.Label lblBitsPerPixelOutput 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
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
      Left            =   2280
      TabIndex        =   8
      Top             =   1560
      Width           =   1215
   End
   Begin VB.Label lblDimPxl 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00C0C0C0&
      BackStyle       =   0  'Transparent
      Caption         =   "X,Y Dimensions in Pixels:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   360
      Width           =   2055
   End
   Begin VB.Label lblBitsPerPixel 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00C0C0C0&
      BackStyle       =   0  'Transparent
      Caption         =   "Bits Per Pixel:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   1080
      TabIndex        =   6
      Top             =   1560
      Width           =   1095
   End
   Begin VB.Label lblPixelsPerInchOutput 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
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
      Left            =   2280
      TabIndex        =   5
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label lblPixelsPerInch 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00C0C0C0&
      BackStyle       =   0  'Transparent
      Caption         =   "X,Y Pixels Per Logical Inch:"
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   960
      Width           =   2055
   End
   Begin VB.Label lblDimPxlOutput 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
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
      Left            =   2280
      TabIndex        =   3
      Top             =   360
      Width           =   1215
   End
End
Attribute VB_Name = "frmDeviceInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Sub LoadInfo(hdc&)
    #If Win32 Then
        Dim r As Long, DimHorz As Long, _
            DimVert As Long, LogPixX As Long, _
            LogPixY As Long
    #Else
        Dim r As Integer, DimHorz As Integer, _
            DimVert As Integer, LogPixX As Integer, _
            LogPixY As Integer
    #End If
        
    r = GetDeviceCaps(hdc&, TECHNOLOGY)
    DimHorz = GetDeviceCaps(hdc&, HORZRES)
    DimVert = GetDeviceCaps(hdc&, VERTRES)
    lblDimPxlOutput.Caption = Str$(DimHorz) & _
        ", " & Str$(DimVert)
    LogPixX = GetDeviceCaps(hdc&, LOGPIXELSX)
    LogPixY = GetDeviceCaps(hdc&, LOGPIXELSY)
    lblPixelsPerInchOutput.Caption = Str$(LogPixX) & _
        ", " & Str$(LogPixY)
    lblBitsPerPixelOutput.Caption = Str$(GetDeviceCaps( _
        hdc&, BITSPIXEL))
    lblNumberColorsOutput.Caption = Str$(GetDeviceCaps( _
        hdc&, NUMCOLORS))
End Sub

Private Sub cmdExit_Click()
    End
End Sub

Private Sub cmdPrinterInfo_Click()
    LoadInfo Printer.hdc
    cmdPrinterInfo.FontBold = True
    cmdVideoInfo.FontBold = False
End Sub


Private Sub cmdVideoInfo_Click()
    LoadInfo Me.hdc
    cmdPrinterInfo.FontBold = False
    cmdVideoInfo.FontBold = True
End Sub


Private Sub Form_Load()
    Me.BackColor = GetSysColor(COLOR_BACKGROUND)
End Sub


