...
PUBLIC struct dmap dmap[] = {
/*  ?   Open       Read/Write   Close       Task #      Device  File
    -   ----       ----------   -----       -------     ------  ----       */
  DT(1, no_dev,    no_dev,      no_dev,     0)           /* 0 = not used   */
  DT(1, dev_opcl,  call_task,   dev_opcl,   MEM)         /* 1 = /dev/mem   */
  DT(1, dev_opcl,  call_task,   dev_opcl,   FLOPPY)      /* 2 = /dev/fd0   */
  DT(ENABLE_WINI,
        dev_opcl,  call_task,   dev_opcl,   WINCHESTER)  /* 3 = /dev/hd0   */
  DT(1, tty_open,  call_task,   dev_opcl,   TTY)         /* 4 = /dev/tty00 */
  DT(1, ctty_open, call_ctty,   ctty_close, TTY)         /* 5 = /dev/tty   */
  DT(1, dev_opcl,  call_task,   dev_opcl,    PRINTER)     /* 6 = /dev/lp    */

#if (MACHINE == IBM_PC)
  DT(ENABLE_NETWORKING,
        net_open,  call_task,   dev_opcl,   INET_PROC_NR)/* 7 = /dev/ip    */
  DT(ENABLE_CDROM,
        dev_opcl,  call_task,   dev_opcl,   CDROM)       /* 8 = /dev/cd0   */
/* FLEDS: agrego el dispositivo del fleds al mapeo */
  DT(1, dev_opcl,  call_task,   dev_opcl,   FLEDS)           /* 9 = /dev/fleds   */
  DT(ENABLE_SCSI,
        dev_opcl,  call_task,   dev_opcl,   SCSI)        /*10 = /dev/sd0   */
  DT(0, 0,         0,           0,          0)           /*11 = not used   */
  DT(0, 0,         0,           0,          0)           /*12 = not used   */
  DT(ENABLE_AUDIO,
        dev_opcl,  call_task,   dev_opcl,   AUDIO)       /*13 = /dev/audio */
  DT(ENABLE_AUDIO,
        dev_opcl,  call_task,   dev_opcl,   MIXER)       /*14 = /dev/mixer */
#endif /* IBM_PC */

#if (MACHINE == ATARI)
  DT(ENABLE_SCSI,
        dev_opcl,  call_task,   dev_opcl,   SCSI)        /* 7 = /dev/hdscsi0 */
#endif
};
...
