#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "../../src/vepf.h"
#include <fstream>
#include <sstream>
#include <exception>

#define PRIME_LIST_FILEPATH "testfile/primes-to-100k.txt"

void validator(std::string_view filepath, std::function<bool(uint64_t)> prime_validator) 
{
    std::fstream fstream;
    fstream.open(filepath.data(), std::ios::in);

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

    SECTION("prime generator")
    {
        BENCHMARK("Generate Prime 1e3") { return vepf_generate_set(e3); };
        BENCHMARK("Generate Prime 1e6") { return vepf_generate_set(e6); };
        BENCHMARK("Generate Prime 1e9") { return vepf_generate_set(e9); };
    }

    SECTION("prime validation")
    {
        BENCHMARK_ADVANCED("Prime Validation Negative")(Catch::Benchmark::Chronometer meter)
        {
            auto value = GENERATE(random(-1e6, -1e1));
            meter.measure([&](void){ return vepf_is_prime(value, e9); });
        };
        BENCHMARK_ADVANCED("Prime Validation Even")(Catch::Benchmark::Chronometer meter)
        {
            auto value = GENERATE(filter([](auto i){ return (uint64_t) i % 2 == 0; }, random(1e1, 1e6)));
            meter.measure([&](void){ return vepf_is_prime(value, e9); });
        };
        BENCHMARK_ADVANCED("Prime Validation Odd")(Catch::Benchmark::Chronometer meter)
        {
            auto value = GENERATE(filter([](auto i){ return (uint64_t) i % 2 == 1; }, random(1e1, 1e6)));
            meter.measure([&](void){ return vepf_is_prime(value, e9); });
        };
    }
}