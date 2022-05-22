/**
 * @file vepf.h
 * @author Ramadhan Kalih Sewu (gitub.com/ramdanks)
 * @brief 
 * @version 0.1
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef VEPF_H
#define VEPF_H

#include "array.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 
 * 
 * @param value 
 * @return true 
 * @return false 
 */
bool is_prime(int64_t value);

/**
 * @brief 
 * 
 * @param value 
 * @param array 
 * @return true 
 * @return false 
 */
bool vepf_is_prime(int64_t value, array array);

/**
 * @brief calculate primeness for a number with the size specified by size.
 * This only contains odd numbers lookup table, index 0 means the primeness of value 1, index 1 means the primeness of value 3, and so on.
 * Example syntax: array.data[0] == is number 1 prime?
 * 
 * @param size 
 * @return array 
 */
array vepf_generate(size_t size);

/**
 * @brief 
 * 
 * @param array 
 * @return array 
 */
array vepf_generate_set(array array);

/**
 * @brief 
 * 
 * @param size 
 * @return array 
 */
array vepf_allocate(size_t size);

#ifdef __cplusplus
}
#endif

#endif