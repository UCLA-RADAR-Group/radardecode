#ifndef EXECSHMH
#define EXECSHMH
/*****************************************************************************
 *
 * FILE: execshm.h
 *
 *   This file contains the shared memory filled in by the CIMA executive.
 *
 *   This information is broadcast when the executive is running.
 *
 * HISTORY
 *
 * who          when           what
 * ---------    -----------    ----------------------------------------------
 * jeffh        10 Aug 2004    Original coding
 * lerner       13 Nov 2007    Changed size of most strings, turned 'restfreqN' into an array, extended 'restfreq' and 'destfreq' to 8 frequencies, renamed 'obs_mode' to 'obs_name', 'obs_type' to 'cima_mode', 'repeat' to 'loop', 'total_repeats' to 'loops' and 'scan' to 'scan_id', added 'corr_dny', 'filter', 'polarization', 'custom_iflo', 'dop_mode', 'radar_blanker', 'winking_cal', 'caltype', 'enabled_wapps', 'wapp_dual', 'wapp_alfa', 'wapp_mode', 'task_name', 'task_info', task_message', 'task_bitmap', 'parts', 'part', 'task_start', 'part_start', 'part_type', 'part_timer', 'last_task', 'file_name', 'file_size', 'obsmode', 'scantype', 'pattern_id', 'timestamp' and a set of extra variables as well as removed 'lineN', 'corr_wapp', 'secsp_repeat', 'total_remain', 'ison', 'map_x', 'map_y', 'lastcal', 'rcvpower', 'wind_speed' and 'wind_direction'
 *
 *****************************************************************************/

typedef struct {

/*  General information  */

  char project_id[8];       /* project-ID, type 'a2142' or 'x108' */
  char observers[80];       /* name of current observers */
  char work_directory[128]; /* project directory */
  char cima_mode[8];        /* 'line' or 'pulsar' */

/*  Source information  */

  char catalog[128];        /* current catalog name */
  char source[32];          /* requested source name */
  double velocity;          /* last requested velocity */
  char veltype[24];         /* last velocity type */
  char velframe[24];        /* last velocity frame */
  double ra;                /* requested source RA or coordinate-1 */
  double dec;               /* requested source Dec or coordinate-2 */
  char epoch[8];            /* requested coordinate system */
  double off1;              /* requested coordinate-1 offset */
  double off2;              /* requested coordinate-2 offset */
  char off_units[8];        /* requested offset coordinate system */

/*  IF/LO configuration  */

  char receiver[8];         /* requested receiver */
  char backends[32];        /* requested backend(s) */
  char ifconfig[32];        /* requested IF-path */
  char filter[48];          /* requested filter - if applicable */
  char polarization[16];    /* requested polarization - if applicable */
  int custom_iflo;          /* IF/LO set-up is 1=custom or 0=standard */
  int dop_mode;             /* Doppler mode is 1=SUBBAND or 0=RFONLY */
  int radar_blanker;        /* radar blanking is 1=on or 0=off */
  int winking_cal;          /* 25Hz winking cal is 1=on or 0=off */

  double centfreq;          /* requested center rest frequency (MHz) */
  double restfreq[8];       /* requested rest frequency (MHz) */
  double destfreq[8];       /* destination center frequency (MHz) */

/*  Interim correlator  */

  int corr_estart;
  int corr_dumplen;
  int corr_icyc;
  int corr_blank;
  char corr_enable[16];
  char corr_config[16];
  char corr_bw[32];
  char corr_lags[16];
  char corr_dny[16];

/*  WAPPs  */

  int wapp_dual;            /* WAPP mode is 1=dual board or 0=single board */
  int wapp_alfa;            /* WAPP is set up for 1=ALFA or 0=other receiver */
  int enabled_wapps[4];     /* WAPP(n) is 1=enabled or 0=disabled */
  char wapp_mode[16];       /* WAPP boards and polarization usage string */

/*  Observation info  */

  char obs_name[32];        /* name of observing mode */
  char caltype[8];          /* name of calibrator */
  char obsmode[16];         /* CIMAFITS observing mode name */
  char scantype[16];        /* CIMAFITS scan type name */
  int pattern_id;           /* scan number for start of this pattern */
  int scan_id;              /* scan number for this scan */

/*  Display information  */

  char task_name[80];       /* name of current top task */
  char task_info[128];      /* last task INFO message */
  char task_message[128];   /* last task MESSAGE message */
  char task_bitmap[32];     /* last selected task bitmap */
  char loops[8];            /* total number of loops */
  char loop[8];             /* current loop */
  char parts[8];            /* total number of parts per loop */
  char part[8];             /* current part */
  int task_start;           /* timestamp when last task started */
  int part_start;           /* timestamp when last task part started */
  int part_type;            /* part is 1=timer ot 2=wait */
  int part_timer;           /* number of seconds for part_type=1 */
  int last_task;            /* total length of last completed task (secs) */
  int secs_remain;          /* seconds remaining */
  char file_name[80];       /* current data file name */
  double file_size;         /* current size of data file (kB) */

/*  Broadcast information  */

  unsigned int send_count;  /* arbitrary counter that increments after send */
  int timestamp;            /* timestamp of last broadcast - from time(NULL) */

/*  Extras  */

  int extra_i1;
  int extra_i2;
  int extra_i3;
  int extra_i4;
  double extra_f1;
  double extra_f2;
  double extra_f3;
  double extra_f4;
  char extra_s1[32];
  char extra_s2[32];
  char extra_s3[32];
  char extra_s4[32];
} EXECSHM;
#endif
