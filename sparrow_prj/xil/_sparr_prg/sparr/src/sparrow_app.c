/*
 * Copyright (c) 2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * 
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

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
///#include "../../../sparrow_ioctl.h"
#include "./inc/sparrow_cnf.h"
#include "./inc/my_types.h"
#include "./inc/sparrow_udp_cmds.h"
#include "./inc/sparrow_fpga.h"
#include <stdio.h>

extern void *udp_thread(void *arg);
extern pthread_t udp;

extern void set_changed_param(void);
extern uint32_t g_changed_param;

const char* VER_TXT="sparrow v1.0(G.V.A.)";
const char* MOD_PATH="/dev/sparrow";


int mod_fd;
///========================================
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
///=========================================
int main()
{
int	rez=0;
char tbuf[256];

///===========================================
printf("\nvers[%s]\n",VER_TXT);
printf("=========================\n"
		"sparrow \n"
		"(Built on %s %s)"
		"\n==========================",
		__DATE__, __TIME__);
mod_fd = open(MOD_PATH, O_RDWR);
if(mod_fd <= 0)
	{
	printf("file open error : %s[%d]\n",MOD_PATH,mod_fd);
	syslog(LOG_INFO,"file open error : %s\n",MOD_PATH);
	return -1;
	}
printf("file open ok : [%s][%d]\n",MOD_PATH,mod_fd);
syslog(LOG_INFO,"file open ok : [%s][%d]\n",MOD_PATH,mod_fd);
rez=get_mod_vers(tbuf);
fprintf(stderr,"\n mod[%d][%s]",rez,tbuf);
pthread_create(&udp, NULL, udp_thread, NULL);
pthread_detach(udp);
set_spd_spi(4);
init_dac(0);
usleep(10);
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
