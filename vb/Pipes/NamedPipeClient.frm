VERSION 5.00
Begin VB.Form frmNamedPipeClient 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Named Pipe Client"
   ClientHeight    =   2760
   ClientLeft      =   2445
   ClientTop       =   1980
   ClientWidth     =   4485
   Icon            =   "NamedPipeClient.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2760
   ScaleWidth      =   4485
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   3600
      Top             =   1680
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   3360
      TabIndex        =   1
      Top             =   2280
      Width           =   975
   End
   Begin VB.TextBox txtNamedPipeDest 
      BackColor       =   &H8000000F&
      Height          =   2055
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   120
      Width           =   4215
   End
End
Attribute VB_Name = "frmNamedPipeClient"
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

Private Const PIPE_ACCESS_DUPLEX = &H3
Private Const PIPE_ACCESS_OUTBOUND = &H2
Private Const PIPE_ACCESS_INBOUND = &H1
Private Const PIPE_TYPE_BYTE = &H0
Private Const PIPE_TYPE_MESSAGE = &H4

Private Const INVALID_HANDLE_VALUE = -1
Private Const GENERIC_READ = &H80000000
Private Const GENERIC_WRITE = &H40000000
Private Const OPEN_EXISTING = 3
Private Const FILE_SHARE_READ = &H1
Private Const FILE_ATTRIBUTE_NORMAL = &H80

Private Const PipeName$ = "\\.\pipe\MyNamedPipe"
Dim hClient&    ' Client Pipe Handle

Private Sub cmdExit_Click()
    Unload Me
    End
End Sub

Private Sub Form_Load()
    If App.PrevInstance Then End
        
    Timer1.Enabled = True
End Sub


Private Sub Form_Unload(Cancel As Integer)
    If (hClient& <> 0) Then CloseHandle (hClient&)
End Sub


Private Sub Timer1_Timer()
    Dim sa As SECURITY_ATTRIBUTES
    
    sa.bInheritHandle = True
    sa.nLength = Len(sa)

    hClient& = CreateFile(PipeName$, GENERIC_READ, _
                FILE_SHARE_READ, sa, OPEN_EXISTING, _
                FILE_ATTRIBUTE_NORMAL, 0)
    If (hClient& <> INVALID_HANDLE_VALUE) Then
        MsgBox "Got it!"
        Unload Me
        End
    End If
End Sub


