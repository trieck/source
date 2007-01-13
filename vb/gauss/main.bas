Attribute VB_Name = "basMain"
Option Explicit

Private Const N = 100


Sub main()

    Dim A(0 To N - 1, 0 To N) As Single
    Dim x(N) As Single
    
    Call Populate(A)
   
    
    Dim i As Integer, j As Integer
    Dim v As String
    For i = 0 To N - 1
        For j = 0 To N
            v = v & A(i, j)
            If (j <> N) Then v = v & "|"
        Next j
        v = v & vbCrLf
    Next i
    Debug.Print "************"
    Debug.Print v
    
    Call GaussianElimination(A, x)
    v = ""
    
    For i = 0 To N - 1
        v = v & x(i)
        If (i <> N - 1) Then v = v & "|"
    Next i
    Debug.Print v
    Debug.Print "************"
    
End Sub



'   Populate matrix
'
'   Parameters:
'       A - augmented square matrix, N x N + 1
Private Sub Populate(A() As Single)
    Dim i, j, N As Integer
    Randomize
    
    N = UBound(A, 1)
    
    For i = 0 To N
        For j = 0 To N + 1
            A(i, j) = Int(1000 * Rnd + 1)
        Next j
    Next i
    
    
End Sub


