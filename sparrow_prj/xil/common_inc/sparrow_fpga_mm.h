#ifndef __SPARROW_FPGA_MM_H__
#define __SPARROW_FPGA_MM_H__
///========================
static const int UGEN_BASE_ADDR = 0x43C00000;
////#define AWG_BASE_SIZE 0x40000
static const int UGEN_BASE_SIZE = 0x10000;

#define ADC_RAM_OFFSET    0x8000

/** FPGA DAC output signal 1 offset */
#define DAC_RAM_OFFSET    0x4000
#define SIN_BUFF_SIZE 8192

#define DAC_REG_OFFSET    			0x1000

#define DAC_CONF_OFFSET    			0x0
#define DAC_OUT_OFFSET      		0x1
#define DAC_B_PH_L_OFFSET     		0x2
#define DAC_B_PH_H_OFFSET    		0x3
#define DAC_DDS_L_OFFSET     		0x4
#define DAC_DDS_H_OFFSET    		0x5
#define DAC_CNT_LEN_OFFSET   		0x6
#define DELAY_DAC_L_OFFSET   				0x8
#define DELAY_DAC_H_OFFSET   				0x9

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
#define ADDR_CNF_SPI			ADDR_COMMON+0x17

#define ADDR_SPI_RDY		ADDR_SPI_CS_A	///.1 bit
#define SPI_BUSY_BIT		(0x1<<1)	///.1 bit
///=======ADDR_CNF_SPI======================
#define SPI_INV_SCK		(0x1<<0)	///.0 bit
#define SPI_NOINV_SCK		(0x0<<0)	///.0 bit

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
#define ADDR_DAC_CONF    0x800
///#define B_ON_DDS		1
///#define B_ENA_DDS		2
///#define ON_DDS 			(0x1<<B_ON_DDS)
///#define ENA_DDS			(0x1<<B_ENA_DDS)

#define DEF_DAC_CONF	0	////(ON_DDS|ENA_DDS)

#define ADDR_DAC_DDS	0x804	///32b
////#define DEF_DDS_VAL		42949673	/// 4MHz 400MHz
#define DEF_DDS_VAL		68174084	/// 4MHz 252MHz
#define DEF_FRQ_DAC		2520000		///252MHz(0.1 KHz)
///======== ADC ===========

#define ADDR_ADC_OUT    		0x1001
#define ADDR_ADC_LEN_CNT    	0x1006
#define DEF_LEN_ADC_CNT			0x1000

#endif ///__SPARROW_FPGA_MM_H__
