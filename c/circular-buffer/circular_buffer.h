#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stddef.h>

typedef int buffer_value_t;

typedef struct {
    size_t head;
    size_t len;
    size_t capacity;
    buffer_value_t* values;
} circular_buffer_t;

circular_buffer_t* new_circular_buffer(size_t capacity);
void delete_buffer(circular_buffer_t* buffer);
void clear_buffer(circular_buffer_t* buffer);

uint16_t read(circular_buffer_t* buffer, buffer_value_t* value);
uint16_t write(circular_buffer_t* buffer, buffer_value_t value);
uint16_t overwrite(circular_buffer_t* buffer, buffer_value_t value);

#endif
