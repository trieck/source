Attribute VB_Name = "basFile"
Option Explicit

Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Declare Function GlobalLock Lib "kernel32" (ByVal hMem As Long) As Long
Declare Function GlobalUnlock Lib "kernel32" (ByVal hMem As Long) As Long
Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long
Declare Function lclose Lib "kernel32" Alias "_lclose" (ByVal hFile As Long) As Long
Declare Function lopen Lib "kernel32" Alias "_lopen" (ByVal lpPathName As String, ByVal iReadWrite As Long) As Long
Declare Function lread Lib "kernel32" Alias "_lread" (ByVal hFile As Long, lpBuffer As Any, ByVal wBytes As Long) As Long
Declare Function llseek Lib "kernel32" Alias "_llseek" (ByVal hFile As Long, ByVal lOffset As Long, ByVal iOrigin As Long) As Long
Declare Sub agCopyData Lib "apigid32.dll" (source As Any, dest As Any, ByVal nCount&)
Declare Sub agCopyDataBynum Lib "apigid32.dll" Alias "agCopyData" (ByVal source&, ByVal dest&, ByVal nCount&)
Declare Function agGetStringFromPointer$ Lib "apigid32.dll" Alias "agGetStringFromLPSTR" (ByVal ptr&)
Declare Function agGetStringFrom2NullBuffer$ Lib "apigid32.dll" (ByVal ptr&)
Declare Function agGetAddressForVBString& Lib "apigid32.dll" (vbstring$)
Declare Function agGetAddressForObject& Lib "apigid32.dll" (object As Any)

Public Const GMEM_DISCARDABLE = &H100
Public Const GMEM_ZEROINIT = &H40
Public Const GMEM_MOVEABLE = &H2
Public Const GMEM_FIXED = &H0

Public Const READAPI = 0
Public Const FILE_END = 2
Public Const FILE_BEGIN = 0
Public Const MB_OK = &H0&


Sub FileRead()
    Dim hMem As Long, hFile As Long, numBytes As Long
    Dim Message$
    Static a$
    Dim i As Long
               
    a$ = InputBox$("Enter File Path:", "File Name", a$)
    
    If Trim(a$) = "" Then End
    
    hFile = lopen(a$, READAPI)
    
    numBytes = llseek(hFile, 0&, FILE_END)
    
    If (numBytes = -1) Then
        Call lclose(hFile)
        FileRead
    End If
    
    ' Allocate memory
    hMem = GlobalAlloc(GMEM_DISCARDABLE Or GMEM_FIXED Or GMEM_ZEROINIT, numBytes)
           
    ' Read Data into memory
    Call llseek(hFile, 0&, FILE_BEGIN)
    
    Call lread(hFile, ByVal hMem, numBytes)
                     
    MsgBox agGetStringFromPointer(hMem), vbInformation, App.Title
        
    Call GlobalFree(hMem)
    
    Call lclose(hFile)
        
    FileRead
End Sub


Sub main()
    FileRead
    
End Sub


