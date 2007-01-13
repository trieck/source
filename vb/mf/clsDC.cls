VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsDC"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
Private Declare Function GetDeviceCaps Lib "gdi32" (ByVal hdc As Long, ByVal nIndex As Long) As Long
Private Declare Function DPtoLP Lib "gdi32" (ByVal hdc As Long, lpPoint As Any, ByVal nCount As Long) As Long
Private Declare Function APISetMapMode Lib "gdi32" Alias "SetMapMode" (ByVal hdc As Long, ByVal nMapMode As Long) As Long
Private Declare Function APISetWindowExt Lib "gdi32" Alias "SetWindowExtEx" (ByVal hdc As Long, ByVal nX As Long, ByVal nY As Long, lpSize As SIZE) As Long
Private Declare Function APISetViewportExt Lib "gdi32" Alias "SetViewportExtEx" (ByVal hdc As Long, ByVal nX As Long, ByVal nY As Long, lpSize As SIZE) As Long
Private Declare Function APISetViewportOrg Lib "gdi32" Alias "SetViewportOrgEx" (ByVal hdc As Long, ByVal nX As Long, ByVal nY As Long, lpPoint As POINTAPI) As Long
Private Declare Function APISaveDC Lib "gdi32" Alias "SaveDC" (ByVal hdc As Long) As Long
Private Declare Function APIRestoreDC Lib "gdi32" Alias "RestoreDC" (ByVal hdc As Long, ByVal nSavedDC As Long) As Long
Private Declare Function GetDC Lib "user32" (ByVal hwnd As Long) As Long
Private Declare Function ReleaseDC Lib "user32" (ByVal hwnd As Long, ByVal hdc As Long) As Long
Private Declare Function GetClipBox Lib "gdi32" (ByVal hdc As Long, lpRect As RECT) As Long
Private Declare Function GetClientRect Lib "user32" (ByVal hwnd As Long, lpRect As RECT) As Long

Private Declare Function APICreateMetaFile Lib "gdi32" Alias "CreateMetaFileA" (ByVal lpString As String) As Long
Private Declare Function APIPlayMetaFile Lib "gdi32" Alias "PlayMetaFile" (ByVal hdc As Long, ByVal hMF As Long) As Long
Private Declare Function APICloseMetaFile Lib "gdi32" Alias "CloseMetaFile" (ByVal hMF As Long) As Long
Private Declare Function APIDeleteMetaFile Lib "gdi32" Alias "DeleteMetaFile" (ByVal hMF As Long) As Long

Private Declare Function SetClipboardData Lib "user32" (ByVal wFormat As Long, ByVal hMem As Long) As Long

Private Declare Function EmptyClipboard Lib "user32" () As Long
Private Declare Function OpenClipboard Lib "user32" (ByVal hwnd As Long) As Long
Private Declare Function CloseClipboard Lib "user32" () As Long

Private Declare Sub CopyData Lib "kernel32" Alias "RtlMoveMemory" (ByVal lpDest As Long, lpSource As Any, ByVal lBytes As Long)

Private Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Private Declare Function GlobalLock Lib "kernel32" (ByVal hMem As Long) As Long
Private Declare Function GlobalUnlock Lib "kernel32" (ByVal hMem As Long) As Long
Private Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long

Private Type METAFILEPICT
        mm As Long
        xExt As Long
        yExt As Long
        hMF As Long
End Type

Private Type SIZE
        cx As Long
        cy As Long
End Type

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

' Error constants
Private Const E_NO_HDC = -1
Private Const E_NO_HMF = -2
Private Const E_METAFILE_EXISTS = -3

Private Const HORZRES = 8
Private Const VERTRES = 10
Private Const HORZSIZE = 4
Private Const VERTSIZE = 6

Private Const GMEM_DISCARDABLE = &H100
Private Const GMEM_MOVEABLE = &H2
Private Const GMEM_DDESHARE = &H2000

Private Const MM_ANISOTROPIC = 8
Private Const MM_ISOTROPIC = 7

Private Const CF_METAFILEPICT = 3
Private Const CF_ENHMETAFILE = 14

' Private data members
Private m_phWnd As Long         ' Window Handle
Private m_phDC As Long          ' Device Context handle
Private m_pnSavedDC As Long     ' Saved DC
Private m_phMF As Long          ' Metafile handle


Public Function CloseMetaFile(ByVal hmfDC As Long) As Long
    If (m_phMF) Then
        CloseMetaFile = E_METAFILE_EXISTS
        Exit Function
    End If
    
    m_phMF = APICloseMetaFile(hmfDC)
    
    CloseMetaFile = m_phMF
    
End Function


Public Function CopyMetafile() As Boolean
    Dim hMem As Long
    Dim lpMetafilePict As Long
    Dim mfp As METAFILEPICT
    Dim hdcMeta As Long
    Dim newMF As Long
    Dim i As Long
    Dim oldsize As SIZE
        
    If (m_phDC = 0) Then
        CopyMetafile = False
        Exit Function
    End If
    
    If (m_phMF = 0) Then
        CopyMetafile = False
        Exit Function
    End If
                  
    hdcMeta = APICreateMetaFile(vbNullString)
    Call APISetWindowExt(hdcMeta, 32767, 32767, oldsize)
    Call APIPlayMetaFile(hdcMeta, m_phMF)
    newMF = APICloseMetaFile(hdcMeta)
    
    hMem = GlobalAlloc(GMEM_DDESHARE, Len(mfp))
    If (hMem = 0) Then
        CopyMetafile = False
        Exit Function
    End If
    
    lpMetafilePict = GlobalLock(hMem)
    If (lpMetafilePict = 0) Then
        Call GlobalFree(hMem)
        CopyMetafile = False
        Exit Function
    End If
    
    mfp.mm = MM_ANISOTROPIC
    mfp.xExt = 0
    mfp.yExt = 0
    mfp.hMF = newMF
    
    Call CopyData(lpMetafilePict, mfp, Len(mfp))
    
    i = GlobalUnlock(hMem)
           
    OpenClipboard (m_phWnd)
    
    EmptyClipboard
       
    i = SetClipboardData(CF_METAFILEPICT, hMem)
    
    CloseClipboard
    
    If (i = 0) Then
        GlobalFree (hMem)
    End If
    
    CopyMetafile = IIf(i = 0, False, True)
        
End Function

Public Function CreateMetaFile() As Long
        
    If (m_phDC = 0) Then
        CreateMetaFile = E_NO_HDC
        Exit Function
    End If

    If (m_phMF <> 0) Then
        CreateMetaFile = E_METAFILE_EXISTS
        Exit Function
    End If
            
    CreateMetaFile = APICreateMetaFile(vbNullString)
    
End Function


Public Function DeleteMetaFile() As Long
    If (m_phMF = 0) Then Exit Function
    
    DeleteMetaFile = APIDeleteMetaFile(m_phMF)
    m_phMF = 0
End Function

Public Property Get hdc() As Long
    hdc = m_phDC
End Property

Public Sub Init(ByVal hwnd As Long)
    If (m_phWnd) Then Exit Sub
    
    m_phWnd = hwnd
    
    If (m_phDC) Then Call ReleaseDC(m_phWnd, m_phDC)
    
    m_phDC = GetDC(hwnd)
End Sub

Public Function PlayMetaFile() As Long
      
    If (m_phDC = 0) Then
        PlayMetaFile = E_NO_HDC
        Exit Function
    End If
    
    If (m_phMF = 0) Then
        PlayMetaFile = E_NO_HMF
        Exit Function
    End If
                           
    PlayMetaFile = APIPlayMetaFile(m_phDC, m_phMF)
End Function

Public Function RestoreDC() As Long
    If (m_pnSavedDC = 0) Then Exit Function
    
    RestoreDC = APIRestoreDC(m_phDC, m_pnSavedDC)
    
    m_pnSavedDC = 0
End Function

Public Function SaveDC() As Long
    If (Not m_phDC) Then Exit Function
    
    m_pnSavedDC = APISaveDC(m_phDC)
    
    SaveDC = m_pnSavedDC
    
End Function

Public Function SetMapMode(ByVal nMapMode As Long) As Long
    If (m_phDC = 0) Then Exit Function
    
    SetMapMode = APISetMapMode(m_phDC, nMapMode)
End Function

Public Function SetViewportOrg(ByVal nXVal As Long, ByVal nYVal As Long) As Long
    Dim lpPoint As POINTAPI
    
    If (m_phDC = 0) Then Exit Function
    
    SetViewportOrg = APISetViewportOrg(m_phDC, nXVal, nYVal, lpPoint)
End Function
Public Function SetViewportExt(ByVal nXVal As Long, ByVal nYVal As Long) As Long
    Dim lpSize As SIZE
    
    If (m_phDC = 0) Then Exit Function
    
    SetViewportExt = APISetViewportExt(m_phDC, nXVal, nYVal, lpSize)
End Function

Public Function SetWindowExt(ByVal nXVal As Long, ByVal nYVal As Long) As Long
    Dim lpSize As SIZE
    
    If (m_phDC = 0) Then Exit Function
    
    SetWindowExt = APISetWindowExt(m_phDC, nXVal, nYVal, lpSize)
End Function


Private Sub Class_Terminate()
    Call DeleteMetaFile
        
    If (m_phWnd And m_phDC) Then
        Call ReleaseDC(m_phWnd, m_phDC)
    End If
End Sub



Private Sub NormalizeRect(lpRect As RECT)
    
    Dim tmpRect As RECT
    
    tmpRect = lpRect
    
    ' Swap top and bottom
    ' if bottom < top
    If (lpRect.Bottom < lpRect.Top) Then
        lpRect.Bottom = tmpRect.Top
        lpRect.Top = tmpRect.Bottom
    End If
    
    ' Swap left and right
    ' if right < left
    If (lpRect.Right < lpRect.Left) Then
        lpRect.Right = tmpRect.Left
        lpRect.Left = tmpRect.Right
    End If
End Sub
