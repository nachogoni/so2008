Attribute VB_Name = "Module1"
'Apis - Color del pixel
Public Declare Function GetPixel Lib "gdi32" (ByVal hdc As Long, ByVal X As Long, ByVal Y As Long) As Long
Public Declare Function SetPixel Lib "gdi32.dll" (ByVal hdc As Long, ByVal X As Long, ByVal Y As Long, ByVal crColor As Long) As Long
  
'Mouse
Public Type POINTAPI
  X As Long
  Y As Long
End Type
Public Declare Function GetCursorPos Lib "USER32" (lpPoint As POINTAPI) As Long

'WinAmp
Public Declare Function FindWindow Lib "USER32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Public hWndWinamp As Long, WinAmpDC As Long

'Windows
Public Declare Function GetWindowDC Lib "USER32" (ByVal hwnd As Long) As Long

Function WinAMP_FindWindow() As Boolean
    
    hWndWinamp = FindWindow("Winamp v1.x", vbNullString)
    
    If hWndWinamp <> 0 Then
        WinAMP_FindWindow = True
    Else
        WinAMP_FindWindow = False
    End If

End Function


