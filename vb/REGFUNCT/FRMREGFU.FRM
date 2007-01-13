VERSION 4.00
Begin VB.Form frmRegFunctions 
   Caption         =   "Registry Functions"
   ClientHeight    =   3840
   ClientLeft      =   2055
   ClientTop       =   1470
   ClientWidth     =   4755
   Height          =   4245
   Left            =   1995
   LinkTopic       =   "Form1"
   ScaleHeight     =   3840
   ScaleWidth      =   4755
   Top             =   1125
   Width           =   4875
   Begin VB.CommandButton cmdQueryValue 
      Caption         =   "Query Value"
      Height          =   1455
      Left            =   1440
      TabIndex        =   0
      Top             =   1080
      Width           =   1815
   End
   Begin VB.Frame Frame1 
      Height          =   2055
      Left            =   1080
      TabIndex        =   1
      Top             =   720
      Width           =   2535
   End
End
Attribute VB_Name = "frmRegFunctions"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Private Sub cmdQueryValue_Click()
   Dim MyLong&, Buffer$, BufferSize&, Temp&
   
   Buffer$ = String(255, 0)
   BufferSize& = 256
   
   MyLong& = RegOpenKey(h8&, "MSOfficeSetup\\ACCESS", Temp&)
   
   MsgBox "" & MyLong&
   
End Sub


