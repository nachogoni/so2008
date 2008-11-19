VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   BackColor       =   &H00000000&
   Caption         =   "Form1"
   ClientHeight    =   11985
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   17970
   LinkTopic       =   "Form1"
   ScaleHeight     =   11985
   ScaleWidth      =   17970
   StartUpPosition =   1  'CenterOwner
   Begin VB.TextBox txt 
      Height          =   4455
      Left            =   9720
      TabIndex        =   39
      Top             =   6840
      Width           =   7455
   End
   Begin MSCommLib.MSComm comm 
      Left            =   120
      Top             =   2040
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      BaudRate        =   115200
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Enviar"
      Height          =   495
      Left            =   120
      TabIndex        =   38
      Top             =   1440
      Width           =   1215
   End
   Begin VB.VScrollBar VScroll1 
      Height          =   6735
      LargeChange     =   50
      Left            =   720
      Max             =   500
      Min             =   10
      SmallChange     =   10
      TabIndex        =   37
      Top             =   3960
      Value           =   10
      Width           =   255
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   10
      Left            =   120
      Top             =   4080
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   31
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   36
      Top             =   11400
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   30
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   35
      Top             =   11040
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   29
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   34
      Top             =   10680
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   28
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   33
      Top             =   10320
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   27
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   32
      Top             =   9960
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   26
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   31
      Top             =   9600
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   25
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   30
      Top             =   9240
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   24
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   29
      Top             =   8880
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   23
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   28
      Top             =   8520
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   22
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   27
      Top             =   8160
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   21
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   26
      Top             =   7800
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   20
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   25
      Top             =   7440
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   19
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   24
      Top             =   7080
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   18
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   23
      Top             =   6720
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   17
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   22
      Top             =   6360
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   16
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   21
      Top             =   6000
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   15
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   20
      Top             =   5640
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   14
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   19
      Top             =   5280
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   13
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   18
      Top             =   4920
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   12
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   17
      Top             =   4560
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   11
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   16
      Top             =   4200
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   10
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   15
      Top             =   3840
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   9
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   14
      Top             =   3480
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   8
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   13
      Top             =   3120
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   7
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   12
      Top             =   2760
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   6
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   11
      Top             =   2400
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   5
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   10
      Top             =   2040
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   4
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   9
      Top             =   1680
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   3
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   8
      Top             =   1320
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   2
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   7
      Top             =   960
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   1
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   6
      Top             =   600
      Width           =   200
   End
   Begin VB.PictureBox p 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   200
      Index           =   0
      Left            =   9000
      ScaleHeight     =   165
      ScaleWidth      =   165
      TabIndex        =   5
      Top             =   240
      Width           =   200
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Animar"
      Height          =   495
      Left            =   120
      TabIndex        =   4
      Top             =   3240
      Width           =   1215
   End
   Begin MSComDlg.CommonDialog cd 
      Left            =   120
      Top             =   4560
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Pixelar"
      Height          =   495
      Left            =   120
      TabIndex        =   3
      Top             =   840
      Width           =   1215
   End
   Begin VB.PictureBox pic2 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BackColor       =   &H00000000&
      ForeColor       =   &H80000008&
      Height          =   9255
      Left            =   9360
      ScaleHeight     =   615
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   543
      TabIndex        =   2
      Top             =   240
      Width           =   8175
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Cargar imagen"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   240
      Width           =   1215
   End
   Begin VB.PictureBox pic1 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BackColor       =   &H00000000&
      ForeColor       =   &H80000008&
      Height          =   8175
      Left            =   1440
      ScaleHeight     =   543
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   495
      TabIndex        =   0
      Top             =   240
      Width           =   7455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim ancho As Integer
Dim alto As Integer
Dim espaciado As Integer
Dim colu As Integer
Dim sentido As Integer
Dim matriz() As Integer

Dim fleds() As Integer

Private Sub Command1_Click()
    cd.ShowOpen
    If cd.FileName <> "" Then
        pic1.Picture = LoadPicture(cd.FileName)
    End If
End Sub

Private Sub Command2_Click()
    ii = 0
    iii = 1
    pic2.Cls
    For i = 1 To pic1.ScaleWidth Step pic1.ScaleWidth / ancho
        jj = 0
        jjj = 0
        For j = 1 To pic1.ScaleHeight Step pic1.ScaleHeight / alto
            DoEvents
            jj = jj + espaciado
            jjj = jjj + 1
            col = pic1.Point(i, j)
            r = col Mod 256
            g = (col / 256) Mod 256
            b = ((col / 256) / 256) Mod 256
            gg = 0.3 * r + 0.59 * g + 0.11 * b
            gg = r + g + b
            If gg > 127 Then
                gg = 255
            Else
                gg = 0
            End If
'            pic2.Line (ii, jj)-(ii + 1, jj + 1), RGB(gg, gg, gg), BF
            pic2.Line (ii, jj)-(ii + 1, jj + 1), RGB(r, g, b), BF
            
            matriz(iii, jjj) = gg

            fleds(iii, jjj, 1) = r
            fleds(iii, jjj, 2) = g
            fleds(iii, jjj, 3) = b

        Next
        ii = ii + espaciado
        iii = iii + 1
    Next
    
    Me.Caption = ii & ":" & jj
End Sub

Private Sub Command3_Click()
    Timer1.Enabled = Not Timer1.Enabled
    pic1.Visible = Not Timer1.Enabled
    pic2.Visible = Not Timer1.Enabled
End Sub

Private Sub Command4_Click()
    If Not comm.PortOpen Then
        comm.PortOpen = True
    End If
    txt.Text = ""
    comm.Output = "R"
    For i = 1 To ancho
        r = 0
        g = 0
        b = 0
        For j = alto To 1 Step -1
            If fleds(i, j, 1) > 127 Then
                '1
                r = r * 2 + 1
            Else
                '0
                r = r * 2
            End If
            If fleds(i, j, 2) > 127 Then
                '1
                g = g * 2 + 1
            Else
                '0
                g = g * 2
            End If
            If fleds(i, j, 3) > 127 Then
                '1
                b = b * 2 + 1
            Else
                '0
                b = b * 2
            End If
        Next j
        comm.Output = Chr(r) & Chr(g) & Chr(b)
        txt.Text = txt.Text & Chr(r) & Chr(g) & Chr(b)
    Next i
End Sub

Private Sub Form_Load()
    ancho = 8
    alto = 8
    espaciado = 6
    colu = 1
    sentido = 1
    ReDim matriz(ancho, alto) As Integer
    ReDim fleds(ancho, alto, 3) As Integer
End Sub

Private Sub Form_Unload(Cancel As Integer)
    comm.PortOpen = False
End Sub

Private Sub Timer1_Timer()
    For i = 1 To alto
        p(i - 1).BackColor = RGB(matriz(colu, i), matriz(colu, i), matriz(colu, i))
    Next i
    If sentido = 1 Then
        colu = colu + 1
        If colu = ancho Then
            sentido = 0
        End If
    Else
        colu = colu - 1
        If colu = 0 Then
            sentido = 1
        End If
    End If
End Sub

Private Sub VScroll1_Change()
    Timer1.Interval = VScroll1.Value
    Me.Caption = VScroll1.Value
End Sub
