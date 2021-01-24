/*
 *sparrow_types.h
 *
 *  Created on: apr 6, 2019
 *      Author: vovag
 */

#ifndef _SPARROW_TYPES_H_
#define _SPARROW_TYPES_H_


#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned short
#endif
#ifndef s16
#define s16 signed short
#endif
#ifndef u32
#define u32 unsigned long
#endif
#ifndef s32
#define s32 signed long
#endif

#ifndef ON
#define ON 1
#endif
#ifndef OFF
#define OFF 0
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef MIN
#define MIN(a, b) (a < b ? a : b)
#endif
///================================
typedef u16 (*u16_fn_pu8)(u8*);
typedef u8 (*u8_fn_u8)(u8);
typedef void (*void_fn_u8)(u8);
typedef int (*int_fn_u8_pvoid)(u8,void *);
typedef u16 (*u16_fn_u8_pu8)(u8,u8*);
typedef void (*void_fn_int)(int);
typedef void (*void_fn_pvoid)(void*);
typedef int (*int_fn_pvoid)(void*);
typedef int (*int_fn_void)(void);
typedef u32 (*u32_fn_void)(void);
typedef u8 (*u8_fn_void)(void);
typedef u16 (*u16_fn_void)(void);
typedef s16 (*s16_fn_void)(void);
typedef u32 (*u32_fn_s16)(s16);
///===================================
#define MAX_XIL_DATA_LEN	32
typedef struct _adc_spi_req
{
u8 addr;
u8 data;
u8 rsv[2];///nbytes;
}adc_spi_req_t;

typedef struct _dac_spi_req
{
u8 addr;
u8 rsv;///nbytes;
u16 data;
}dac_spi_req_t;

typedef struct _xil_dat_req_s
{
u16 addr;
u16 ndata;
u16 data[MAX_XIL_DATA_LEN];
}xil_dat_req_t;


#define TYPE_NO_ARC		0
#define TYPE_ARC_MLZO	1
#define TYPE_ARC_LZMA	2


typedef struct udp_stat_s_
{
u8 	*in_buf;					//
u8 	*obr_buff;				//
u16 len_obr_dat;
u8 	*snd_buff;				//
u8 	*t_snd_buff1;			//
u8 	*t_snd_buff2;			//
u16	frame_out_len;
u16	offs_snd_buf;
void *t_rsv_buff;
u16	snd_buff2_len;
	int	err_len;
	int err_fcs;
	int	frames_sent;
	int	frames_received;
}udp_stat_t;



#endif /* SPARK_TYPES_H_ */
