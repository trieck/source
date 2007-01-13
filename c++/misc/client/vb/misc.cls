VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CMiscellaneous"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private m_pObj As Miscellaneous
Private m_pErrorInfo As udtErrorInfo

Private Type udtErrorInfo
    Number As Long
    Source As String
    Description As String
End Type
    
Public Property Get EnumDrives() As String
    Debug.Assert (Not m_pObj Is Nothing)
    
    EnumDrives = m_pObj.EnumDrives()
End Property



Public Property Get ErrNumber() As Long
    ErrNumber = m_pErrorInfo.Number
End Property

Public Property Get ErrSource() As String
    ErrSource = m_pErrorInfo.Source
End Property

Public Property Get ErrDescription() As String
    ErrDescription = m_pErrorInfo.Description
End Property
    
Public Property Get GetComputerName() As String
    Debug.Assert (Not m_pObj Is Nothing)
    
    GetComputerName = m_pObj.GetComputerName
End Property

Public Property Get GetDate() As String
    Debug.Assert (Not m_pObj Is Nothing)
    
    GetDate = m_pObj.GetDate()
End Property

Public Property Get GetDateTime() As String
    Debug.Assert (Not m_pObj Is Nothing)
    
    GetDateTime = m_pObj.GetDateTime()
End Property

Public Function GetDriveSpace(ByVal strDriveLetter As String) As Long
    
    On Error Resume Next
    
    Debug.Assert (Not m_pObj Is Nothing)
    Debug.Assert (Len(strDriveLetter) > 0)
    
    GetDriveSpace = m_pObj.GetDriveSpace(strDriveLetter)
    
    If Err.Number <> 0 Then SetErrorInfo
    
    On Error GoTo 0
        
End Function


Public Property Get GetTime() As String
    Debug.Assert (Not m_pObj Is Nothing)
    
    GetTime = m_pObj.GetTime()
End Property



Private Sub SetErrorInfo()
    m_pErrorInfo.Number = Err.Number
    m_pErrorInfo.Source = Err.Source
    m_pErrorInfo.Description = Err.Description
End Sub

Private Sub Class_Initialize()
    Set m_pObj = New MiscLib.Miscellaneous
    
    Debug.Assert (Not m_pObj Is Nothing)
End Sub

Private Sub Class_Terminate()
    Set m_pObj = Nothing
End Sub


