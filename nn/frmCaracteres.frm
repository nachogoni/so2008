VERSION 5.00
Begin VB.Form frmCaracteres 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Caracteres para Display"
   ClientHeight    =   3825
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4920
   ClipControls    =   0   'False
   Icon            =   "frmCaracteres.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3825
   ScaleWidth      =   4920
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdFuncion 
      Caption         =   "_FUNCION_"
      Height          =   255
      Left            =   3600
      TabIndex        =   17
      Top             =   3480
      Width           =   1215
   End
   Begin VB.CommandButton cmdHexaToScreen 
      Caption         =   "He&xa a cartel"
      Height          =   255
      Left            =   120
      TabIndex        =   16
      Top             =   1080
      Width           =   4695
   End
   Begin VB.TextBox txtHexa 
      Appearance      =   0  'Flat
      Height          =   855
      Left            =   120
      MultiLine       =   -1  'True
      TabIndex        =   15
      Text            =   "frmCaracteres.frx":0442
      Top             =   120
      Width           =   4695
   End
   Begin VB.CommandButton cmdSalir 
      Caption         =   "&Salir"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   3360
      Width           =   1215
   End
   Begin VB.TextBox txtColumnas 
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Text            =   "16"
      Top             =   1680
      Width           =   1215
   End
   Begin VB.TextBox txtEtiqueta 
      Height          =   285
      Left            =   120
      TabIndex        =   1
      Text            =   "_Etiq1_"
      Top             =   2400
      Width           =   1215
   End
   Begin VB.CommandButton cmdGuarda 
      Caption         =   "&Guardar"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "&Borrar"
      Height          =   255
      Left            =   1560
      TabIndex        =   3
      Top             =   3480
      Width           =   1935
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   230
      Index           =   7
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   12
      TabStop         =   0   'False
      Top             =   3120
      Width           =   230
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   230
      Index           =   6
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   11
      TabStop         =   0   'False
      Top             =   2880
      Width           =   230
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   230
      Index           =   5
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   10
      TabStop         =   0   'False
      Top             =   2640
      Width           =   230
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   230
      Index           =   4
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   9
      TabStop         =   0   'False
      Top             =   2400
      Width           =   230
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   230
      Index           =   3
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   2160
      Width           =   230
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   230
      Index           =   2
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   1920
      Width           =   230
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   230
      Index           =   1
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   1680
      Width           =   230
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   230
      Index           =   0
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   5
      TabStop         =   0   'False
      Top             =   1440
      Width           =   230
   End
   Begin VB.Label lblColumnas 
      Alignment       =   2  'Center
      Caption         =   "Columnas (>=8):"
      Height          =   195
      Left            =   120
      TabIndex        =   14
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label lblEtiqueta 
      Alignment       =   2  'Center
      Caption         =   "Etiqueta:"
      Height          =   195
      Left            =   120
      TabIndex        =   13
      Top             =   2160
      Width           =   1215
   End
End
Attribute VB_Name = "frmCaracteres"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Columnas As Integer

Private Sub cmdClear_Click()
    Dim i As Integer
    For i = 0 To Columnas * 8 - 1
        pic(i).BackColor = vbWhite
    Next
    txtHexa.text = GeneraHexa(False)
End Sub

Private Sub cmdFuncion_Click()
    If Coma Then
        Anexo = ", "
        Cant = 1
    Else
        Anexo = " "
        Cant = 0
    End If
    For i = 1 To Columnas
        Parcial(0) = 0
        Parcial(1) = 0
        Parcial(2) = 0
        For X = 0 To 7
            DoEvents
            Select Case pic((i - 1) * 8 + X).BackColor
                Case vbBlack:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbRed:
                    Parcial(0) = Parcial(0) + (2 ^ X)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbBlue:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
                    Parcial(2) = Parcial(2) + (2 ^ X)
                Case vbGreen:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
                    Parcial(1) = Parcial(1) + (2 ^ X)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbYellow:
                    Parcial(0) = Parcial(0) + (2 ^ X)
                    Parcial(1) = Parcial(1) + (2 ^ X)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbCyan:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
                    Parcial(1) = Parcial(1) + (2 ^ X)
                    Parcial(2) = Parcial(2) + (2 ^ X)
                Case vbMagenta:
                    Parcial(0) = Parcial(0) + (2 ^ X)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
                    Parcial(2) = Parcial(2) + (2 ^ X)
                Case vbWhite:
                    Parcial(0) = Parcial(0) + (2 ^ X)
                    Parcial(1) = Parcial(1) + (2 ^ X)
                    Parcial(2) = Parcial(2) + (2 ^ X)
            End Select
        Next
        If Coma Then n = ","
        ParcialStr = "0x" & Hex(Parcial(0)) & n & " 0x" & Hex(Parcial(1)) & n & " 0x" & Hex(Parcial(2))
        Salida = Salida & ParcialStr & Anexo
    Next
End Sub

Private Sub cmdGuarda_Click()
    Dim Ruta As String, Salida As String
    Salida = txtEtiqueta.text & ":" & Chr(9) & "db " & Chr(9) & GeneraHexa(True)
    Ruta = App.Path
    If Right(Ruta, 1) <> "\" Then
        Ruta = Ruta & "\"
    End If
    Open Ruta & "salida.txt" For Append As #1
        Print #1, Salida
    Close
End Sub

Private Function hextodec(text As String) As Integer
    Dim l As String
    resp = 0
    For i = 1 To Len(text)
        l = UCase(Mid(text, i, 1))
        If l >= "A" And l <= "F" Then
            resp = resp * (16 ^ (i - 1)) + (10 + (Asc(l) - Asc("A")))
        ElseIf l >= "0" And l <= "9" Then
            resp = resp * (16 ^ (i - 1)) + Val(l)
        End If
    Next
    hextodec = resp
End Function

Private Sub cmdHexaToScreen_Click()
    columna = 1
    fila = 0
    r = -1
    g = 0
    b = 0
    For n = 1 To Len(txtHexa.text)
        l = Mid(txtHexa.text, n, 1)
        If b = -1 And l = "x" Then
            b = hextodec(Mid(txtHexa.text, n + 1, 2))
            n = n + 2
        End If
        If g = -1 And l = "x" Then
            g = hextodec(Mid(txtHexa.text, n + 1, 2))
            n = n + 2
            b = -1
        End If
        If r = -1 And l = "x" Then
            r = hextodec(Mid(txtHexa.text, n + 1, 2))
            n = n + 2
            g = -1
        End If
        If (r > -1 And g > -1 And b > -1) Then
            For fila = 0 To 7
                rr = r And &H1
                gg = g And &H1
                bb = b And &H1
                If rr = 1 And gg = 1 And bb = 1 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbWhite
                ElseIf rr = 1 And gg = 1 And bb = 0 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbYellow
                ElseIf rr = 1 And gg = 0 And bb = 1 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbMagenta
                ElseIf rr = 1 And gg = 0 And bb = 0 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbRed
                ElseIf rr = 0 And gg = 1 And bb = 1 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbCyan
                ElseIf rr = 0 And gg = 1 And bb = 0 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbGreen
                ElseIf rr = 0 And gg = 0 And bb = 1 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbBlue
                ElseIf rr = 0 And gg = 0 And bb = 0 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbBlack
                End If
                r = r \ 2
                g = g \ 2
                b = b \ 2
            Next
            columna = columna + 1
            r = -1
        End If
    Next
End Sub

Private Sub cmdSalir_Click()
    Dim resp As Long
    resp = MsgBox("¿Desea salir?", vbYesNo + vbQuestion, "Caracteres")
    If resp = vbYes Then Unload Me
End Sub

Private Sub Form_Load()
    Columnas = 1
    ActualizarColumnas
    cmdClear_Click
    txtHexa.text = GeneraHexa(False)
End Sub

Private Sub Form_Resize()
    txtHexa.Width = Me.Width
    txtHexa.Left = -10
    cmdHexaToScreen.Width = Me.Width
    cmdHexaToScreen.Left = -10
End Sub

Private Sub pic_MouseUp(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    ' left click
    If Button = 1 Then
        If pic(Index).BackColor = vbWhite Then
            pic(Index).BackColor = vbBlack
        ElseIf pic(Index).BackColor = vbBlack Then
            pic(Index).BackColor = vbRed
        ElseIf pic(Index).BackColor = vbRed Then
            pic(Index).BackColor = vbBlue
        ElseIf pic(Index).BackColor = vbBlue Then
            pic(Index).BackColor = vbGreen
        ElseIf pic(Index).BackColor = vbGreen Then
            pic(Index).BackColor = vbYellow
        ElseIf pic(Index).BackColor = vbYellow Then
            pic(Index).BackColor = vbCyan
        ElseIf pic(Index).BackColor = vbCyan Then
            pic(Index).BackColor = vbMagenta
        ElseIf pic(Index).BackColor = vbMagenta Then
            pic(Index).BackColor = vbWhite
        End If
    End If
    ' right click
    If Button = 2 Then
        If pic(Index).BackColor = vbWhite Then
            pic(Index).BackColor = vbMagenta
        ElseIf pic(Index).BackColor = vbRed Then
            pic(Index).BackColor = vbBlack
        ElseIf pic(Index).BackColor = vbBlack Then
            pic(Index).BackColor = vbWhite
        ElseIf pic(Index).BackColor = vbBlue Then
            pic(Index).BackColor = vbRed
        ElseIf pic(Index).BackColor = vbGreen Then
            pic(Index).BackColor = vbBlue
        ElseIf pic(Index).BackColor = vbYellow Then
            pic(Index).BackColor = vbGreen
        ElseIf pic(Index).BackColor = vbCyan Then
            pic(Index).BackColor = vbYellow
        ElseIf pic(Index).BackColor = vbMagenta Then
            pic(Index).BackColor = vbCyan
        End If
    End If
    txtHexa.text = GeneraHexa(False)
End Sub

Private Sub txtColumnas_Change()
    If Val(txtColumnas.text) >= 1 And Val(txtColumnas.text) <= 56 Then ActualizarColumnas
End Sub

Private Sub txtColumnas_KeyPress(KeyAscii As Integer)
    If Not (KeyAscii >= Asc("0") And KeyAscii <= Asc("9") Or KeyAscii = 8) Then
        KeyAscii = 0
    End If
End Sub

Private Sub ActualizarColumnas()
    Dim i As Integer, X As Integer
    Dim Cols As Integer
    Cols = txtColumnas.text
    txtColumnas.Locked = True
    If Cols < Columnas Then
        'Descarga los pics que no se usaran-
        For i = Cols + 1 To Columnas
            For X = 0 To 7
                DoEvents
                Unload pic((i - 1) * 8 + X)
            Next
        Next
    End If
    If Cols > Columnas Then
        'Carga pics nuevos
        For i = Columnas To Cols - 1
            For X = 0 To 7
                DoEvents
                Load pic(i * 8 + X)
                pic(i * 8 + X).Visible = True
                pic(i * 8 + X).Top = pic((i - 1) * 8 + X).Top
                pic(i * 8 + X).Left = pic((i - 1) * 8 + X).Left + 255 - 15
            Next
        Next
    End If
    txtColumnas.Locked = False
    Columnas = Cols
    cmdClear.Width = 241 * (Columnas)
    Me.Width = pic(pic.UBound).Left + pic(pic.UBound).Width + 230
    txtHexa.text = GeneraHexa(False)
End Sub

Private Function GeneraHexa(Coma As Boolean) As String
    Dim i As Integer, X As Integer, Parcial(0 To 2) As Integer
    Dim Cant As Byte
    Dim Salida As String, Anexo As String, ParcialStr As String
    If Coma Then
        Anexo = ", "
        Cant = 1
    Else
        Anexo = " "
        Cant = 0
    End If
    For i = 1 To Columnas
        Parcial(0) = 0
        Parcial(1) = 0
        Parcial(2) = 0
        For X = 0 To 7
            DoEvents
            Select Case pic((i - 1) * 8 + X).BackColor
                Case vbBlack:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbRed:
                    Parcial(0) = Parcial(0) + (2 ^ X)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbBlue:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
                    Parcial(2) = Parcial(2) + (2 ^ X)
                Case vbGreen:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
                    Parcial(1) = Parcial(1) + (2 ^ X)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbYellow:
                    Parcial(0) = Parcial(0) + (2 ^ X)
                    Parcial(1) = Parcial(1) + (2 ^ X)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbCyan:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
                    Parcial(1) = Parcial(1) + (2 ^ X)
                    Parcial(2) = Parcial(2) + (2 ^ X)
                Case vbMagenta:
                    Parcial(0) = Parcial(0) + (2 ^ X)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
                    Parcial(2) = Parcial(2) + (2 ^ X)
                Case vbWhite:
                    Parcial(0) = Parcial(0) + (2 ^ X)
                    Parcial(1) = Parcial(1) + (2 ^ X)
                    Parcial(2) = Parcial(2) + (2 ^ X)
            End Select
        Next
        If Coma Then n = ","
        ParcialStr = "0x" & Hex(Parcial(0)) & n & " 0x" & Hex(Parcial(1)) & n & " 0x" & Hex(Parcial(2))
        Salida = Salida & ParcialStr & Anexo
    Next
    GeneraHexa = Trim(Left(Salida, Len(Salida) - Cant))
End Function
