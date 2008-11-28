...
PUBLIC struct tasktab tasktab[] = {
	{ tty_task,		TTY_STACK,	"TTY"		},
/* FLEDS: Agrego la tarea al scheduler */
#if ENABLE_FLEDS
	{ fleds_task,		FLEDS_STACK,	"FLEDS"		},
#endif
#if ENABLE_NETWORKING
	{ dp8390_task,		DP8390_STACK,	"DP8390"	},
#endif
#if ENABLE_CDROM
	{ cdrom_task,		CDROM_STACK,	"CDROM"		},
#endif
#if ENABLE_AUDIO
	{ audio_task,		AUDIO_STACK,	"AUDIO"		},
	{ mixer_task,		MIXER_STACK,	"MIXER"		},
#endif
#if ENABLE_SCSI
	{ scsi_task,		SCSI_STACK,	"SCSI"		},
#endif
#if ENABLE_WINI
	{ winchester_task,	WINCH_STACK,	"WINCH"		},
#endif
	{ syn_alrm_task,	SYN_ALRM_STACK, "SYN_AL"	},
	{ idle_task,		IDLE_STACK,	"IDLE"		},
	{ printer_task,		PRINTER_STACK,	"PRINTER"	},
	{ floppy_task,		FLOP_STACK,	"FLOPPY"	},
	{ mem_task,		MEM_STACK,	"MEMORY"	},
	{ clock_task,		CLOCK_STACK,	"CLOCK"		},
	{ sys_task,		SYS_STACK,	"SYS"		},
	{ 0,			HARDWARE_STACK,	"HARDWAR"	},
	{ 0,			0,		"MM"		},
	{ 0,			0,		"FS"		},
#if ENABLE_NETWORKING
	{ 0,			0,		"INET"		},
#endif
	{ 0,			0,		"INIT"		},
};
...
