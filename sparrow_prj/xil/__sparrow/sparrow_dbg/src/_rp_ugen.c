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

#include "./inc/rp_ugen_cnf.h"
#include "./inc/my_types.h"
#include "./inc/udp_types.h"
#include "./inc/udp_cmds.h"
#include "./inc/ugen_fpga.h"

extern void *udp_thread(void *arg);
extern pthread_t udp;

u8 buffOscs[NUM_OSC][MAX_OSC_LEN];
extern u32 g_changed_param;
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

int main(int argc, char *argv[])
{
////  int fd,file, sockServer, sockClient;


	init_ugen_fpga();

	pthread_create(&udp, NULL, udp_thread, NULL);
	pthread_detach(udp);

	for(;;)
	{
	if(g_changed_param)
		{
		set_changed_param();
		}
	usleep(10);
	}


return 0;
}
