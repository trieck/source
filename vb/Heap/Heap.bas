Attribute VB_Name = "basHeap"
Option Explicit


Public Sub exch(v As Variant, ByVal j As Integer, ByVal k As Integer)
    If Not IsArray(v) Then Exit Sub
    Dim t As Variant
    t = v(j)
    v(j) = v(k)
    v(k) = t
End Sub


Sub main()
    Dim h As clsHeap
    Set h = New clsHeap
    
    h.insert (1.04)
    h.insert (1.25)
    
End Sub


