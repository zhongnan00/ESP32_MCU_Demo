/**
 * @file lib_ring_buffer.c
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "lib_ring_buffer.h"
#include <string.h>

void ring_buffer_init(ring_buffer_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    memset(rb->buffer, 0, sizeof(rb->buffer));
}

bool ring_buffer_is_empty(ring_buffer_t *rb)
{
return rb->count == 0;
}

bool ring_buffer_is_full(ring_buffer_t *rb)
{
    return rb->count == RING_BUFFER_SIZE;
} 

bool ring_buffer_push(ring_buffer_t *rb, int data)
{
    if(ring_buffer_is_full(rb)) {
        return false;
    }
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
    rb->count++;
    return true;
}

bool ring_buffer_pop(ring_buffer_t *rb, int *data)
{
    if(ring_buffer_is_empty(rb)) {
        return false;
    }
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
    rb->count--;
    return true;
}

bool ring_buffer_pop_only(ring_buffer_t *rb)
{
    if(ring_buffer_is_empty(rb)) {
        return false;
    }
    // *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
    rb->count--;
    return true;
}
