VERSION 5.00
Begin VB.Form frmPipeServer 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Pipe Server"
   ClientHeight    =   2550
   ClientLeft      =   2460
   ClientTop       =   2130
   ClientWidth     =   5055
   Icon            =   "pipe.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2550
   ScaleWidth      =   5055
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   3960
      TabIndex        =   3
      Top             =   2040
      Width           =   975
   End
   Begin VB.CommandButton cmdSendData 
      Caption         =   "Send Data"
      Enabled         =   0   'False
      Height          =   375
      Left            =   1440
      TabIndex        =   2
      Top             =   2040
      Width           =   1215
   End
   Begin VB.TextBox txtWriteText 
      Height          =   1815
      Left            =   120
      MultiLine       =   -1  'True
      TabIndex        =   1
      Top             =   120
      Width           =   4815
   End
   Begin VB.CommandButton cmdCreatePipe 
      Caption         =   "Create Pipe"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   2040
      Width           =   1215
   End
End
Attribute VB_Name = "frmPipeServer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, lpSecurityAttributes As SECURITY_ATTRIBUTES, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Private Declare Function WriteFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToWrite As Long, lpNumberOfBytesWritten As Long, ByVal lpOverlapped As Long) As Long
Private Declare Function CreatePipe Lib "kernel32" (phReadPipe As Long, phWritePipe As Long, lpPipeAttributes As SECURITY_ATTRIBUTES, ByVal nSize As Long) As Long
Private Declare Function SetStdHandle Lib "kernel32" (ByVal nStdHandle As Long, ByVal nHandle As Long) As Long
Private Declare Function CreateProcess Lib "kernel32" Alias "CreateProcessA" (ByVal lpApplicationName As String, ByVal lpCommandLine As String, lpProcessAttributes As SECURITY_ATTRIBUTES, lpThreadAttributes As SECURITY_ATTRIBUTES, ByVal bInheritHandles As Long, ByVal dwCreationFlags As Long, lpEnvironment As Any, ByVal lpCurrentDirectory As String, lpStartupInfo As STARTUPINFO, lpProcessInformation As PROCESS_INFORMATION) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
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

Private Const DestPath$ = "pipedest.exe"

Dim hRead&, hWrite&
Private Sub cmdCreatePipe_Click()
        
    Dim sa As SECURITY_ATTRIBUTES
    Dim si As STARTUPINFO
    Dim pi As PROCESS_INFORMATION
    
    sa.nLength = Len(sa)
    sa.bInheritHandle = True
    
    Dim res As Long
    
    ' Create the Pipe
    res = CreatePipe(hRead&, hWrite&, sa, 0)
    
    If (res = 0) Then
        MsgBox "Can't create the pipe."
        Unload Me
        Exit Sub
    End If
    
    ' Create the process
    Call SetStdHandle(STD_INPUT_HANDLE, hRead&)
    
    res = CreateProcess(DestPath$, _
        vbNullString, sa, sa, True, NORMAL_PRIORITY_CLASS, ByVal 0&, _
        vbNullString, si, pi)
        
    If (res = 0) Then
        MsgBox "Can't create process."
        Unload Me
        Exit Sub
    End If
    
    ' Close process handles
    Call CloseHandle(pi.hProcess)
    Call CloseHandle(pi.hThread)
    
    cmdCreatePipe.Enabled = False
    cmdSendData.Enabled = True
    txtWriteText.SetFocus
    
End Sub


Private Sub cmdExit_Click()
    Unload Me
End Sub

Private Sub cmdSendData_Click()
    Dim sTemp As String
    Dim bTemp() As Byte
    Dim res&
    Dim Written&
        
    sTemp = txtWriteText
    ReDim bTemp(Len(sTemp))
        
    Call CopyMemory(bTemp(0), ByVal sTemp, Len(sTemp))
    res = WriteFile(hWrite&, bTemp(0), UBound(bTemp), Written, 0)
    If (res = 0 Or Written = 0) Then
        MsgBox "WriteFile() failed writing to pipe."
        End
    End If
End Sub


Private Sub Form_Unload(Cancel As Integer)
    If (hWrite& <> 0) Then
        Call CloseHandle(hWrite&)
    End If
End Sub


