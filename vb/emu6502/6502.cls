VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cls6502"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' CPU Registers
Private A As Byte   ' Accumulator
Private x As Byte   ' X index register
Private Y As Byte   ' Y index register
Private PCL As Byte ' Program counter low
Private PCH As Byte ' Program counter high
Private S As Byte   ' Stack pointer
Private P As Byte   ' Processor status

Public Property Get RegA() As Byte
    RegA = A
End Property

Public Property Let RegA(ByVal val As Byte)
    A = val
End Property

Public Property Get RegX() As Byte
    RegX = x
End Property

Public Property Let RegX(ByVal val As Byte)
    x = val
End Property

Public Property Get RegY() As Byte
    RegY = Y
End Property

Public Property Let RegY(ByVal val As Byte)
    Y = val
End Property

Public Property Get RegPCL() As Byte
    RegPCL = PCL
End Property

Public Property Let RegPCL(ByVal val As Byte)
    PCL = val
End Property

Public Property Get RegPCH() As Byte
    RegPCH = PCH
End Property

Public Property Let RegPCH(ByVal val As Byte)
    PCH = val
End Property

Public Property Get RegS() As Byte
    RegS = S
End Property

Public Property Let RegS(ByVal val As Byte)
    S = val
End Property

Public Property Get RegP() As Byte
    RegP = P
End Property

Public Property Let RegP(ByVal val As Byte)
    P = val
End Property

Private Sub Class_Initialize()
    A = 0
    x = 0
    Y = 0
    PCL = 0
    PCH = 0
    S = 0
    P = 0
End Sub
