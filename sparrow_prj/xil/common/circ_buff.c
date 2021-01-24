#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
////#include "../common/circ_buff.h"
#include "circ_buff.h"

////#include "circ_buff.h"
///static
inline uint32_t cb_get_free_space( circ_buffer_t* ring_buffer );

void *cb_init(circ_buffer_t *cb, size_t capacity, size_t sz)
{
////cb->buffer = (void*)malloc(capacity * sz);
cb->buffer = (void*)malloc(capacity * sz);
if(cb->buffer == 0)
	return 0;
////cb->buffer_end = (char *)cb->buffer + capacity * sz;
cb->capacity = capacity;
///cb->count = 0;
cb->sz = sz;
cb->p_rd = 0;
cb->p_wr = 0;
return cb->buffer;
}
void cb_clear(circ_buffer_t *cb)
{
if(cb->buffer == 0)
	return ;
///cb->buffer_end = (char *)cb->buffer + capacity * sz;
///cb->count = 0;
cb->p_rd = 0;
cb->p_wr = 0;
}
void cb_clear_all(circ_buffer_t *cb)
{
if(cb->buffer == 0)
	return ;
memset(cb->buffer,0,cb->capacity*cb->sz);
///cb->count = 0;
cb->p_rd = 0;
cb->p_wr = 0;
}

void cb_free(circ_buffer_t *cb)
{
///free(cb->buffer);
free(cb->buffer);
}

int cb_push(circ_buffer_t *cb, const void *item)
{
if(cb->buffer == NULL)
	return -1;
if(cb_get_free_space(cb)==0)
	return 0;
memcpy(cb->buffer+(cb->p_wr*cb->sz), item, cb->sz);
cb->p_wr++;
if(cb->p_wr == cb->capacity)
	cb->p_wr = 0;
////cb->count++;
return cb_get_count(cb);
}
void *cb_curr_dat(circ_buffer_t *cb)
{
return (void *)(cb->buffer+(cb->p_rd*cb->sz));
}

int cb_pop(circ_buffer_t *cb, void *item)
{

if(cb->p_wr == cb->p_rd)
{
	fprintf(stderr,"\ncp_pop_err0");
	return -1;
}
memcpy(item, cb->buffer+(cb->p_rd*cb->sz), cb->sz);
cb->p_rd++;
if(cb->p_rd == cb->capacity)
    cb->p_rd = 0;
////cb->count--;
return cb_get_count(cb);
}
uint32_t cb_get_count(circ_buffer_t *cb)
{
if(cb->buffer == NULL)
	{
	fprintf(stderr,"\ncp_pop_err1");
	return -1;
	}
else
	{
	uint32_t head_to_end = cb->capacity - cb->p_rd;
	return ((head_to_end + cb->p_wr) % cb->capacity);
	}
}
///===========================================
inline uint32_t cb_get_free_space( circ_buffer_t* ring_buffer )
{
uint32_t tail_to_end = ring_buffer->capacity-1 - ring_buffer->p_wr;
return ((tail_to_end + ring_buffer->p_rd) % ring_buffer->capacity);
}
