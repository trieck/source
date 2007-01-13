VERSION 5.00
Begin VB.Form frmFileForm 
   ClientHeight    =   5325
   ClientLeft      =   1905
   ClientTop       =   2535
   ClientWidth     =   6630
   Icon            =   "FileForm.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5325
   ScaleWidth      =   6630
End
Attribute VB_Name = "frmFileForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private szFileName As String

Public Sub SetFileName(ByVal sNewFile As String)
    szFileName = sNewFile
End Sub

Private Sub Form_Load()
    Me.Caption = szFileName
End Sub

Private Sub Form_Paint()
    Dim pt As POINTAPI
      
    If (Len(szFileName$) <> 0) Then
        Call BlastBitmapFile(Me.hwnd, szFileName, pt)
    End If
    
End Sub


