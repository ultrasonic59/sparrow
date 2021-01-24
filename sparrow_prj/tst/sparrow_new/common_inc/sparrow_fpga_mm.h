#ifndef __SPARROW_FPGA_MM_H__
#define __SPARROW_FPGA_MM_H__
///========================
///=========================================
#define ADDR_COMMON		0x0000
#define ADDR_RD_C0			ADDR_COMMON+0x5
#define ADDR_RD_C1			ADDR_COMMON+0x6
#define ADDR_SPD_SPI		ADDR_COMMON+0x11
#define ADDR_SPI_CS_A		ADDR_COMMON+0x12
#define ADDR_SPI_CS_B		ADDR_COMMON+0x13
#define ADDR_SPI_WR_DATA		ADDR_COMMON+0x14
#define ADDR_SPI_REQ_DATA		ADDR_COMMON+0x15
#define ADDR_SPI_RD_DATA		ADDR_COMMON+0x16

#define ADDR_SPI_RDY		ADDR_SPI_CS_A	///.1 bit
#define SPI_BUSY_BIT		(0x1<<1)	///.1 bit

///=========================================
#define ADDR_CONFIG0 	0x0
#define fifo_ena_bit		(0x1<<7)
#define alarm_out_ena_bit	(0x1<<6)
#define alarm_out_pol_bit	(0x1<<7)
#define alignrx_ena_bit		(0x1<<4)
#define lvdssyncrx_ena_bit	(0x1<<3)
#define lvdsdataclk_ena_bit	(0x1<<2)
#define synconly_ena_bit	(0x1<<0)
#define ADDR_CONFIG1 	0x1
#define iotest_ena_bit				(0x1<<15)
#define fullwordinterface_ena_bit	(0x1<<13)
#define _64cnt_ena_bit				(0x1<<12)
#define dacclkgone_ena_bit			(0x1<<11)
#define collision_ena_bit			(0x1<<9)
#define daca_complimenta_bit		(0x1<<7)
#define sif_sync_bit				(0x1<<5)
#define sif_sync_ena_bit			(0x1<<4)
#define alarm_2away_ena_bit			(0x1<<3)
#define alarm_1away_ena_bit			(0x1<<2)
#define alarm_collision_ena_bit		(0x1<<1)
#define ADDR_CONFIG2 	0x2
#define ADDR_CONFIG3 	0x3
#define ADDR_CONFIG4 	0x4
#define ADDR_CONFIG6 	0x6
#define ADDR_CONFIG20 	0x14
#define sifdac_ena_bit			(0x1<<15)
#define sifdac(x)			(x&0x3fff)
///========================
#endif ///__SPARROW_FPGA_MM_H__
