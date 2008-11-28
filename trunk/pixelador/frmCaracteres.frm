VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form frmCaracteres 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Pixelador para FLEDS ;)"
   ClientHeight    =   3870
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4920
   ClipControls    =   0   'False
   Icon            =   "frmCaracteres.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3870
   ScaleWidth      =   4920
   StartUpPosition =   3  'Windows Default
   Begin MSCommLib.MSComm comm 
      Left            =   4320
      Top             =   2040
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      BaudRate        =   115200
   End
   Begin VB.PictureBox pic1 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BackColor       =   &H00000000&
      ForeColor       =   &H80000008&
      Height          =   510
      Left            =   4320
      ScaleHeight     =   32
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   32
      TabIndex        =   18
      Top             =   1440
      Visible         =   0   'False
      Width           =   510
   End
   Begin VB.CommandButton cmdImagen 
      Caption         =   "Cargar imagen"
      Height          =   255
      Left            =   120
      TabIndex        =   17
      Top             =   2040
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
   Begin VB.CommandButton cmdEnviar 
      Caption         =   "&Enviar"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   3480
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
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CommandButton cmdGuarda 
      Caption         =   "&Guardar"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   3120
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
   Begin MSComDlg.CommonDialog cd 
      Left            =   4320
      Top             =   3360
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
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
      Top             =   2520
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
        pic(i).BackColor = vbBlack
    Next
    txtHexa.text = GeneraHexa(False)
End Sub

Private Sub cmdEnviar_Click()
    Dim i As Integer, X As Integer, parcial(0 To 2) As Integer
    
    If Not comm.PortOpen Then
        comm.PortOpen = True
    End If
   
    For i = 1 To Columnas
        parcial(0) = 0
        parcial(1) = 0
        parcial(2) = 0
        For X = 0 To 7
            DoEvents
            Select Case pic((i - 1) * 8 + X).BackColor
                Case vbBlack:
                Case vbRed:
                    parcial(0) = parcial(0) + (2 ^ X)
                Case vbBlue:
                    parcial(2) = parcial(2) + (2 ^ X)
                Case vbGreen:
                    parcial(1) = parcial(1) + (2 ^ X)
                Case vbYellow:
                    parcial(0) = parcial(0) + (2 ^ X)
                    parcial(1) = parcial(1) + (2 ^ X)
                Case vbCyan:
                    parcial(1) = parcial(1) + (2 ^ X)
                    parcial(2) = parcial(2) + (2 ^ X)
                Case vbMagenta:
                    parcial(0) = parcial(0) + (2 ^ X)
                    parcial(2) = parcial(2) + (2 ^ X)
                Case vbWhite:
                    parcial(0) = parcial(0) + (2 ^ X)
                    parcial(1) = parcial(1) + (2 ^ X)
                    parcial(2) = parcial(2) + (2 ^ X)
            End Select
        Next
        
        comm.Output = (Asc("@") + i) & parcial(0) & parcial(1) & parcial(2)
    Next i
End Sub

Private Sub cmdGuarda_Click()
    Dim Ruta As String, Salida As String, hexa As String
    hexa = GeneraHexa(True)
    Salida = "char " & txtEtiqueta.text & "[] = {" & Left(hexa, Len(hexa) - 1) & "};"
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

Private Sub cmdImagen_Click()
    Dim i As Integer, j As Integer, ii As Integer, jj As Integer, iii As Integer, jjj As Integer
    Dim espaciado As Integer, columna As Integer, fila As Integer
    
    On Error GoTo err
    
    fila = 0
    columna = 1
     cd.ShowOpen
    If cd.FileName <> "" Then
        pic1.Picture = LoadPicture(cd.FileName)
        
        On Error Resume Next
        
        espaciado = pic1.ScaleWidth / txtColumnas.text
        ii = 0
        iii = 1
        For i = 1 To pic1.ScaleWidth Step pic1.ScaleWidth / Columnas
            jj = 0
            jjj = 0
            For j = 1 To pic1.ScaleHeight Step pic1.ScaleHeight / 8
                DoEvents
                jj = jj + espaciado
                jjj = jjj + 1
                col = pic1.Point(i, j)
                r = col Mod 256
                g = (col / 256) Mod 256
                b = ((col / 256) / 256) Mod 256
                
                If r > 127 Then
                    r = 255
                Else
                    r = 0
                End If
                If g > 127 Then
                    g = 255
                Else
                    g = 0
                End If
                If b > 127 Then
                    b = 255
                Else
                    b = 0
                End If
                
                
                If r = 255 And g = 255 And b = 255 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbWhite
                ElseIf r = 255 And g = 255 And b = 0 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbYellow
                ElseIf r = 255 And g = 0 And b = 255 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbMagenta
                ElseIf r = 255 And g = 0 And b = 0 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbRed
                ElseIf r = 0 And g = 255 And b = 255 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbCyan
                ElseIf r = 0 And g = 255 And b = 0 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbGreen
                ElseIf r = 0 And g = 0 And b = 255 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbBlue
                ElseIf r = 0 And g = 0 And b = 0 Then
                    pic((columna - 1) * 8 + fila).BackColor = vbBlack
                End If
                fila = fila + 1
            Next
            ii = ii + espaciado
            iii = iii + 1
        Next
        columna = columna + 1
        txtHexa.text = GeneraHexa(False)
        punto = Len(cd.FileName)
        For i = Len(cd.FileName) To 1 Step -1
            If (Mid(cd.FileName, i, 1) = ".") Then punto = i
            If (Mid(cd.FileName, i, 1) = "\") Then Exit For
        Next i
        txtEtiqueta.text = Mid(cd.FileName, i + 1, punto - i - 1)
    End If
    Exit Sub
err:
    MsgBox "Error al abrir la imagen...", vbCritical + vbOKOnly, "Pixelador"
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

Private Sub Form_Unload(Cancel As Integer)
    Dim resp As Long
    resp = MsgBox("¿Desea salir?", vbYesNo + vbQuestion, "Pixelador")
    If resp = vbNo Then Cancel = 1
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
    Dim i As Integer, X As Integer, parcial(0 To 2) As Integer
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
        parcial(0) = 0
        parcial(1) = 0
        parcial(2) = 0
        For X = 0 To 7
            DoEvents
            Select Case pic((i - 1) * 8 + X).BackColor
                Case vbBlack:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbRed:
                    parcial(0) = parcial(0) + (2 ^ X)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbBlue:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
                    parcial(2) = parcial(2) + (2 ^ X)
                Case vbGreen:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
                    parcial(1) = parcial(1) + (2 ^ X)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbYellow:
                    parcial(0) = parcial(0) + (2 ^ X)
                    parcial(1) = parcial(1) + (2 ^ X)
'                    Parcial(2) = Parcial(2) + (2 ^ x)
                Case vbCyan:
'                    Parcial(0) = Parcial(0) + (2 ^ x)
                    parcial(1) = parcial(1) + (2 ^ X)
                    parcial(2) = parcial(2) + (2 ^ X)
                Case vbMagenta:
                    parcial(0) = parcial(0) + (2 ^ X)
'                    Parcial(1) = Parcial(1) + (2 ^ x)
                    parcial(2) = parcial(2) + (2 ^ X)
                Case vbWhite:
                    parcial(0) = parcial(0) + (2 ^ X)
                    parcial(1) = parcial(1) + (2 ^ X)
                    parcial(2) = parcial(2) + (2 ^ X)
            End Select
        Next
        If Coma Then n = ","
        ParcialStr = "0x" & Hex(parcial(0)) & n & " 0x" & Hex(parcial(1)) & n & " 0x" & Hex(parcial(2))
        Salida = Salida & ParcialStr & Anexo
    Next
    GeneraHexa = Trim(Left(Salida, Len(Salida) - Cant))
End Function
