#ifndef _UDP_TYPES_H_
#define _UDP_TYPES_H_

///#define MAX_ALT_DATA_LEN 64

///===========================================
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
#if 0
typedef struct _adc_spi_req
{
u8 addr;
u8 rsv;///nbytes;
u16 data;
}adc_spi_req_t;
#endif
#if 0
typedef struct _alt_dat_req_s
{
u16 addr;
u16 ndata;
u16 data[MAX_ALT_DATA_LEN];
}alt_dat_req_t;
#endif

#endif ////_UDP_TYPES_H_

