// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#include <benchmark/benchmark.h>

#include "io.hpp"

static void BM_Buffered_fstream_output_uint_unbuffered(benchmark::State &state) {
    auto iobin = get_iobin_ofstream();
    unsigned int num{ 5 };
    for (auto _ : state) {
        benchmark::DoNotOptimize(num);
        iobin(num);
    }
}

static void BM_Buffered_fstream_output_uint_buffered(benchmark::State &state) {
    auto iobin = get_iobin_buffered_ofstream();
    unsigned int num{ 5 };
    for (auto _ : state) {
        benchmark::DoNotOptimize(num);
        iobin(num);
    }
}

static void BM_Buffered_fstream_input_uint_unbuffered(benchmark::State &state) {
    unsigned int num{ 5 };
    {
        auto iobin = get_iobin_ofstream();
        // Create a 50 meg file.
        for (std::size_t i{}; i < 100'000'000; ++i) {
            iobin(num);
        }
    }
    num = 0;
    auto iobin = get_iobin_ifstream();
    for (auto _ : state) {
        benchmark::DoNotOptimize(num);
        iobin(num);
        assert(num == 5);
    }
}

static void BM_Buffered_fstream_input_uint_buffered(benchmark::State &state) {
    unsigned int num{ 5 };
    {
        auto iobin = get_iobin_buffered_ofstream();
        // Create a 50 meg file.
        for (std::size_t i{}; i < 100'000'000; ++i) {
            iobin(num);
        }
    }
    num = 0;
    auto iobin = get_iobin_buffered_ifstream();
    for (auto _ : state) {
        benchmark::DoNotOptimize(num);
        iobin(num);
    }
}


BENCHMARK(BM_Buffered_fstream_output_uint_unbuffered);
BENCHMARK(BM_Buffered_fstream_output_uint_buffered);
BENCHMARK(BM_Buffered_fstream_input_uint_unbuffered);
BENCHMARK(BM_Buffered_fstream_input_uint_buffered);