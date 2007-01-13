Attribute VB_Name = "basMain"
Option Explicit

' global phone book database object
Public glbPB As CPBDB

Public Sub FormCenter(frm As Form, Optional frmHost As Form)
    Dim hostwidth As Integer, hostheight As Integer
    Dim formwidth As Integer, formheight As Integer
    
    If Not IsMissing(frmHost) Then
        hostwidth = frmHost.ScaleWidth
        hostheight = frmHost.ScaleHeight
    Else
        hostwidth = Screen.Width
        hostheight = Screen.Height
    End If
    
    formwidth = frm.ScaleWidth
    formheight = frm.ScaleHeight
    
    frm.Left = hostwidth / 2 - formwidth / 2
    frm.Top = hostheight / 2 - formheight / 2
End Sub
