#include "vepf.h"
#include <math.h>
#include <stdlib.h>
#include "bbool.h"

bool is_prime(int64_t value)
{
    if (value <= 1)
        return false;

    if (value == 2)
        return true;

    if (value % 2 == 0)
        return false;


    for (uint64_t i = 0; i <= value / 2; ++i)
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

array vepf_generate(const size_t size)
{
    const size_t size_sqrt = sqrtl(size) + 1.0;
    const size_t size_mem = size / 8 / 2;

    uint8_t* primes = malloc(size_mem);

    for (size_t i = 0; i < size_mem; ++i)
        primes[i] = 0xFF;

    for (size_t i = 3; i < size_sqrt; i += 2)
        if (get_bbool(i / 2, primes))
            for (size_t j = i * i / 2; j < size_mem; j += i)
                set_false_bbool(j, primes);

    array ret = { primes, size_mem };
    return ret;
}