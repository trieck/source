Attribute VB_Name = "basTCipher"
Private key_table As Variant
Const public_key& = &HCAFEBABE

Sub main()
    Call Initialize_Key_Table
    
    Dim s As String, enc As String, dec As String
    
    s = "To be or not to be,"
    enc = TEncipher(s, public_key)
    dec = TEncipher(enc, public_key)
    
End Sub


Function TEncipher(ByVal s As String, ByVal key As Long) As String
    Dim output As String
    Dim c As Byte
        
    For i = 1 To Len(s)
        c = Asc(Mid(s, i, 1))
        c = rotor_one(c, key)
        c = rotor_two(c, key)
        c = rotor_three(c, key)
        c = rotor_four(c, key)
        c = rotor_four(Not c, Not key)
        c = rotor_three(c, Not key)
        c = rotor_two(c, Not key)
        c = rotor_one(c, Not key)
        output = output & Chr(c)
    Next i
    
    TEncipher = output
End Function


Function rotor_one(ByVal c As Byte, key As Long) As Byte
    Dim index As Integer
    index = ((key And &HFF000000) / 2 ^ 24) And &HFF
    rotor_one = (c + key_table(index)) And &HFF
End Function

Function rotor_two(ByVal c As Byte, key As Long) As Byte
    Dim index As Integer
    index = ((key And &HFF0000) / 2 ^ 16) And &HFF
    rotor_two = (c + key_table(index)) And &HFF
End Function

Function rotor_three(ByVal c As Byte, key As Long) As Byte
    Dim index As Integer
    index = ((key And &HFF00) / 2 ^ 8) And &HFF
    rotor_three = (c + key_table(index)) And &HFF
End Function

Function rotor_four(ByVal c As Byte, key As Long) As Byte
    Dim index As Integer
    index = (key And &HFF)
    rotor_four = (c + key_table(index)) And &HFF
End Function

Sub Initialize_Key_Table()
    key_table = Array(&H23, &H30, &HD7, &H7B, &H59, &H1B, &HD9, &HB7, &HF7, &HDE, &HCB, &H60, &HF6, &H69, &H5F, &HE9, _
        &H9A, &H17, &H46, &H61, &H9C, &H3, &H5E, &H41, &HBA, &H78, &H4D, &H4F, &HE5, &H76, &HC4, &H2, _
        &HB, &H26, &H84, &H1D, &H92, &HA0, &HA5, &HC, &H16, &HCF, &H4, &HA8, &HF8, &H40, &H49, &H53, _
        &H8, &HC8, &H86, &H2D, &H43, &H51, &HE7, &HD2, &H9B, &H56, &H81, &H38, &HAD, &H2B, &HAA, &H91, _
        &H7, &HA, &HE2, &H5D, &H3E, &HFA, &HCA, &HB8, &HB1, &H5B, &H14, &HF9, &H83, &H2C, &HC9, &H82, _
        &HEA, &H4C, &H45, &H35, &H42, &H4A, &H58, &HD1, &HFB, &H3C, &H70, &HA9, &HCD, &H3A, &HCC, &HBB, _
        &HB3, &HAB, &HBD, &H73, &H29, &HA4, &HBF, &HFD, &H1F, &H7C, &HA1, &H85, &HA3, &H68, &H20, &HE1, _
        &H34, &H3D, &H0, &HF0, &HC0, &H47, &H8C, &H1C, &H89, &H6A, &H93, &HFF, &H6C, &H80, &HB2, &HB0, _
        &HDB, &H6E, &H6F, &H8B, &H13, &H6B, &H97, &H25, &HB9, &H9, &H5A, &H96, &H54, &HE0, &H7A, &HF5, _
        &HBC, &H1, &H90, &HD3, &H94, &H8E, &HED, &H5, &H27, &HE4, &H31, &HAE, &H18, &H2E, &HC1, &HD8, _
        &H21, &H4B, &HA2, &HD5, &H6, &HA7, &H39, &HCE, &HC3, &HBE, &HAC, &HE6, &H7D, &HE, &H2F, &HFC, _
        &HDD, &HE3, &HEE, &H48, &H63, &HF1, &HAF, &H71, &H4E, &HC7, &H24, &HD4, &H1E, &H36, &H9F, &H62, _
        &HC6, &HF3, &HC2, &HD6, &HEC, &HC5, &HDC, &H10, &H74, &H98, &HFE, &H66, &HEF, &H64, &HF2, &H87, _
        &H8A, &H75, &H28, &H52, &H22, &H44, &HDA, &H55, &H79, &HB6, &H65, &H3B, &H50, &HE8, &HB5, &H15, _
        &HF4, &HEB, &H33, &H1A, &HF, &H88, &H57, &H5C, &H11, &H6D, &HB4, &H19, &H77, &H67, &HD0, &HA6, _
        &H95, &HD, &H2A, &HDF, &H32, &H9D, &H37, &H3F, &H99, &H8F, &H7F, &H8D, &H12, &H72, &H7E, &H9E)
End Sub

