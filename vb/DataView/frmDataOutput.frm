VERSION 4.00
Begin VB.Form frmDataOutput 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Data Output"
   ClientHeight    =   4545
   ClientLeft      =   2235
   ClientTop       =   1530
   ClientWidth     =   6300
   Height          =   4950
   Icon            =   "frmDataOutput.frx":0000
   Left            =   2175
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   NegotiateMenus  =   0   'False
   ScaleHeight     =   4545
   ScaleWidth      =   6300
   ShowInTaskbar   =   0   'False
   Top             =   1185
   Width           =   6420
   Begin VB.Data datDataOutput 
      BackColor       =   &H00C0C0C0&
      Connect         =   "Access"
      DatabaseName    =   ""
      Exclusive       =   0   'False
      Height          =   300
      Left            =   120
      Options         =   0
      ReadOnly        =   0   'False
      RecordsetType   =   2  'Snapshot
      RecordSource    =   "NAMES"
      Top             =   4200
      Width           =   6015
   End
   Begin MSDBGrid.DBGrid dbgDataOutput 
      Bindings        =   "frmDataOutput.frx":030A
      Height          =   3975
      Left            =   120
      OleObjectBlob   =   "frmDataOutput.frx":0320
      TabIndex        =   0
      Top             =   120
      Width           =   6015
   End
End
Attribute VB_Name = "frmDataOutput"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

