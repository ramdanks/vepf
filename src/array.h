#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* data;
    size_t size;
} array;

array array_malloc(size_t size);

array array_calloc(size_t size);

void array_realloc(array* array, size_t size);

void array_free(array* array);

#ifdef __cplusplus
}
#endif

#endif