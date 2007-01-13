VERSION 5.00
Begin VB.Form frmMFTest 
   Appearance      =   0  'Flat
   AutoRedraw      =   -1  'True
   Caption         =   "Metafile Test"
   ClientHeight    =   3255
   ClientLeft      =   2325
   ClientTop       =   2430
   ClientWidth     =   4485
   ClipControls    =   0   'False
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "mf.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   217
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   299
   Begin VB.PictureBox pctMain 
      FillColor       =   &H80000012&
      FillStyle       =   0  'Solid
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3015
      Left            =   120
      ScaleHeight     =   197
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   277
      TabIndex        =   0
      Top             =   120
      Width           =   4215
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuCopy 
         Caption         =   "&Copy"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
      End
   End
End
Attribute VB_Name = "frmMFTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Declare Function CreateSolidBrush Lib "gdi32" (ByVal crColor As Long) As Long
Private Declare Function SelectObject Lib "gdi32" (ByVal hdc As Long, ByVal hObject As Long) As Long
Private Declare Function DeleteObject Lib "gdi32" (ByVal hObject As Long) As Long
Private Declare Function FillRect Lib "user32" (ByVal hdc As Long, lpRect As RECT, ByVal hBrush As Long) As Long
Private Declare Function DPtoLP Lib "gdi32" (ByVal hdc As Long, lpPoint As Any, ByVal nCount As Long) As Long
Private Declare Function LPtoDP Lib "gdi32" (ByVal hdc As Long, lpPoint As Any, ByVal nCount As Long) As Long
Private Declare Function Rectangle Lib "gdi32" (ByVal hdc As Long, ByVal x1 As Long, ByVal y1 As Long, ByVal x2 As Long, ByVal y2 As Long) As Long
Private Declare Function Ellipse Lib "gdi32" (ByVal hdc As Long, ByVal x1 As Long, ByVal y1 As Long, ByVal x2 As Long, ByVal y2 As Long) As Long
Private Declare Function GetClientRect Lib "user32" (ByVal hwnd As Long, lpRect As RECT) As Long
Private Declare Function TextOut Lib "gdi32" Alias "TextOutA" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal lpString As String, ByVal nCount As Long) As Long
Private Declare Function CreatePen Lib "gdi32" (ByVal nPenStyle As Long, ByVal nWidth As Long, ByVal crColor As Long) As Long
Private Declare Function GetSysColor Lib "user32" (ByVal nIndex As Long) As Long

Private m_pDC As clsDC
Private m_pmfDC As Long

Private Const COLOR_RED = 1
Private Const COLOR_GREEN = 2
Private Const COLOR_BLUE = 3
Private Const COLOR_PURPLE = 4

Private Const MM_ANISOTROPIC = 8
Private Const MM_ISOTROPIC = 7

Private Const HORZ_EXTENT = 32767
Private Const VERT_EXTENT = 32767

Private Const PS_SOLID = 0
Private Const COLOR_BTNFACE = 15

Private Type POINTAPI
        x As Long
        y As Long
End Type

Private Type RECT
        Left As Long
        Top As Long
        Right As Long
        Bottom As Long
End Type

Private Function DrawRectangle(hdc As Long, lColor As Long, rc As RECT)
    Dim hBrush&, hBrushOld&
    Dim b As Byte
    Dim nHeight As Long, nStart As Long
    Dim lNewColor As Long
    
    ' nHeight represents the height
    ' of 1/5 of the rectangle
    nHeight = (rc.Bottom - rc.Top) / 10
        
    nStart = rc.Top
    
    For b = 1 To 11
        Select Case lColor
            Case COLOR_RED
                lNewColor = RGB(b * 25, 0, 0)
            Case COLOR_GREEN
                lNewColor = RGB(0, b * 25, 0)
            Case COLOR_BLUE
                lNewColor = RGB(0, 0, b * 25)
            Case COLOR_PURPLE
                lNewColor = RGB(b * 25, 0, b * 25)
        End Select
        
        hBrush = CreateSolidBrush(lNewColor)
        hBrushOld = SelectObject(hdc, hBrush)
        
        Call FillRect(hdc, MakeRect(rc.Left, nStart, rc.Right, nStart + nHeight), hBrush)
        nStart = nStart + nHeight
        
        Call SelectObject(hdc, hBrushOld)
        DeleteObject (hBrush)
    Next b
End Function

Private Function MakeRect(x1 As Long, y1 As Long, x2 As Long, y2 As Long) As RECT
    Dim rc As RECT
    
    rc.Left = x1
    rc.Top = y1
    rc.Right = x2
    rc.Bottom = y2
    
    MakeRect = rc
End Function

Private Sub Form_Load()
    Set m_pDC = New clsDC
        
    ' Initialize the DC Object
    m_pDC.Init (pctMain.hwnd)
        
    ' Set the mapping mode
    m_pDC.SetMapMode (MM_ANISOTROPIC)
End Sub

Private Sub Form_Resize()
    pctMain.Left = Me.ScaleLeft
    pctMain.Top = Me.ScaleTop
    
    pctMain.Width = Me.ScaleWidth
    pctMain.Height = Me.ScaleHeight
End Sub


Private Sub Form_Unload(Cancel As Integer)
    Set m_pDC = Nothing
End Sub




Private Sub mnuCopy_Click()
    If (Not m_pDC.CopyMetafile()) Then
        MsgBox "Error copying metafile"
    Else
        MsgBox "Success copying metafile"
    End If
End Sub

Private Sub mnuExit_Click()
    Unload Me
End Sub

Private Sub pctMain_Paint()
    Dim m_pmfDC As Long
    Dim cxClient As Long
    Dim cyClient As Long
    Dim cxCenter As Long
    Dim cyCenter As Long
    Dim rc As RECT
    
    If (m_pDC Is Nothing) Then Exit Sub
    
    With m_pDC
        .SaveDC
        
    ' Get Client area
        Call GetClientRect(pctMain.hwnd, rc)
        
        cxClient = (rc.Right - rc.Left)
        cyClient = (rc.Bottom - rc.Top)
        
    ' Set the Window extent
        .SetWindowExt HORZ_EXTENT, VERT_EXTENT
    
    ' Set the Viewport extent
        .SetViewportExt cxClient, -cyClient
            
    ' Set the Viewport origin
        .SetViewportOrg 0, cyClient
        
    ' Create the metafile
        m_pmfDC = .CreateMetaFile
              
    ' Draw into the metafile
        cxCenter = HORZ_EXTENT / 2
        cyCenter = VERT_EXTENT / 2

        rc = MakeRect(cxCenter, cyCenter, 0, VERT_EXTENT)
        Call DrawRectangle(m_pmfDC, COLOR_RED, rc)
        
        rc = MakeRect(cxCenter, cyCenter, HORZ_EXTENT, 0)
        Call DrawRectangle(m_pmfDC, COLOR_GREEN, rc)
        
        rc = MakeRect(cxCenter, cyCenter, 0, 0)
        Call DrawRectangle(m_pmfDC, COLOR_BLUE, rc)
        
        rc = MakeRect(cxCenter, cyCenter, HORZ_EXTENT, VERT_EXTENT)
        Call DrawRectangle(m_pmfDC, COLOR_PURPLE, rc)
        
    ' Close the metafile
        .CloseMetaFile (m_pmfDC)
    
    ' Play it
        .PlayMetaFile

        .RestoreDC
    End With
End Sub


