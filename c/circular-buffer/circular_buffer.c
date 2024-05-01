#include "circular_buffer.h"
#include <stdlib.h>
#include <errno.h>

circular_buffer_t* new_circular_buffer(size_t capacity) {
    if (!capacity) return NULL;

    circular_buffer_t* buffer = calloc(
            sizeof(circular_buffer_t) + sizeof(buffer_value_t[capacity]), 1);
    if (!buffer) return NULL;

    *buffer = (circular_buffer_t) {
            .capacity= capacity,
    };

    return buffer;
}

uint16_t read(circular_buffer_t* buffer, buffer_value_t* value) {
    if (!buffer || !buffer->len) {
        errno = ENODATA;
        return EXIT_FAILURE;
    }

    *value = buffer->values[buffer->head];
    buffer->head = (buffer->head + 1) % buffer->capacity;
    buffer->len--;

    return EXIT_SUCCESS;
}

uint16_t write(circular_buffer_t* buffer, buffer_value_t value) {
    if (!buffer || buffer->len == buffer->capacity) {
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }

    return overwrite(buffer, value);
}

uint16_t overwrite(circular_buffer_t* buffer, buffer_value_t value) {
    if (!buffer) return EXIT_FAILURE;

    const size_t pos = (buffer->head + buffer->len) % buffer->capacity;
    buffer->len++;
    buffer->values[pos] = value;

    if (buffer->capacity < buffer->len) {
        buffer->len--;
        buffer->head = (buffer->head + 1) % buffer->capacity;
    }

    return EXIT_SUCCESS;
}

void delete_buffer(circular_buffer_t* buffer) {
    if (!buffer) return;
    free(buffer);
}

void clear_buffer(circular_buffer_t* buffer) {
    if (!buffer) return;
    buffer->len = 0;
}
