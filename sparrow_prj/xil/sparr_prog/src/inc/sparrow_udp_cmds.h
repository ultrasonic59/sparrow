/*
 * udp_cmds.h
 *
 *  Created on: Mar 28, 2015
 *      Author: vovag
 */

#ifndef _SPARROW_UDP_CMDS_H_
#define _SPARROW_UDP_CMDS_H_
///========== put to goat_cpu ====================
#define CMD_PUT_DAT  			0x3
#define CMD_REQ_DAT  			0x4
#define CMD_PUT_REQ_DAT  		0x5
#define CMD_PUT_BUF  			0x6
///========== get from dev ====================
#define CMD_ACK  				0x85
///===================================
#if 0
#define NUM_REQ_CLR_ERR					0x13		///
///#define NUM_REQ_GET_TIMS				0x2b

#define NUM_REQ_CLEAR_BUFF  			0x30	/// очистить буферы от старых данных (принудительно)

#define NUM_WR_N_PAR_CMD				0x32

#define NUM_RD_PAR_DEV_CMD				0x33
#define NUM_WR_PAR_DEV_CMD				0x34
#define NUM_WR_ON_GENS					0x35
///===== contr =======================================
///===================================
///#define NUM_SET_RTC					0x87

#endif

#if 0

#define CHNG_CHAN		(0x1<<0)
#define CHNG_NUS		(0x1<<2)
#define CHNG_BSTRB		(0x1<<10)
#define CHNG_LSTRB		(0x1<<11)
#endif
///================================================
#define NUM_REQ_STAT			0x8		///
#define NUM_REQ_REJ				0x9		///
#define NUM_SET_REJ				0xA		///

////#define NUM_REQ_GET_AMPS				0x2a
#define NUM_REQ_GET_OSC0				0x2c
///#define NUM_REQ_GET_OSC1				0x2d
#define NUM_REQ_GET_AMPS				0x2d

#define NUM_WR_N_PAR_CMD				0x32
///================================================
#define NUM_PUT_SPI_ADC_DAT			0x90
#define NUM_GET_SPI_ADC_DAT			0x91
#define NUM_SEND_SPI_ADC_REQ		0x92

#define NUM_SEND_XIL_DAT			0x93
#define NUM_REQ_XIL_DAT				0x94
#define NUM_SEND_XIL_REQ			0x95

#define NUM_PUT_SPI_DAC_DAT			0x98
#define NUM_GET_SPI_DAC_DAT			0x99
#define NUM_SEND_SPI_DAC_REQ		0x9A
///================================================
#define CHNG_TIMP_LEN			(0x1<<1)
#define CHNG_TIMP_OFFSET		(0x1<<2)
#define CHNG_TCYCLE				(0x1<<3)
#define CHNG_TDEF				(0x1<<4)
#define CHNG_IMP_POINTS			(0x1<<5)
#define CHNG_KUS				(0x1<<6)
#define CHNG_ATT				(0x1<<9)

#define CHNG_BSTRB		(0x1<<10)
#define CHNG_LSTRB		(0x1<<11)
#define CHNG_PRE		(0x1<<20)
#define CHNG_RNG		(0x1<<21)
#define CHNG_LEN_DEF	(0x1<<22)
#define CHNG_FORM		(0x1<<23)

///================================================
#define SEND_DAT					(0x1<<0)
#define SEND_ACK					(0x1<<1)
#define SEND_REQ_DAT				(0x1<<2)
#define SEND_REQ					(0x1<<3)
///===================================

///===================================
#define DEF_NUM_PAR 2
///===================================
#define ACK_OK 		0xA5

extern unsigned char volatile dev_state;
///==========================================
#endif /* _UDP_CMDS_H_ */
