VERSION 5.00
Begin VB.Form frmFTPTest 
   BackColor       =   &H00808080&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "FTP Test"
   ClientHeight    =   3480
   ClientLeft      =   2565
   ClientTop       =   2655
   ClientWidth     =   3810
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3480
   ScaleWidth      =   3810
   Begin VB.CommandButton cmdFTP 
      Caption         =   "FTP Connect"
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   3000
      Width           =   3255
   End
   Begin VB.Label lblCopyingFile 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   480
      Width           =   3615
   End
   Begin VB.Label lblNow 
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      Caption         =   "Now Copying..."
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   240
      Width           =   3375
   End
End
Attribute VB_Name = "frmFTPTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Const FTP_TRANSFER_TYPE_UNKNOWN = 0
Private Const FTP_TRANSFER_TYPE_ASCII = 1
Private Const FTP_TRANSFER_TYPE_BINARY = 2
Private Const INTERNET_DEFAULT_FTP_PORT = 21
Private Const INTERNET_FLAG_PASSIVE = &H8000000
Private Const INTERNET_OPEN_TYPE_PRECONFIG = 0
Private Const INTERNET_SERVICE_FTP = 1

Private Declare Function FtpGetFile Lib "wininet" Alias "FtpGetFileA" (ByVal hFtp&, ByVal _
    lpszRemoteFile$, ByVal lpszNewFile$, ByVal fFailIfExists&, ByVal dwFlagsAndAttributes&, ByVal dwFlags&, ByVal dwContext&) As Long
    
Private Declare Function FtpPutFile Lib "wininet" Alias "FtpPutFileA" (ByVal hFtp&, ByVal _
    lpszLocalFile$, ByVal lpszNewRemoteFile$, ByVal dwFlags&, ByVal dwContext&) As Long
    
Private Declare Function FtpSetCurrentDirectory Lib "wininet" Alias "FtpSetCurrentDirectoryA" ( _
    ByVal hFtp&, ByVal lpszDirectory$) As Long
    
Private Declare Function FtpCreateDirectory Lib "wininet" Alias "FtpCreateDirectoryA" ( _
    ByVal hFtp&, ByVal lpszDirectory$) As Boolean
    
Private Declare Function InternetCloseHandle Lib "wininet" (ByVal hInet&) As Long

Private Declare Function InternetConnect Lib "wininet" Alias "InternetConnectA" (ByVal hInet&, _
    ByVal lpszServerName$, ByVal nServerPort&, ByVal lpszUserName$, ByVal lpszPassword$, _
    ByVal dwService&, ByVal dwFlags&, ByVal dwContext&) As Long
    
Private Declare Function InternetOpen Lib "wininet" Alias "InternetOpenA" (ByVal lpszAgent$, _
    ByVal dwAccessType&, ByVal lpszProxyName$, lpszProxyBypass$, ByVal dwFlags&) As Long
       
Private Declare Function GetPrivateProfileString Lib "kernel32" Alias _
    "GetPrivateProfileStringA" (ByVal lpApplicationName As String, _
    ByVal lpKeyName As String, ByVal lpDefault As String, _
    ByVal lpReturnedString As String, ByVal nSize As Long, _
    ByVal lpFileName As String) As Long
    
Private Sub DumpFiles(hFtp&)
    Dim sLocalFile$, sRemoteFile$, lResult&
    Dim sPath$, sSubDir$, sSubDirs$(), sFile$, sFiles$()
    Dim nDirs&, nFiles&, i As Integer, j As Integer
        
    ' Get File Path
    sPath$ = GetINIInfo("FileInfo", "FilePath")
    
    ' Build List of Directories and Files beneath them
    sSubDir$ = Dir$(sPath$ & "*.*", vbDirectory)
    While Len(sSubDir$)
        If (sSubDir$ <> "." And sSubDir$ <> "..") Then
            If (GetAttr(sSubDir$) And vbDirectory) Then
                nDirs& = nDirs& + 1
                ReDim Preserve sSubDirs(nDirs)
                sSubDirs$(nDirs - 1) = sSubDir$
            End If
        End If
        sSubDir$ = Dir$
    Wend
    
    For i = 0 To UBound(sSubDirs$)
        sFile$ = Dir$(sPath$ & sSubDirs$(i) & "\*.*", vbNormal)
        While Len(sFile$)
            nFiles = nFiles + 1
            ReDim Preserve sFiles$(nFiles)
            sFiles$(nFiles) = sFile$
            sFile$ = Dir$
        Wend
        Call FtpCreateDirectory(hFtp&, sSubDirs$(i))
        Call FtpSetCurrentDirectory(hFtp, sSubDirs$(i))
        For j = 0 To nFiles
            sLocalFile$ = sPath$ & sSubDirs$(i) & "\" & sFiles$(j)
            lblCopyingFile.Caption = sLocalFile$
            sRemoteFile$ = sFiles$(j)
            DoEvents
            lResult& = FtpPutFile(hFtp&, sLocalFile, _
                sRemoteFile$, FTP_TRANSFER_TYPE_BINARY, 0)
        Next j
        Erase sFiles$
        Call FtpSetCurrentDirectory(hFtp&, "..")
    Next i
      
           
    End Sub

Private Function GetINIInfo(AppName$, Key$) As String
    Dim buffer$, bufLength&
    
    buffer$ = String(255, 0)
    
    Call GetPrivateProfileString(AppName$, Key$, "", buffer$, 255, App.Path & "\" & "FTPTest.ini")
    
    GetINIInfo = Left$(buffer$, InStr(buffer$, Chr(0)) - 1)
    
End Function


Private Sub cmdFTP_Click()
    Dim hFtp&, hInet&, lResult&
    Dim sLocalFile$, sPassword$, sRemoteFile$
    Dim sServer$, sUserName$
    
    Screen.MousePointer = vbHourglass
    
    hInet& = InternetOpen("FTP Test", _
        INTERNET_OPEN_TYPE_PRECONFIG, vbNullString, _
        vbNullString, 0)
    
    If (hInet&) Then
        sServer$ = GetINIInfo("Network", "Server")
        sUserName$ = GetINIInfo("Network", "UserName")
        sPassword$ = GetINIInfo("Network", "Password")
        hFtp& = InternetConnect(hInet&, sServer$, _
            INTERNET_DEFAULT_FTP_PORT, sUserName$, _
            sPassword$, INTERNET_SERVICE_FTP, _
            INTERNET_FLAG_PASSIVE, 0)
        If (hFtp&) Then
            lResult& = FtpSetCurrentDirectory(hFtp, "projects")
            If (lResult&) Then
                DumpFiles (hFtp&)
            End If
                        
        End If
        lResult& = InternetCloseHandle(hInet&)
    End If
    Screen.MousePointer = vbDefault
End Sub

Private Sub Label2_Click()

End Sub


