
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <syslog.h>

#include <dirent.h>

///#include "../../utils.h"
///#include "../inc/misc.h"
///#include "../../common/weasel_bl_types.h"
#include "../inc/sparrow_cnf.h"
#include "../inc/my_types.h"
#include "../inc/udp_types.h"
#include "../inc/sparrow_udp_cmds.h"

////extern int pc_connected;

////#define OUTPUT_PLUGIN_NAME "UDP output plugin"

///static
pthread_t udp;
////pthread_t worker;


int g_sd;	///socket

///static int fd;
static int delay=0;
////static unsigned char *frame = NULL;

// UDP port
///static int port = 2000;
int stop=0;

/******************************************************************************
Description.: clean up allocated ressources
Input Value.: unused argument
Return Value: -
******************************************************************************/
#if 0
void udp_cleanup(void *arg)
{
    static unsigned char first_run = 1;

    if(!first_run) {
        DBG("already cleaned up ressources\n");
        return;
    }

    first_run = 0;
    OPRINT("cleaning up ressources allocated by worker thread\n");

    if(frame != NULL) {
        free(frame);
    }
    close(fd);
}
#endif
extern udp_stat_t g_udp_stat;
extern u16 obr_udp_cmd(u8 *i_buff,u16 i_len,u8 *o_buff);
extern void udp_pc_init(void);
////extern void set_tst_oscs(u8 idat);
///extern u8 *t_par_buff;
///extern int put_led(int i_led);
int udp_thr_stop=0;
/******************************************************************************
Description.: this is the main worker thread
              it loops forever, grabs a fresh frame and stores it to file
Input Value.:
Return Value:
******************************************************************************/
void *udp_thread(void *arg)
{
////int kk=0;
int ok = 1;
uint16_t o_len=0;
uint8_t *o_data;
///======================
////o_len=obr_udp_cmd(data,len);
udp_pc_init();
o_data = g_udp_stat.snd_buff;
/* set cleanup handler to cleanup allocated ressources */
////pthread_cleanup_push(udp_cleanup, NULL);

    // set UDP server data structures ---------------------------
///    if(port <= 0) {
///    	fprintf(stderr,"a valid UDP port must be provided\n");
///        return NULL;
////    }
    struct sockaddr_in addr;
    int sd;
    int bytes;
    unsigned int addr_len = sizeof(addr);
    char udpbuffer[MAX_FRAME_LEN] = {0};
    char sendbuffer[MAX_FRAME_LEN] = {0};
    sd = socket(PF_INET, SOCK_DGRAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(UDP_PORT);
    if(bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0)
        perror("bind");
////	t_par_buff = (u8 *)malloc(sizeof(par_bl_trk_t)+sizeof(ed_par_bl_trk_t)+8);

    // -----------------------------------------------------------
////    OPRINT("udp_thread1\n");

    while(ok >= 0 && !udp_thr_stop)
    {
///        OPRINT("udp_thread2\n");
////        DBG("waiting for a UDP message\n");

        // UDP receive ---------------------------------------------
        memset(udpbuffer, 0, sizeof(udpbuffer));
        bytes = recvfrom(sd, udpbuffer, sizeof(udpbuffer), 0, (struct sockaddr*)&addr, &addr_len);
 ////       pc_connected=1;
        o_len=obr_udp_cmd((u8*)udpbuffer,bytes,(u8*)sendbuffer);
///===========================================
 ////       fprintf(stderr,"\n recvfrom =%x=======",bytes);
///===========================================
        memcpy(sendbuffer,o_data,o_len);
        sendto(sd, sendbuffer, o_len, 0, (struct sockaddr*)&addr, sizeof(addr));
        /* if specified, wait now */
        if(delay > 0) {
            usleep(1000 * delay);
        }
    }

    // close UDP port
////    if(port > 0)
        close(sd);
/* cleanup now */
////pthread_cleanup_pop(1);
return NULL;
}

/******************************************************************************
Description.: calling this function stops the worker thread
Input Value.: -
Return Value: always 0
******************************************************************************/
int udp_stop(int id)
{
////DBG("will cancel worker thread\n");
////pthread_cancel(udp);
return 0;
}


