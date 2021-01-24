/*
 * my_types.h
 *
 *  Created on: Oct 21, 2016
 *      Author: vovag
 */

#ifndef _MY_TYPES_H_
#define _MY_TYPES_H_
///=============================================================================
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

typedef struct my_timespec_s
  {
	long int tv_sec;		/* Seconds.  */
    long int tv_nsec;		/* Nanoseconds.  */
  }my_timespec_t;

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
#endif /* MY_TYPES_H_ */
