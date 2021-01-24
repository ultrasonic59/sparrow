#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
////#include <bits/mathcalls.h>
#include <pthread.h>
#include <syslog.h>

#include "../../common_inc/sparrow_ioctl.h"
#include "./inc/sparrow_cnf.h"
#include "./inc/my_types.h"
///#include "./inc/udp_types.h"
#include "./inc/sparrow_udp_cmds.h"
#include "./inc/sparrow_fpga.h"

extern void *udp_thread(void *arg);
extern pthread_t udp;

u8 buffOscs[NUM_OSC][MAX_OSC_LEN];
extern u32 g_changed_param;

const char* VER_TXT="sparrow v1.0(G.V.A.)";
const char* MOD_PATH="/dev/sparrow";
///const char* MOD_PATH="/dev/i2c-0)";
///const char* MOD_PATH="/dev/ttyPS0)";
////const char* MOD_PATH="/home/sparrow/mod_load)";

volatile u8 tst_t=7;

void set_tst_oscs(u8 idat)
{
int ii;
for(ii=0;ii<MAX_OSC_LEN;ii++)
	{
	buffOscs[1][ii]=ii+idat;
	buffOscs[0][ii]= ~(ii+idat);
	}
}
extern void set_changed_param(void);
int mod_fd=0;
int pc_connected=0;


//#define DEBUG		1


int get_mod_vers(char *tbuf)
{
if( ioctl(mod_fd, IOCTL_GET_VERS,tbuf )<0)
	{
	sprintf(tbuf,"[-----]");
	return -1;
	}
fprintf(stderr,"\n %s",tbuf);
return 0;
}

///===================================================
int main(int argc, char *argv[])
{
	int ii;
int	rez=0;
char tbuf[256];
///===========================================
printf("\nvers[%s]\n",VER_TXT);
printf("=========================\n"
	          "sparrow \n"
	         "(Built on %s %s)"
	        "\n==========================",
	         __DATE__, __TIME__);

#if 1
openlog("sparrow",LOG_PID|LOG_CONS,LOG_USER);

///=======================================================
syslog(LOG_INFO,"\nopen(%s)\n",MOD_PATH);
printf("\nopen(%s)\n",MOD_PATH);

mod_fd = open(MOD_PATH, O_RDWR);
if(mod_fd <= 0)
	{
	printf("file open error : %s[%d]\n",MOD_PATH,mod_fd);
	syslog(LOG_INFO,"file open error : %s\n",MOD_PATH);
	return -1;
	}
else
	{
	printf("file open ok : [%s][%d]\n",MOD_PATH,mod_fd);
	syslog(LOG_INFO,"file open ok : [%s][%d]\n",MOD_PATH,mod_fd);
	}
rez=get_mod_vers(tbuf);
fprintf(stderr,"\n mod[%d][%s]",rez,tbuf);
#endif
///=======================================================
///set_spd_spi(DEF_SPI_SPEED);
///set_spd_spi(4);
///init_dac(0);

///	init_ugen_fpga();

	pthread_create(&udp, NULL, udp_thread, NULL);
	pthread_detach(udp);
///for(ii=0;ii<10;ii++)
///{
	set_spd_spi(4);
	init_dac(0);
	usleep(10);
///}
	for(;;)
	{
///		set_spd_spi(4);
	if(g_changed_param)
		{
		set_changed_param();
		}
	usleep(10);
	}


return 0;
}
