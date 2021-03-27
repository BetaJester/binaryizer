# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
# for details.

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)

include(FetchContent)
FetchContent_Declare(
	pwropt
	GIT_REPOSITORY https://github.com/BetaJester/pwropt.git
	GIT_TAG main
)
FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG master
)
FetchContent_Declare(
	benchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG master
)
FetchContent_MakeAvailable(fmt pwropt benchmark)

add_executable(binaryizer_benchmarks
	"main.cpp"
)
pwropt_target_compile_options(binaryizer_benchmarks PRIVATE pwr_werror pwr_lefticus)
pwropt_target_cxx_latest(binaryizer_benchmarks PRIVATE)
target_link_libraries(binaryizer_benchmarks PRIVATE bj::binaryizer fmt::fmt benchmark::benchmark benchmark::benchmark_main)

