#pragma once
#ifndef BBOOL_H
#define BBOOL_H

#include "array.h"
#include <stddef.h>
#include <stdbool.h>

bool get_bbool(size_t index, void* array);

void set_bbool(size_t index, void* array, bool value);

void set_true_bbool(size_t index, void* array);

void set_false_bbool(size_t index, void* array);

void set_toggle_bbool(size_t index, void* array);

#endif