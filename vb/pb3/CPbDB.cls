VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CPBDB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' Private members

Private m_sDBPath As String     ' database path
Private aRs As CRecord            ' Recordset variable

Public interface
Public m_DB As Database         ' database object
Public Sub DoUpdate(iD&, vArray As Variant)
   Call aRs.UpdateRecord(iD&, vArray)
End Sub

Public Sub OpenDB(ByRef Path$)
    Set m_DB = Workspaces(0). _
        OpenDatabase(Path$, False, False)
    Debug.Assert Not IsEmpty(m_DB)
    
End Sub

Private Sub Class_Initialize()
    Set aRs = New CRecord
End Sub

Private Sub Class_Terminate()
'   clean up
    m_DB.Close
    Set m_DB = Nothing
    Set aRs = Nothing
End Sub



Public Function DoLookup() As Variant
'   Find Criteria
    Dim tmp$
    tmp$ = InputBox("Enter Last Name:", "Phone Book")
    If tmp$ = "" Then Exit Function
           
    aRs.SQL = "select id, last_name, first_name from NAMES where last_name like '" _
            & tmp$ & "*" & "'" & " order by last_name"
    
    DoLookup = aRs.GetNames()
End Function

Public Function GetData(iD As Long) As Variant
    aRs.SQL = "select * from NAMES where id = " & iD
    
    GetData = aRs.OpenRs()
End Function
