/*
 * udp_cmds.h
 *
 *  Created on: Mar 28, 2015
 *      Author: vovag
 */

#ifndef _UDP_CMDS_H_
#define _UDP_CMDS_H_
///========== put to goat_cpu ====================
#define CMD_PUT_DAT  			0x3
#define CMD_REQ_DAT  			0x4
#define CMD_PUT_REQ_DAT  		0x5
#define CMD_PUT_BUF  			0x6
///========== get from dev ====================
#define CMD_ACK  				0x85
///===================================
#define NUM_INIT_ADC  			0x4		///

#define NUM_REQ_CONTRL_STAT  	0x5		///
#define NUM_REQ_ONCN  			0x6		///
#define NUM_SET_MASTER_SLAVE	0x7

#define NUM_REQ_STAT			0x8		///
#define NUM_REQ_REJ				0x9		///
#define NUM_SET_REJ				0xA		///
#if 0
#define NUM_SET_PAR				0xB		///
#define NUM_PUT_CONTRL_CMD		0xC		///
#define NUM_SET_KEY				0xD
#define NUM_SET_SYS_PAR			0xE		///
#define NUM_SET_NPAR			0xF		///
#define NUM_SET_BUFF_CMD		0x10		///
//#define NUM_REQ_FDATE						0x11		///
//#define NUM_REQ_FTIME						0x12		///

#define NUM_SET_PAR_POW			0x19
#define NUM_REQ_GET_AMPS_TIMS	0x1a
#define NUM_REQ_GET_CONTR_STAT	0x1b
#define NUM_SET_MARKER			0x1c

#define NUM_SET_CNGEN			0x1d		///
#define NUM_SET_CNUS			0x1e		///
#define NUM_SET_CNTACT			0x1f		/// curr takt

#define NUM_REQ_RD_SYS_PAR_		0x20		///
#define NUM_REQ_RD_N_PAR_				0x21		/// first
#define NUM_WR_BUFF_CMD					0x22
#define NUM_WR_ALL_PAR_CMD				0x23
#define NUM_SET_PAR_US					0x24
#define NUM_GET_PAR_US					0x25
#define NUM_SET_PAR_GEN					0x26
#define NUM_GET_PAR_GEN					0x27
#define NUM_SET_PAR_OSC					0x28
#define NUM_GET_PAR_OSC					0x29
#define NUM_REQ_START_CONTR				0x2e
#define NUM_REQ_STOP_CONTR				0x2f
#define NUM_SET_MAX_TACT				0x30
#define NUM_REQ_GET_ZAMER				0x31
#endif

#define NUM_REQ_CLR_ERR					0x13		///
#define NUM_REQ_GET_AMPS				0x2a
///#define NUM_REQ_GET_TIMS				0x2b
#define NUM_REQ_GET_OSC0				0x2c
#define NUM_REQ_GET_OSC1				0x2d

#define NUM_REQ_CLEAR_BUFF  			0x30	/// очистить буферы от старых данных (принудительно)

#define NUM_WR_N_PAR_CMD				0x32

#define NUM_RD_PAR_DEV_CMD				0x33
#define NUM_WR_PAR_DEV_CMD				0x34
#define NUM_WR_ON_GENS					0x35
///===== contr =======================================
#define CMD_CONTR_REQ_PAR               0x40    // returns stat_cn (1 byte); konc_opt (2 bytes); coord (2 bytes)
#define CMD_CONTR_SET_PAR16        		0x41    // <cmd><par_id><par_val>  par_id: 1 byte; par_val: 2 bytes

#define CMD_CONTR_ON_OFF_EM        		0x43    // <cmd><mask_id><mask_val> mask_em: 1 byte; mask_val: 1 byte
#define CMD_CONTR_ON_OFF_REL    		0x44    // <cmd><mask_id><mask_val> mask_em: 1 byte; mask_val: 1 byte
#define CMD_CONTR_ON_OFF_KR        		0x45    // <cmd><mask_id><mask_val> mask_em: 1 byte; mask_val: 1 byte

#define CMD_CONTR_BATH            		0x46    // <cmd><param> param: 1 byte (0 - down, 1 - up)

#define CMD_CONTR_CLR_COOR        		0x47
#define CMD_CONTR_CLR_ERR        		0x48

#define CMD_CONTR_VDP            		0x49    // <cmd><speed> speed: 2 bytes (speed==0 - vdp off)
#define CMD_CONTR_INIT            		0x4A
///========= CMD_CONTR_SET_PAR16 ===============================
#define PARAM_ID_DIST_1_2		0x4
#define PARAM_ID_DIST_1_3		0x5

#define PARAM_ID_MAX_DIST		0x6
#define PARAM_ID_MARKER_ON		0x7

///===================================
#define NUM_SET_RTC					0x87

#define NUM_PUT_SPI_ADC_DAT			0x90
#define NUM_GET_SPI_ADC_DAT			0x91
#define NUM_SEND_SPI_ADC_REQ		0x92

#define NUM_SEND_XIL_DAT			0x93
#define NUM_REQ_XIL_DAT				0x94
#define NUM_SEND_XIL_REQ			0x95

#define NUM_SEND_MOD_CMD			0x96
#define NUM_REQ_MOD_DAT				0x97

#define NUM_SEND_MOD_STR			0x96
#define NUM_REQ_MOD_STR				0x97

#define NUM_SEND_ACT_DAT			0xA0
#define NUM_REQ_ACT_DAT				0xA1
#define NUM_SEND_ACT_REQ			0xA2

#define CHNG_TIMP_LEN			(0x1<<1)
#define CHNG_TIMP_OFFSET		(0x1<<2)
#define CHNG_TCYCLE				(0x1<<3)
#define CHNG_TDEF				(0x1<<4)
#define CHNG_IMP_POINTS			(0x1<<5)
#define CHNG_PRESC				(0x1<<6)

#define CHNG_CHAN		(0x1<<0)
#define CHNG_NUS		(0x1<<2)
#define CHNG_BSTRB		(0x1<<10)
#define CHNG_LSTRB		(0x1<<11)
#define CHNG_PRE		(0x1<<20)
#define CHNG_RNG		(0x1<<21)
#define CHNG_LEN_DEF	(0x1<<22)
#define CHNG_FORM		(0x1<<23)

#define FILE_BLOCK_SIZE			512
#define MAX_FILE_NAME_LEN 		15

///++++++++++++++++++++++++++++++++++++++++
#define SEND_DAT					(0x1<<0)
#define SEND_ACK					(0x1<<1)
#define SEND_REQ_DAT				(0x1<<2)
#define SEND_REQ					(0x1<<3)
///===================================
#if 0
///#define	FLG_STAT_SD_INST	(0x1<<0)
///#define	FLG_STAT_MMC_INIT	(0x1<<1)
///#define	FLG_STAT_FMOUNT		(0x1<<2)
///#define	FLG_STAT_RD_TTF		(0x1<<3)
///#define	FLG_STAT_LD_TRK		(0x1<<4)
#define	FLG_STAT_ALL_OK		(FLG_STAT_LD_TRK|FLG_STAT_RD_TTF  \
							|FLG_STAT_FMOUNT|FLG_STAT_MMC_INIT \
						|FLG_STAT_SD_INST)
#endif

#define	FLG_STAT_ERR			(0x1<<7)

///===================================
///#define ENET_BUFFER_SIZE 1520
///#define UDP_MAX_BUFF_SIZE 8192

///===================================
#define DEF_NUM_PAR 2
///===================================
////#define MAX_FRAME_LEN 8192
#define ACK_OK 		0xA5

extern unsigned char volatile dev_state;
///==========================================
#endif /* _UDP_CMDS_H_ */
