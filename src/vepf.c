#include "vepf.h"
#include <math.h>
#include <stdlib.h>
#include "bbool.h"

#define VEPF_SIZE_MEM(size)         size / 8 / 2
#define VEPF_SIZE_PRIME(size_mem)   size_mem * 8 * 2

bool is_prime(int64_t value)
{
    if (value <= 1)
        return false;

    if (value == 2)
        return true;

    if (value % 2 == 0)
        return false;


    for (uint64_t i = 3; i <= value / 2; i += 2)
        if (value % i == 0)
            return false;
    
    return true;
}

bool vepf_is_prime(int64_t value, array array)
{
    if (value <= 1)
        return false;

    if (value == 2)
        return true;

    if (value % 2 == 0)
        return false;

    // opt store primeness for odd numbers only (index 1 == 3, index 2 == 5, index 3 == 7, and so on)
    size_t index = value / 2;

    return get_bbool(index, array.data);
}

array vepf_generate(size_t size)
{
    array buf = vepf_allocate(size);
    return vepf_generate_set(buf);
}

array vepf_generate_set(array array)
{
    uint8_t* prime_buf      = (uint8_t*) array.data;
    const size_t size_prime = VEPF_SIZE_PRIME(array.size);
    const size_t size_sqrt  = sqrtl(size_prime) + 1.0;

    for (size_t i = 0; i < array.size; ++i)
        prime_buf[i] = 0xFF;

    for (size_t i = 3; i < size_sqrt; i += 2)
        if (get_bbool(i / 2, prime_buf))
            for (size_t j = i * i / 2; j < array.size; j += i)
                set_false_bbool(j, prime_buf);

    return array;
}

array vepf_allocate(size_t size)
{
    size_t size_mem = VEPF_SIZE_MEM(size);
    void* mem = malloc(size_mem);
    return (array) { mem, mem == NULL ? 0 : size_mem };
}