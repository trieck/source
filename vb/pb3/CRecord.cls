VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CRecord"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' private members
Private m_nID As Long
Private m_sLastName As String
Private m_sFirstName As String
Private m_sHomeAddress As String
Private m_sHomeCity As String
Private m_sHomeState As String * 2
Private m_sHomeZip As String
Private m_sHomePhone As String
Private m_sBusPhone As String


' public interface
Public SQL As String


Private Function CheckNull(vNewValue As Variant) As String
    If (IsNull(vNewValue)) Then
        CheckNull = ""
    Else
        CheckNull = CStr(vNewValue)
    End If
End Function

Public Function GetNames() As Variant
    Dim rs As Recordset
    Dim i As Integer
    Dim sNames() As Variant
    
    On Error GoTo gnError
    
    Set rs = glbPB.m_DB.OpenRecordset(SQL)
    
    If rs.EOF Then
        GetNames = Empty
        rs.Close
        Exit Function
    Else:   While (Not rs.EOF)
                ReDim Preserve sNames(1, i)
                ' Check for lastname and first name
                If (Not IsNull(rs("last_name")) And Not IsNull(rs("first_name"))) Then
                    sNames(0, i) = rs("ID")
                    sNames(1, i) = rs("last_name") & ", " & rs("first_name")
                ElseIf IsNull(rs("first_name")) Then
                    sNames(0, i) = rs("ID")
                    sNames(1, i) = rs("last_name")
                ElseIf IsNull(rs("last_name")) Then
                    sNames(0, i) = rs("ID")
                    sNames(1, i) = rs("first_name")
                Else
                    sNames(0, i) = Null
                    sNames(1, i) = Null
                End If
                i = i + 1: rs.MoveNext
            Wend
            rs.Close
            GetNames = sNames
    End If
    Exit Function
gnError:
    MsgBox Err.Description, vbInformation, App.Title
    Exit Function
End Function

Public Function OpenRs() As Variant
    Dim rs As Recordset
    
    On Error GoTo orError
    
    Set rs = glbPB.m_DB.OpenRecordset(SQL)
    
    If (Not rs.EOF) Then
        m_nID = rs("ID")
        m_sLastName = CheckNull(rs("last_name"))
        m_sFirstName = CheckNull(rs("first_name"))
        m_sHomeAddress = CheckNull(rs("home_street"))
        m_sHomeCity = CheckNull(rs("home_city"))
        m_sHomeState = CheckNull(rs("home_state"))
        m_sHomeZip = CheckNull(rs("home_postal"))
        m_sHomePhone = CheckNull(rs("home_phone"))
        m_sBusPhone = CheckNull(rs("business_phone"))
    End If
    
    OpenRs = Array(m_nID, m_sLastName, m_sFirstName, m_sHomeAddress, _
                        m_sHomeCity, m_sHomeState, m_sHomeZip, m_sHomePhone, m_sBusPhone)
    rs.Close
    Set rs = Nothing
    Exit Function
orError:
    MsgBox Err.Description, vbInformation, App.Title
    Exit Function
    
End Function


Public Sub UpdateRecord(iD&, vArray As Variant)
    Dim qry As QueryDef, i As Integer
    
    On Error GoTo urError
    
    Set qry = glbPB.m_DB.QueryDefs("qryUpdateNames")
    
    For i = 0 To vArray.ubound
        qry.Parameters(i) = vArray(i)
    Next
    
    qry.Parameters(i) = iD&
    qry.Execute
    qry.Close
    
    Exit Sub
    
urError:
    MsgBox Err.Description, vbInformation, App.Title
    Exit Sub
End Sub
