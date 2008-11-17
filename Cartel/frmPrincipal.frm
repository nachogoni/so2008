VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   9405
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   14745
   LinkTopic       =   "Form1"
   ScaleHeight     =   9405
   ScaleWidth      =   14745
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdIzq 
      Caption         =   "Izquiera"
      Height          =   495
      Left            =   1560
      TabIndex        =   130
      Top             =   2640
      Width           =   1215
   End
   Begin VB.CommandButton cmdRND 
      Caption         =   "RND"
      Height          =   495
      Left            =   240
      TabIndex        =   129
      Top             =   2640
      Width           =   1215
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   127
      Left            =   3840
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   128
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   126
      Left            =   3840
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   127
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   125
      Left            =   3840
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   126
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   124
      Left            =   3840
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   125
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   123
      Left            =   3840
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   124
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   122
      Left            =   3840
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   123
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   121
      Left            =   3840
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   122
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   120
      Left            =   3840
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   121
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   119
      Left            =   3600
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   120
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   118
      Left            =   3600
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   119
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   117
      Left            =   3600
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   118
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   116
      Left            =   3600
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   117
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   115
      Left            =   3600
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   116
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   114
      Left            =   3600
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   115
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   113
      Left            =   3600
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   114
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   112
      Left            =   3600
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   113
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   111
      Left            =   3360
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   112
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   110
      Left            =   3360
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   111
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   109
      Left            =   3360
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   110
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   108
      Left            =   3360
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   109
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   107
      Left            =   3360
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   108
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   106
      Left            =   3360
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   107
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   105
      Left            =   3360
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   106
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   104
      Left            =   3360
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   105
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   103
      Left            =   3120
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   104
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   102
      Left            =   3120
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   103
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   101
      Left            =   3120
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   102
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   100
      Left            =   3120
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   101
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   99
      Left            =   3120
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   100
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   98
      Left            =   3120
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   99
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   97
      Left            =   3120
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   98
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   96
      Left            =   3120
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   97
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   95
      Left            =   2880
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   96
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   94
      Left            =   2880
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   95
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   93
      Left            =   2880
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   94
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   92
      Left            =   2880
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   93
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   91
      Left            =   2880
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   92
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   90
      Left            =   2880
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   91
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   89
      Left            =   2880
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   90
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   88
      Left            =   2880
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   89
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   87
      Left            =   2640
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   88
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   86
      Left            =   2640
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   87
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   85
      Left            =   2640
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   86
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   84
      Left            =   2640
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   85
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   83
      Left            =   2640
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   84
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   82
      Left            =   2640
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   83
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   81
      Left            =   2640
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   82
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   80
      Left            =   2640
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   81
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   79
      Left            =   2400
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   80
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   78
      Left            =   2400
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   79
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   77
      Left            =   2400
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   78
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   76
      Left            =   2400
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   77
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   75
      Left            =   2400
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   76
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   74
      Left            =   2400
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   75
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   73
      Left            =   2400
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   74
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   72
      Left            =   2400
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   73
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   71
      Left            =   2160
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   72
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   70
      Left            =   2160
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   71
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   69
      Left            =   2160
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   70
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   68
      Left            =   2160
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   69
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   67
      Left            =   2160
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   68
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   66
      Left            =   2160
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   67
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   65
      Left            =   2160
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   66
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   64
      Left            =   2160
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   65
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   63
      Left            =   1920
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   64
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   62
      Left            =   1920
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   63
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   61
      Left            =   1920
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   62
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   60
      Left            =   1920
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   61
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   59
      Left            =   1920
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   60
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   58
      Left            =   1920
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   59
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   57
      Left            =   1920
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   58
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   56
      Left            =   1920
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   57
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   55
      Left            =   1680
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   56
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   54
      Left            =   1680
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   55
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   53
      Left            =   1680
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   54
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   52
      Left            =   1680
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   53
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   51
      Left            =   1680
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   52
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   50
      Left            =   1680
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   51
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   49
      Left            =   1680
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   50
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   48
      Left            =   1680
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   49
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   47
      Left            =   1440
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   48
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   46
      Left            =   1440
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   47
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   45
      Left            =   1440
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   46
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   44
      Left            =   1440
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   45
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   43
      Left            =   1440
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   44
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   42
      Left            =   1440
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   43
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   41
      Left            =   1440
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   42
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   40
      Left            =   1440
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   41
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   39
      Left            =   1200
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   40
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   38
      Left            =   1200
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   39
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   37
      Left            =   1200
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   38
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   36
      Left            =   1200
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   37
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   35
      Left            =   1200
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   36
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   34
      Left            =   1200
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   35
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   33
      Left            =   1200
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   34
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   32
      Left            =   1200
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   33
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   31
      Left            =   960
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   32
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   30
      Left            =   960
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   31
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   29
      Left            =   960
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   30
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   28
      Left            =   960
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   29
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   27
      Left            =   960
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   28
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   26
      Left            =   960
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   27
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   25
      Left            =   960
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   26
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   24
      Left            =   960
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   25
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   23
      Left            =   720
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   24
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   22
      Left            =   720
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   23
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   21
      Left            =   720
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   22
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   20
      Left            =   720
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   21
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   19
      Left            =   720
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   20
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   18
      Left            =   720
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   19
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   17
      Left            =   720
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   18
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   16
      Left            =   720
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   17
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   15
      Left            =   480
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   16
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   14
      Left            =   480
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   15
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   13
      Left            =   480
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   14
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   12
      Left            =   480
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   13
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   11
      Left            =   480
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   12
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   10
      Left            =   480
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   11
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   9
      Left            =   480
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   10
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   8
      Left            =   480
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   9
      Top             =   240
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   7
      Left            =   240
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   8
      Top             =   1920
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   6
      Left            =   240
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   7
      Top             =   1680
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   5
      Left            =   240
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   6
      Top             =   1440
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   4
      Left            =   240
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   5
      Top             =   1200
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   3
      Left            =   240
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   4
      Top             =   960
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   2
      Left            =   240
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   3
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   1
      Left            =   240
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   2
      Top             =   480
      Width           =   255
   End
   Begin VB.PictureBox pic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   240
      ScaleHeight     =   225
      ScaleWidth      =   225
      TabIndex        =   1
      Top             =   240
      Width           =   255
   End
   Begin VB.CommandButton cmdDibuja 
      Caption         =   "Dibuja "
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   3240
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim matriz() As Long

Private Sub cmdDibuja_Click()
    
    ancho = UBound(matriz, 1)
    alto = UBound(matriz, 2)
    
    For x = 0 To ancho - 1
        For y = 0 To alto - 1
            pic(y * alto + x).BackColor = matriz(i, j)
        Next j
    Next i

End Sub

Private Sub cmdIzq_Click()

    Dim aux() As Long

    ancho = UBound(matriz, 2)
    alto = UBound(matriz, 1)
    
    ReDim aux(alto) As Long
    
    For j = 0 To alto - 1
        aux(j) = matriz(j, ancho - 1)
    Next j

    For i = 1 To ancho - 1
        For j = 0 To alto - 1
            matriz(i - 1, j) = matriz(i, j)
        Next j
    Next i
    
    For j = 0 To alto - 1
        matriz(ancho - 1, j) = aux(j)
    Next j
    
    cmdDibuja_Click


End Sub

Private Sub cmdRND_Click()
    
    ancho = UBound(matriz, 1)
    alto = UBound(matriz, 2)
    
    For i = 0 To ancho - 1
        For j = 0 To alto - 1
            Randomize Timer
            matriz(i, j) = RGB(Rnd() * 255, Rnd() * 255, Rnd() * 255)
        Next j
    Next i
    
    cmdDibuja_Click
    
End Sub

Private Sub Form_Load()
    
    ReDim matriz(8, 16) As Long
    
End Sub
