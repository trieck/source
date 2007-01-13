VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsHeap"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'  From Sedgewick 9.5

Private Const maxN As Integer = 20  ' Maximum size of priority queue
Private pq(maxN + 1) As Single      ' Priority queue
Private N As Integer                ' Number of items in queue


' Restore the heap condition when a node's priority is increased,
' we move up the heap, exchanging the node at position k with it's
' parent (at position k/2) if necessary, continuing as long as
' [k/2] < a[k] or until we reach the top of the heap
Private Sub fixUp()
    Dim k As Integer
    k = N
    While (k > 1 And pq(k / 2) < pq(k))
        Call exch(pq, k, k / 2)
        k = k / 2
    Wend
    
End Sub

Public Sub insert(ByVal item As Single)
    pq(N) = item
    N = N + 1
    Call fixUp
End Sub


