Attribute VB_Name = "basGauss"
Option Explicit

'   Gaussian Elimination
'
'   Parameters:
'       A - augmented square matrix, N x N + 1
'       x - solution matrix, N x 1
'
'   Return value:
'       True - if non-singular.
'       False - if singular or error.
'
Function GaussianElimination(A() As Single, x() As Single) As Boolean
    
    Dim i, j, k, N, max As Integer
    Dim t As Single
    
    On Error GoTo errHandler
    
    N = UBound(A, 1) - LBound(A, 1) + 1
    For i = 0 To N - 1
        max = i
        For j = i + 1 To N - 1
            If Abs(A(i, j)) > Abs(A(max, i)) Then
                max = j
            End If
        Next j
        If (max <> i) Then
        For k = i To N
            t = A(max, k)
            A(max, k) = A(i, k)
            A(i, k) = t
        Next k
        End If
        For j = i + 1 To N - 1
            For k = N To i Step -1
                A(j, k) = A(j, k) - A(i, k) * A(j, i) / A(i, i)
            Next k
        Next j
    Next i
    
    For i = N - 1 To 0 Step -1
        t = 0
        For j = i + 1 To N - 1
            t = t + A(i, j) * x(j)
        Next j
        x(i) = (A(i, N) - t) / A(i, i)
    Next i
    
    GaussianElimination = True
    Exit Function
    
errHandler:    ' Division by zero
    GaussianElimination = False
    On Error GoTo 0
    
End Function


