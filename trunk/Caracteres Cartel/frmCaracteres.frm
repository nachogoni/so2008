VERSION 5.00
Begin VB.Form frmCaracteres 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Caracteres para Display"
   ClientHeight    =   2895
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4920
   ClipControls    =   0   'False
   Icon            =   "frmCaracteres.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2895
   ScaleWidth      =   4920
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdSalir 
      Caption         =   "&Salir"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   2400
      Width           =   1215
   End
   Begin VB.TextBox txtColumnas 
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Text            =   "32"
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox txtEtiqueta 
      Height          =   285
      Left            =   120
      TabIndex        =   1
      Text            =   "_Etiq1_"
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CommandButton cmdGuarda 
      Caption         =   "&Guardar"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   1920
      Width           =   1215
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "&Borrar"
      Height          =   255
      Left            =   1560
      TabIndex        =   3
      Top             =   2520
      Width           =   1935
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   7
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   12
      TabStop         =   0   'False
      Top             =   2160
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   6
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   11
      TabStop         =   0   'False
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   5
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   10
      TabStop         =   0   'False
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   4
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   9
      TabStop         =   0   'False
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   3
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   2
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   1
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   1560
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   5
      TabStop         =   0   'False
      Top             =   480
      Width           =   255
   End
   Begin VB.Label lblHexa 
      Alignment       =   2  'Center
      Caption         =   "Label1"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   6.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   0
      TabIndex        =   15
      Top             =   120
      Width           =   480
   End
   Begin VB.Label lblColumnas 
      Alignment       =   2  'Center
      Caption         =   "Columnas (>=8):"
      Height          =   195
      Left            =   120
      TabIndex        =   14
      Top             =   480
      Width           =   1215
   End
   Begin VB.Label lblEtiqueta 
      Alignment       =   2  'Center
      Caption         =   "Etiqueta:"
      Height          =   195
      Left            =   120
      TabIndex        =   13
      Top             =   1200
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
    lblHexa.Caption = GeneraHexa(False)
End Sub

Private Sub cmdGuarda_Click()
    Dim Ruta As String, Salida As String
    Salida = txtEtiqueta.Text & ":" & Chr(9) & "db " & Chr(9) & GeneraHexa(True)
    Ruta = App.Path
    If Right(Ruta, 1) <> "\" Then
        Ruta = Ruta & "\"
    End If
    Open Ruta & "salida.txt" For Append As #1
        Print #1, Salida
    Close
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
    lblHexa.Caption = GeneraHexa(False)
End Sub

Private Sub Form_Resize()
    lblHexa.Width = Me.Width
End Sub

Private Sub pic_Click(Index As Integer)
    If pic(Index).BackColor = vbWhite Then
        pic(Index).BackColor = vbBlack
    Else
        pic(Index).BackColor = vbWhite
    End If
    lblHexa.Caption = GeneraHexa(False)
End Sub

Private Sub txtColumnas_Change()
    If Val(txtColumnas.Text) >= 1 And Val(txtColumnas.Text) <= 56 Then ActualizarColumnas
End Sub

Private Sub txtColumnas_KeyPress(KeyAscii As Integer)
    If Not (KeyAscii >= Asc("0") And KeyAscii <= Asc("9") Or KeyAscii = 8) Then
        KeyAscii = 0
    End If
End Sub

Private Sub ActualizarColumnas()
    Dim i As Integer, x As Integer
    Dim Cols As Integer
    Cols = txtColumnas.Text
    txtColumnas.Locked = True
    If Cols < Columnas Then
        'Descarga los pics que no se usaran-
        For i = Cols + 1 To Columnas
            For x = 0 To 7
                DoEvents
                Unload pic((i - 1) * 8 + x)
            Next
        Next
    End If
    If Cols > Columnas Then
        'Carga pics nuevos
        For i = Columnas To Cols - 1
            For x = 0 To 7
                DoEvents
                Load pic(i * 8 + x)
                pic(i * 8 + x).Visible = True
                pic(i * 8 + x).Top = pic((i - 1) * 8 + x).Top
                pic(i * 8 + x).Left = pic((i - 1) * 8 + x).Left + pic((i - 1) * 8 + x).Width - 15
            Next
        Next
    End If
    txtColumnas.Locked = False
    Columnas = Cols
    cmdClear.Width = 241 * (Columnas)
    Me.Width = pic(pic.UBound).Left + pic(pic.UBound).Width + 230
    lblHexa.Caption = GeneraHexa(False)
End Sub

Private Function GeneraHexa(Coma As Boolean) As String
    Dim i As Integer, x As Integer, Parcial As Integer
    Dim Cant As Byte
    Dim Salida As String, Anexo As String
    If Coma Then
        Anexo = "h, "
        Cant = 2
    Else
        Anexo = "h "
        Cant = 1
    End If
    For i = 1 To Columnas
        For x = 0 To 7
            DoEvents
            If pic((i - 1) * 8 + x).BackColor = vbBlack Then Parcial = Parcial + (2 ^ x)
        Next
        Salida = Salida & Format(Hex(Parcial), "00") & Anexo
        Parcial = 0
    Next
    GeneraHexa = Trim(Left(Salida, Len(Salida) - Cant))
End Function
