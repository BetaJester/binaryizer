// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
// for details.

#ifdef _WIN32
#pragma comment ( lib, "Shlwapi.lib" )
#endif

#include <fstream>
#include <sstream>

#include <benchmark/benchmark.h>
#include <bj/binaryizer/iostream_binaryizer.hpp>
#include <bj/binaryizer/midiint.hpp>

static void BM_stringstream_uint_low(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 5 };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_uint_medium(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 50000 };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_midi_uint_low(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 5 };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_midi_uint_medium(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 50000 };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_uint_huge(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 0xFFFFFFFF };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_midi_uint_huge(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 0xFFFFFFFF };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_uint_low(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 5 };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_uint_medium(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 50000 };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_midi_uint_low(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 5 };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_midi_uint_medium(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 50000 };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_uint_huge(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 0xFFFFFFFF };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_midi_uint_huge(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        unsigned int num{ 0xFFFFFFFF };
        unsigned int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

// Signed

static void BM_stringstream_int_low(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 5 };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_int_medium(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 50000 };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_midi_int_low(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 5 };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_midi_int_medium(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 50000 };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_int_huge(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 0xFFFFFF };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_stringstream_midi_int_huge(benchmark::State &state) {
    bj::iostream_binaryizer<std::stringstream> iobin(std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 0xFFFFFF };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_int_low(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 5 };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_int_medium(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 50000 };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_midi_int_low(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 5 };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_midi_int_medium(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 50000 };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_int_huge(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 0xFFFFFF };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(num);
        iobin.in(in);
        benchmark::DoNotOptimize(in);
    }
}

static void BM_fstream_midi_int_huge(benchmark::State &state) {
    bj::iostream_binaryizer<std::fstream> iobin("testoutput.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    for (auto _ : state) {
        iobin.stream().clear();
        int num{ 0xFFFFFF };
        int in{};
        benchmark::DoNotOptimize(num);
        iobin.out(bj::midiint(num));
        iobin.in(bj::midiint(in));
        benchmark::DoNotOptimize(in);
    }
}

BENCHMARK(BM_stringstream_uint_low);
BENCHMARK(BM_stringstream_midi_uint_low);
BENCHMARK(BM_stringstream_uint_medium);
BENCHMARK(BM_stringstream_midi_uint_medium);
BENCHMARK(BM_stringstream_uint_huge);
BENCHMARK(BM_stringstream_midi_uint_huge);
BENCHMARK(BM_fstream_uint_low);
BENCHMARK(BM_fstream_midi_uint_low);
BENCHMARK(BM_fstream_uint_medium);
BENCHMARK(BM_fstream_midi_uint_medium);
BENCHMARK(BM_fstream_uint_huge);
BENCHMARK(BM_fstream_midi_uint_huge);
// Signed.
BENCHMARK(BM_stringstream_int_low);
BENCHMARK(BM_stringstream_midi_int_low);
BENCHMARK(BM_stringstream_int_medium);
BENCHMARK(BM_stringstream_midi_int_medium);
BENCHMARK(BM_stringstream_int_huge);
BENCHMARK(BM_stringstream_midi_int_huge);
BENCHMARK(BM_fstream_int_low);
BENCHMARK(BM_fstream_midi_int_low);
BENCHMARK(BM_fstream_int_medium);
BENCHMARK(BM_fstream_midi_int_medium);
BENCHMARK(BM_fstream_int_huge);
BENCHMARK(BM_fstream_midi_int_huge);