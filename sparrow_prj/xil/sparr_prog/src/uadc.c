#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h> // I2C bus definitions
#include "../../common_inc/sparrow_fpga_mm.h"

extern volatile void *fpga_regs;
extern volatile uint16_t  *g_dac_mem ;

extern int fd_i2c;
const int mcp4725_address = 0x60;

#if 0
  // connect to mcp4725 as i2c slave
  if (ioctl(fd_i2c, I2C_SLAVE, mcp4725_address) < 0) {
    printf("Error: Couldn't find device on address[%x]!\n",mcp4725_address);
///    exit (1);
  }
#endif

int init_kus_adc(void)
{
return 0;
}

int put_kus_adc(uint16_t i_val)
{
uint8_t writeBuf[3];

  // connect to mcp4725 as i2c slave
if (ioctl(fd_i2c, I2C_SLAVE, mcp4725_address) < 0) {
    fprintf(stderr,"Error: Couldn't find device on address[%x]!\n",mcp4725_address);
	return -1;
  }
// 12-bit device values from 0-4095

  // page 18-19 spec sheet
  writeBuf[0] = 0b01000000; // control byte
  // bits 7-5; 010 write DAC; 011 write DAC and EEPROM
  // bits 4-3 unused
  // bits 2-1 PD1, PD0 PWR down P19 00 normal.
  // bit 0 unused
  
writeBuf[1] = i_val >> 4; // MSB 11-4 shift right 4 places

writeBuf[2] = i_val << 4; // LSB 3-0 shift left 4 places

  if (write(fd_i2c, writeBuf, 3) != 3) {
    perror("Write to mcp4725");
    return -2;
  }

return 0;
}
uint16_t get_adc_ram_dat(uint16_t i_offs)
{
uint16_t rez;

g_dac_mem = (uint16_t *)(fpga_regs +
		ADC_RAM_OFFSET);
rez=g_dac_mem[i_offs] ;
return rez;
}



