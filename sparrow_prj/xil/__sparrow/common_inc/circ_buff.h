/*
 * cir_buff.h
 *
 *  Created on:  27.07.2015
 *  Author: vovag
 */

#ifndef _CIR_BUFF_H_
#define _CIR_BUFF_H_

typedef struct circ_buffer_s
{
void *buffer;     // data buffer
void *buffer_end; // end of data buffer
size_t capacity;  // maximum number of items in the buffer
size_t count;     // number of items in the buffer
size_t sz;        // size of each item in the buffer
void *head;       // pointer to head
void *tail;       // pointer to tail
} circ_buffer_t;
///===================================
extern void *cb_init(circ_buffer_t *cb, size_t capacity, size_t sz);
extern void cb_clear(circ_buffer_t *cb);
extern void cb_clear_all(circ_buffer_t *cb);
extern void cb_free(circ_buffer_t *cb);
extern int cb_push(circ_buffer_t *cb, const void *item);
extern int cb_pop(circ_buffer_t *cb, void *item);
extern int cb_get_count(circ_buffer_t *cb);
extern int cb_push_nzero(circ_buffer_t *cb, int num);
extern void *cb_curr_dat(circ_buffer_t *cb);
extern int cb_inc_ptr(circ_buffer_t *cb);
extern void *cb_reinit(circ_buffer_t *cb, size_t capacity, size_t sz);

#endif /* CIR_BUFF_H_ */
