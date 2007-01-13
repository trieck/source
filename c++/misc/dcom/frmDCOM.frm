VERSION 5.00
Begin VB.Form frmDCOM 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "DCOM"
   ClientHeight    =   1485
   ClientLeft      =   3735
   ClientTop       =   2940
   ClientWidth     =   4455
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "frmDCOM.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   99
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   297
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdCancel 
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   3600
      TabIndex        =   2
      Top             =   525
      Width           =   735
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3600
      TabIndex        =   1
      Top             =   120
      Width           =   735
   End
   Begin VB.CheckBox chkEnableDCOM 
      Caption         =   "Enable DCOM"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   1080
      Width           =   1815
   End
   Begin VB.Label lblInstructions 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      ForeColor       =   &H80000008&
      Height          =   855
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   3375
   End
End
Attribute VB_Name = "frmDCOM"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Declare Function GetProcAddress Lib "kernel32" (ByVal hModule As Long, ByVal lpProcName As String) As Long
Private Declare Function LoadLibrary Lib "kernel32" Alias "LoadLibraryA" (ByVal lpLibFileName As String) As Long
Private Declare Function GetModuleHandle Lib "kernel32" Alias "GetModuleHandleA" (ByVal lpModuleName As String) As Long

Private Declare Function RegOpenKeyEx Lib "advapi32.dll" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, phkResult As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, lpData As Any, lpcbData As Long) As Long
Private Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, lpData As Any, ByVal cbData As Long) As Long

Private Const HKEY_LOCAL_MACHINE = &H80000002
Private Const KEY_QUERY_VALUE = &H1
Private Const KEY_SET_VALUE = &H2
Private Const KEY_ENUMERATE_SUB_KEYS = &H8
Private Const KEY_CREATE_SUB_KEY = &H4
Private Const KEY_STANDARD_ACCESS = KEY_QUERY_VALUE Or KEY_SET_VALUE _
                                    Or KEY_ENUMERATE_SUB_KEYS Or KEY_CREATE_SUB_KEY
                
Private Const ERROR_SUCCESS = 0&
Private Const REG_SZ = 1

Private Const NO_DCOM_SUPPORT = "The operating system does " _
                                & "not support DCOM Services."
                                
Private Const DCOM_ENABLED = "DCOM is currently enabled."
Private Const DCOM_DISABLED = "DCOM is currently disabled."

'   Function    :   EnableDCOM()
'   Purpose     :   Enable / Disable DCOM Services
'   Date        :   11/02/1997
Private Sub EnableDCOM(ByVal fEnable As Boolean)
    Dim hKey As Long
    Dim lResult As Long
    
    lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Ole", _
                            0, _
                            KEY_STANDARD_ACCESS, _
                            hKey)
                            
    Debug.Assert (lResult = ERROR_SUCCESS)
    
    Dim strRgch As String * 2
    Dim cb As Long
    
    cb = Len(strRgch)
    
    strRgch = IIf(fEnable, "Y", "N") & Chr(0)
    
    lResult = RegSetValueEx(hKey, "EnableDCOM", 0, REG_SZ, ByVal strRgch, cb)
    Debug.Assert (lResult = ERROR_SUCCESS)
    
    lResult = RegCloseKey(hKey)
    Debug.Assert (lResult = ERROR_SUCCESS)
    
End Sub

'   Function    :   FreeThreadedSupport()
'   Purpose     :   Determine whether DCOM services
'                   are available
'   Date        :   11/02/1997
Private Function FreeThreadedSupport() As Boolean
    Dim lAddress As Long
    Dim hModule As Long
    
    hModule = LoadLibrary("OLE32.DLL")
    If (hModule = 0) Then
        FreeThreadedSupport = False
        Exit Function
    End If
        
    lAddress = GetProcAddress(hModule, "CoInitializeEx")
    
    If (lAddress = 0) Then
        FreeThreadedSupport = False
        Exit Function
    End If
    
    FreeThreadedSupport = True

End Function

'   Function    :   IsDCOMEnabled()
'   Purpose     :   Determine whether DCOM services
'                   are enabled
'   Date        :   11/02/1997
Private Function IsDCOMEnabled() As Boolean
    Dim lResult As Long
    Dim hKey As Long
    
    lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Ole", _
                            0, _
                            KEY_STANDARD_ACCESS, _
                            hKey)
                            
    Debug.Assert (lResult = ERROR_SUCCESS)
    
    Dim strRgch As String * 2
    Dim cb As Long
    
    cb = Len(strRgch)
        
    lResult = RegQueryValueEx(hKey, "EnableDCOM", 0, REG_SZ, ByVal strRgch, cb)
    
    Debug.Assert (lResult = ERROR_SUCCESS)
    
    lResult = RegCloseKey(hKey)
    Debug.Assert (lResult = ERROR_SUCCESS)
    
    If (UCase$(Left$(strRgch, 1)) = "Y") Then
        IsDCOMEnabled = True
    Else
        IsDCOMEnabled = False
    End If
    
End Function

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()

    Dim fEnable As Boolean
    
    fEnable = (chkEnableDCOM.Value = 1)
    
    Call EnableDCOM(fEnable)
    
    Unload Me
    
End Sub

Private Sub Form_Load()
    ' Check whether 'OLE32.DLL' supports free threading
    If (Not FreeThreadedSupport()) Then
        lblInstructions = NO_DCOM_SUPPORT
        cmdOK.Enabled = False
        chkEnableDCOM.Enabled = False
        Exit Sub
    ' Check whether DCOM is enabled
    Else
        If (IsDCOMEnabled()) Then
            chkEnableDCOM.Value = 1
            lblInstructions = DCOM_ENABLED
        Else
            chkEnableDCOM.Value = 0
            lblInstructions = DCOM_DISABLED
        End If
    
    End If
    
End Sub


