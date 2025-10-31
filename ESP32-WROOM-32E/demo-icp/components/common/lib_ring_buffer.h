/**
 * @file lib_ring_buffer.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef _LIB_RING_BUFFER_H_
#define _LIB_RING_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>


#define RING_BUFFER_SIZE 16

typedef struct {
    int buffer[RING_BUFFER_SIZE];
    int head;
    int tail;
    uint16_t count;
} ring_buffer_t;

void ring_buffer_init(ring_buffer_t *rb);

bool ring_buffer_is_empty(ring_buffer_t *rb);

bool ring_buffer_is_full(ring_buffer_t *rb);

bool ring_buffer_push(ring_buffer_t *rb, int data);

bool ring_buffer_pop(ring_buffer_t *rb, int *data);

bool ring_buffer_pop_only(ring_buffer_t *rb);

#endif /* _LIB_RING_BUFFER_H_ */
