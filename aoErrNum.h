
/*
modification history
--------------------
01a,22nov91,pjp  added aoM_bufPool.
01a,22nov91,pjp  created
01a,27aug92,pjp  added vp1Drv module
01a,30aug92,pjp  added sbpDrv module
01a,05sep92,pjp  added extTick module
01a,11oct92,pjp  added mcpProg module
01a,18oct92,pjp  added riDrv   module
01a,30apr93,pjp  converted to aoErrNum.h
01a,01feb94,pjp  added aoParse...
...pre 1987 mod history removed.  See RCS.
01a,25jun94,pjp  moved routines riLib and following  to 3ef and increasing
   ,06mar95,pjp  added logic analyzer 
   ,07mar95,pjp  added hp3488 switch  
   ,07aug95,pjp  added dcdRemDrv errors.
   ,06dec95,pjp  added tdCom errors
   ,22feb96,pjp  added micro control com errors.
   ,30aug96,pjp  added corLProc errors.
   ,26sep02,pjp  added hp437 errors
   ,29oct02,pjp  added agcProg generic cmd errors
   ,19oct07,pjp  added kronhiteE filter errors
   ,26sep14,pjp  added prologix gpib enet errors
*/

#ifndef INCaoErrNumh
#define INCaoErrNumh

#if FALSE
#include	<errnoLib.h>
#endif

#define	AOERR_MASK	0XFFFF000
#define AOERR_MIN	aoM_bufPoolLib

/* module numbers - DO NOT CHANGE NUMBERS! Add or delete only! */

#define aoM_bufPoolLib	( 0x3e8 << 16 )	/* vxWorks stops at 500, max=64K-1 */
#define aoM_aoqLib	( 0x3e9 << 16 )	/* vxWorks stops at 500, max=64K-1 */
#define aoM_vp1Drv	( 0x3ea << 16 )  /* vp1 Driver errors*/
#define aoM_sbpDrv	( 0x3eb << 16 )  /* sbp Driver errors*/
#define aoM_extTick	( 0x3ec << 16 )  /* extTick NO errors*/
#define aoM_mcpProg	( 0x3ed << 16 )  /* mcpProg    errors*/
#define aoM_riDrv  	( 0x3ee << 16 )  /* ri Driver  errors*/
#define aoM_riLib  	( 0x3ef << 16 )  /* rilib   NO errors*/
#define aoM_rtgLib  ( 0x3f0 << 16 )  /* rtgLib     errors*/
#define aoM_rmtcLib	( 0x3f1 << 16 )  /* rmtcLib    errors*/
#define aoM_agents 	( 0x3f2 << 16 )  /* agents     errors*/ 
#define aoM_generic	( 0x3f3 << 16 )  /* global     errors*/ 
#define aoM_sps	    ( 0x3f4 << 16 )  /* sps        errors*/ 
#define aoM_aoMsg	( 0x3f5 << 16 )  /* msgQ       errors*/ 
#define aoM_skProg	( 0x3f6 << 16 )  /* socket prg errors*/ 
#define aoM_mzDrv 	( 0x3f7 << 16 )  /* mizar gpib errors*/ 
#define aoM_spsProg	( 0x3f8 << 16 )  /* spsProg    errors*/ 
#define aoM_autoLd 	( 0x3f9 << 16 )  /* autoLd     errors*/ 
#define aoM_parse  	( 0x3fa << 16 )  /* aoParse    errors*/ 
#define aoM_swProg  ( 0x3fb << 16 )  /* swProg     errors*/ 
#define aoM_dsProg	( 0x3fc << 16 )  /* discProg   errors*/ 
#define aoM_tpProg	( 0x3fd << 16 )  /* tapeProg   errors*/ 
#define aoM_riProg	( 0x3fe << 16 )  /* riProg   errors*/ 
#define aoM_sufRpc	( 0x3ff << 16 )  /* sufRpc   errors*/ 
#define aoM_ipSyn 	( 0x400 << 16 )  /* ipSyn    errors*/ 
#define aoM_xbErr 	( 0x401 << 16 )  /* xbErr    errors*/ 
#define aoM_dcd   	( 0x402 << 16 )  /* decoder  errors*/ 
#define aoM_apProg	( 0x403 << 16 )  /* apProg  errors*/ 
#define aoM_tpInpProg	( 0x404 << 16 )  /* tpInpProg   errors*/ 
#define aoM_kl2500  ( 0x405 << 16 )  /* kl2500   errors*/ 
#define aoM_rfiRcv  ( 0x406 << 16 )  /* rfiRcv   errors*/ 
#define aoM_la   	( 0x407 << 16 )  /* logic analyzer errors*/ 
#define aoM_hp3488	( 0x408 << 16 )  /* hp3488 switch driver*/ 
#define aoM_hp87130	( 0x409 << 16 )  /* hp87130 switch driver*/ 
#define aoM_rfIf1	( 0x40a << 16 )  /* rf  if1 values*/ 
#define aoM_aomSk   ( 0x40b << 16 )  /* aoMessage sock program*/
#define aoM_hp83712 ( 0x40c << 16 )  /* hp83712 synth*/
#define aoM_pnt     ( 0x40d << 16 )  /* pointing program */
#define aoM_ipDio   ( 0x40e << 16 )  /* ip digital i/o */
#define aoM_ipDma   ( 0x40f << 16 )  /* ip dma i/o */
#define aoM_gcsr    ( 0x410 << 16 )  /* gcsr routines */
#define aoM_dcdR  	( 0x411 << 16 )  /* remote decoder  errors*/ 
#define aoM_prgMgr	( 0x412 << 16 )  /* program manager errors*/ 
#define aoM_gwPrg	( 0x413 << 16 )  /* gateWayProg errors*/ 
#define aoM_netcf	( 0x414 << 16 )  /* network configuration*/
#define aoM_unpR 	( 0x415 << 16 )  /* unpack data records*/
#define aoM_dcdPrL  ( 0x416 << 16 )  /* dcdProgL on 162fx*/
#define aoM_tdCom   ( 0x417 << 16 )  /* tdCom program communication*/
#define aoM_pnc     ( 0x418 << 16 )  /* pncode generator..*/
#define aoM_if2   	( 0x419 << 16 )  /* iflo2..*/
#define aoM_hp8648  ( 0x41a << 16 )  /* hp8648 synth*/
#define aoM_tt560   ( 0x41b << 16 )  /* irig tt560 board*/
#define aoM_lmsg   	( 0x41c << 16 )  /* locMsgLib*/
#define aoM_mctrl  	( 0x41d << 16 )  /* micro controllers comm*/
#define aoM_ttPr  	( 0x41e << 16 )  /* ttProg..*/
#define aoM_llgen 	( 0x41f << 16 )  /* low level generic routines..*/
#define aoM_agc 	( 0x420 << 16 )  /* agc routines. pointing...*/
#define aoM_irigSv 	( 0x421 << 16 )  /* irig server..*/
#define aoM_qph    	( 0x422 << 16 )  /* q routines agc*/
#define aoM_vtxP   	( 0x423 << 16 )  /* vtxProg*/
#define aoM_if1P   	( 0x424 << 16 )  /* if1 program*/
#define aoM_corLProc ( 0x425 << 16 )  /* corLProc  program*/
#define aoM_pt      ( 0x426 << 16 )  /* penTeck a/d board*/
#define aoM_ptProg  ( 0x427 << 16 )  /* ptProg for penteck boards*/
#define aoM_hp34401 ( 0x428 << 16 )  /* multi meter*/
#define aoM_tk420   ( 0x429 << 16 )  /* scope*/
#define aoM_ipGen   ( 0x42a << 16 )  /* ipGen board of bills*/
#define aoM_hp8590  ( 0x42b << 16 )  /* spectrum analyzer*/
#define aoM_scrm    ( 0x42c << 16 )  /* scramnet*/
#define aoM_bt4200  ( 0x42d << 16 )  /* bt4200 power meter*/
#define aoM_ddsPr   ( 0x42e << 16 )  /* ddsProgram*/
#define aoM_ttt     ( 0x42f << 16 )  /* ttProg or tieProg*/
#define aoM_logd    ( 0x430 << 16 )  /* logd data logger*/
#define aoM_hp442   ( 0x431 << 16 )  /* power meter*/
#define aoM_ipFifo  ( 0x432 << 16 )  /* ipFifo*/
#define aoM_model   ( 0x433 << 16 )  /* modelLib errors*/
#define aoM_rdrdop  ( 0x434 << 16 )  /* radar doppler/ephm errors*/
#define aoM_initDat ( 0x435 << 16 )  /* init data routines*/
#define aoM_sbProg  ( 0x436 << 16 )  /* sband sbProg*/
#define aoM_epv     ( 0x437 << 16 )  /* ephmeris errors epvLib*/
#define aoM_corProg ( 0x438 << 16 )  /* corProgs */
#define aoM_ipCal   ( 0x439 << 16 )  /* ipCal board */
#define aoM_errLib  ( 0x43a << 16 )  /* errRepLib */
#define aoM_ipPc    ( 0x43b << 16 )  /* ip power counter */
#define aoM_rcvM    ( 0x43c << 16 )  /* rcvMProg */
#define aoM_pncl    ( 0x43d << 16 )  /* pncode long generator..*/
#define aoM_lrmon   ( 0x43e << 16 )  /* lrMon laser ranginge.*/
#define aoM_ter     ( 0x43f << 16 )  /* tertiary errors.*/
#define aoM_gio     ( 0x440 << 16 )  /* general i/o program*/
#define aoM_gior    ( 0x441 << 16 )  /* general i/o remote program*/
#define aoM_hp34970 ( 0x442 << 16 )  /* multi meter 34970*/
#define aoM_gpibEnet ( 0x443 << 16 )  /* gpibEnet errors*/
#define aoM_hp437   ( 0x444 << 16 )  /* hp437 errors*/
#define aoM_ALFAM   ( 0x445 << 16 )  /* alfa motor errors*/
#define aoM_KHFILT  ( 0x446 << 16 )  /* kronhite filters*/
#define aoM_MODBUS  ( 0x447 << 16 )  /* modbus errors*/
#define aoM_PRLX    ( 0x448 << 16 )  /* prologix gpibEnet*/
/*
 *	errors by module
 *	 format:
 *	**!name  comment  ... start module errors
*/
/*
 * aoM_bufPoolLib
*/
#define S_bufPoolLib_NOMEM_BUF                  (aoM_bufPoolLib | 1)
#define S_bufPoolLib_NOMEM_SEM                  (aoM_bufPoolLib | 2) 
#define S_bufPoolLib_BAD_BPID_REMOVE            (aoM_bufPoolLib | 3)
#define S_bufPoolLib_BAD_BUFPTR_REMOVE          (aoM_bufPoolLib | 4)
#define S_bufPoolLib_MEMPART_ALREADY_EXISTS     (aoM_bufPoolLib | 5)
#define S_bufPoolLib_MEMPART_DOESNT_EXIST       (aoM_bufPoolLib | 6)
#define S_bufPoolLib_MEMPART_NOT_ENOUGH_MEM     (aoM_bufPoolLib | 7)
#define S_bufPoolLib_MEMPART_CANT_FREE_PARTBUF  (aoM_bufPoolLib | 8)
#define S_bufPoolLib_ILLEGAL_BUFLEN_REQ         (aoM_bufPoolLib | 9)
#define S_bufPoolLib_BUFNODE_PTR_IS_NULL        (aoM_bufPoolLib |0xa)
#define S_bufPoolLib_BUFPOOL_PTR_IS_NULL        (aoM_bufPoolLib |0xb)
/*
 * aoM_aoqLib
*/
#define S_aoqLib_NOMEM_Q                       (aoM_aoqLib | 1)
#define S_aoqLib_NOMEM_SEM                     (aoM_aoqLib | 2)
#define S_aoqLib_BAD_QPTR_REMOVE               (aoM_aoqLib | 3)
#define S_aoqLib_SEMINUSE_REMOVE               (aoM_aoqLib | 4)
#define S_aoqLib_QNEMPTY_REMOVE                (aoM_aoqLib | 5)
#define S_aoqLib_BAD_SEMID_REMOVE              (aoM_aoqLib | 6)
#define S_aoqLib_MXSEM_TIMEOUT                 (aoM_aoqLib | 7)
#define S_aoqLib_EMPSEM_TIMEOUT                (aoM_aoqLib | 8)
/*
 * aoM_vp1Drv
*/
#define S_vp1Drv_TIMEOUT_WAITING_XMTR_EMPTY             (aoM_vp1Drv | 1)
#define S_vp1Drv_TIMEOUT_WAITING_RCVR_DATAFLAG          (aoM_vp1Drv | 2)
#define S_vp1Drv_TIMEOUT_WAITING_DATA_CONFIG_ACK        (aoM_vp1Drv | 3)
#define S_vp1Drv_ILLEGAL_VAL_PIRQN                      (aoM_vp1Drv | 4)
#define S_vp1Drv_ILLEGAL_VAL_INTLEVVME                  (aoM_vp1Drv | 5)
#define S_vp1Drv_TIMEOUT_WAITING_PIRQN_ACK              (aoM_vp1Drv | 6)
#define S_vp1Drv_PARITY_ERR_RCVR                        (aoM_vp1Drv | 7)
#define S_vp1Drv_ILLEGAL_IOCTL                          (aoM_vp1Drv | 8)
/*
 * aoM_sbpDrv   (sbp.h)
*/
#define S_sbpDrv_TIMEOUT_WAITING_XMTR_EMPTY             (aoM_sbpDrv | 1)
#define S_sbpDrv_TIMEOUT_WAITING_RCVR_DATAFLAG          (aoM_sbpDrv | 2)
#define S_sbpDrv_TIMEOUT_WAITING_DATA_CONFIG_ACK        (aoM_sbpDrv | 3)
#define S_sbpDrv_ILLEGAL_VAL_PIRQN                      (aoM_sbpDrv | 4)
#define S_sbpDrv_ILLEGAL_VAL_INTLEVVME                  (aoM_sbpDrv | 5)
#define S_sbpDrv_TIMEOUT_WAITING_PIRQN_ACK              (aoM_sbpDrv | 6)
#define S_sbpDrv_PARITY_ERR_RCVR                        (aoM_sbpDrv | 7)
#define S_sbpDrv_ILLEGAL_IOCTL                          (aoM_sbpDrv | 8)
#define S_sbpDrv_ILLEGAL_INT_REQUESTED                  (aoM_sbpDrv | 9)
/*
 * aoM_mcpProg
*/
#define  S_mcpProg_UNKNOWN_PRG_ID	       		(aoM_mcpProg |0x01)
#define  S_mcpProg_PRG_NOT_LOADED_IN_MEM       		(aoM_mcpProg |0x02)
#define  S_mcpProg_TOO_MANY_PROGS_RUNNING 		(aoM_mcpProg |0x03)
#define  S_mcpProg_COULDNT_START_REQ_PRG     		(aoM_mcpProg |0x04)
#define  S_mcpProg_COULDNT_GET_PRG_MSGQ_ID     		(aoM_mcpProg |0x05)
#define  S_mcpProg_CANT_SNDMSG_QID_NULL       		(aoM_mcpProg |0x06)
#define  S_mcpProg_PRGID_NOT_IN_MCP_TBL    		(aoM_mcpProg |0x07)
#define  S_mcpProg_PRGID_ALREADY_ACTIVE    		(aoM_mcpProg |0x08)
#define  S_mcpProg_CANT_MALLOC_RCVBUF                   (aoM_mcpProg |0x09)
#define  S_mcpProg_GENBUFP_BAD_ID                       (aoM_mcpProg |0x0a)
#define  S_mcpProg_GENBUFP_ID_IN_USE                    (aoM_mcpProg |0x0b)
#define  S_mcpProg_GENBUFP_ID_LIST_FULL                 (aoM_mcpProg |0x0c)
#define  S_mcpProg_GENBUFP_BAD_NUMBUFS                  (aoM_mcpProg |0x0d)
#define  S_mcpProg_GENBUFP_ERR_QUERY_PROG               (aoM_mcpProg |0x0e)
#define  S_mcpProg_GENBUFP_BAD_BUFLEN                   (aoM_mcpProg |0x0f)
#define  S_mcpProg_GENBUFP_CANT_MALLOC                  (aoM_mcpProg |0x10)
#define  S_mcpProg_NO_STOPDATA_FUNC                     (aoM_mcpProg |0x11)
#define  S_mcpProg_UNKNOWN_CMD                          (aoM_mcpProg |0x12)
#define  S_mcpProg_BAD_CMD_PARAMETER                    (aoM_mcpProg |0x13)
#define  S_mcpProg_SU_FILE_HASH_TABLE_NOT_INITIALIZED   (aoM_mcpProg |0x14)
#define  S_mcpProg_CANT_TAKE_MXSEM_SU_FILE_HASH_TABLE   (aoM_mcpProg |0x15)
#define  S_mcpProg_CANT_CREATE_ENTRY_SU_FILE_HASH_TABLE (aoM_mcpProg |0x16)
#define  S_mcpProg_CANT_MALLOC_DSTRING_SU_FILE          (aoM_mcpProg |0x17)
#define  S_mcpProg_CANT_MALLOC_STRUCT_SU_FILE           (aoM_mcpProg |0x18)
#define  S_mcpProg_CANT_MALLOC_HDRINFO_SU_FILE          (aoM_mcpProg |0x19)
#define  S_mcpProg_NOT_RUNNING_GLOB_STRUCT_NULL         (aoM_mcpProg |0x1a)
 /*
 * aoM_riDrv    ri.h...
*/
#define S_riDrv_TIMEOUT_WAITING_XMTR_EMPTY              (aoM_riDrv |0x01)
#define S_riDrv_TIMEOUT_WAITING_RCVR_DATAFLAG           (aoM_riDrv |0x02)
#define S_riDrv_TIMEOUT_WAITING_DATA_CONFIG_ACK         (aoM_riDrv |0x03)
#define S_riDrv_ILLEGAL_VAL_INTLEVVME                   (aoM_riDrv |0x05)
#define S_riDrv_PARITY_ERR_RCVR                         (aoM_riDrv |0x07)
#define S_riDrv_ILLEGAL_IOCTL                           (aoM_riDrv |0x08)
#define S_riDrv_ADR_NOT_INT_ALIGNED                     (aoM_riDrv |0x09)
#define S_riDrv_BAD_WC                                  (aoM_riDrv |0x0a)
#define S_riDrv_BAD_CMD                                 (aoM_riDrv |0x0b)
#define S_riDrv_BAD_WC_SFW                              (aoM_riDrv |0x0c)
#define S_riDrv_BAD_LDMUX_WC                            (aoM_riDrv |0x0d)
#define S_riDrv_BAD_RDMUX_WC                            (aoM_riDrv |0x0e)
#define S_riDrv_BAD_GWLEN                               (aoM_riDrv |0x0f)
#define S_riDrv_BAD_SEQLEN                              (aoM_riDrv |0x10)
#define S_riDrv_SBPDEV_NOT_ASSIGNED                     (aoM_riDrv |0x11)
#define S_riDrv_BADSC_SMPMODE                           (aoM_riDrv |0x12)
#define S_riDrv_BADSC_FORMATTER_MODE                    (aoM_riDrv |0x13)
#define S_riDrv_BADSC_PACKING                           (aoM_riDrv |0x14)
#define S_riDrv_BADSC_MUX_SINEWAVE_CHAN                 (aoM_riDrv |0x15)
#define S_riDrv_PWRSUP_P15V_BAD                         (aoM_riDrv |0x16)
#define S_riDrv_PWRSUP_M15V_BAD                         (aoM_riDrv |0x17)
#define S_riDrv_PWRSUP_P5V_LINEAR_BAD                   (aoM_riDrv |0x18)
#define S_riDrv_PWRSUP_M5V_LINEAR_BAD                   (aoM_riDrv |0x19)
#define S_riDrv_PWRSUP_P5V_SWITCHING_BAD                (aoM_riDrv |0x1a)
#define S_riDrv_SERLOOPBACK_MISMATCH                    (aoM_riDrv |0x1b)
#define S_riDrv_BAD_FIFO_REQ                            (aoM_riDrv |0x1c)
#define S_riDrv_TIMEOUT_READ                            (aoM_riDrv |0x1d)
#define S_riDrv_ILLEGAL_ADR                             (aoM_riDrv |0x1e)
#define S_riDrv_BADREAD_BYTECOUNT                       (aoM_riDrv |0x1f)
#define S_riDrv_GWCNT_ERR                               (aoM_riDrv |0x20)
#define S_riDrv_WC_NONZERO_ATINT                        (aoM_riDrv |0x21)
#define S_riDrv_TIMEOUT_CLEAR                           (aoM_riDrv |0x22)
#define S_riDrv_BADREAD_ADR                             (aoM_riDrv |0x23)
/*
 * aoM_riLib 
*/
#define S_riLib_CANT_OPEN_MUXFILE         		(aoM_riLib |0x01)
#define S_riLib_MALLOC_ERR_MUXDATA_BUF    		(aoM_riLib |0x02)
/*
 * aoM_rtgLib 
*/
#define S_rtgLib_LOAD_READBACK_MISMATCH         (aoM_rtgLib |0x01)
/*
 * aoM_rmtcLib 
*/
#define S_ERMTC_EOF                       (aoM_rmtcLib | 1)
#define S_ERMTC_SHORT_REC_READ_DATA       (aoM_rmtcLib | 2)
#define S_ERMTC_SHORT_REC_READ_HDR        (aoM_rmtcLib | 3)
#define S_ERMTC_READ_HDR                  (aoM_rmtcLib | 4)
#define S_ERMTC_READ_DATA                 (aoM_rmtcLib | 5)
#define S_ERMTC_SHORT_REC_WRITE_DATA      (aoM_rmtcLib | 6)
#define S_ERMTC_SHORT_REC_WRITE_HDR       (aoM_rmtcLib | 7)
#define S_ERMTC_WRITE_HDR                 (aoM_rmtcLib | 8)
#define S_ERMTC_WRITE_DATA                (aoM_rmtcLib | 9)
#define S_ERMTC_BAD_HDR_ID                (aoM_rmtcLib |0xa)
#define S_ERMTC_OUT_OF_SEQ_CMD            (aoM_rmtcLib |0xb)
#define S_ERMTC_OUT_OF_SEQ_RSVPID         (aoM_rmtcLib |0xc)
#define S_ERMTC_NACK                      (aoM_rmtcLib |0xd)
#define S_ERMTC_RCV_DATABUF_OVERFLOW      (aoM_rmtcLib |0xe)
/*
 * aoM_agents 
*/
#define S_AGERR_DATATAKING_WONT_STOP	  (aoM_agents | 1)
#define S_AGERR_UNKNOWNAGENT              (aoM_agents | 2)
#define S_AGERR_AGENTNOTLOADED 		  (aoM_agents | 3)
#define S_AGERR_ERRSPAWNING               (aoM_agents | 4)
#define S_AGERR_BAD_EXIT_REQ              (aoM_agents | 5)
#define S_AGERR_BAD_RMTHOSTNAME           (aoM_agents | 6)
#define S_AGERR_UNKNOWN_REQ               (aoM_agents | 7)
#define S_AGERR_NOBUF_FOR_MSGDATA         (aoM_agents | 8)
#define S_AGERR_DATATAKING_RUNNING        (aoM_agents | 9)
#define S_AGERR_AGENT_BUFREQ_OUTSTANDING  (aoM_agents |0xa)
#define S_AGERR_AGENTLIST_TABLE_FULL      (aoM_agents |0xb)
#define S_AGERR_AGENT_NOT_IN_LIST         (aoM_agents |0xd)
/*
 * aoM_generic
*/
#define S_GEN_NOMORE_INFO                     (aoM_generic | 1)
#define S_GEN_PROG_REQ_TO_EXIT                (aoM_generic | 2)
#define S_GEN_SETUP_SIZE_INCORRECT            (aoM_generic | 3)
#define S_GEN_CANT_MALLOC_SETUP_BUF           (aoM_generic | 4)
#define S_GEN_QUERYBUF_TOO_SMALL              (aoM_generic | 5)
#define S_GEN_BAD_SETUP_KEYVALUE              (aoM_generic | 6)
#define S_GEN_ILLEGAL_IOCTL_REQ               (aoM_generic | 7)
#define S_GEN_BAD_EXTERNAL_INT_NUMBER         (aoM_generic | 8)
#define S_GEN_NO_ROOM_HDR_SECTION_IN_HDR      (aoM_generic | 9)
#define S_GEN_INTERRUPT_OCCURED_BEFORE_WAIT   (aoM_generic |0x0a)
#define S_GEN_ILLEGAL_MSG_CMD                 (aoM_generic |0x0b)
#define S_GEN_PRGNAME_NOT_IN_PRIORITIES_FILES (aoM_generic |0x0c)
#define S_GEN_NEED_TO_DO_SETUP                (aoM_generic |0x0d)
#define S_GEN_NEED_TO_SPECIFY_OUT_MSGQ        (aoM_generic |0x0e)
#define S_GEN_NEED_TO_SPECIFY_BUFFERPOOL      (aoM_generic |0x0f)
#define S_GEN_SETUPQ_MALLOC_ERROR 	      	  (aoM_generic |0x10)
#define S_GEN_ILLEGAL_DEVICE_NUMBER           (aoM_generic |0x11)
#define S_GEN_ILLEGAL_VME_INTERRUPT_LEVEL     (aoM_generic |0x12)
#define S_GEN_ILLEGAL_VME_INTERRUPT_NUMBER    (aoM_generic |0x13)
#define S_GEN_FUNCTION_NOT_YET_IMPLEMENTED    (aoM_generic |0x14)
#define S_GEN_PROGRAM_HAS_EXITED              (aoM_generic |0x15)
#define S_GEN_SETUP_MODIFIED_REQ_SETTING      (aoM_generic |0x16)
#define S_GEN_BUFLEN_EXCEEDS_64K              (aoM_generic |0x17)
#define S_GEN_GENERIC_CMD_NOT_UNDERSTOOD      (aoM_generic |0x18)
#define S_GEN_UNKNOWN_SETUP_KEY               (aoM_generic |0x19)
#define S_GEN_CANT_OPEN_PROGPRIORITY_FILE     (aoM_generic |0x1a)
#define S_GEN_HDRVINIT_NOT_INITIALIZED        (aoM_generic |0x1b)

/*
 * aoM_sps      sps.h...
*/
#define S_sps_BAD_CLOCK_DIVISOR           (aoM_sps |0x01)
#define S_sps_BAD_REQBUF_OFF 		  (aoM_sps |0x02)
#define S_sps_BAD_REQBUF_LEN 		  (aoM_sps |0x03)
#define S_sps_REQBUF_WOULD_OVERFLOW 	  (aoM_sps |0x04)
#define S_sps_BAD_CMD			  (aoM_sps |0x05)
#define S_sps_BAD_TRIGGER_CODE		  (aoM_sps |0x06)
#define S_sps_BAD_ACTMODE_CODE		  (aoM_sps |0x07)
#define S_sps_READ_OUTSIDE_MEM    	  (aoM_sps |0x08)
#define S_sps_READ_IN_ACTIVE_BUF  	  (aoM_sps |0x09)
#define S_sps_READ_ADR0_WHILE_CLEAR	  (aoM_sps |0x10)
#define S_sps_BAD_READ_CODE               (aoM_sps |0x11)
#define S_sps_ILLEGAL_IOCTL               (aoM_sps |0x12)
#define S_sps_CANT_LOAD_ON_ACTBUF         (aoM_sps |0x13)
#define S_sps_WRITE_ADR0_WHILE_CLEAR      (aoM_sps |0x14)
#define S_sps_NOTRIG_START_AFTER_CLEAR    (aoM_sps |0x15)
#define S_sps_START_WITH_NOCLKS_DEFINED   (aoM_sps |0x16)
#define S_sps_START_WITH_NOOFFLEN_DEFINED (aoM_sps |0x17)
#define S_sps_BAD_INTMODE_CODE            (aoM_sps |0x18)
#define S_sps_BAD_NUMBER_BUFS             (aoM_sps |0x19)
#define S_sps_BUFSW_RUNNING               (aoM_sps |0x20)
#define S_sps_NO_BUFSW_DEFINED            (aoM_sps |0x21)
#define S_sps_BUFSW_NOT_RUNNING           (aoM_sps |0x22)
#define S_sps_IPP_ILLEGAL                 (aoM_sps |0x23)
#define S_sps_GW_ILLEGAL                  (aoM_sps |0x24)
#define S_sps_GD_ILLEGAL                  (aoM_sps |0x25)
#define S_sps_GD_IPP_GW_DONT_ADDUP        (aoM_sps |0x26)
/*
 *	aoM_msg	message queuesx
*/
#define S_aoMsg_RCV_BUF_SHORT		  (aoM_aoMsg | 0x01) /* msgQ  errors*/ 
#define S_aoMsg_MALLOC_AOMSG_Q		  (aoM_aoMsg | 0x02) /* malloc Q*/ 
#define S_aoMsg_CREATE_VXWQ		  (aoM_aoMsg | 0x03) /* q create*/ 
#define S_aoMsg_NOMEM_SEM		  (aoM_aoMsg | 0x04) /* semaphore*/
#define S_aoMsg_TIMEOUT      		  (aoM_aoMsg | 0x05) 
#define S_aoMsg_TIMEOUT_NOWAIT		  (aoM_aoMsg | 0x06)
#define S_aoMsg_DELETE_BAD_AOMSG_Q_ID	  (aoM_aoMsg | 0x07) 
#define S_aoMsg_DELETE_SEMINUSE		  (aoM_aoMsg | 0x08) /* delete sem*/
#define S_aoMsg_DELETE_BAD_SEMID	  (aoM_aoMsg | 0x09)
#define S_aoMsg_DELETE_BAD_VXW_MSGQ_ID    (aoM_aoMsg | 0x0a)
#define S_aoMsg_CMD_NEEDS_REPLYQ          (aoM_aoMsg | 0x0b)
#define S_aoMsg_MSGRCVED_NEQ_MSGNUMSEND   (aoM_aoMsg | 0x0c)
#define S_aoMsg_BAD_MSGID_FOR_RCV	  (aoM_aoMsg | 0x0d)
#define S_aoMsg_RCV_INCORRECT_MSGLEN	  (aoM_aoMsg | 0x0e)
#define S_aoMsg_EXPECTED_SETUP_CMD  	  (aoM_aoMsg | 0x0f)
#define S_aoMsg_ILLEGAL_MSG_CMD     	  (aoM_aoMsg | 0x10)
#define S_aoMsg_EXPECTED_DATP_CMD  	  (aoM_aoMsg | 0x11)
#define S_aoMsg_BAD_MAXNUM_MSGS_FOR_Q     (aoM_aoMsg | 0x12)
#define S_aoMsg_MALLOC_AOMSG_DATA         (aoM_aoMsg | 0x13)
#define S_aoMsg_GWOUT_QID_IS_NULL         (aoM_aoMsg | 0x14)
#define S_aoMsg_SEND_QID_NULL             (aoM_aoMsg | 0x15)
#define S_aoMsg_OUTQ_ARGS_TOO_SMALL       (aoM_aoMsg | 0x16)
#define S_aoMsg_QSETUP_NEEDS_REPLY        (aoM_aoMsg | 0x17)
#define S_aoMsg_QBUFSIZE_NEEDS_REPLY      (aoM_aoMsg | 0x18)
#define S_aoMsg_SETUP_NO_SETUPINFO        (aoM_aoMsg | 0x19) 
#define S_aoMsg_NOP_REQUIRES_REPLY        (aoM_aoMsg | 0x1a) 
#define S_aoMsg_USEBP_NEEDS_BPNAME        (aoM_aoMsg | 0x1b) 
#define S_aoMsg_SPSFILEINP_NO_BUFID       (aoM_aoMsg | 0x1c) 
#define S_aoMsg_SPSFILEINP_NO_FILENAME    (aoM_aoMsg | 0x1d) 
#define S_aoMsg_SPSFILEINP_MALLOC         (aoM_aoMsg | 0x1e) 
#define S_aoMsg_SPSBUFADD_MALLOC          (aoM_aoMsg | 0x1f) 
#define S_aoMsg_SPSMODBUF_MALLOC          (aoM_aoMsg | 0x20) 
#define S_aoMsg_SPSFREEBUF_NO_BUFID       (aoM_aoMsg | 0x21) 
#define S_aoMsg_SPSSTARTBUF_NO_BUFID      (aoM_aoMsg | 0x22) 
#define S_aoMsg_TAPECMD_ILLEGAL           (aoM_aoMsg | 0x23) 
#define S_aoMsg_MSGBUILD_TOADR_NULL       (aoM_aoMsg | 0x24) 
#define S_aoMsg_TAPESTAT_NEEDS_REPLY      (aoM_aoMsg | 0x24)
#define S_aoMsg_TAPESENSE_NEEDS_REPLY     (aoM_aoMsg | 0x25)
#define S_aoMsg_REPLYADR_NULL             (aoM_aoMsg | 0x26)
#define S_aoMsg_DSPROG_REQPOS_NEEDS_REPLY (aoM_aoMsg | 0x27)
#define S_aoMsg_DSPROG_BYTESLEFT_NEEDS_REPLY (aoM_aoMsg | 0x28)
#define S_aoMsg_MSGBUILD_MSGQID_NULL      (aoM_aoMsg | 0x29) 
#define S_aoMsg_SENDDATA_TOQID_NULL       (aoM_aoMsg | 0x2a) 
#define S_aoMsg_GENERIC_MSG_BUT_NO_DATA   (aoM_aoMsg | 0x2b) 
/*
 *	aoM_sockProg
*/
#define S_skProg_ILLEGAL_SOCKET_FD     	  (aoM_skProg| 0x01)
#define S_skProg_NO_SOCKET_DEFINED        (aoM_skProg| 0x02)
#define S_skProg_SOCK_IO_ERR              (aoM_skProg| 0x03)
/*
 *	aoM_mzDrv mizar driver
*/
#define S_mzDrv_ECIC (aoM_mzDrv | 0x01)/* Must be CIC to use this function */
#define S_mzDrv_ENOL (aoM_mzDrv | 0x02)/* No listener for write function */
#define S_mzDrv_EADR (aoM_mzDrv | 0x03)/* Device not addressed correctly */
#define S_mzDrv_EARG (aoM_mzDrv | 0x04)/* Invalid argument to function call */
#define S_mzDrv_ESAC (aoM_mzDrv | 0x05)/* Must be SC to use this function */
#define S_mzDrv_EABO (aoM_mzDrv | 0x06)/* I/O transfer aborted */
#define S_mzDrv_EBID (aoM_mzDrv | 0x07)/* Invalid board structure ID */
#define S_mzDrv_EDID (aoM_mzDrv | 0x08)/* Invalid device structure ID */
#define S_mzDrv_ECMD (aoM_mzDrv | 0x09)/* Cmd error during device function */
#define S_mzDrv_EBUS (aoM_mzDrv | 0x0a)/* Bus error during device function */
#define S_mzDrv_ETMW (aoM_mzDrv | 0x0b)/* Timeout on int wait function */
#define S_mzDrv_EBRD (aoM_mzDrv | 0x0c)/* Invalid board address */
#define S_mzDrv_EMEM (aoM_mzDrv | 0x0d)/* Memory allocation error */
#define S_mzDrv_ERMT (aoM_mzDrv | 0x0e)/* Remote procedure call error */
#define S_mzDrv_ETMB (aoM_mzDrv | 0x0f)/* Timeout Trying to get board */
#define S_mzDrv_ERDB (aoM_mzDrv | 0x10)/* read buf filled up */
#define S_mzDrv_ILLEGAL_IOCTL  (aoM_mzDrv | 0x11)/* bad ioctl*/
#define S_mzDrv_0BYTES_READ    (aoM_mzDrv | 0x12)/* zero bytes from read*/
/*
 *	aoM_spsProg and agent
*/
#define S_spsProg_TOO_MANY_BUFS_FOR_PROG  	(aoM_spsProg| 0x01)
#define S_spsProg_NO_SPACE_SPSMEM_FOR_BUF 	(aoM_spsProg| 0x02)
#define S_spsProg_BUF_NOT_LOADED_IN_SPS   	(aoM_spsProg| 0x03)
#define S_spsProg_NO_BUFS_ON_FREE_LIST    	(aoM_spsProg| 0x04)
#define S_spsProg_ADDBUF_MSG_REQS_REPLYQ       	(aoM_spsProg| 0x05)
#define S_spsProg_BUFID_TOO_LONG               	(aoM_spsProg| 0x06)
#define S_spsProg_NOT_ENOUGH_DATA_SENT        	(aoM_spsProg| 0x07)
#define S_spsProg_INCORRECT_DATALEN_MSG       	(aoM_spsProg| 0x08)
#define S_spsProg_CANT_MALLOC_TEMP_BUF        	(aoM_spsProg| 0x09)
#define S_spsProg_ERROR_INPUTING_BUF_FILE     	(aoM_spsProg| 0x0a)
#define S_spsProg_NO_BUF_FOR_LIST             	(aoM_spsProg| 0x0b)
#define S_spsProg_FILEINP_LEN_MATCH_ERR         (aoM_spsProg| 0x0c)
#define S_spsProg_SPSPROG_NOT_RUNNING           (aoM_spsProg| 0x0d)
#define S_spsProg_NO_BUFID_SPECIFIED            (aoM_spsProg| 0x0e)
#define S_spsProg_PRLIST_MALLOC_ERR           	(aoM_spsProg| 0x0f)
/*
 *	aoM_autoLd 
*/
#define S_autoLd_PRGNAME_NOT_IN_LIST     	(aoM_autoLd | 0x01)
#define S_autoLd_DEPENDENCY_LOOP         	(aoM_autoLd | 0x02)
#define S_autoLd_CANT_OPEN_PRGFILE       	(aoM_autoLd | 0x03)
#define S_autoLd_MSG_REQUIRES_REPLY      	(aoM_autoLd | 0x04)
/*
 *	aoM_parse  
*/
#define S_parse_WRONG_DATATYPE_FOR_KEY   	(aoM_parse  | 0x01)
#define S_parse_KEYVAL_WONT_FIT_IN_BUF   	(aoM_parse  | 0x02)
#define S_parse_KEYINDEX_UNKNOWN_TO_PROG 	(aoM_parse  | 0x03) 
#define S_parse_ILLEGAL_VAL_FOR_KEYWORD  	(aoM_parse  | 0x04) 
#define S_parse_INTERNAL_ERR_BAD_PARSE_CODE (aoM_parse  | 0x05) 
/* 
*	aoM_swProg 
*/
#define S_swProg_IO_ON_BUT_PRG_NOT_RUNNING      (aoM_swProg  |0x01)
#define S_swProg_BAD_SETUPKEY_TP_DS_SK          (aoM_swProg  |0x02)
#define S_swProg_SETUPQ_MALLOC_ERROR            (aoM_swProg  |0x03)
/*
 *	aoM_dsProg 
*/
#define S_dsProg_NO_DISC_FILE_DEFINED           (aoM_dsProg  |0x01)
#define S_dsProg_DISC_IO_ERR                    (aoM_dsProg  |0x02)
#define S_dsProg_DISC_FLUSH_ERR                 (aoM_dsProg  |0x03)
#define S_dsProg_SETUPQ_MALLOC_ERROR            (aoM_dsProg  |0x04)
/*
 *	aoM_tpProg 
*/
#define S_tpProg_NO_TAPES_DEFINED               (aoM_tpProg  |0x01)
#define S_tpProg_TAPE_IO_ERR                    (aoM_tpProg  |0x02)
#define S_tpProg_SETUPQ_MALLOC_ERROR            (aoM_tpProg  |0x03)
#define S_tpProg_STAT_MALLOC_ERROR              (aoM_tpProg  |0x04)
#define S_tpProg_SENSE_MALLOC_ERROR             (aoM_tpProg  |0x05)
/*
 *	aoM_riProg 
*/
#define S_riProg_RIPROGTD_ALREADY_TAKINGDATA    (aoM_riProg  |0x01)
#define S_riProg_RIPROGTD_HAS_EXITED            (aoM_riProg  |0x02)
#define S_riProg_RIPROGTD_NOT_TAKINGDATA        (aoM_riProg  |0x03)
#define S_riProg_TIMEDOUT_WAITING_FOR_RIPROGTD  (aoM_riProg  |0x04)
#define S_riProg_TDRIPROG_BAD_CMD               (aoM_riProg  |0x05)
#define S_riProg_MALLOC_QSTARTUP_REPLY          (aoM_riProg  |0x06)
#if FALSE
#define S_riProg_NEED_TO_SPECIFY_OUT_MSGQ       (aoM_riProg  |0x07)
#define S_riProg_NEED_TO_SPECIFY_BUFFERPOOL     (aoM_riProg  |0x08)
#define S_riProg_SETUPQ_MALLOC_ERROR            (aoM_riProg  |0x09)
#endif
/*
 *	aoM_sufRpc 
*/
#define  S_sufRpc_CANT_MALLOC_SUBUF             (aoM_sufRpc  |0x01)
#define  S_sufRpc_CANT_OPEN_SUFILE              (aoM_sufRpc  |0x02)
#define  S_sufRpc_CANT_MALLOC_SUPRG_STRUCT      (aoM_sufRpc  |0x03)
#define  S_sufRpc_BAD_PROG_LINE                 (aoM_sufRpc  |0x04)
#define  S_sufRpc_UNKNOWN_PROGNAME_ON_PRG_LINE  (aoM_sufRpc  |0x05)
#define  S_sufRpc_SUBUF_OVERFLOW                (aoM_sufRpc  |0x06)
#define  S_sufRpc_BAD_HDRLEN_IN_FILE            (aoM_sufRpc  |0x07)
#define  S_sufRpc_CANT_MALLOC_HDRBUF            (aoM_sufRpc  |0x08)
#define  S_sufRpc_CANT_OPEN_HDRFILE             (aoM_sufRpc  |0x09)
#define  S_sufRpc_HDR_BYTES_READ_MISMATCH        (aoM_sufRpc  |0x0a)
/*
 *	aoM_ipSyn 
*/
#define  S_ipSyn_ILLEGAL_IPP                    (aoM_ipSyn   |0x01)
#define  S_ipSyn_ILLEGAL_INT_REQUESTED          (aoM_ipSyn   |0x02)
#define  S_ipSyn_INT1_USED_BY_EXTTICK_ROUTINE   (aoM_ipSyn   |0x03)
#define  S_ipSyn_STAT_DATA_ERR_FLAG_HI          (aoM_ipSyn   |0x04)
#define  S_ipSyn_ILLEGAL_RESET_REQUEST          (aoM_ipSyn   |0x05)
/*
 *	exabyte tape errors. lower 16 bits are status
*/
#define aoM_xbErr_BASE                              (aoM_xbErr |0x00 ) 
#define aoM_xbErr_MASK_LOW                          0x0000ffff 
#define aoM_xbErr_MASK_HI                           0xffff0000 
/*
 *	decoder errors.
*/
#define aoM_dcd_ILLEGAL_INT_REQUESTED    		(aoM_dcd     |0x00) 
#define aoM_dcd_ILLEGAL_SHIFT_ENA_LEN  		  	(aoM_dcd     |0x01) 
#define aoM_dcd_ILLEGAL_CODE_LEN  				(aoM_dcd     |0x02) 
#define aoM_dcd_ILLEGAL_CODE_START_ADR 			(aoM_dcd     |0x03) 
#define aoM_dcd_ILLEGAL_INTEGRATION_LEN			(aoM_dcd     |0x04) 
#define aoM_dcd_ILLEGAL_CORRELATION_PRODUCT		(aoM_dcd     |0x05) 
#define aoM_dcd_ILLEGAL_CONFIGURATION_WORD		(aoM_dcd     |0x06) 
#define aoM_dcd_ILLEGAL_COMMAND_WORD			(aoM_dcd     |0x07) 
#define aoM_dcd_LDRAM_ADDR_OVERFLOW   			(aoM_dcd     |0x08) 
#define aoM_dcd_LDRAM_ADDR_READBACK_MISMATCH	(aoM_dcd     |0x09) 
#define aoM_dcd_RDRAM_ADDR_OVERFLOW   			(aoM_dcd     |0x0a) 
#define aoM_dcd_ILLEGAL_SBC_NUMBER   		    (aoM_dcd     |0x0b) 
#define aoM_dcd_ILLEGAL_NUMBER_LAGS_REQUESTED   (aoM_dcd     |0x0c) 
#define aoM_dcd_DMPLEN_SHIFTLEN_INCOMPATIBLE    (aoM_dcd     |0x0d) 
#define aoM_dcd_ILLEGAL_RAM_LENGTH_REQUESTED    (aoM_dcd     |0x0e) 
#define aoM_dcd_RMTCREAD_ERR_REQ_LENGTH         (aoM_dcd     |0x0f) 
#define aoM_dcd_RAM_ILLEGAL_FIRST_ADR		    (aoM_dcd     |0x10) 
#define aoM_dcd_ILLEGAL_NUMBER_CHIPS_REQUESTED  (aoM_dcd     |0x11) 
#define aoM_dcd_ILLEGAL_CHIP_NUMBER_REQUESTED   (aoM_dcd     |0x12) 
#define aoM_dcd_SHIFT_ENA_VERIFY_MISMATCH       (aoM_dcd     |0x13) 
#define aoM_dcd_CODE_LEN_VERIFY_MISMATCH        (aoM_dcd     |0x14) 
#define aoM_dcd_CODE_START_ADR_VERIFY_MISMATCH  (aoM_dcd     |0x15) 
#define aoM_dcd_CODE_INTEG_LEN_VERIFY_MISMATCH  (aoM_dcd     |0x16) 
#define aoM_dcd_CODE_TIMEOUT_WAIT_INTEG_INT     (aoM_dcd     |0x17) 
#define aoM_dcd_LATE_FOR_DUMP_INTEGRATION_INT   (aoM_dcd     |0x18) 
#define aoM_dcd_CODE_CORRCHIP_TOTCNT_ERR        (aoM_dcd     |0x19) 
#define aoM_dcd_DUMPCNT_MISMATCH                (aoM_dcd     |0x1a) 
#define aoM_dcd_ERROR_OPENING_IP_DIGITAL_IO     (aoM_dcd     |0x1b) 
#define aoM_dcd_BAD_BW_NUM                      (aoM_dcd     |0x1c)
#define aoM_dcd_BAD_LAGCONFIG_FOR_DIG_FILTER    (aoM_dcd     |0x1d)
#define aoM_dcd_DNYQUIST_NOT_ALLOWED_THIS_BW    (aoM_dcd     |0x1e)
#define aoM_dcd_BW_REQUIRES_INTERLEAVE          (aoM_dcd     |0x1f)
#define aoM_dcd_DNYQUIST_AND_INTERLEAVE_ILLEGAL (aoM_dcd     |0x20)
#define aoM_dcd_BAD_NUMLAGS_THIS_CONFIG         (aoM_dcd     |0x21)
#define aoM_dcd_BAD_PWRCNT_READ_CODE            (aoM_dcd     |0x22)
#define aoM_dcd_PWRCNT_BUF_IS_NULL              (aoM_dcd     |0x23)
#define aoM_dcd_SINC_BAD_CLOCK_DIV_REQ          (aoM_dcd     |0x24) 
#define aoM_dcd_SINC_BAD_NUMBER_ACCUMULATIONS_REQ (aoM_dcd   |0x25)
#define aoM_dcd_SINC_BAD_OUTPUT_BIT_REQ	  	    (aoM_dcd     |0x26)
#define aoM_dcd_ILLEGAL_BIT_PACKING_REQ       	(aoM_dcd     |0x27)
#define aoM_dcd_ILLEGAL_SHIFT_PACKING_REQ      	(aoM_dcd     |0x28)
#define aoM_dcd_INBUFS_PER_OUTBUF_REQ      	    (aoM_dcd     |0x29)
#define aoM_dcd_TOTCNT_NEEDS_1024_LAGS_READ     (aoM_dcd     |0x2a)
#define aoM_dcd_RDSETUP_TOT_NUMLAGS_MISMATCH    (aoM_dcd     |0x2b)
#define aoM_dcd_RDSETUP_TOTCNTS_MISMATCH        (aoM_dcd     |0x2c)
#define aoM_dcd_RDSETUP_NOT_DONE                (aoM_dcd     |0x2d)
#define aoM_dcd_READ_LAGSTOREAD_MISMATCH        (aoM_dcd     |0x2e)
#define aoM_dcd_COMPLEX_MODE_AS_COR_ILLEGAL     (aoM_dcd     |0x2f)
#define aoM_dcd_ILLEGAL_LAGCONFIG_FOR_GETPOWER  (aoM_dcd     |0x30)
#define aoM_dcd_BAD_LAGCONFIG                   (aoM_dcd     |0x31)
#define aoM_dcd_BAD_DF_BIT_SHIFT                (aoM_dcd     |0x32)
#define aoM_dcd_ILLEGAL_PNCODE_LEN              (aoM_dcd     |0x33)

/*
 *	apProg errors.
*/
#define aoM_apProg_HOST_RCVBUF_TOO_SMALL	(aoM_apProg  |0x00) 
#define aoM_apProg_ERR_CNV_HOST_TO_VME_ADR 	(aoM_apProg  |0x01) 
#define aoM_apProg_SETUP_TOO_MANY_PROG_PARAMS 	(aoM_apProg  |0x02) 
#define aoM_apProg_SETUP_NO_PROGID         	(aoM_apProg  |0x03) 
#define aoM_apProg_SETUP_NO_FILENAME            (aoM_apProg  |0x04) 
#define aoM_apProg_SETUP_MISSING_IO_BUF_INFO    (aoM_apProg  |0x05) 
#define aoM_apProg_SETUP_MISSING_STRIPE_INFO    (aoM_apProg  |0x06) 
#define aoM_apProg_SETUP_NOT_ENOUGH_APS_AVAIL   (aoM_apProg  |0x07) 
#define aoM_apProg_SETUP_NO_SLOT_IN_SKYPROGSTBL (aoM_apProg  |0x08) 
#define aoM_apProg_SETUP_STARTING_APPROG        (aoM_apProg  |0x09) 
#define aoM_apProg_RCVAPPROG_MSGQ_IS_NULL       (aoM_apProg  |0x0a) 
#define aoM_apProg_GET_DMASEM_ERROR             (aoM_apProg  |0x0b) 
#define aoM_apProg_SND_TOAP_BUF_TOO_LARGE	(aoM_apProg  |0x0c)
#define aoM_apProg_BAD_SKYPROG_IND_FOR_SYNC 	(aoM_apProg  |0x0d)
#define aoM_apProg_ERR_TAKING_SYNC_SEMAPHORE    (aoM_apProg  |0x0e)
/*
 * tpInpProg
*/
#define S_tpInpProg_PROGTD_ALREADY_TAKINGDATA      (aoM_tpInpProg  |0x01)
#define S_tpInpProg_PROGTD_HAS_EXITED              (aoM_tpInpProg  |0x02)
#define S_tpInpProg_PROGTD_NOT_TAKINGDATA          (aoM_tpInpProg  |0x03)
#define S_tpInpProg_TIMEDOUT_WAITING_FOR_PROGTD    (aoM_tpInpProg  |0x04)
#define S_tpInpProg_PROGTD_BAD_CMD                 (aoM_tpInpProg  |0x05)
#define S_tpInpProg_NEED_TO_DO_SETUP               (aoM_tpInpProg  |0x06)
#define S_tpInpProg_NEED_TO_SPECIFY_OUT_MSGQ       (aoM_tpInpProg  |0x07)
#define S_tpInpProg_NEED_TO_SPECIFY_BUFFERPOOL     (aoM_tpInpProg  |0x08)
#define S_tpInpProg_NO_TAPES_DEFINED               (aoM_tpInpProg  |0x09)
#define S_tpInpProg_TAPE_IO_ERR                    (aoM_tpInpProg  |0x0a)
/*
 * kl2500 switch 
*/
#define S_aoM_kl2500_BAD_SW_NUM    	           (aoM_kl2500     |0x01)
#define S_aoM_kl2500_REQ_NOT_VALID  	           (aoM_kl2500     |0x02)
#define S_aoM_kl2500_SW_DID_NOT_OPEN               (aoM_kl2500     |0x03)
#define S_aoM_kl2500_SWS_DID_NOT_CLR               (aoM_kl2500     |0x04)
#define S_aoM_kl2500_BAD_SW_POSITION 	           (aoM_kl2500     |0x05)
#define S_aoM_kl2500_SW_DID_NOT_CLOSE              (aoM_kl2500     |0x06)
#define S_aoM_kl2500_COULD_NOT_RD_SW               (aoM_kl2500     |0x07)
/*
 * rfiRcv 
*/

#define S_rfiRcv_BAD_ANT_ID    		           (aoM_rfiRcv     |0x01)
#define S_rfiRcv_BAD_FILTER_ID    	           (aoM_rfiRcv     |0x02)
#define S_rfiRcv_BAD_FOAMP_ID    	           (aoM_rfiRcv     |0x03)
#define S_rfiRcv_FLTNUM_AND_CFR_BOTH_DEFAULTED     (aoM_rfiRcv     |0x04)
#define S_rfiRcv_BAD_FILTER_NUM_REQ	           (aoM_rfiRcv     |0x05)
#define S_rfiRcv_BAD_CFR_REQ                       (aoM_rfiRcv     |0x06)
#define S_rfiRcv_BAD_BW_REQ                        (aoM_rfiRcv     |0x07)
#define S_rfiRcv_BAD_ANT_NUM                       (aoM_rfiRcv     |0x08)
#define S_rfiRcv_BAD_FIBER_OPTIC_AMP_NUM           (aoM_rfiRcv     |0x09)
/*
 * logic analyzer errors
*/

#define S_aoM_la_TIMEOUT_WAITING_RUN	           ( aoM_la        |0x01)
/*
 * hp3488 switch driver
*/
#define S_hp3488_BAD_CHN_ADR 		   	      ( aoM_hp3488    |0x01)
#define S_hp3488_BAD_MEM_REG 		              ( aoM_hp3488    |0x02)
#define S_hp3488_SYNTAX_ERR  		              ( aoM_hp3488    |0x03) 
#define S_hp3488_EXEC_ERR  		   	      ( aoM_hp3488    |0x04) 
#define S_hp3488_TRIG_ERR        		      ( aoM_hp3488    |0x05)
#define S_hp3488_LOGIC_ERR  		              ( aoM_hp3488    |0x06)
#define S_hp3488_POWER_ERR  		              ( aoM_hp3488    |0x07)
#define S_hp3488_ILLEGAL_DIGITAL_IO_PORT   	      ( aoM_hp3488    |0x08)
#define S_hp3488_DWRITE_DATA_OUT_OF_RANGE 	      ( aoM_hp3488    |0x09)
#define S_hp3488_DMODE_MODE_ILLEGAL                   ( aoM_hp3488    |0x0a)
#define S_hp3488_DREAD_NON_INT_DATA_READ  	      ( aoM_hp3488    |0x0b)
#define S_hp3488_OPEN_WITH_ILLEGAL_DEV_NUM	      ( aoM_hp3488    |0x0c)
/*
 * hp87130 switch driver
*/
#define S_hp87130_DCDREPLY_RETURN_CNT_MISMATCH        ( aoM_hp87130   |0x01)
#define S_hp87130_MAKELIST_STRING_TOO_SMALL           ( aoM_hp87130   |0x02)
#define S_hp87130_QWIDTH_REPLY_DATA_BAD_FORMAT        ( aoM_hp87130   |0x03)
#define S_hp87130_QWIDTH_REPLY_MISSING_DATA           ( aoM_hp87130   |0x04)
#define S_hp87130_QWIDTH_NO_DATA_RETURNED             ( aoM_hp87130   |0x05)
#define S_hp87130_QERROR_BAD_RET_VAL                  ( aoM_hp87130   |0x06)
#define S_hp87130_PARSE_ERR_BAD_CARDNUM               ( aoM_hp87130   |0x07)
/*
 * rf if1 setup
*/
#define S_rfIf1_ILLEGAL_RF_FREQ_REQ                   ( aoM_rfIf1     |0x01)
#define S_rfIf1_ILLEGAL_IF1_FREQ_REQ                  ( aoM_rfIf1     |0x02) 
#define S_rfIf1_ILLEGAL_RF_ATTN_A_REQ                 ( aoM_rfIf1     |0x03)
#define S_rfIf1_ILLEGAL_RF_ATTN_B_REQ                 ( aoM_rfIf1     |0x04)
#define S_rfIf1_ILLEGAL_IF1_ATTN_A_REQ                ( aoM_rfIf1     |0x05)
#define S_rfIf1_ILLEGAL_IF1_ATTN_B_REQ                ( aoM_rfIf1     |0x06)
#define S_rfIf1_ILLEGAL_RFTBL_SW_NUM                  ( aoM_rfIf1     |0x07)
#define S_rfIf1_ILLEGAL_ATTN_SW_NUM                   ( aoM_rfIf1     |0x08)
#define S_rfIf1_ILLEGAL_IF1TBL_SW_NUM                 ( aoM_rfIf1     |0x09)
#define S_rfIf1_ILLEGAL_SW_NUM                        ( aoM_rfIf1     |0x0a)
#define S_rfIf1_ERROR_CLOSE_SW                        ( aoM_rfIf1     |0x0b)
#define S_rfIf1_ERROR_OPEN_SW                         ( aoM_rfIf1     |0x0c)
#define S_rfIf1_ILLEGAL_CABLE_A_REQ                   ( aoM_rfIf1     |0x0d)
#define S_rfIf1_ILLEGAL_CABLE_B_REQ                   ( aoM_rfIf1     |0x0e)
#define S_rfIf1_SW_ERROR                              ( aoM_rfIf1     |0x0f)
#define S_rfIf1_SW_ERROR_READING_ERRORS               ( aoM_rfIf1     |0x10)
#define S_rfIf1_SW_ERROR_BAD_RET_VALUE                ( aoM_rfIf1     |0x11)
#define S_rfIf1_SW_VERIFY_ERROR                       ( aoM_rfIf1     |0x12)
#define S_rfIf1_ILLEGAL_HYBRID_INOUT_REQ              ( aoM_rfIf1     |0x13)
#define S_rfIf1_ERROR_SET_VERIFY                      ( aoM_rfIf1     |0x14)
#define S_rfIf1_ERROR_SET_WIDTH                       ( aoM_rfIf1     |0x15)
#define S_rfIf1_ERROR_SET_DRIVE                       ( aoM_rfIf1     |0x16)
#define S_rfIf1_PWRMETER_NOT_OPEN                     ( aoM_rfIf1     |0x17)
#define S_rfIf1_LBN_FILTERBANK_ILLEGAL_REQUEST        ( aoM_rfIf1     |0x18)
/*
 * aoMessage socket program
*/
#define S_aomSk_EOF                       	      (aoM_aomSk   | 1)
#define S_aomSk_SHORT_REC_READ_DATA  		      (aoM_aomSk   | 2)
#define S_aomSk_SHORT_REC_READ_HDR                    (aoM_aomSk   | 3)
#define S_aomSk_ERROR_READ_HDR                        (aoM_aomSk   | 4)
#define S_aomSk_ERROR_READ_DATA                       (aoM_aomSk   | 5) 
#define S_aomSk_BAD_HDR_ID                            (aoM_aomSk   |0xa)
#define S_aomSk_MALLOC_ERR_DATA_BUF                   (aoM_aomSk   |0xf)
#define S_aomSk_FD_TABLE_FULL                         (aoM_aomSk   |0x10)
/*
 * pointing program 
*/
#define S_pnt_BAD_UTC_TO_UT1_FILENAME          	      (aoM_pnt     |   1)
#define S_pnt_UTC_TO_UT1_DATE_BEFORE_FILE_DATES       (aoM_pnt     |   2)
#define S_pnt_UTC_TO_UT1_NO_DATES_IN_FILE             (aoM_pnt     |   3)
#define S_pnt_BAD_OBS_POSITION_FILENAME       	      (aoM_pnt     |   4)
#define S_pnt_LOCKAGCST_ERR_WAITING_FOR_AGCSTSEM      (aoM_pnt     |   6)
#define S_pnt_LOCKAGCST_ERR_TAKING_AGCSTMXSEM         (aoM_pnt     |   7)
#define S_pnt_LOCKPNTX_ERR_WAITING_FOR_AGCSTSEM       (aoM_pnt     |   8)
#define S_pnt_LOCKPNTX_ERR_TAKING_PNTXMXSEM           (aoM_pnt     |   9)
#define S_pnt_MALLOC_ERR_AGCMONREQ                    (aoM_pnt     |0x0a)
#define S_pnt_AGCMODE_PDATA_NULL                      (aoM_pnt     |0x0b)
#define S_pnt_AGCMODE_BAD_MODE_REQUESTED              (aoM_pnt     |0x0c)
#define S_pnt_OPARMS_PDATA_NULL                       (aoM_pnt     |0x0d)
#define S_pnt_TURMODE_SLEW_PDATA_BAD                  (aoM_pnt     |0x0e)
#define S_pnt_BAD_MASTERMODE_IN_AGCPROG               (aoM_pnt     |0x0f)
#define S_pnt_MALLOC_ERR_RETURNBUF_GEN_QUERY          (aoM_pnt     |0x10)
#define S_pnt_PNTPROG_HAS_BAD_WRAP                    (aoM_pnt     |0x11)
#define S_pnt_ILLEGAL_TOLERANCE_VALUE_REQUESTED       (aoM_pnt     |0x12)
#define S_pnt_ILLEGAL_WRAP_REQUESTED                  (aoM_pnt     |0x13)
#define S_pnt_CANNOT_OPEN_MODEL_FILE                  (aoM_pnt     |0x14)
#define S_pnt_CANNOT_OPEN_ENCODER_FILE                (aoM_pnt     |0x15)
#define S_pnt_BADLINE_MODEL_FILE                      (aoM_pnt     |0x16)
#define S_pnt_BADLINE_ENCODER_FILE                    (aoM_pnt     |0x17)
#define S_pnt_TRKCMD_BAD_REQUEST_CODE                 (aoM_pnt     |0x18)
#define S_pnt_TUR_TRACKING_MUST_STOP_BEFORE_POS       (aoM_pnt     |0x19)
#define S_pnt_UNSUPPORTED_MODE_REQUEST                (aoM_pnt     |0x1a)
#define S_pnt_ILLEGAL_DOPCOR_VEL_SYSTEM               (aoM_pnt     |0x1b)
#define S_pnt_ILLEGAL_TIEDOWN_REQUESTED               (aoM_pnt     |0x1c)
#define S_pnt_BAD_TTT_LOCATION_REQUESTED              (aoM_pnt     |0x1d)
#define S_pnt_TIE_TRACKING_MUST_STOP_BEFORE_POS       (aoM_pnt     |0x1e)
#define S_pnt_TIE_PENDING_PNT_NO_POS_REQ_ALLOWED      (aoM_pnt     |0x1f)
#define S_pnt_TIE_ACTIVE_PNT_NO_POS_REQ_ALLOWED       (aoM_pnt     |0x20)
#define S_pnt_ILLEGAL_SETTLE_TIME_REQUESTED           (aoM_pnt     |0x21)
#define S_pnt_TD_PITCH_ROLL_COEFF_NOT_INITIALIZED     (aoM_pnt     |0x22)
#define S_pnt_TD_PITCH_ROLL_COEFF_INIT_BAD_DATA       (aoM_pnt     |0x23)
#define S_pnt_TER_TRACKING_MUST_STOP_BEFORE_POS       (aoM_pnt     |0x24)
#define S_pnt_TER_PENDING_PNT_NO_POS_REQ_ALLOWED      (aoM_pnt     |0x25)
#define S_pnt_TER_ACTIVE_PNT_NO_POS_REQ_ALLOWED       (aoM_pnt     |0x26)
#define S_pnt_ILLEGAL_TERTIARY_AXIS_REQUESTED         (aoM_pnt     |0x27)
#define S_pnt_NO_ENCTBLNAME_IN_MODELFILE              (aoM_pnt     |0x28)
#define S_pnt_ILLEGAL_MAXVEL_FOR_TUR                  (aoM_pnt     |0x29)
#define S_pnt_EPHM_LD_OPENNING_FILE                   (aoM_pnt     |0x2a)
#define S_pnt_EPHM_LD_INPUT_DATE                      (aoM_pnt     |0x2b)
#define S_pnt_EPHM_LD_CONVERTING_DATA                 (aoM_pnt     |0x2c)
#define S_pnt_EPHM_ILLEGAL_LD_REQUEST                 (aoM_pnt     |0x2d)
#define S_pnt_EPHM_MALLOC_ERR                         (aoM_pnt     |0x2e)
#define S_pnt_EPHM_NEED_FILE_LOAD_BEFORE_TRACK        (aoM_pnt     |0x2f)
#define S_pnt_EPHM_NEED_FILE_LOAD_BEFORE_GET          (aoM_pnt     |0x30)
#define S_pnt_EPHM_BAD_TIME_GET_REQ                   (aoM_pnt     |0x31)

/*
 * ipdigital i/o
*/
#define S_ipDio_ILLEGAL_IPSLOT       		      (aoM_ipDio  |  1) 
/*
 * ip dma.
*/
#define S_ipDma_ENA_BIT_DIDNOT_SET   		      (aoM_ipDma  |  1) 
#define S_ipDma_TIMEOUT_DMA_INTERRUPT 		      (aoM_ipDma  |  2) 
#define S_ipDma_STAT_TIMEOUT_IP_BUS    	              (aoM_ipDma  |  3) 
#define S_ipDma_STAT_CHN_CMD_READ_BUS_ERR             (aoM_ipDma  |  4) 
#define S_ipDma_STAT_TIMEOUT_68K_BUS                  (aoM_ipDma  |  5) 
#define S_ipDma_STAT_CHN_BLK_DONE                     (aoM_ipDma  |  6) 
#define S_ipDma_STAT_DMAEND_ASSERTED_BY_IP            (aoM_ipDma  |  7) 
#define S_ipDma_STAT_DMA_DONE_NOT_ASSERTED            (aoM_ipDma  |  8) 
#define S_ipDma_WORDS_READ_NOT_CORRECT                (aoM_ipDma  |  9) 
#define S_ipDma_BYTESTOXFER_VERIFY_MISMATCH           (aoM_ipDma  |0xa) 
#define S_ipDma_LATE_FOR_INTERRUPT                    (aoM_ipDma  |0xb) 
#define S_ipDma_ILLEGAL_IPTOUSE	                      (aoM_ipDma  |0xc) 
#define S_ipDma_WORDS_WRITTEN_NOT_CORRECT             (aoM_ipDma  |0xd)
/*
 * aoGcsr - ao system gcsr routines.
*/
#define S_gcsr_ILLEGAL_GCSR_GRP		      	          (aoM_gcsr   |  1) 
#define S_gcsr_ILLEGAL_CPU_NUM 		              	  (aoM_gcsr   |  2) 
#define S_gcsr_ILLEGAL_MB_NUM  		              	  (aoM_gcsr   |  3) 
#define S_gcsr_INTERRUPT_NOT_INITIALIZED              (aoM_gcsr   |  4)
#define S_gcsr_ILLEGAL_INTERRUPT_LEVEL 	              (aoM_gcsr   |  5) 
#define S_gcsr_ILLEGAL_SLAVE_NUMBER                   (aoM_gcsr   |  6) 
#define S_gcsr_NOT_ENOUGH_SLAVE_SLOTS_AVAILABLE       (aoM_gcsr   |  7) 
#define S_gcsr_INTERRUPT_REQUIRED_FOR_REPLY           (aoM_gcsr   |  8) 
#define S_gcsr_ILLEGAL_CMD_REQ                        (aoM_gcsr   |  9) 
#define S_gcsr_DEVICE_NOT_OPENED                      (aoM_gcsr   | 0xa) 
#define S_gcsr_CPUNUM_REQ_VMEINT_OUTSIDE_RANGE        (aoM_gcsr   | 0xb) 
#define S_gcsr_SLAVE_TIMEDOUT_ON_RESET                (aoM_gcsr   | 0xc) 
/*
 * dcdR - remote decoder routines.
*/
#define S_dcdR_TOO_MANY_DECODERS_REQUESTED	      	  (aoM_dcdR   |  1)
#define S_dcdR_ILLEGAL_DECODER_BOARD_NUMBER           (aoM_dcdR   |  2)
#define S_dcdR_REQUESTED_DECODER_NOT_AVAILABLE        (aoM_dcdR   |  3)
#define S_dcdR_MALLOC_ERR_INUSE_SLVI                  (aoM_dcdR   |  4)
#define S_dcdR_DCDNUM_NOT_CONFIGURED_OPEN_CALL        (aoM_dcdR   |  5)
#define S_dcdR_READ_TOO_MANY_BOARDS_REQUESTED         (aoM_dcdR   |  6)
#define S_dcdR_MEASURE_PWR_ILLEGAL_REQ                (aoM_dcdR   |  7) 
#define S_dcdR_MEASURE_PWR_ILLEGAL_INTEG_TIME         (aoM_dcdR   |  8)
#define S_dcdR_SET_ATTN_NOT_ENOUGH_ATTEN_VALUES       (aoM_dcdR   |  9)
#define S_dcdR_ADJ_PWR_ILLEGAL_INTEG_TIME             (aoM_dcdR   |0x0a)
/*
 * prgMgr - program manager
*/
#define S_PRGMGR_CANT_OPEN_PRGFILE		              (aoM_prgMgr |   1)
#define S_PRGMGR_BAD_LINE_IN_PRGFILE		          (aoM_prgMgr |   2)
#define S_PRGMGR_WAITFUNC_NOT_LOADED        	      (aoM_prgMgr |   3)
#define S_PRGMGR_BAD_PROGRAM_NAME           	      (aoM_prgMgr |   4)
#define S_PRGMGR_BAD_PROGRAM_NUMBER         	      (aoM_prgMgr |   5)
#define S_PRGMGR_CANT_START_REMOTE_PROG     	      (aoM_prgMgr |   6)
#define S_PRGMGR_PROGRAM_NOT_LOADED         	      (aoM_prgMgr |   7)
#define S_PRGMGR_PROGRAM_ALREADY_RUNNING    	      (aoM_prgMgr |   8)
#define S_PRGMGR_BAD_LOCPROG_STATUS_CODE    	      (aoM_prgMgr |0x09)
#define S_PRGMGR_START_FUNCTION_IS_NULL     	      (aoM_prgMgr |0x0a)
#define S_PRGMGR_PRGSTART_DIDNT_SET_QIDS              (aoM_prgMgr |0x0b)
#define S_PRGMGR_NOT_A_LOCAL_PROGRAM                  (aoM_prgMgr |0x0c)
#define S_PRGMGR_PROG_HAS_NO_INPQ                     (aoM_prgMgr |0x0d)
#define S_PRGMGR_PROG_HAS_NO_REPLYQ                   (aoM_prgMgr |0x0e)
#define S_PRGMGR_PROG_NOT_RUNNING                     (aoM_prgMgr |0x0f)
#define S_PRGMGR_EXIT_REQ_FOR_PRGMGR                  (aoM_prgMgr |0x10)
#define S_PRGMGR_UNKNOWN_CPU_NAME                     (aoM_prgMgr |0x11)
#define S_PRGMGR_NOT_INITIALIZED                      (aoM_prgMgr |0x12)
#define S_PRGMGR_QID_NOT_IN_PRGTBL                    (aoM_prgMgr |0x13)
#define S_PRGMGR_BP_ALREADY_EXISTS                    (aoM_prgMgr |0x14)
#define S_PRGMGR_BP_NO_FREE_SLOTS_BPTABLE             (aoM_prgMgr |0x15)
#define S_PRGMGR_BP_BPNAME_DOESNT_EXIST               (aoM_prgMgr |0x16)
#define S_PRGMGR_SIGNAL_FOR_REMOTE_PROG               (aoM_prgMgr |0x17)
#define S_PRGMGR_SIGNAL_PRG_NOT_RUNNING               (aoM_prgMgr |0x18)
#define S_PRGMGR_SIGNAL_BAD_TASKID                    (aoM_prgMgr |0x19)
#define S_PRGMGR_MALLOC_REPLY_BUF                     (aoM_prgMgr |0x1a)
#define S_PRGMGR_NO_PROGRAM_SPECIFIED                 (aoM_prgMgr |0x1b)
#define S_PRGMGR_PRGNAME_TOO_LONG                     (aoM_prgMgr |0x1c)
/*
 * gateway program errors
*/
#define S_GWPRG_GWIN_BAD_TO_ADR                       (aoM_gwPrg  |0x01)
#define S_GWPRG_GWIN_BAD_FROM_ADR                     (aoM_gwPrg  |0x02)
#define S_GWPRG_GWOUT_BAD_TO_ADR                      (aoM_gwPrg  |0x03)
/*
 * network initialization 
*/
#define S_NETCF_CANT_OPEN_HOSTS_FILE                  (aoM_netcf  |0x01)
#define S_NETCF_BAD_ENTRY_HOSTS_FILE                  (aoM_netcf  |0x02)
#define S_NETCF_TOO_MANY_HOSTS_IN_FILE                (aoM_netcf  |0x03)
#define S_NETCF_CANT_OPEN_NETWORK_FILE                (aoM_netcf  |0x04)
#define S_NETCF_BAD_ENTRY_NETWORK_FILE                (aoM_netcf  |0x05)
#define S_NETCF_TOO_MANY_NETWORKS_IN_FILE             (aoM_netcf  |0x06)
#define S_NETCF_BAD_CRATE_NAME                        (aoM_netcf  |0x07)
#define S_NETCF_BAD_CRATE_MASTER_CPU_IPADR            (aoM_netcf  |0x08)
#define S_NETCF_LOCAL_CPUNAME_NOT_IN_HOSTS_FILE       (aoM_netcf  |0x09)
/*
 * unpacking records...
*/
#define  S_UNPR_BAD_HDRMARKER                           (aoM_unpR |   1)
#define  S_UNPR_HDRID_MISMATCH                          (aoM_unpR |   2)
#define  S_UNPR_BYTESREAD_RECLEN_MISMATCH               (aoM_unpR |   3)
#define  S_UNPR_EOF                                     (aoM_unpR |   4)
#define  S_UNPR_RETURN_BUF_TOO_SMALL                    (aoM_unpR |   5)
#define  S_UNPR_INPREC_BUFSIZE_TOO_SMALL                (aoM_unpR |   6)
#define  S_UNPR_GRPREC_BUFSIZE_TOO_SMALL                (aoM_unpR |   7)
#define  S_UNPR_GRPREC_COUNTER_MISMATCH                 (aoM_unpR |   8)
/*
 * dcdPrL decoder program on mv162fx
*/
#define  S_DCDPRL_TDPROG_BAD_CMD                        (aoM_dcdPrL |   1)
#define  S_DCDPRL_ALREADY_TAKING_DATA                   (aoM_dcdPrL |   2)
#define  S_DCDPRL_TDPROG_HAS_EXITED  		 	(aoM_dcdPrL |   3)
#define  S_DCDPRL_TDPROG_NOT_TAKING_DATA_NO_STOP 	(aoM_dcdPrL |   4)
#define  S_DCDPRL_TIMEDOUT_WAITING_FOR_TDPROG    	(aoM_dcdPrL |   5)
#define  S_DCDPRL_READ_REQUESTED_TOO_MANY_WORDS        	(aoM_dcdPrL |   6)
#define  S_DCDPRL_READ_OBUF_MSGQ_IS_NULL               	(aoM_dcdPrL |   7)
#define  S_DCDPRL_READ_NOT_TAKING_DATA                 	(aoM_dcdPrL |   8)
#define  S_DCDPRL_ILLEGAL_REQ_WHILE_TAKINGDATA         	(aoM_dcdPrL |   9)
#define  S_DCDPRL_MSGTYPE_NOT_DATABUF                  	(aoM_dcdPrL | 0xa)
#define  S_DCDPRL_LATE_WAITING_FOR_DUMP_INTERRUPT       (aoM_dcdPrL | 0xb)
#define  S_DCDPRL_TIMEOUT_STARTUP_PROCESSING_PROG       (aoM_dcdPrL | 0xc)
#define  S_DCDPRL_PROCESSING_PROG_INPQ_NULL             (aoM_dcdPrL | 0xd)
/*
 * tdCom program communications.
*/
#define  S_TDCOM_ALREADY_TAKING_DATA                    (aoM_tdCom  |   1)
#define  S_TDCOM_TAKEDATA_PROGRAM_HAS_EXITED            (aoM_tdCom  |   2)
#define  S_TDCOM_TAKEDATA_PROGRAM_NOT_TAKING_DATA       (aoM_tdCom  |   3)
#define  S_TDCOM_TIMEDOUT_WAITING_FOR_TAKEDATA_PROGRAM  (aoM_tdCom  |   4)
#define  S_TDCOM_ILLEGAL_CMD_FOR_TAKEDATA_PROGRAM  	    (aoM_tdCom  |   5)
#define  S_TDCOM_CANT_FLUSH_BUFS_WHILE_TAKING_DATA 	    (aoM_tdCom  |   6)
#define  S_TDCOM_TDPROG_RECEIVED_ILLEGAL_CMD            (aoM_tdCom  |   7)
/*
 * pncode generator
*/
#define  S_PNC_ILLEGAL_SHIFT_ENA_LEN                    (aoM_pnc    |   1)
#define  S_PNC_ILLEGAL_CODE_LEN                         (aoM_pnc    |   2)
#define  S_PNC_ILLEGAL_CODE_START_ADR                   (aoM_pnc    |   3)
#define  S_PNC_ILLEGAL_COMMAND_WORD                     (aoM_pnc    |   4)
#define  S_PNC_LDRAM_ADDR_READBACK_MISMATCH             (aoM_pnc    |   5)
#define  S_PNC_RDRAM_ADDR_OVERFLOW                      (aoM_pnc    |   6)
#define  S_PNC_STATUS_RUNBIT_HI_AFTER_STOP              (aoM_pnc    |   7)
#define  S_PNC_SHIFTENABLE_READBACK_MISMATCH            (aoM_pnc    |   8)
#define  S_PNC_CODELEN_READBACK_MISMATCH                (aoM_pnc    |   9)
#define  S_PNC_CODE_START_ADR_READBACK_MISMATCH         (aoM_pnc    | 0xa)
#define  S_PNC_STATUS_RUNBIT_LOW_AFTER_IMD_START        (aoM_pnc    | 0xb)
#define  S_PNC_ILLEGAL_START_REQUEST                    (aoM_pnc    | 0xc)
#define  S_PNC_ERROR_COMPUTE_CODE                       (aoM_pnc    | 0xd)
/*
 * long pncode generator
*/
#define  S_PNCL_ILLEGAL_SHIFT_ENA_LEN                    (aoM_pncl    |   1)
#define  S_PNCL_ILLEGAL_CONFIG_WRD                       (aoM_pncl    |   2)
#define  S_PNCL_ILLEGAL_CODE_START_VAL                   (aoM_pncl    |   3)
#define  S_PNCL_ILLEGAL_COMMAND_WORD                     (aoM_pncl    |   4)
#define  S_PNCL_STATUS_RUNBIT_HI_AFTER_STOP              (aoM_pncl    |   7)
#define  S_PNCL_SHIFTENABLE_READBACK_MISMATCH            (aoM_pncl    |   8)
#define  S_PNCL_FREE                                     (aoM_pncl    |   8) 
#define  S_PNCL_CODE_START_VAL_READBACK_MISMATCH         (aoM_pncl    | 0xa)
#define  S_PNCL_STATUS_RUNBIT_LOW_AFTER_IMD_START        (aoM_pncl    | 0xb)
#define  S_PNCL_ILLEGAL_START_REQUEST                    (aoM_pncl    | 0xc)
#define  S_PNCL_MALLOC_ERR_QUERY_PHASE                   (aoM_pncl    | 0xd)
#define  S_PNCL_MALLOC_ERR_QUERY_GEN                     (aoM_pncl    | 0xe)
/*
 * if2 program.
*/
#define  S_IF2_HP3488_BAD_DIGIO_CARD_TYPE             (aoM_if2  |   1) 
#define  S_IF2_ILLEGAL_INP_IF_FREQ_REQ                (aoM_if2  |   2)
#define  S_IF2_MIXER1_ILLEGAL_INP_FREQ_REQ            (aoM_if2  |   3)
#define  S_IF2_MIXER2_ILLEGAL_INP_FREQ_REQ            (aoM_if2  |   4)
#define  S_IF2_MIXER3_ILLEGAL_INP_FREQ_REQ            (aoM_if2  |   5)
#define  S_IF2_MIXER4_ILLEGAL_INP_FREQ_REQ            (aoM_if2  |   6)
#define  S_IF2_INPFRQ_MIXER1_FRQ_MISMATCH             (aoM_if2  |   7)
#define  S_IF2_INPFRQ_MIXER2_FRQ_MISMATCH             (aoM_if2  |   8)
#define  S_IF2_INPFRQ_MIXER3_FRQ_MISMATCH             (aoM_if2  |   9)
#define  S_IF2_INPFRQ_MIXER4_FRQ_MISMATCH             (aoM_if2  | 0xa)
#define  S_IF2_AMP1_ILLEGAL_INP_FREQ_REQ              (aoM_if2  | 0xb)
#define  S_IF2_AMP2_ILLEGAL_INP_FREQ_REQ              (aoM_if2  | 0xc)
#define  S_IF2_AMP3_ILLEGAL_INP_FREQ_REQ              (aoM_if2  | 0xd)
#define  S_IF2_AMP4_ILLEGAL_INP_FREQ_REQ              (aoM_if2  | 0xe)
#define  S_IF2_AMP1_INP_MISMATCH             		  (aoM_if2  | 0xf)
#define  S_IF2_AMP2_INP_MISMATCH             		  (aoM_if2  | 0x10)
#define  S_IF2_AMP3_INP_MISMATCH             		  (aoM_if2  | 0x11)
#define  S_IF2_AMP4_INP_MISMATCH             		  (aoM_if2  | 0x12)
#define  S_IF2_AMP1_EXT_SW_ILLEGAL_VALUE     		  (aoM_if2  | 0x13)
#define  S_IF2_AMP2_EXT_SW_ILLEGAL_VALUE     		  (aoM_if2  | 0x14)
#define  S_IF2_AMP3_EXT_SW_ILLEGAL_VALUE     		  (aoM_if2  | 0x15)
#define  S_IF2_AMP4_EXT_SW_ILLEGAL_VALUE     		  (aoM_if2  | 0x16)
#define  S_IF2_AMP1_EXTERNAL_INP_MISMATCH   		  (aoM_if2  | 0x17)
#define  S_IF2_AMP2_EXTERNAL_INP_MISMATCH   		  (aoM_if2  | 0x18)
#define  S_IF2_AMP3_EXTERNAL_INP_MISMATCH   		  (aoM_if2  | 0x19)
#define  S_IF2_AMP4_EXTERNAL_INP_MISMATCH   		  (aoM_if2  | 0x1a)
#define  S_IF2_FRQ_SWNUM_NOT_IN_SWTABLE          	  (aoM_if2  | 0x1b)
#define  S_IF2_FRQ_REQ_NOT_IN_INPIF_FRQ_TABLE 	 	  (aoM_if2  | 0x1c)
#define  S_IF2_FRQ_REQ_NOT_IN_MIXER_FRQ_TABLE 	      (aoM_if2  | 0x1d)
#define  S_IF2_FRQ_REQ_NOT_IN_AMP_INP_TABLE 		  (aoM_if2  | 0x1e)
#define  S_IF2_BAD_AMP_EXTERNAL_INP_MASK    		  (aoM_if2  | 0x1f)
#define  S_IF2_VLBA_INP_MISMATCH         	          (aoM_if2  | 0x20)
#define  S_IF2_BAD_VLBA_INP_FREQ             	      (aoM_if2  | 0x21)
#define  S_IF2_BAD_PRE_ATTN_REQUEST          	      (aoM_if2  | 0x22)
#define  S_IF2_BAD_PRE_AMP_REQUEST          	      (aoM_if2  | 0x23)
#define  S_IF2_SYNTHSW1_NOT_IN_SWTABLE      	      (aoM_if2  | 0x24)
#define  S_IF2_ILLEGAL_SYNTH1_POS_REQUESTED           (aoM_if2  | 0x25)
#define  S_IF2_ILLEGAL_SYNTH2_POS_REQUESTED           (aoM_if2  | 0x26)
#define  S_IF2_ILLEGAL_SYNTH3_POS_REQUESTED           (aoM_if2  | 0x27)
#define  S_IF2_ILLEGAL_SYNTH4_POS_REQUESTED           (aoM_if2  | 0x28)
#define  S_IF2_SYNTH1_POS_MISMATCH                    (aoM_if2  | 0x29)
#define  S_IF2_SYNTH2_POS_MISMATCH                    (aoM_if2  | 0x2a)
#define  S_IF2_SYNTH3_POS_MISMATCH                    (aoM_if2  | 0x2b)
#define  S_IF2_SYNTH4_POS_MISMATCH                    (aoM_if2  | 0x2c)
#define  S_IF2_RDBACK_REQUIRES_REPLY_MSG              (aoM_if2  | 0x2d)
#define  S_IF2_PWRMETER_NOT_OPEN                      (aoM_if2  | 0x2e)
#define  S_IF2_MEASURE_PWR_ILLEGAL_REQ                (aoM_if2  | 0x2f)
#define  S_IF2_MEASURE_PWR_ILLEGAL_LOCATION           (aoM_if2  | 0x30)
#define  S_IF2_MEASURE_PWR_ILLEGAL_POL                (aoM_if2  | 0x31)
#define  S_IF2_MEASURE_PWR_ILLEGAL_NUMBER_READS_REQ   (aoM_if2  | 0x32)
#define  S_IF2_MEASURE_PWR_MALLOC_ERR                 (aoM_if2  | 0x33)
#define  S_IF2_MIXER5_ILLEGAL_INP_FREQ_REQ            (aoM_if2  | 0x34)
#define  S_IF2_MIXER6_ILLEGAL_INP_FREQ_REQ            (aoM_if2  | 0x35)
#define  S_IF2_MIXER7_ILLEGAL_INP_FREQ_REQ            (aoM_if2  | 0x36)
#define  S_IF2_MIXER8_ILLEGAL_INP_FREQ_REQ            (aoM_if2  | 0x37)
#define  S_IF2_ILLEGAL_SYNTH5_POS_REQUESTED           (aoM_if2  | 0x38)
#define  S_IF2_ILLEGAL_SYNTH6_POS_REQUESTED           (aoM_if2  | 0x39)
#define  S_IF2_ILLEGAL_SYNTH7_POS_REQUESTED           (aoM_if2  | 0x3a)
#define  S_IF2_ILLEGAL_SYNTH8_POS_REQUESTED           (aoM_if2  | 0x3b)
#define  S_IF2_ILLEGAL_ILLEGAL_SIGNAL_SRC             (aoM_if2  | 0x3c)
#define  S_IF2_COULD_NOT_OPEN_SYNTH_DEVICE            (aoM_if2  | 0x3d)
#define  S_IF2_ILLEGAL_RDRBLANK_VALUE                 (aoM_if2  | 0x3e)
#define  S_IF2_ILLEGAL_KRONHITE_REQ                   (aoM_if2  | 0x3f)
#define  S_IF2_KRONHITE_REQ_GT_32_BYTES               (aoM_if2  | 0x40)
#define  S_IF2_KRONHITE_MALLOC_ERR                    (aoM_if2  | 0x41)
#define  S_IF2_KRONHITE_DEVICE_2A_NOTOPEN             (aoM_if2  | 0x42)
#define  S_IF2_KRONHITE_DEVICE_2B_NOTOPEN             (aoM_if2  | 0x43)
#define  S_IF2_KRONHITE_DEVICE_4A_NOTOPEN             (aoM_if2  | 0x44)
/*
 * hp83712 synthesizers
*/
#define  S_HP83712_ILLEGAL_DEVICE_NUM              	(aoM_hp83712|   1)
#define  S_HP83712_ILLEGAL_FREQ_REQ                	(aoM_hp83712|   2)
/*
 * hp8648 synthesizers
*/
#define  S_HP8648_ILLEGAL_DEVICE_NUM               	(aoM_hp8648|    1)
/*
 * tt560 irig board.
*/
#define  S_TT560_SELFTEST_RAM_FAILURE             		(aoM_tt560|     1)
#define  S_TT560_SELFTEST_PROCESSOR_CLK_FAILURE   		(aoM_tt560|     2)
#define  S_TT560_SELFTEST_GPSENG_COM_FAILURE      		(aoM_tt560|     3)
#define  S_TT560_SELFTEST_GPSENG_OPERATION_FAILURE      (aoM_tt560|     4)
#define  S_TT560_SELFTEST_DAC_SETTING_NEAR_LIMIT        (aoM_tt560|     5)
#define  S_TT560_REQTIME_TIMEOUT_REQTIME_SEM   		    (aoM_tt560|     6)
#define  S_TT560_REQTIME_ERROR_LOOPING_INTERRUPT_CNT    (aoM_tt560|     7)
#define  S_TT560_TIMEOUT_WAITING_FOR_1SEC_TICK          (aoM_tt560|     8)
#define  S_TT560_STATUS_INP_REF_ERR                     (aoM_tt560|     9)
#define  S_TT560_STATUS_INP_PHLOCK_ERR                  (aoM_tt560|   0xa)
#define  S_TT560_STATUS_INP_ILLEGAL_STATUS              (aoM_tt560|   0xb) 
#define  S_TT560_DRIVER_NOT_INITIALIZED                 (aoM_tt560|   0xc) 
/*
 * locMsgLib 
*/
#define  S_LMSG_TIMEOUT                           	(aoM_lmsg|      1)
#define  S_LMSG_INIT_MALLOC_ERR_STRUCT            	(aoM_lmsg|      2)
#define  S_LMSG_INIT_MALLOC_ERR_MSG_BUFS          	(aoM_lmsg|      3)
/*
 * micro controllers
*/
#define  S_MCTRL_WRITE_HDR_ERR                   	(aoM_mctrl|     1)
#define  S_MCTRL_WRITE_DATA_ERR                   	(aoM_mctrl|     2)
#define  S_MCTRL_READ_HDR_ERR                   	(aoM_mctrl|     3)
#define  S_MCTRL_READ_BAD_HDRID                 	(aoM_mctrl|     4)
#define  S_MCTRL_READ_DATA_ERR                   	(aoM_mctrl|     5) 
#define  S_MCTRL_INIT_BAD_NET_NUMBER              	(aoM_mctrl|     6) 
#define  S_MCTRL_INIT_MALLOC_ERR_ID               	(aoM_mctrl|     7) 
#define  S_MCTRL_SYNC_READ_HDR_ERR                	(aoM_mctrl|     8)
#define  S_MCTRL_WATCHDOG_TIMEOUT                 	(aoM_mctrl|     9)
#define  S_MCTRL_PROG_EXIT_REQ                    	(aoM_mctrl|   0xa)
#define  S_MCTRL_HDR_ADR_ILLEGAL                  	(aoM_mctrl|   0xb)
#define  S_MCTRL_ILLEGAL_SLV_NUM_RCVREQ           	(aoM_mctrl|   0xc) 
#define  S_MCTRL_ILLEGAL_SLV_NUM_SNDREQ           	(aoM_mctrl|   0xd)
#define  S_MCTRL_ILLEGAL_COM_STAT                 	(aoM_mctrl|   0xe)
#define  S_MCTRL_COM_STAT_M_SND_TMOUT               (aoM_mctrl|   0xf) 
#define  S_MCTRL_COM_STAT_M_BCRC_FROM_S             (aoM_mctrl|   0x10)
#define  S_MCTRL_COM_STAT_M_BSTAT_SEND              (aoM_mctrl|   0x11)
#define  S_MCTRL_COM_STAT_M_BCMD_FROM_VME           (aoM_mctrl|   0x12)
#define  S_MCTRL_COM_STAT_S_BCMD_FROM_M             (aoM_mctrl|   0x13)
#define  S_MCTRL_COM_STAT_S_BCRC_FROM_M             (aoM_mctrl|   0x14)
#define  S_MCTRL_COM_STAT_S_BDATA_FROM_M            (aoM_mctrl|   0x15)
#define  S_MCTRL_HDRID_MISMATCH_SND_RCV             (aoM_mctrl|   0x16)
#define  S_MCTRL_ILLEGAL_DATALEN_READ_HDR           (aoM_mctrl|   0x17)
#define  S_MCTRL_ILLEGAL_DATALEN_WRITE              (aoM_mctrl|   0x18)
#define  S_MCTRL_COM_STAT_S_BUF_OVERFLOW            (aoM_mctrl|   0x19)
#define  S_MCTRL_COM_STAT_S_PARAM_NOT_SAVED         (aoM_mctrl|   0x1a)
#define  S_MCTRL_COM_STAT_S_INDEX_OUT_OF_RNG        (aoM_mctrl|   0x1b)
/*
 * Turrent/tertiary program..
*/
/*
 * low level generic programs tertiary,turret, agc 
*/
#define  S_LLGEN_BAD_TIMESTAMP_IN_INP_MSG        	(aoM_llgen |     1)
#define  S_LLGEN_FLUSH_REQ_WHILE_FLUSHING       	(aoM_llgen |     2)
/*
 * low level agc pointing routines.
*/
#define  S_AGC_GETMSG_BAD_HDRID_IN_MSG            		(aoM_agc   |     1)
#define  S_AGC_GETMSG_BAD_MSGLEN             	        (aoM_agc   |     2)
#define  S_AGC_GETMSG_BAD_MSGTYPE             	        (aoM_agc   |     3)
#define  S_AGC_GETMSG_SEQ_NUMBER_MISMATCH      	        (aoM_agc   |     4)
#define  S_AGC_ILLEGAL_AXIS_REQ               	        (aoM_agc   |     5)
#define  S_AGC_ILLEGAL_TRANSFER_CONTROL_ADR   	        (aoM_agc   |     6)
#define  S_AGC_ILLEGAL_MILLISECS_FROM_MIDNITE 	        (aoM_agc   |     7)
#define  S_AGC_POS_REQ_OUTSIDE_SOFTWARE_LIM_AZ          (aoM_agc   |     8)
#define  S_AGC_POS_REQ_OUTSIDE_SOFTWARE_LIM_GR          (aoM_agc   |     9)
#define  S_AGC_POS_REQ_OUTSIDE_SOFTWARE_LIM_CH          (aoM_agc   |  0x0a)
#define  S_AGC_MODE_SEL_BAD_MODE                        (aoM_agc   |  0x0b)
#define  S_AGC_VEL_REQ_OUTSIDE_SOFTWARE_LIM_AZ          (aoM_agc   |  0x0c)
#define  S_AGC_VEL_REQ_OUTSIDE_SOFTWARE_LIM_GR          (aoM_agc   |  0x0d)
#define  S_AGC_VEL_REQ_OUTSIDE_SOFTWARE_LIM_CH          (aoM_agc   |  0x0e)
#define  S_AGC_AUX_REQ_BAD_MOTOR_REQ                    (aoM_agc   |  0x0f)
#define  S_AGC_BAD_MONREQ_CODE                          (aoM_agc   |  0x10)
#define  S_AGC_BAD_HDRID_IN_MSG            	            (aoM_agc   |  0x11)
#define  S_AGC_BAD_MSGTYPE_IN_MSG            	        (aoM_agc   |  0x12)
#define  S_AGC_BAD_GCMD_CMDREQ_IN_MSG        	        (aoM_agc   |  0x13)
#define  S_AGC_BAD_MSGLEN_FOR_PROG_TRACK_MSG 	        (aoM_agc   |  0x14)
#define  S_AGC_BAD_MODE_IN_MODE_SEL_MSG        	        (aoM_agc   |  0x15)
#define  S_AGC_MSG_TOO_LONG_FOR_LOCAL_MSGQ    	        (aoM_agc   |  0x16)
#define  S_AGC_MON_REQ_MSG_NEEDS_A_REPLY      	        (aoM_agc   |  0x17)
#define  S_AGC_QPTLOC_PUT_TO_FULL_Q           	        (aoM_agc   |  0x18)
#define  S_AGC_PT_TIME_HAS_PASSED             	        (aoM_agc   |  0x19)
#define  S_AGC_PT_LOC_Q_EMPTY             	            (aoM_agc   |  0x1a)
#define  S_AGC_PT_LOC_Q_FULL              	            (aoM_agc   |  0x1b)
#define  S_AGC_READ_FROM_VTX_TIMEOUT      	            (aoM_agc   |  0x1c)
#define  S_AGC_LISTEN_REQ_DURING_READ     	            (aoM_agc   |  0x1d)
#define  S_AGC_SEL_ONREAD_BUT_ZEROBYTES_AVAIL           (aoM_agc   |  0x1e)
#define  S_AGC_ILLEGAL_MASTER_MODE_REQ                  (aoM_agc   |  0x1f)
/*
 *  faults/warnings from agc status's
*/
#define  S_AGC_GENSTAT_EMERGENCY_OFF                    (aoM_agc   |  0x20)
#define  S_AGC_GENSTAT_COLLISTION_SW_ENC                (aoM_agc   |  0x21)
#define  S_AGC_GENSTAT_LIMIT_OVERRIDE_ACTIVE            (aoM_agc   |  0x22)
#define  S_AGC_GENSTAT_PCU_COMMUNICATIONS_FAULT         (aoM_agc   |  0x23)
#define  S_AGC_GENSTAT_CP581_COMMUNICATIONS_FAULT       (aoM_agc   |  0x24)
#define  S_AGC_GENSTAT_PLC_FAULT                        (aoM_agc   |  0x25)
#define  S_AGC_GENSTAT_EVENT_FLAG                       (aoM_agc   |  0x26)
#define  S_AGC_GENSTAT_SPARE                            (aoM_agc   |  0x27)
#define  S_AGC_GENSTAT_DRIVE_CABINET_1_OVERTEMP         (aoM_agc   |  0x28)
#define  S_AGC_GENSTAT_DRIVE_CABINET_2_OVERTEMP         (aoM_agc   |  0x29)
#define  S_AGC_GENSTAT_DRIVE_CABINET_3_OVERTEMP         (aoM_agc   |  0x2a)
#define  S_AGC_GENSTAT_24V_POWER_SUPPLY_FAULT           (aoM_agc   |  0x2b) 
#define  S_AGC_GENSTAT_BRAKE_POWER_SUPPLY_FAULT         (aoM_agc   |  0x2c)
#define  S_AGC_GENSTAT_PLC_POWER_SUPPLY_FAULT           (aoM_agc   |  0x2d)
#define  S_AGC_GENSTAT_DRIVE_POWER_OFF                  (aoM_agc   |  0x2e)
#define  S_AGC_GENSTAT_CABINET_DOORS_OPEN               (aoM_agc   |  0x2f)
/**/
#define  S_AGC_AZSTAT_SERVO_FAILURE                     (aoM_agc   |  0x30)
#define  S_AGC_AZSTAT_ENCODER1_FAULT                    (aoM_agc   |  0x31)
#define  S_AGC_AZSTAT_ENCODER2_FAULT                    (aoM_agc   |  0x32)
#define  S_AGC_AZSTAT_DRIVE_ENABLE                      (aoM_agc   |  0x33)
#define  S_AGC_AZSTAT_RUNAWAY                           (aoM_agc   |  0x34)
#define  S_AGC_AZSTAT_MOTOR_OVERTEMP                    (aoM_agc   |  0x35)
#define  S_AGC_AZSTAT_ENCODER_FAILURE                   (aoM_agc   |  0x36)
#define  S_AGC_AZSTAT_BRAKE_FAILURE                     (aoM_agc   |  0x37)
#define  S_AGC_AZSTAT_NEGATIVE_LIMIT                    (aoM_agc   |  0x38)
#define  S_AGC_AZSTAT_NEGATIVE_PRE_LIMIT                (aoM_agc   |  0x39)
#define  S_AGC_AZSTAT_OPERATING_RANGE                   (aoM_agc   |  0x3a)
#define  S_AGC_AZSTAT_POSITIVE_PRE_LIMIT                (aoM_agc   |  0x3b) 
#define  S_AGC_AZSTAT_POSITIVE_LIMIT                    (aoM_agc   |  0x3c)
#define  S_AGC_AZSTAT_EMERGENCY_LIMIT                   (aoM_agc   |  0x3d)
#define  S_AGC_AZSTAT_CABLE_CAR_INTERLOCK               (aoM_agc   |  0x3e)
#define  S_AGC_AZSTAT_BRAKE_RELEASED                    (aoM_agc   |  0x3f)
/**/
#define  S_AGC_GRSTAT_SERVO_FAILURE                     (aoM_agc   |  0x40)
#define  S_AGC_GRSTAT_B1                                (aoM_agc   |  0x41)
#define  S_AGC_GRSTAT_B2                                (aoM_agc   |  0x42)
#define  S_AGC_GRSTAT_DRIVE_ENABLE                      (aoM_agc   |  0x43)
#define  S_AGC_GRSTAT_RUNAWAY                           (aoM_agc   |  0x44)
#define  S_AGC_GRSTAT_MOTOR_OVERTEMP                    (aoM_agc   |  0x45)
#define  S_AGC_GRSTAT_ENCODER_FAILURE                   (aoM_agc   |  0x46)
#define  S_AGC_GRSTAT_BRAKE_FAILURE                     (aoM_agc   |  0x47)
#define  S_AGC_GRSTAT_NEGATIVE_LIMIT                    (aoM_agc   |  0x48)
#define  S_AGC_GRSTAT_NEGATIVE_PRE_LIMIT                (aoM_agc   |  0x49)
#define  S_AGC_GRSTAT_OPERATING_RANGE                   (aoM_agc   |  0x4a)
#define  S_AGC_GRSTAT_POSITIVE_PRE_LIMIT                (aoM_agc   |  0x4b) 
#define  S_AGC_GRSTAT_POSITIVE_LIMIT                    (aoM_agc   |  0x4c)
#define  S_AGC_GRSTAT_EMERGENCY_LIMIT                   (aoM_agc   |  0x4d)
#define  S_AGC_GRSTAT_CABLE_CAR_INTERLOCK               (aoM_agc   |  0x4e)
#define  S_AGC_GRSTAT_BRAKE_RELEASED                    (aoM_agc   |  0x4f)
/**/
#define  S_AGC_CHSTAT_SERVO_FAILURE                     (aoM_agc   |  0x50)
#define  S_AGC_CHSTAT_B1                                (aoM_agc   |  0x51)
#define  S_AGC_CHSTAT_B2                                (aoM_agc   |  0x52)
#define  S_AGC_CHSTAT_DRIVE_ENABLE                      (aoM_agc   |  0x53)
#define  S_AGC_CHSTAT_RUNAWAY                           (aoM_agc   |  0x54)
#define  S_AGC_CHSTAT_MOTOR_OVERTEMP                    (aoM_agc   |  0x55)
#define  S_AGC_CHSTAT_ENCODER_FAILURE                   (aoM_agc   |  0x56)
#define  S_AGC_CHSTAT_BRAKE_FAILURE                     (aoM_agc   |  0x57)
#define  S_AGC_CHSTAT_NEGATIVE_LIMIT                    (aoM_agc   |  0x58)
#define  S_AGC_CHSTAT_NEGATIVE_PRE_LIMIT                (aoM_agc   |  0x59)
#define  S_AGC_CHSTAT_OPERATING_RANGE                   (aoM_agc   |  0x5a)
#define  S_AGC_CHSTAT_POSITIVE_PRE_LIMIT                (aoM_agc   |  0x5b) 
#define  S_AGC_CHSTAT_POSITIVE_LIMIT                    (aoM_agc   |  0x5c)
#define  S_AGC_CHSTAT_EMERGENCY_LIMIT                   (aoM_agc   |  0x5d)
#define  S_AGC_CHSTAT_CABLE_CAR_INTERLOCK               (aoM_agc   |  0x5e)
#define  S_AGC_CHSTAT_BRAKE_RELEASED                    (aoM_agc   |  0x5f)

#define  S_AGC_AZAMP11_FAULT                            (aoM_agc   |  0x60)
#define  S_AGC_AZAMP11_OVERTEMP                         (aoM_agc   |  0x61)
#define  S_AGC_AZAMP12_FAULT                            (aoM_agc   |  0x62)
#define  S_AGC_AZAMP12_OVERTEMP                         (aoM_agc   |  0x63)
#define  S_AGC_AZAMP51_FAULT                            (aoM_agc   |  0x64)
#define  S_AGC_AZAMP51_OVERTEMP                         (aoM_agc   |  0x65)
#define  S_AGC_AZAMP52_FAULT                            (aoM_agc   |  0x66)
#define  S_AGC_AZAMP52_OVERTEMP                         (aoM_agc   |  0x67)
#define  S_AGC_AZAMP41_FAULT                            (aoM_agc   |  0x68)
#define  S_AGC_AZAMP41_OVERTEMP                         (aoM_agc   |  0x69)
#define  S_AGC_AZAMP42_FAULT                            (aoM_agc   |  0x6a)
#define  S_AGC_AZAMP42_OVERTEMP                         (aoM_agc   |  0x6b)
#define  S_AGC_AZAMP81_FAULT                            (aoM_agc   |  0x6c)
#define  S_AGC_AZAMP81_OVERTEMP                         (aoM_agc   |  0x6d)
#define  S_AGC_AZAMP82_FAULT                            (aoM_agc   |  0x6e)
#define  S_AGC_AZAMP82_OVERTEMP                         (aoM_agc   |  0x6f)
/**/
#define  S_AGC_GRAMP11_FAULT                            (aoM_agc   |  0x70)
#define  S_AGC_GRAMP11_OVERTEMP                         (aoM_agc   |  0x71)
#define  S_AGC_GRAMP12_FAULT                            (aoM_agc   |  0x72)
#define  S_AGC_GRAMP12_OVERTEMP                         (aoM_agc   |  0x73)
#define  S_AGC_GRAMP21_FAULT                            (aoM_agc   |  0x74)
#define  S_AGC_GRAMP21_OVERTEMP                         (aoM_agc   |  0x75)
#define  S_AGC_GRAMP22_FAULT                            (aoM_agc   |  0x76)
#define  S_AGC_GRAMP22_OVERTEMP                         (aoM_agc   |  0x77)
#define  S_AGC_GRAMP31_FAULT                            (aoM_agc   |  0x78)
#define  S_AGC_GRAMP31_OVERTEMP                         (aoM_agc   |  0x79)
#define  S_AGC_GRAMP32_FAULT                            (aoM_agc   |  0x7a)
#define  S_AGC_GRAMP32_OVERTEMP                         (aoM_agc   |  0x7b)
#define  S_AGC_GRAMP41_FAULT                            (aoM_agc   |  0x7c)
#define  S_AGC_GRAMP41_OVERTEMP                         (aoM_agc   |  0x7d)
#define  S_AGC_GRAMP42_FAULT                            (aoM_agc   |  0x7e)
#define  S_AGC_GRAMP42_OVERTEMP                         (aoM_agc   |  0x7f)
/**/
#define  S_AGC_CHAMP1_FAULT                             (aoM_agc   |  0x80)
#define  S_AGC_CHAMP1_OVERTEMP                          (aoM_agc   |  0x81)
#define  S_AGC_CHAMP2_FAULT                             (aoM_agc   |  0x82)
#define  S_AGC_CHAMP2_OVERTEMP                          (aoM_agc   |  0x83)
/**/
#define  S_AGC_AZMOT11_OVERTEMP                         (aoM_agc   |  0x90)
#define  S_AGC_AZMOT12_OVERTEMP                         (aoM_agc   |  0x91)
#define  S_AGC_AZMOT51_OVERTEMP                         (aoM_agc   |  0x92)
#define  S_AGC_AZMOT52_OVERTEMP                         (aoM_agc   |  0x93)
#define  S_AGC_AZMOT41_OVERTEMP                         (aoM_agc   |  0x94)
#define  S_AGC_AZMOT42_OVERTEMP                         (aoM_agc   |  0x95)
#define  S_AGC_AZMOT81_OVERTEMP                         (aoM_agc   |  0x96)
#define  S_AGC_AZMOT82_OVERTEMP                         (aoM_agc   |  0x97)
/**/
#define  S_AGC_GRMOT11_OVERTEMP                         (aoM_agc   |  0x98)
#define  S_AGC_GRMOT12_OVERTEMP                         (aoM_agc   |  0x99) 
#define  S_AGC_GRMOT21_OVERTEMP                         (aoM_agc   |  0x9a)
#define  S_AGC_GRMOT22_OVERTEMP                         (aoM_agc   |  0x9b)
#define  S_AGC_GRMOT31_OVERTEMP                         (aoM_agc   |  0x9c)
#define  S_AGC_GRMOT32_OVERTEMP                         (aoM_agc   |  0x9d)
#define  S_AGC_GRMOT41_OVERTEMP                         (aoM_agc   |  0x9e)
#define  S_AGC_GRMOT42_OVERTEMP                         (aoM_agc   |  0x9f)
/**/
#define  S_AGC_CHMOT1_OVERTEMP                          (aoM_agc   |  0xa0)
#define  S_AGC_CHMOT2_OVERTEMP                          (aoM_agc   |  0xa1)
/**/
#define  S_AGC_AZEQP_PWRSUPPLY1_FAULT                   (aoM_agc   |  0xa8)
#define  S_AGC_AZEQP_PWRSUPPLY2_FAULT                   (aoM_agc   |  0xa9)
#define  S_AGC_AZEQP_MAIN_CONTACTOR1_ON                 (aoM_agc   |  0xaa)
#define  S_AGC_AZEQP_MAIN_CONTACTOR2_ON                 (aoM_agc   |  0xab)
#define  S_AGC_AZEQP_DC_BUS1_FAULT                      (aoM_agc   |  0xac)
#define  S_AGC_AZEQP_DC_BUS2_FAULT                      (aoM_agc   |  0xad)
#define  S_AGC_AZEQP_BRAKES_GROUP1_FAULT                (aoM_agc   |  0xae)
#define  S_AGC_AZEQP_BRAKES_GROUP2_FAULT                (aoM_agc   |  0xaf)
/**/
#define  S_AGC_GREQP_PWRSUPPLY1_FAULT                   (aoM_agc   |  0xb0)
#define  S_AGC_GREQP_PWRSUPPLY2_FAULT                   (aoM_agc   |  0xb1)
#define  S_AGC_GREQP_MAIN_CONTACTOR1_ON                 (aoM_agc   |  0xb2)
#define  S_AGC_GREQP_MAIN_CONTACTOR2_ON                 (aoM_agc   |  0xb3)
#define  S_AGC_GREQP_DC_BUS1_FAULT                      (aoM_agc   |  0xb4)
#define  S_AGC_GREQP_DC_BUS2_FAULT                      (aoM_agc   |  0xb5)
#define  S_AGC_GREQP_BRAKES_GROUP1_FAULT                (aoM_agc   |  0xb6)
#define  S_AGC_GREQP_BRAKES_GROUP2_FAULT                (aoM_agc   |  0xb7)
/**/
#define  S_AGC_CHEQP_PWRSUPPLY1_FAULT                   (aoM_agc   |  0xb8)
#define  S_AGC_CHEQP_PWRSUPPLY2_FAULT                   (aoM_agc   |  0xb9)
#define  S_AGC_CHEQP_MAIN_CONTACTOR1_ON                 (aoM_agc   |  0xba)
#define  S_AGC_CHEQP_MAIN_CONTACTOR2_ON                 (aoM_agc   |  0xbb)
#define  S_AGC_CHEQP_DC_BUS1_FAULT                      (aoM_agc   |  0xbc)
#define  S_AGC_CHEQP_DC_BUS2_FAULT                      (aoM_agc   |  0xbd)
#define  S_AGC_CHEQP_BRAKES_GROUP1_FAULT                (aoM_agc   |  0xbe)
#define  S_AGC_CHEQP_BRAKES_GROUP2_FAULT                (aoM_agc   |  0xbf)
/**/
#define  S_AGC_SEL_BUT_NO_FD_WITHDATA                   (aoM_agc   |  0xc0)
#define  S_AGC_MONREQ_MALLOC_ERR                        (aoM_agc   |  0xc1)
#define  S_AGC_MONREQ_DATA_WAS_CHANGING                 (aoM_agc   |  0xc2)
#define  S_AGC_ILLEGAL_RESET_DESTINATION                (aoM_agc   |  0xc3)
#define  S_AGC_CMDRSP_INVALID_CMD_RCVD_VTX_STAT4        (aoM_agc   |  0xc4)
#define  S_AGC_CMDRSP_CMD_NOT_VALID_CUR_MODE_VTX_STAT5  (aoM_agc   |  0xc5)
#define  S_AGC_CMDRSP_CMD_PARM_OUT_OF_RANGE_VTX_STAT6   (aoM_agc   |  0xc6)
#define  S_AGC_CMDRSP_CMD_RSP_STAT_INCORRECT_VALUE      (aoM_agc   |  0xc7)
#define  S_AGC_PNTXF_STATE_REQ_WRONG_SEC                (aoM_agc   |  0xc8)
#define  S_AGC_PNTXF_STATE_NULL_ADR                     (aoM_agc   |  0xc9)
#define  S_AGC_PNTXF_STATE_0LEN_REQ                     (aoM_agc   |  0xca)
#define  S_AGC_LCU_IRIG_CLK_ERR                         (aoM_agc   |  0xcb)
/**/
#define  S_AGC_PREPROC_BAD_AXIS_REQUEST                 (aoM_agc   |  0xcc)
#define  S_AGC_PREPROC_TIME_INCREMENT_BAD               (aoM_agc   |  0xcd)

#define  S_AGC_ILLEGAL_POSLOGGER_REQ                    (aoM_agc   |  0xce)
#define  S_AGC_ILLEGAL_FASTCBLK_REQ                     (aoM_agc   |  0xcf)
#define  S_AGC_MALLOC_ERR_RETURNBUF_GEN_QUERY           (aoM_agc   |  0xd0)
/*
 * irig server
*/
#define  S_IRIGSV_CLIENT_MSG_SENT_BAD_BYTECOUNT        	(aoM_irigSv|     1)
#define  S_IRIGSV_CLIENT_MSG_RCV_BAD_BYTECOUNT          (aoM_irigSv|     2)
#define  S_IRIGSV_CLIENT_LOOPED_MAX_TRIES               (aoM_irigSv|     3)
#define  S_IRIGSV_CLIENT_TIMEOUT_RCV                    (aoM_irigSv|     4)
#define  S_IRIGSV_CLIENT_FD_NOT_SET_AFTER_SELECT        (aoM_irigSv|     5)
#define  S_IRIGSV_CLIENT_TIME_MISMATCH                  (aoM_irigSv|     6)
/*
 * q routines agc
*/
#define  S_QPH_PUT_TO_FULL_Q                            (aoM_qph   |     1)
#define  S_QPH_Q_EMPTY                                  (aoM_qph   |     2)
#define  S_QPH_MALLOC_ERR_INIT                          (aoM_qph   |     3)
#define  S_QPH_BAD_MAXELMTS_INIT                        (aoM_qph   |     4)
#define  S_QPH_BAD_ELMTLEN_INIT                         (aoM_qph   |     5)
#define  S_QPH_QPUT_NO_FREE_POS                         (aoM_qph   |     6)
/*
 * vtxProgram
*/
#define  S_VTXP_INPMSG_TOO_LONG                         (aoM_vtxP  |     1)
/*
 * if1Prog
*/
#define  S_IF1P_BAD_SW_NUM                              (aoM_if1P  |     1)
#define  S_IF1P_87130_SW_VERIFY_ERR                     (aoM_if1P  |   0x2)
#define  S_IF1P_87130_CLOSE_SW_ERR                      (aoM_if1P  |   0x3)
#define  S_IF1P_87130_OPEN_SW_ERR                       (aoM_if1P  |   0x4)
#define  S_IF1P_87130_SET_VERIFY_ERR                    (aoM_if1P  |   0x5)
#define  S_IF1P_87130_SET_WIDTH_ERR                     (aoM_if1P  |   0x6)
#define  S_IF1P_87130_SET_DRIVE_ERR                     (aoM_if1P  |   0x7)
#define  S_IF1P_ILLEGAL_RF_NUM_REQ                      (aoM_if1P  |   0x8)
#define  S_IF1P_ILLEGAL_MIXER_NUM_REQ                   (aoM_if1P  |   0x9)
#define  S_IF1P_ILLEGAL_RF_ATTN_A_REQ                   (aoM_if1P  |   0xa)
#define  S_IF1P_ILLEGAL_RF_ATTN_B_REQ                   (aoM_if1P  |   0xb)
#define  S_IF1P_ILLEGAL_IF_ATTN_A_REQ                   (aoM_if1P  |   0xc)
#define  S_IF1P_ILLEGAL_IF_ATTN_B_REQ                   (aoM_if1P  |   0xd)
#define  S_IF1P_ILLEGAL_CABLE_A_REQ                     (aoM_if1P  |   0xe)
#define  S_IF1P_ILLEGAL_CABLE_B_REQ                     (aoM_if1P  |   0xf)
#define  S_IF1P_87130_SW_ERROR                          (aoM_if1P  |  0x10)
#define  S_IF1P_3488RDBACK_NEEDS_REPLY_ADR	            (aoM_if1P  |  0x11)
#define  S_IF1P_87130ERRS_NEEDS_REPLY_ADR	            (aoM_if1P  |  0x12)
#define  S_IF1P_WAIT_NEEDS_REPLY_ADR	                (aoM_if1P  |  0x13)
#define  S_IF1P_MEASURE_PWR_ILLEGAL_REQ                 (aoM_if1P  |  0x14)
#define  S_IF1P_MEASURE_PWR_ILLEGAL_LOCATION            (aoM_if1P  |  0x15)
#define  S_IF1P_MEASURE_PWR_ILLEGAL_POL                 (aoM_if1P  |  0x16)
#define  S_IF1P_MEASURE_PWR_ILLEGAL_NUMBER_READS_REQ    (aoM_if1P  |  0x17)
#define  S_IF1P_MEASURE_PWR_MALLOC_ERR                  (aoM_if1P  |  0x18)
#define  S_IF1P_ILLEGAL_SYN_AMPLITUDE                   (aoM_if1P  |  0x19)
#define  S_IF1P_ILLEGAL_CAL_REQ                         (aoM_if1P  |  0x1a)
#define  S_IF1P_ILLEGAL_LBAND_FILTER_NUM_REQUESTED      (aoM_if1P  |  0x1b)
#define  S_IF1P_ILLEGAL_CAL_RCVR_REQUESTED              (aoM_if1P  |  0x1c)
#define  S_IF1P_ILLEGAL_RCVMON_ADR_REQUESTED            (aoM_if1P  |  0x1d)
#define  S_IF1P_ILLEGAL_RCVMON_DEWAR_REQUESTED          (aoM_if1P  |  0x1e)
#define  S_IF1P_ILLEGAL_AC1_PWRSWITCH_VALUE             (aoM_if1P  |  0x1f)
#define  S_IF1P_ILLEGAL_AC2_PWRSWITCH_VALUE             (aoM_if1P  |  0x20)
#define  S_IF1P_ILLEGAL_LBW_CIR_LINEAR_VALUE            (aoM_if1P  |  0x21)
#define  S_IF1P_METER_DISP_ILLEGAL_REQ                  (aoM_if1P  |  0x22)
#define  S_IF1P_METER_DISP_Q_NO_DATA_RETURNED           (aoM_if1P  |  0x23)
#define  S_IF1P_METER_DISP_Q_MALLOC_ERR                 (aoM_if1P  |  0x24)
#define  S_IF1P_LBNFB_ERR_RD_POSITION_VOLTAGE           (aoM_if1P  |  0x25)
#define  S_IF1P_LBNFB_ERR_CONVERT_POSITION_VOLTAGE      (aoM_if1P  |  0x26)
#define  S_IF1P_LBNFB_MALLOC_QUERY_BUF                  (aoM_if1P  |  0x27)
#define  S_IF1P_ILLEGAL_LBANDN_FILTER_NUM_REQUESTED     (aoM_if1P  |  0x28)
#define  S_IF1P_ILLEGAL_SBW_FILTER_NUM_REQUESTED        (aoM_if1P  |  0x29)
#define  S_IF1P_ILLEGAL_IF1_FREQ                        (aoM_if1P  |  0x2a)
#define  S_IF1P_ILLEGAL_430FILTER_REQ                   (aoM_if1P  |  0x2b)
#define  S_IF1P_ILLEGAL_ALFA_FB_REQ                     (aoM_if1P  |  0x2c)
#define  S_IF1P_ALFA_FB_3488_2_TROUBLE                  (aoM_if1P  |  0x2d)
#define  S_IF1P_ILLEGAL_CB_CIR_LINEAR_VALUE             (aoM_if1P  |  0x2e)
#define  S_IF1P_ILLEGAL_327FILTER_REQ                   (aoM_if1P  |  0x2f)
/*
 * corLProg
*/
#define  S_CORLPROC_ILLEGAL_DATAFORMAT_REQ              (aoM_corLProc|0x01)
#define  S_CORLPROC_MEASURE_PWR_MALLOC_ERR              (aoM_corLProc|0x02)
/*
 * penTeck a/d boards.
*/
#define  S_PENTEK_BUFSIZE_ILLEGAL_VALUE                (aoM_pt       |0x01)
#define  S_PENTEK_BUFFER_SWAP_OVERRUN                  (aoM_pt       |0x02)
/*
 *  ptProg for penteck boards
*/
#define  S_PTPROG_TOTSMP_IN_BUF_NOT_MULT_OF_16         (aoM_ptProg   |0x01)
#define  S_PTPROG_NO_PT_INP_SECTION_IN_HDR             (aoM_ptProg   |0x02)
#define  S_PTPROG_MUST_READ_MULTIPLE_OF_4_SHORTS       (aoM_ptProg   |0x03)
#define  S_PTPROG_PENTECK_BANK_SWAP_DID_NOT_OCCUR      (aoM_ptProg   |0x04)
#define  S_PTPROG_INTSTATUS_RUN_BIT_OFF                (aoM_ptProg   |0x05)
#define  S_PTPROG_BAD_BANK_TOP_CNT                     (aoM_ptProg   |0x06) 
#define  S_PTPROG_BAD_STATUS_AT_INTERRUPT              (aoM_ptProg   |0x07) 
/*
 *   multi meter
*/
#define  S_HP34401_ILLEGAL_DEVICE_NUM                  (aoM_hp34401  |0x01) 
#define  S_HP34401_INPUTDATA_FLOAT_CONVERT_ERR         (aoM_hp34401  |0x02)
#define  S_HP34401_INPUTDATA_99E37_OVERLOAD            (aoM_hp34401  |0x03)
/*
 *  tek scope
*/
#define  S_TK420_ILLEGAL_DEVICE_NUM                    (aoM_tk420    |0x01)
/*
 *  ipGen board of bills
*/
#define  S_ipGen_ILLEGAL_INT_REQUESTED                  (aoM_ipGen    |0x01)
/*
 *  8590 spectrum analyzer
*/
#define  S_hp8590_ILLEGAL_DB_PER_DIV                    (aoM_hp8590   |0x01)
/*
 *  scramnet memory
*/
#define  S_scrm_ILLEGAL_SCRMBLK_INDEX                   (aoM_scrm    |0x01)
#define  S_scrm_BLK_IS_BEING_MODIFIED                   (aoM_scrm    |0x02)
#define  S_scrm_BLKINFO_HAS_NOT_BEEN_INITIALIZED        (aoM_scrm    |0x03)
#define  S_scrm_ERR_OPENING_AOSCRM_NODEID_FILE          (aoM_scrm    |0x04)
#define  S_scrm_HOST_NOT_IN_AOSCRM_NODEID_FILE          (aoM_scrm    |0x05)
#define  S_scrm_INITIALIZATION_DIDNOT_COMPLETE          (aoM_scrm    |0x06)
#define  S_scrm_BRD_NOT_RESPONDING_A16                  (aoM_scrm    |0x07)
#define  S_scrm_BRD_NOT_RESPONDING_A32                  (aoM_scrm    |0x08)
#define  S_scrm_ILLEGAL_BOARD_NUM                       (aoM_scrm    |0x09)
#define  S_scrm_SP_SCRAM_INIT_FAILED                    (aoM_scrm    |0x0a)
#define  S_scrm_SP_TXRX_ID_FAILED                       (aoM_scrm    |0x0b)
#define  S_scrm_GBLKINFO_NOT_INITIALIZED                (aoM_scrm    |0x0c)
#define  S_scrm_BUFIND_IN_BLKHDR_BAD                    (aoM_scrm    |0x0d)
#define  S_scrm_BUFIND_BLKINFO_BAD                      (aoM_scrm    |0x0e)
#define  S_scrm_MODCNT_CHANGED_BLK_WAS_MODIFIED         (aoM_scrm    |0x0f)
#define  S_scrm_SCRM_BLKHDR_NOT_INITIALIZED             (aoM_scrm    |0x10)
#define  S_scrm_SCRMLOAD_BLKLEN_DIFFERS_FROM_WRITER     (aoM_scrm    |0x11)

/*
 *  bt4200 power meter
*/
#define  S_bt4200_STAT_ENTRY_TOO_SMALL                  (aoM_bt4200  |0x01)
#define  S_bt4200_STAT_ENTRY_TOO_BIG                    (aoM_bt4200  |0x02)
#define  S_bt4200_STAT_UNDER_RANGE                      (aoM_bt4200  |0x03)
#define  S_bt4200_STAT_OVER_RANGE                       (aoM_bt4200  |0x04)
#define  S_bt4200_STAT_BAD_STAT_RETURNED                (aoM_bt4200  |0x05)
#define  S_bt4200_READ_DBM_BAD_DATA_FORMAT_RETURNED     (aoM_bt4200  |0x06)
#define  S_bt4200_STAT_CHN_3_OVER_UNDER_RANGE           (aoM_bt4200  |0x07)
#define  S_bt4200_READ_PWR_BAD_DATA_FORMAT_RETURNED     (aoM_bt4200  |0x08)
/*
 *  ddsProgram
*/
#if FALSE 
#define  S_ddsPr_xxx                                    (aoM_ddsPr   |0x01)
#endif
/*
 *  ttProg or tieProg
*/
#define  S_TTT_BAD_PARAMETER_INDEX         			    (aoM_ttt     |0x01)
#define  S_TTT_GETPARAM_REQ_REPLY          	            (aoM_ttt     |0x02)
#define  S_TTT_GETTIME_REQ_REPLY          	            (aoM_ttt     |0x03)
#define  S_TTT_GETCLOCK_REQ_REPLY          	            (aoM_ttt     |0x04)
#define  S_TTT_BAD_MODE_REQUESTED          	            (aoM_ttt     |0x05)
#define  S_TTT_GETFREEPOS_REQ_REPLY        	            (aoM_ttt     |0x06)
#define  S_TTT_BAD_CMD_REQ                    	        (aoM_ttt     |0x07)
#define  S_TTT_BAD_TIMESTAMP_IN_INP_MSG        	        (aoM_ttt     |0x08)
#define  S_TTT_BAD_FEEDBACK_REQ                	        (aoM_ttt     |0x09)
#define  S_TTT_ILLEGAL_REQ_IN_MAINTENANCE_MODE 	        (aoM_ttt     |0x0a)
#define  S_TTT_TD_REQFDBACK_DOESNT_MATCH_POS_SLEW_REQ   (aoM_ttt     |0x0b)
#define  S_TTT_TT_MON_REQ_MSG_NEEDS_A_REPLY             (aoM_ttt     |0x0c)
#define  S_TTT_TT_BAD_MONREQ_CODE                       (aoM_ttt     |0x0d)
#define  S_TTT_TT_MONREQ_MALLOC_ERR                     (aoM_ttt     |0x0e)
#define  S_TTT_TT_MONREQ_DATA_WAS_CHANGING              (aoM_ttt     |0x0f)
#define  S_TTT_TIE_MON_REQ_MSG_NEEDS_A_REPLY            (aoM_ttt     |0x10)
#define  S_TTT_TIE_MONREQ_MALLOC_ERR                    (aoM_ttt     |0x11)
#define  S_TTT_TIE_MONREQ_DATA_WAS_CHANGING             (aoM_ttt     |0x12)
#define  S_TTT_TIE_REBOOT_BIT_IN_STATUS_HI              (aoM_ttt     |0x13)
#define  S_TTT_TIE_MON_POS_MSG_NEEDS_A_REPLY            (aoM_ttt     |0x14)
#define  S_TTT_TER_MON_REQ_MSG_NEEDS_A_REPLY            (aoM_ttt     |0x15)
#define  S_TTT_TER_MONREQ_MALLOC_ERR                    (aoM_ttt     |0x16)
#define  S_TTT_TER_MONREQ_DATA_WAS_CHANGING             (aoM_ttt     |0x17)
/*
 *  logDLib data logger 
*/
#define  S_LOGD_TOO_MUCH_MEMORY_REQUESTED  			    (aoM_logd    |0x01)
#define  S_LOGD_MALLOC_LOG_INFO_BLOCK      			    (aoM_logd    |0x02)
#define  S_LOGD_TOO_MANY_LOGGERS_ACTIVE    			    (aoM_logd    |0x03)
#define  S_LOGD_LOG_TASK_DIDNT_START       			    (aoM_logd    |0x04)
#define  S_LOGD_LOGID_BAD_INDEX       			        (aoM_logd    |0x05)
#define  S_LOGD_LOGID_USECNT_HAS_CHANGED         		(aoM_logd    |0x06)
#define  S_LOGD_MALLOC_RCVMSG_BUF                		(aoM_logd    |0x07)
#define  S_LOGD_LOGID_IS_NULL                    		(aoM_logd    |0x08)
/*
 *   power meter
*/
#define  S_HP442_ILLEGAL_DEVICE_NUM                     (aoM_hp442  |0x01) 
#define  S_HP442_ILLEGAL_FREQ_REQ                       (aoM_hp442  |0x02)
#define  S_HP442_PWR_VALUE_OUT_OF_RANGE                 (aoM_hp442  |0x03)
/*
* 	hp 437 power meter
*/
#define  S_HP437_ILLEGAL_DEVICE_NUM                     (aoM_hp437  |0x01)
#define  S_HP437_ILLEGAL_FREQ_REQ                       (aoM_hp437  |0x02)
#define  S_HP437_PWR_VALUE_OUT_OF_RANGE                 (aoM_hp437  |0x03)
/*
 *  ipFifo board
*/
#define  S_IPFIFO_ILLEGAL_INT_WORD_COUNT                (aoM_ipFifo |0x01)
/*
 *  modelLib routines
*/
#define  S_MODEL_NO_MODEL_FILE_OR_NAME                  (aoM_model  |0x01)
#define  S_MODEL_ERR_OPENING_MODEL_FILE                 (aoM_model  |0x02)
#define  S_MODEL_MODELNAME_NOT_IN_FILE                  (aoM_model  |0x03)
#define  S_MODEL_BAD_HDRLINE_FOR_MODELNAME              (aoM_model  |0x04)
#define  S_MODEL_BAD_NUM_COEF_IN_HDRLINE                (aoM_model  |0x05)
#define  S_MODEL_BAD_MODEL_DATA_IN_LINE                 (aoM_model  |0x06)
#define  S_MODEL_NOT_ENOUGH_MODEL_COEF                  (aoM_model  |0x07)
#define  S_MODEL_NO_ENCODER_FILE_SPECIFIED              (aoM_model  |0x08)
#define  S_MODEL_ERR_OPENING_ENCODER_FILE               (aoM_model  |0x09)
#define  S_MODEL_ENCNAME_NOT_IN_ENCFILE                 (aoM_model  |0x0a)
#define  S_MODEL_BAD_ENCODER_DATA_IN_LINE               (aoM_model  |0x0b)
#define  S_MODEL_NOT_ENOUGH_ENC_TABLE_ENTRIES           (aoM_model  |0x0c)
#define  S_MODEL_UNKNOWN_MODEL_FORMAT                   (aoM_model  |0x0d)
#define  S_MODEL_NO_ENCTBL_FOR_THIS_MODEL               (aoM_model  |0x0e)
/*
 *  radar doppler errors
*/
#define  S_RDRDOP_EPHM_OPENNING_FILE              (aoM_rdrdop |0x01)
#define  S_RDRDOP_EPHM_1ST_LINE_BAD               (aoM_rdrdop |0x02)
#define  S_RDRDOP_EPHM_2ND_LINE_BAD               (aoM_rdrdop |0x03)
#define  S_RDRDOP_EPHM_INPUT_DATE                 (aoM_rdrdop |0x04)
#define  S_RDRDOP_EPHM_CONVERTING_DATA            (aoM_rdrdop |0x05)
#define  S_RDRDOP_REQ_BEFORE_START_EPHMFILE       (aoM_rdrdop |0x06)
#define  S_RDRDOP_REQ_BEYOND_END_EPHMFILE         (aoM_rdrdop |0x07)
#define  S_RDRDOP_MALLOC_SAVE_BUF                 (aoM_rdrdop |0x08)
#define  S_RDRDOP_CMPPOLY_TOO_FEW_EPHM_ENTRIES    (aoM_rdrdop |0x09)
#define  S_RDRDOP_NEED_TO_DO_SETUP_FIRST          (aoM_rdrdop |0x0a)
#define  S_RDRDOP_NEED_TO_INPUT_EPHMFILE_FIRST    (aoM_rdrdop |0x0b) 
#define  S_RDRDOP_MALLOC_ERR_RETURN_BUF           (aoM_rdrdop |0x0c) 
#define  S_RDRDOP_ILLEGAL_BAUDLEN                 (aoM_rdrdop |0x0d)
#define  S_RDRDOP_ILLEGAL_CODELEN                 (aoM_rdrdop |0x0e)
#define  S_RDRDOP_RXONREQ_BEFORE_TX_DOWN_TIME     (aoM_rdrdop |0x0f)
#define  S_RDRDOP_RXONREQ_AFTER_ECHO_GONE         (aoM_rdrdop |0x10)
#define  S_RDRDOP_DOPIPP_UPDATE_TOO_SHORT         (aoM_rdrdop |0x11)
#define  S_RDRDOP_TXLOMULT_BAD                    (aoM_rdrdop |0x12)
#define  S_RDRDOP_TXRX_DOP_NEEDS_BOTH_STARTTIMES  (aoM_rdrdop |0x13)
/*
 *  initialize global  data errors 
*/
#define  S_INITDAT_DIR_BADLINE_IN_FILE            (aoM_initDat|0x01)
#define  S_INITDAT_DIR_NAME_WONT_FIT_IN_RETURN    (aoM_initDat|0x02)
#define  S_INITDAT_DIR_UNKNOWN_KEY_REQUESTED      (aoM_initDat|0x03)
#define  S_INITDAT_BADLINE_IN_FILE                (aoM_initDat|0x04)
#define  S_INITDAT_NAME_WONT_FIT_IN_RETURN        (aoM_initDat|0x05)
#define  S_INITDAT_UNKNOWN_KEY_REQUESTED          (aoM_initDat|0x06)
/*
 *  sbProg errors (program to communicate with sband console)
*/
#define  S_SBPROG_BYTES_WRITTEN_NOT_EQ_REQUESTED  (aoM_sbProg |0x01)
#define  S_SBPROG_BYTES_READ_NOT_EQ_REQUESTED     (aoM_sbProg |0x02)
#define  S_SBPROG_WR_WD_TIMEOUT                   (aoM_sbProg |0x03)
#define  S_SBPROG_RD_WD_TIMEOUT                   (aoM_sbProg |0x04)
#define  S_SBPROG_OPS_ER0_NOT_IN_ODACP_CONTROL    (aoM_sbProg |0x05)
#define  S_SBPROG_OPS_ER1_UNKNOWN_CMD             (aoM_sbProg |0x06)
#define  S_SBPROG_OPS_ER2_ARGS_OUT_OF_RANGE       (aoM_sbProg |0x07)
#define  S_SBPROG_OPS_UNKNOWN_REPLY_RETURNED      (aoM_sbProg |0x08)
#define  S_SBPROG_RD_CHKSUM_ERR_BINARY_DATA       (aoM_sbProg |0x09)
#define  S_SBPROG_RD_ILLEGAL_STAT_INDEX           (aoM_sbProg |0x0a)
#define  S_SBPROG_MALLOC_ERR_RETURN_BUF           (aoM_rdrdop |0x0b) 
#define  S_SBPROG_ILLEGAL_DRIVE_SETTING           (aoM_rdrdop |0x0c) 
#define  S_SBPROG_ILLEGAL_POWER_SETTING           (aoM_rdrdop |0x0d) 
#define  S_SBPROG_OPS_ER4_BUSY                    (aoM_sbProg |0x0e)
#define  S_SBPROG_RD_ILLEGAL_DUMP_INDEX           (aoM_sbProg |0x0f)
/*
 *  epvLib  ephmeris pos/vel errors
*/
#define  S_EPV_ERROR_OPENNING_EPHMERIS_FILE       (aoM_epv    |0x01)
#define  S_EPV_ERROR_READING_HEADER               (aoM_epv    |0x02)
#define  S_EPV_ERROR_HEADER_HAS_BAD_FORMAT        (aoM_epv    |0x03)
#define  S_EPV_REQUESTED_MJD_NOT_IN_EHPMFILE      (aoM_epv    |0x04)
#define  S_EPV_SEEK_POSITION_OUTSIDE_FILE         (aoM_epv    |0x05)
#define  S_EPV_READ_ERROR_MJD_REQUESTED           (aoM_epv    |0x06)
#define  S_EPV_MISMATCH_MJDREQ_MJDDAY             (aoM_epv    |0x07)
#define  S_EPV_REQUESTED_DAYFRACT_OUT_OF_RANGE    (aoM_epv    |0x08)
/*
 *  corProg, corLProg, corLProc
*/
#define  S_CORP_BAD_NUM_FREQ_BUFS                 (aoM_corProg|0x01)
#define  S_CORP_BAD_STEPS_IN_CYCLE                (aoM_corProg|0x02)
#define  S_CORP_BAD_CYLES_PER_INTEGRATION         (aoM_corProg|0x03)
#define  S_CORP_BAD_FREQ_REQ_IN_CYCLE             (aoM_corProg|0x04)
#define  S_CORP_BAD_CAL_REQ_IN_CYCLE              (aoM_corProg|0x05)
#define  S_CORP_FRQCYCLE_CALCYCLE_DIFFERENT_LEN   (aoM_corProg|0x06)
#define  S_CORP_BAD_CALCYCLE_LEN                  (aoM_corProg|0x07)
#define  S_CORP_BAD_FRQCYCLE_LEN                  (aoM_corProg|0x08)
#define  S_CORP_WAIT_DUMP_WRONG_DUMP_NUMBER       (aoM_corProg|0x09)
#define  S_CORP_INTEG_STATBIT_DIDNT_COME_ON       (aoM_corProg|0x0a)
#define  S_CORP_ADJPWR_MALLOC_ERR				  (aoM_corProg|0x0b)
#define  S_CORP_LATE_ON_TICK_START                (aoM_corProg|0x0c)
#define  S_CORP_ILLEGAL_BAUDLEN                   (aoM_corProg|0x0d)
#define  S_CORP_ILLEGAL_CODELEN                   (aoM_corProg|0x0e)
#define  S_CORP_ILLEGAL_CODEDELAY                 (aoM_corProg|0x0f)
#define  S_CORP_ILLEGAL_SMPPERBAUD                (aoM_corProg|0x1a)
#define  S_CORP_SMPPERBAUD_SHIFTLEN_INCOMPATIBLE  (aoM_corProg|0x1b)
#define  S_CORP_DCD_PACKING_ILLEGAL               (aoM_corProg|0x1c)
#define  S_CORP_DCD_PACKING_SHIFT_ILLEGAL         (aoM_corProg|0x1d)
#define  S_CORP_PACKING_PACKING_SHIFT_INCOMPATIBLE (aoM_corProg|0x1e)
#define  S_CORP_LAGSPERBOARD_NOTDIVISIBLE_BY_PACKING (aoM_corProg|0x1f)
#define  S_CORP_ILLEGAL_COHADD                    (aoM_corProg|0x20)
#define  S_CORP_COMPUTED_DUMPLEN_TOO_LONG         (aoM_corProg|0x21)
#define  S_CORP_COMPUTED_DUMPLEN_TOO_SHORT        (aoM_corProg|0x22)
#define  S_CORP_PACKED_MODE_NEEDS_DCD_AND_9xCODE  (aoM_corProg|0x23)
#define  S_CORP_PACKED_MODE_MUST_BE_SAME_ALL_BRDS (aoM_corProg|0x24)
/*
 *  ipCal board
*/
#define  S_IPCAL_BAD_TRIG_DELAY_REQ               (aoM_ipCal  |0x01)
/*
 *  errRepLib .. error reporting library
*/
#define  S_ERRREP_SND_TO_SYSLOG_BYTECOUNT_ERR     (aoM_errLib |0x01)
/*
 * ipPc power counter
*/
#define S_ipPc_ILLEGAL_IPSLOT       		      (aoM_ipPc   |  1) 
#define S_ipPc_ILLEGAL_INTEGRATION_LEN            (aoM_ipPc   |  2) 
/*
 * rcvMProg receiver monitor program.
*/
#define S_rcvM_BAD_DEWAR_NUMBER                   (aoM_rcvM   |  1) 
#define S_rcvM_G_BAD_ARGS_REQ                     (aoM_rcvM   |  2) 
#define S_rcvM_BAD_MUX_ADR                        (aoM_rcvM   |  3) 
#define S_rcvM_VOLTAGE_READBACK_OUT_OF_RANGE      (aoM_rcvM   |  4) 
#define S_rcvM_MALLOC_REPLY_DATA                  (aoM_rcvM   |  5) 
/*
 * lrMon laser ranging
*/
#define S_LRMON_TEMP_NEEDS_REPLY_ADR   	          (aoM_lrmon  |  1)
#define S_LRMON_TEMP_STATBIT_0                    (aoM_lrmon  |  2)
#define S_LRMON_CANNOT_GET_MXSEM                  (aoM_lrmon  |  3)
/*
 * tertiary 
*/
#define S_TER_RDSTATWDS_LOOPMAX                  (aoM_ter   |   1)
#define S_TER_RDSTATWDS_PE                       (aoM_ter   |   2)
#define S_TER_IPDAC_ERR_INP_CALDATA              (aoM_ter   |   3)
#define S_TER_RDENC_PE                           (aoM_ter   |   4)
#define S_TER_RDENC_MIND_ERR                     (aoM_ter   |   5)
#define S_TER_RDENC_ZIND_ERR                     (aoM_ter   |   6)
#define S_TER_ILLEGAL_AXIS_REQ                   (aoM_ter   |   7)
#define S_TER_VTOF_INTEG_LD_RDBACK_MISMATCH      (aoM_ter   |   8)
#define S_TER_ILLEGAL_COORD_SYSTEM_REQ           (aoM_ter   |   9)
#define S_TER_ILLEGAL_MODE_REQUEST               (aoM_ter   | 0xa)
#define S_TER_BAD_TMSTAMP_IN_PRGTRK_REQ          (aoM_ter   | 0xb)
#define S_TER_BAD_INDEX_REQ                      (aoM_ter   | 0xc)
#define S_TER_MALLOC_ERR_RETURNBUF_GEN_QUERY     (aoM_ter   | 0xd)
#define S_TER_DRIVE_WENT_OFFLINE                 (aoM_ter   | 0xe)
#define S_TER_DRIVE_ENABLE_GLITCH                (aoM_ter   | 0xf)

/*
 * general i/o program
*/
#define S_GIO_NO_REMOTE_PROG                     (aoM_gio   |   1)
#define S_GIO_SETUPQ_MALLOC_ERROR                (aoM_gio   |   2)
#define S_GIO_TIMEOUT_MSG_SEND_TO_REMOTE         (aoM_gio   |   3)
/*
 * general i/o remote program
*/ 
#define S_GIOR_DEVICE_NOT_OPEN                   (aoM_gior   |   1) 
#define S_GIOR_ILLEGAL_SOCKET_FD                 (aoM_gior   |   2) 
#define S_GIOR_BUFLEN_REG_GT_LOCBUF              (aoM_gior   |   3)
#define S_GIOR_NO_HDRKEYWORD_IN_OUTUBF           (aoM_gior   |   4)

/*
 * general i/o remote program
*/
#define S_HP34970_ILLEGAL_CARD_OR_ADR           (aoM_hp34970   |   1) 
#define S_HP34970_INPUTDATA_FLOAT_CONVERT_ERR   (aoM_hp34970   |0x02)
#define S_HP34970_INPUTDATA_99E37_OVERLOAD      (aoM_hp34970   |0x03)
#define S_HP34970_ILLEGAL_DEVICE_NUM            (aoM_hp34970   |0x04)
/*
 * gpib enet device
*/
#define S_GPIBENET_ERR_OPENING_CONFIG_FILE      (aoM_gpibEnet  |   1) 
#define S_GPIBENET_BAD_GPIBADR_CONFIG_FILE      (aoM_gpibEnet  |   2) 
#define S_GPIBENET_DEVICE_NOT_IN_CONFIG_FILE    (aoM_gpibEnet  |   3) 
#define S_GPIBENET_EPS_ERR_SEE_IBERR            (aoM_gpibEnet  |   4) 
#define S_GPIBENET_GPIB_DESCRIPTOR_OUT_OF_RANGE (aoM_gpibEnet  |   5) 
#define S_GPIBENET_GPIB_DESCRIPTOR_NOT_IN_USE   (aoM_gpibEnet  |   6) 
/*
 * alfa motor errors
*/
#define S_ALFAM_BAD_FD                          (aoM_ALFAM     |   1) 
#define S_ALFAM_BYTES_WRITTEN_NOT_EQ_REQUESTED  (aoM_ALFAM     |   2) 
#define S_ALFAM_BYTES_READ_NOT_EQ_REQUESTED     (aoM_ALFAM     |   3) 
#define S_ALFAM_WR_WD_TIMEOUT                   (aoM_ALFAM     |   4) 
#define S_ALFAM_RD_WD_TIMEOUT                   (aoM_ALFAM     |   5) 
#define S_ALFAM_MALLOC_ERR_INPUT_BUFFER         (aoM_ALFAM     |   6) 
#define S_ALFAM_VELREQ_OUT_OF_RANGE             (aoM_ALFAM     |   7) 
#define S_ALFAM_POSREQ_OUT_OF_RANGE             (aoM_ALFAM     |   8) 
#define S_ALFAM_DCDING_SUMMARY_STAT             (aoM_ALFAM     |   9) 
#define S_ALFAM_DCDING_EXTD_STAT                (aoM_ALFAM     | 0xa) 
#define S_ALFAM_DCDING_EXTD_STAT2               (aoM_ALFAM     | 0xb) 
/*
 * kronhite filters
*/
#define S_KHFILT_BUFOVRFLOW                     (aoM_KHFILT    |   1) 
/*
 * ao modbus errors
*/
#define S_MODBUS_TOO_MANY_REG_REQUESTED         (aoM_MODBUS    |   1)
#define S_MODBUS_IDMISMATCH_SEND_RCV            (aoM_MODBUS    |   2)
#define S_MODBUS_EXCEPTION                      (aoM_MODBUS    |   3)
#define S_MODBUS_BAD_FC_READBACK                (aoM_MODBUS    |   4)
#define S_MODBUS_WR_RDBACK_MISMATCH_ADR         (aoM_MODBUS    |   5)
#define S_MODBUS_WR_RDBACK_MISMATCH_NREG        (aoM_MODBUS    |   6)
#define S_MODBUS_TMOUT_SELECT_READBYTES         (aoM_MODBUS    |   7)
/*
 * prologix gpibenet errors
*/
#define S_PRLX_NO_CTRL_SLOTS_LEFT               (aoM_PRLX      |   1)
#define S_PRLX_NO_DEV_SLOTS_LEFT                (aoM_PRLX      |   2)
#define S_PRLX_BAD_DESCRIPTOR                   (aoM_PRLX      |   3)

#endif	/* INCaoErrNumh */
