Attribute VB_Name = "basMain"
' Global Functions

Public Function FormCenter(frm As Form, Optional vHostForm As Variant) As Long
   
    If (Not IsMissing(HostForm)) Then
        frm.Left = (vHostForm.Width - frm.Width) / 2
        frm.Top = (vHostForm.Height - frm.Height) / 2
    Else
        frm.Left = (Screen.Width - frm.Width) / 2
        frm.Top = (Screen.Height - frm.Height) / 2
    End If
    
End Function


