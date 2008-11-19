VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   690
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2490
   LinkTopic       =   "Form1"
   ScaleHeight     =   690
   ScaleWidth      =   2490
   StartUpPosition =   3  'Windows Default
   Begin MSCommLib.MSComm comm 
      Left            =   1920
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      OutBufferSize   =   16000
      BaudRate        =   115200
   End
   Begin VB.Timer Timer1 
      Interval        =   50
      Left            =   0
      Top             =   0
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Inc As Long, Terminar As Boolean

Private Sub Dibuja_EQ()
    Dim i As Integer, j As Integer, col As Long, X As Integer, Y As Integer
    
    comm.Output = "R"
    
    For X = 20 To 100 Step 5
        i = i + Inc
        j = 0
        DoEvents
        
        r = 0
        g = 0
        b = 0
        
        For Y = 60 To 40 Step -3
            j = j + Inc
            DoEvents
            col = GetPixel(WinAmpDC, X, Y)
            SetPixel Me.hdc, i + 0, j + 0, col
            SetPixel Me.hdc, i + 1, j + 0, col
            SetPixel Me.hdc, i + 0, j + 1, col
            SetPixel Me.hdc, i + 1, j + 1, col
            
            
            rr = col Mod 256
            gg = (col / 256) Mod 256
            bb = ((col / 256) / 256) Mod 256
            
            If rr > 127 Then
                '1
                r = r * 2 + 1
            Else
                '0
                r = r * 2
            End If
            If gg > 127 Then
                '1
                g = g * 2 + 1
            Else
                '0
                g = g * 2
            End If
            If bb > 127 Then
                '1
                b = b * 2 + 1
            Else
                '0
                b = b * 2
            End If
          
        Next
        
        comm.Output = Chr(r)
        comm.Output = Chr(g)
        comm.Output = Chr(b)
        
    Next
End Sub

Private Sub Obtiene_EQ()
    Dim i As Integer, j As Integer, col As Long, X As Integer, Y As Integer
    For X = 20 To 100 Step 4
        i = i + Inc
        j = 0
        DoEvents
        For Y = 40 To 60 Step 1
            j = j + Inc
            DoEvents
            col = GetPixel(WinAmpDC, X, Y)
            SetPixel Me.hdc, i + 0, j + 0, col
            SetPixel Me.hdc, i + 1, j + 0, col
            SetPixel Me.hdc, i + 0, j + 1, col
            SetPixel Me.hdc, i + 1, j + 1, col
        Next
    Next
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
'    Terminar = False
'    Do While Not Terminar
'        Dibuja_EQ
'    Loop
End Sub

Private Sub Form_Load()
    WinAMP_FindWindow
    Inc = 2
    WinAmpDC = GetWindowDC(hWndWinamp)
    comm.PortOpen = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    comm.PortOpen = False
    Terminar = True
End Sub

Private Sub Timer1_Timer()
    Dibuja_EQ
End Sub
