/*
 * SPARROW_ioctl.h
 *
 *  Created on: Iul 31, 2019
 *      Author: vovag
 */

#ifndef SPARROW_IOCTL_H_
#define SPARROW_IOCTL_H_

typedef struct _RETURN_STRING {
   char buf[ 160 ];
} RETURN_STRING;

#define IOC_MAGIC    'h'
////#define IOCTL_GET_STRING _IOR( IOC_MAGIC, 1, RETURN_STRING )
#define IOCTL_GET_VERS _IOR( IOC_MAGIC, 1, RETURN_STRING )

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define IOCTL_SET_SPD_SPI_ADDA 	_IOW( IOC_MAGIC, 7, int )
#define IOCTL_PUT_SPI_DA 		_IOW( IOC_MAGIC, 8, dac_spi_req_t )
#define IOCTL_SET_SPI_DA_REQ 	_IOW( IOC_MAGIC, 9, dac_spi_req_t )
#define IOCTL_GET_SPI_DA_DATA 	_IOR( IOC_MAGIC, 10, dac_spi_req_t )
#define IOCTL_INIT_DA 			_IOW( IOC_MAGIC, 11, int )
#define IOCTL_SET_XIL_REQ _IOW( IOC_MAGIC, 12, xil_dat_req_t )
#define IOCTL_GET_XIL_DATA _IOR( IOC_MAGIC, 13, xil_dat_req_t )
#define IOCTL_SET_XIL_DATA _IOW( IOC_MAGIC, 14, xil_dat_req_t )
#define IOCTL_PUT_SPI_AD 		_IOW( IOC_MAGIC, 15, adc_spi_req_t )
#define IOCTL_SET_SPI_AD_REQ 	_IOW( IOC_MAGIC, 16, adc_spi_req_t )
#define IOCTL_GET_SPI_AD_DATA 	_IOR( IOC_MAGIC, 17, adc_spi_req_t )
#define IOCTL_INIT_AD 			_IOW( IOC_MAGIC, 18, int )
#define IOCTL_GET_AD_DATA 	_IOR( IOC_MAGIC, 19, int )

///=================================================

#endif /* SPARROW_IOCTL_H_ */
