#include "array.h"
#include <stdint.h>
#include <stdlib.h>

array array_malloc(size_t size)
{
    array temp;
    temp.data = malloc(size);
    temp.size = size;
    return temp;
}

array array_calloc(size_t size)
{
    array temp;
    temp.data = calloc(sizeof(uint8_t), size);
    temp.size = size;
    return temp;
}

void array_realloc(array* array, size_t size)
{
    array->data = realloc(array->data, size);
    array->size = size;
}

void array_free(array* array)
{
    free(array->data);
    array->size = 0;
}