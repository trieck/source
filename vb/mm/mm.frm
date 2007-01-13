VERSION 5.00
Begin VB.Form frmMapModeTest 
   AutoRedraw      =   -1  'True
   Caption         =   "MapMode Test"
   ClientHeight    =   3795
   ClientLeft      =   2250
   ClientTop       =   1815
   ClientWidth     =   5010
   ClipControls    =   0   'False
   BeginProperty Font 
      Name            =   "System"
      Size            =   9.75
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   FontTransparent =   0   'False
   ForeColor       =   &H80000008&
   Icon            =   "mm.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3795
   ScaleWidth      =   5010
   Begin VB.PictureBox pctMain 
      BackColor       =   &H80000005&
      ClipControls    =   0   'False
      FillColor       =   &H80000005&
      FillStyle       =   0  'Solid
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00400000&
      Height          =   3615
      Left            =   120
      ScaleHeight     =   237
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   317
      TabIndex        =   0
      Top             =   120
      Width           =   4815
   End
End
Attribute VB_Name = "frmMapModeTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function SetMapMode Lib "gdi32" (ByVal hdc As Long, ByVal nMapMode As Long) As Long
Private Declare Function SetViewportExtEx Lib "gdi32" (ByVal hdc As Long, ByVal nX As Long, ByVal nY As Long, lpSize As Any) As Long
Private Declare Function SetViewportOrgEx Lib "gdi32" (ByVal hdc As Long, ByVal nX As Long, ByVal nY As Long, lpPoint As Any) As Long
Private Declare Function SetWindowExtEx Lib "gdi32" (ByVal hdc As Long, ByVal nX As Long, ByVal nY As Long, lpSize As Any) As Long
Private Declare Function SetWindowOrgEx Lib "gdi32" (ByVal hdc As Long, ByVal nX As Long, ByVal nY As Long, lpPoint As Any) As Long
Private Declare Function TextOut Lib "gdi32" Alias "TextOutA" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal lpString As String, ByVal nCount As Long) As Long
Private Declare Function GetTextMetrics Lib "gdi32" Alias "GetTextMetricsA" (ByVal hdc As Long, lpMetrics As TEXTMETRIC) As Long
Private Declare Function SelectObject Lib "gdi32" (ByVal hdc As Long, ByVal hObject As Long) As Long
Private Declare Function GetStockObject Lib "gdi32" (ByVal nIndex As Long) As Long
Private Declare Function Ellipse Lib "gdi32" (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long
Private Declare Function InvalidateRect Lib "user32" (ByVal hwnd As Long, lpRect As Any, ByVal bErase As Long) As Long
Private Declare Function UpdateWindow Lib "user32" (ByVal hwnd As Long) As Long
Private Declare Function DPtoLP Lib "gdi32" (ByVal hdc As Long, lpPoint As Any, ByVal nCount As Long) As Long
Private Declare Function RestoreDC Lib "gdi32" (ByVal hdc As Long, ByVal nSavedDC As Long) As Long
Private Declare Function SaveDC Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function Rectangle Lib "gdi32" (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long
Private Declare Function DrawText Lib "user32" Alias "DrawTextA" (ByVal hdc As Long, ByVal lpStr As String, ByVal nCount As Long, lpRect As RECT, ByVal wFormat As Long) As Long
Private Declare Function SetRect Lib "user32" (lpRect As RECT, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long
Private Declare Function InflateRect Lib "user32" (lpRect As RECT, ByVal x As Long, ByVal y As Long) As Long

Private Const SYSTEM_FIXED_FONT = 16
Private Const MM_ANISOTROPIC = 8

' Draw Text Constants
Private Const DT_BOTTOM = &H8
Private Const DT_CALCRECT = &H400
Private Const DT_CENTER = &H1
Private Const DT_CHARSTREAM = 4
Private Const DT_DISPFILE = 6
Private Const DT_EDITCONTROL = &H2000
Private Const DT_END_ELLIPSIS = &H8000
Private Const DT_EXPANDTABS = &H40
Private Const DT_EXTERNALLEADING = &H200
Private Const DT_INTERNAL = &H1000
Private Const DT_LEFT = &H0
Private Const DT_METAFILE = 5
Private Const DT_MODIFYSTRING = &H10000
Private Const DT_NOCLIP = &H100
Private Const DT_NOPREFIX = &H800
Private Const DT_PATH_ELLIPSIS = &H4000
Private Const DT_PLOTTER = 0
Private Const DT_RASCAMERA = 3
Private Const DT_RASDISPLAY = 1
Private Const DT_RASPRINTER = 2
Private Const DT_RIGHT = &H2
Private Const DT_RTLREADING = &H20000
Private Const DT_SINGLELINE = &H20
Private Const DT_TABSTOP = &H80
Private Const DT_TOP = &H0
Private Const DT_VCENTER = &H4
Private Const DT_WORD_ELLIPSIS = &H40000
Private Const DT_WORDBREAK = &H10

Private Type RECT
        Left As Long
        Top As Long
        Right As Long
        Bottom As Long
End Type

Private Type POINTAPI
        x As Long
        y As Long
End Type

Private Type TEXTMETRIC
    tmHeight As Long
    tmAscent As Long
    tmDescent As Long
    tmInternalLeading As Long
    tmExternalLeading As Long
    tmAveCharWidth As Long
    tmMaxCharWidth As Long
    tmWeight As Long
    tmOverhang As Long
    tmDigitizedAspectX As Long
    tmDigitizedAspectY As Long
    tmFirstChar As Byte
    tmLastChar As Byte
    tmDefaultChar As Byte
    tmBreakChar As Byte
    tmItalic As Byte
    tmUnderlined As Byte
    tmStruckOut As Byte
    tmPitchAndFamily As Byte
    tmCharSet As Byte
End Type

Private Const SZ_TEXT = "Four Score and seven years ago." _
                        & "  Our fore-fathers set forth upon this continent" _
                        & " a new nation, conceived in liberty and dedicated" _
                        & " to the proposition that all men were created equal."
                        

Private Sub Form_Initialize()
    Call SetMapMode(pctMain.hdc, MM_ANISOTROPIC)
End Sub

Private Sub Form_Resize()
    pctMain.Left = Me.ScaleLeft
    pctMain.Top = Me.ScaleTop
    
    pctMain.Width = Me.ScaleWidth
    pctMain.Height = Me.ScaleHeight
    
    pctMain.Refresh
    Me.Refresh
End Sub


Private Sub pctMain_Paint()
    Dim pt As POINTAPI
    Dim rc As RECT
    Dim nSavedDC As Integer
        
    nSavedDC = SaveDC(pctMain.hdc)
              
    Call SetWindowExtEx(pctMain.hdc, 640, 480, ByVal 0)
    Call SetViewportExtEx(pctMain.hdc, pctMain.ScaleWidth - 10, pctMain.ScaleHeight - 10, ByVal 0)
    Call SetViewportOrgEx(pctMain.hdc, 5, 5, ByVal 0)
    
    Call SetRect(rc, 0, 0, 640, 480)
        
    Call Rectangle(pctMain.hdc, rc.Left, rc.Top, rc.Right, rc.Bottom)
        
    Call DrawText(pctMain.hdc, SZ_TEXT, -1, rc, DT_LEFT Or DT_WORDBREAK)
    
    Call RestoreDC(pctMain.hdc, nSavedDC)
End Sub


