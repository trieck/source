VERSION 5.00
Begin VB.Form frmPipeClient 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Pipe Client"
   ClientHeight    =   3765
   ClientLeft      =   2895
   ClientTop       =   2205
   ClientWidth     =   4230
   Icon            =   "PipeDest.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3765
   ScaleWidth      =   4230
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   3480
      Top             =   120
   End
   Begin VB.TextBox txtPipeText 
      BackColor       =   &H8000000F&
      Height          =   3495
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   120
      Width           =   3975
   End
End
Attribute VB_Name = "frmPipeClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, lpSecurityAttributes As SECURITY_ATTRIBUTES, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Private Declare Function CreatePipe Lib "kernel32" (phReadPipe As Long, phWritePipe As Long, lpPipeAttributes As SECURITY_ATTRIBUTES, ByVal nSize As Long) As Long
Private Declare Function GetStdHandle Lib "kernel32" (ByVal nStdHandle As Long) As Long
Private Declare Function CreateProcess Lib "kernel32" Alias "CreateProcessA" (ByVal lpApplicationName As String, ByVal lpCommandLine As String, lpProcessAttributes As SECURITY_ATTRIBUTES, lpThreadAttributes As SECURITY_ATTRIBUTES, ByVal bInheritHandles As Long, ByVal dwCreationFlags As Long, lpEnvironment As Any, ByVal lpCurrentDirectory As String, lpStartupInfo As STARTUPINFO, lpProcessInformation As PROCESS_INFORMATION) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Private Declare Function ReadFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToRead As Long, lpNumberOfBytesRead As Long, ByVal lpOverlapped As Long) As Long
Private Declare Function PeekNamedPipe Lib "kernel32" (ByVal hNamedPipe As Long, lpBuffer As Any, ByVal nBufferSize As Long, lpBytesRead As Long, lpTotalBytesAvail As Long, lpBytesLeftThisMessage As Long) As Long

Private Type SECURITY_ATTRIBUTES
        nLength As Long
        lpSecurityDescriptor As Long
        bInheritHandle As Long
End Type

Private Type STARTUPINFO
        cb As Long
        lpReserved As Long
        lpDesktop As Long
        lpTitle As Long
        dwX As Long
        dwY As Long
        dwXSize As Long
        dwYSize As Long
        dwXCountChars As Long
        dwYCountChars As Long
        dwFillAttribute As Long
        dwFlags As Long
        wShowWindow As Integer
        cbReserved2 As Integer
        lpReserved2 As Long
        hStdInput As Long
        hStdOutput As Long
        hStdError As Long
End Type
Private Type PROCESS_INFORMATION
        hProcess As Long
        hThread As Long
        dwProcessId As Long
        dwThreadId As Long
End Type

Private Type OVERLAPPED
        Internal As Long
        InternalHigh As Long
        offset As Long
        OffsetHigh As Long
        hEvent As Long
End Type


Private Const NORMAL_PRIORITY_CLASS = &H20
Private Const STD_INPUT_HANDLE = -10&

Dim hPipe&

Private Sub Form_Load()
    If App.PrevInstance Then End
    
    hPipe& = GetStdHandle(STD_INPUT_HANDLE)
    Timer1.Enabled = True
End Sub


Private Sub Form_Unload(Cancel As Integer)
    If (hPipe& <> 0) Then
        Call CloseHandle(hPipe&)
    End If
End Sub


Private Sub Timer1_Timer()
    Dim res&
    Dim X&
    Dim t$
    Dim lRead&, lAvail&, lMessage&
    
    res& = PeekNamedPipe(hPipe&, ByVal 0&, 0, lRead, _
        lAvail, lMessage)
    
    If (res <> 0 And lAvail > 0) Then
        ReDim InBuff(lAvail) As Byte
        
        res = ReadFile(hPipe&, InBuff(0), lAvail, lRead, 0)
        
        t$ = InBuff()
        t$ = StrConv(t$, vbUnicode)
        
        txtPipeText = t$
    End If
        
End Sub


