#include "bbool.h"
#include <stdint.h>

bool get_bbool(size_t index, void* array)
{
    size_t major_idx = index / 8;
    size_t minor_idx = index % 8;

    uint8_t* data = (uint8_t*) array;
    return data[major_idx] & (1 << minor_idx);
}

void set_bbool(size_t index, void* array, bool value)
{
    value ? set_true_bbool(index, array) : set_false_bbool(index, array);
}

void set_true_bbool(size_t index, void* array)
{
    size_t major_idx = index / 8;
    size_t minor_idx = index % 8;

    uint8_t* data = (uint8_t*) array;
    data[major_idx] |= (1 << minor_idx);
}

void set_false_bbool(size_t index, void* array)
{
    size_t major_idx = index / 8;
    size_t minor_idx = index % 8;

    uint8_t* data = (uint8_t*) array;
    data[major_idx] &= ~(1 << minor_idx);
}

void set_toggle_bbool(size_t index, void* array)
{
    size_t major_idx = index / 8;
    size_t minor_idx = index % 8;

    uint8_t* data = (uint8_t*) array;
    data[major_idx] ^= (1 << minor_idx);
}