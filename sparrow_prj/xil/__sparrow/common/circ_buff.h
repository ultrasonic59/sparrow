/*
 * cir_buff.h
 *
 *  Created on:  27.07.2015
 *  Author: vovag
 */

#ifndef _CIR_BUFF_H_
#define _CIR_BUFF_H_
#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/slab.h>

#define _MALLOC(x) kmalloc(x, GFP_KERNEL)
#define _FREE(x) kfree(x)
#else
#include <stdint.h>
#define _MALLOC(x) malloc(x)
#define _FREE(x) free(x)
#endif



typedef struct circ_buffer_s
{
uint8_t *buffer;     // data buffer
size_t capacity;  // maximum number of items in the buffer
size_t sz;        // size of each item in the buffer
uint32_t p_wr;       // pointer to head
uint32_t p_rd;       // pointer to tail
} circ_buffer_t;
///===================================
extern void *cb_init(circ_buffer_t *cb, size_t capacity, size_t sz);
extern void cb_clear(circ_buffer_t *cb);
extern void cb_clear_all(circ_buffer_t *cb);
extern void cb_free(circ_buffer_t *cb);
extern int cb_push(circ_buffer_t *cb, const void *item);
extern int cb_pop(circ_buffer_t *cb, void *item);
////extern uint32_t cb_get_count(circ_buffer_t *cb);
extern int cb_push_nzero(circ_buffer_t *cb, int num);
extern void *cb_curr_dat(circ_buffer_t *cb);
///extern int cb_inc_ptr(circ_buffer_t *cb);
extern uint32_t cb_get_count(circ_buffer_t *cb);

#endif /* CIR_BUFF_H_ */
