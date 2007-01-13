VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsFile"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

' Private Members
Private Path As String

Public Property Get Attributes() As String
    Dim X As Integer, i As Integer
    Dim y As Variant
    
    On Error GoTo aError
    
    y = Array(0, 1, 2, 4, 16, 32)
    
    X = GetAttr(Path)
    
    For i = 0 To UBound(y)
        If (X And y(i)) Then
            Select Case y(i)
                Case vbNormal
                    Attributes = Attributes & "Normal "
                Case vbReadOnly
                    Attributes = Attributes & "Read Only "
                Case vbHidden
                    Attributes = Attributes & "Hidden "
                Case vbSystem
                    Attributes = Attributes & "System "
                Case vbDirectory
                    Attributes = Attributes & "Directory "
                Case vbArchive
                    Attributes = Attributes & "Archive "
            End Select
        End If
    Next i
    Attributes = Trim(Attributes)
    Exit Property
    
aError:
    Err.Raise Number:=vbObjectError + 0, _
        Description:="Error Reading File."
    
    
End Property


Public Property Get DateCreated() As Date
    On Error GoTo dcError
    
    DateCreated = FileDateTime(Path)

    Exit Property
dcError:
    Err.Raise Number:=vbObjectError + 0, _
        Description:="Error Reading File."
    
    
End Property


Public Property Get FileSize() As Long
    On Error GoTo fsError
    
    FileSize = FileLen(Path)
    Exit Property
    
fsError:
    Err.Raise Number:=vbObjectError + 0, _
        Description:="Error Reading File."
    
End Property

Public Property Get FilePath() As String
    FilePath = Path
End Property

Public Property Let FilePath(vNewValue As String)
    Path = vNewValue
End Property


Private Sub Class_Initialize()

End Sub

Private Sub Class_Terminate()
    Set frmFileInfo = Nothing
End Sub


