#include "catch_amalgamated.hpp"

#include "../src/vepf.h"
#include <fstream>
#include <string>
#include <exception>

#define PRIME_LIST_FILEPATH "test/primes-to-100k.txt"

TEST_CASE ("vepf truth", "[vepf]")
{
    std::fstream fstream;
    fstream.open(PRIME_LIST_FILEPATH, std::ios::in);

    if (fstream.is_open() == false)
    {
        std::stringstream info;
        info << "Can't read file: " << PRIME_LIST_FILEPATH;
        throw std::runtime_error(info.str());
    }

    std::string read;
    std::getline(fstream, read);

    for (uint64_t i = 0, value = std::stoull(read); true; ++i)
    {   
        bool real       = is_prime(i);
        bool expected   = i == value;

        if (real != expected)
        {
            std::stringstream info;
            info << "primeness of " << i << ": expected:" << expected << " | real:" << real;
            FAIL(info.str());
        }

        REQUIRE(real == expected);
        
        if (i == value)
        {
            if (!std::getline(fstream, read))
                break;
            value = std::stoull(read);
        }
    }
}

TEST_CASE ("vepf performance", "[vepf][!benchmark]")
{
    array e3 = vepf_allocate(1e3);
    array e6 = vepf_allocate(1e6);
    array e9 = vepf_allocate(1e9);

    BENCHMARK("Generate Prime 1e3") { return vepf_generate_set(e3); };
    BENCHMARK("Generate Prime 1e6") { return vepf_generate_set(e6); };
    BENCHMARK("Generate Prime 1e9") { return vepf_generate_set(e9); };
}