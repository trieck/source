VERSION 5.00
Begin VB.Form frmNamedPipe 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Named Pipe"
   ClientHeight    =   3195
   ClientLeft      =   2385
   ClientTop       =   2385
   ClientWidth     =   4680
   Icon            =   "NamedPipe.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   3360
      TabIndex        =   1
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CommandButton cmdCreateNamedPipe 
      Caption         =   "Create Named Pipe"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   2760
      Width           =   2175
   End
End
Attribute VB_Name = "frmNamedPipe"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, lpSecurityAttributes As SECURITY_ATTRIBUTES, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Private Declare Function WriteFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToWrite As Long, lpNumberOfBytesWritten As Long, ByVal lpOverlapped As Long) As Long
Private Declare Function CreateNamedPipe Lib "kernel32" Alias "CreateNamedPipeA" (ByVal lpName As String, ByVal dwOpenMode As Long, ByVal dwPipeMode As Long, ByVal nMaxInstances As Long, ByVal nOutBufferSize As Long, ByVal nInBufferSize As Long, ByVal nDefaultTimeOut As Long, lpSecurityAttributes As SECURITY_ATTRIBUTES) As Long
Private Declare Function CreateProcess Lib "kernel32" Alias "CreateProcessA" (ByVal lpApplicationName As String, ByVal lpCommandLine As String, lpProcessAttributes As SECURITY_ATTRIBUTES, lpThreadAttributes As SECURITY_ATTRIBUTES, ByVal bInheritHandles As Long, ByVal dwCreationFlags As Long, lpEnvironment As Any, ByVal lpCurrentDirectory As String, lpStartupInfo As STARTUPINFO, lpProcessInformation As PROCESS_INFORMATION) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Private Declare Function FlushFileBuffers Lib "kernel32" (ByVal hFile As Long) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (pDest As Any, pSource As Any, ByVal nCount As Long)

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

Private Const NORMAL_PRIORITY_CLASS = &H20
Private Const STD_INPUT_HANDLE = -10&
Private Const PIPE_ACCESS_DUPLEX = &H3
Private Const PIPE_ACCESS_OUTBOUND = &H2
Private Const PIPE_ACCESS_INBOUND = &H1
Private Const PIPE_TYPE_BYTE = &H0
Private Const PIPE_TYPE_MESSAGE = &H4
Private Const PIPE_UNLIMITED_INSTANCES = 255
Private Const NMPWAIT_USE_DEFAULT_WAIT = &H0
Private Const INVALID_HANDLE_VALUE = -1

Dim hServer&       ' Server pipe handle


'   Closes server side pipe handle
Private Sub ClosePipe()
    If (hServer& <> 0) Then
        Call FlushFileBuffers(hServer&)
        Call CloseHandle(hServer&)
    End If
End Sub

Private Sub cmdCreateNamedPipe_Click()
    Dim PipeName$, DestPath$
    Dim res&
    Dim sa As SECURITY_ATTRIBUTES
    Dim si As STARTUPINFO
    Dim pi As PROCESS_INFORMATION
    
    sa.nLength = Len(sa)
    sa.bInheritHandle = True
    
    PipeName$ = "\\.\pipe\MyNamedPipe"
    DestPath$ = App.Path & "\NamedPipeClient.exe"
    
    ' Create a Named Pipe
    hServer& = CreateNamedPipe(PipeName$, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, _
                PIPE_UNLIMITED_INSTANCES, 1024, 1024, NMPWAIT_USE_DEFAULT_WAIT, _
                sa)
    If (hServer& = INVALID_HANDLE_VALUE) Then
        MsgBox "CreateNamedPipe() failed with INVALID_HANDLE_VALUE.", vbInformation, App.Title
        Exit Sub
    End If
    
    ' Create process
    res = CreateProcess(DestPath$, _
        vbNullString, sa, sa, True, NORMAL_PRIORITY_CLASS, ByVal 0&, _
        vbNullString, si, pi)
        
    If (res = 0) Then
        MsgBox "CreateProcess() failed.", vbInformation, App.Title
        Unload Me
        Exit Sub
    End If
    
    ' Close process handles
    Call CloseHandle(pi.hProcess)
    Call CloseHandle(pi.hThread)
    
    cmdCreateNamedPipe.Enabled = False
End Sub


Private Sub cmdExit_Click()
    Unload Me
    End
End Sub


Private Sub Form_Unload(Cancel As Integer)
    If (hServer& <> 0) Then ClosePipe
End Sub


