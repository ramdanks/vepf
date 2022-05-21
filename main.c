#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "vepf.h"

#define KILOBYTE    1000
#define MEGABYTE    1000 * KILOBYTE
#define GIGABYTE    1000 * MEGABYTE

int main(int argc, char* argv[])
{
    array result = vepf_generate(GIGABYTE);
    return ((uint8_t*) result.data)[result.size - 1];
}
