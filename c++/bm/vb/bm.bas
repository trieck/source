Attribute VB_Name = "basBM"
Option Explicit
 
Declare Function GetBitmapSize Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal szFileName As String) As Long
Declare Function PaintWindow Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal hwnd As Long, ByVal lColor As Long) As Long
Declare Function ExtractBMFH Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal szFileName As String, BMFH As Any) As Long
Declare Function ExtractBMI Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal szFileName As String, BMI As Any) As Long
Declare Function BlastBitmapFile Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal hwnd As Long, ByVal szFileName As String, pt As POINTAPI) As Long
Declare Function BlastBitmap Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal hwnd As Long, ByVal BMI As Long, ByVal lpBits As Long, pt As POINTAPI) As Long
Declare Function StretchBitmapFile Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal hwnd As Long, ByVal szFileName As String) As Long
Declare Function StretchBitmap Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal hwnd As Long, ByVal BMI As Long, ByVal lpBits As Long, pt As POINTAPI) As Long
Declare Function GetBitSize Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal szFileName As String) As Long
Declare Function GetBMBits Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal szFileName As String, lpBits As Any) As Long
Declare Function GetBMISize Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal szFileName As String) As Long
Declare Function ShowBitmapInfo Lib "d:\Tom's Projects\bm\debug\bm.dll" (ByVal hwndParent As Long, ByVal szFileName As String) As Long

Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long
Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long
Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Declare Function FindNextFile Lib "kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Long) As Long
Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (pDest As Any, pSource As Any, ByVal lCount As Long)

Public Const GMEM_FIXED = &H0
Public Const MAX_PATH = 260

Type FILETIME
        dwLowDateTime As Long
        dwHighDateTime As Long
End Type


Type WIN32_FIND_DATA
        dwFileAttributes As Long
        ftCreationTime As FILETIME
        ftLastAccessTime As FILETIME
        ftLastWriteTime As FILETIME
        nFileSizeHigh As Long
        nFileSizeLow As Long
        dwReserved0 As Long
        dwReserved1 As Long
        cFileName As String * MAX_PATH
        cAlternate As String * 14
End Type

Type BITMAPFILEHEADER
        bfType As Integer
        bfSize As Long
        bfReserved1 As Integer
        bfReserved2 As Integer
        bfOffBits As Long
End Type

Type POINTAPI
        x As Long
        y As Long
End Type

Type BITMAPINFOHEADER
        biSize As Long
        biWidth As Long
        biHeight As Long
        biPlanes As Integer
        biBitCount As Integer
        biCompression As Long
        biSizeImage As Long
        biXPelsPerMeter As Long
        biYPelsPerMeter As Long
        biClrUsed As Long
        biClrImportant As Long
End Type

Type RGBQUAD
        rgbBlue As Byte
        rgbGreen As Byte
        rgbRed As Byte
        rgbReserved As Byte
End Type

Type BITMAPINFO
        bmiHeader As BITMAPINFOHEADER
        bmiColors As RGBQUAD
End Type




Public Function GetLogDrives() As Variant
    Dim buffer As String
    Dim j As Integer, i As Integer, k As Integer
    Dim sArray() As String
        
    buffer = String(512, 0)
    
    Call GetLogicalDriveStrings(512, buffer)
    
    k = 1
    ' Strip Nulls from string
    Do
        Dim sTemp As String
        j = InStr(k, buffer, Chr(0))
        sTemp = Mid$(buffer, k, 3)
        If (sTemp = String(3, 0)) Then Exit Do
        ReDim Preserve sArray(i)
        sArray(i) = sTemp
        i = i + 1: k = j + 1
    Loop
    
    GetLogDrives = sArray
End Function

