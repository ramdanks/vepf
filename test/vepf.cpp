#include "catch_amalgamated.hpp"

#include "../src/vepf.h"
#include <fstream>
#include <string>
#include <exception>

#define PRIME_LIST_FILEPATH "test/primes-to-100k.txt"

void validator(std::string_view filepath, std::function<bool(uint64_t)> prime_validator) 
{
    std::fstream fstream;
    fstream.open(filepath, std::ios::in);

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
        bool real       = prime_validator(i);
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

TEST_CASE ("utility truth", "[utility]")
{
    validator(PRIME_LIST_FILEPATH, is_prime);
}

TEST_CASE ("vepf truth", "[vepf]")
{
    array primes = vepf_generate(1e6);
    validator(PRIME_LIST_FILEPATH, [&](auto value){ return vepf_is_prime(value, primes); });
    array_free(&primes);
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