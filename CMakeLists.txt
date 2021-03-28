# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
# for details.

cmake_minimum_required(VERSION 3.18)

project(binaryizer)

option(BINARYIZER_BUILD_TESTS "Build tests for binaryizer" OFF)
option(BINARYIZER_BUILD_BENCHMARKS "Build benchmarks for binaryizer" OFF)

include(FetchContent)
FetchContent_Declare(
	pwropt
	GIT_REPOSITORY https://github.com/BetaJester/pwropt.git
	GIT_TAG main
)
FetchContent_MakeAvailable(pwropt)

add_library(binaryizer INTERFACE)
add_library(bj::binaryizer ALIAS binaryizer)
target_include_directories(binaryizer INTERFACE "include")
target_sources(binaryizer INTERFACE 
	"include/bj/binaryizer/binaryizer.hpp"
	"include/bj/binaryizer/bit_cast.hpp"
	"include/bj/binaryizer/endian.hpp"
	"include/bj/binaryizer/settings.hpp"
	"include/bj/binaryizer/expraw.hpp"
	"include/bj/binaryizer/ibinaryizer.hpp"
	"include/bj/binaryizer/iostream_binaryizer.hpp"
	"include/bj/binaryizer/midiint.hpp"
	"include/bj/binaryizer/obinaryizer.hpp"
	"include/bj/binaryizer/stl/array.hpp"
	"include/bj/binaryizer/stl/basic_string.hpp"
	"include/bj/binaryizer/stl/bitset.hpp"
	"include/bj/binaryizer/stl/deque.hpp"
	"include/bj/binaryizer/stl/forward_list.hpp"
	"include/bj/binaryizer/stl/inner_container.hpp"
	"include/bj/binaryizer/stl/list.hpp"
	"include/bj/binaryizer/stl/map.hpp"
	"include/bj/binaryizer/stl/multimap.hpp"
	"include/bj/binaryizer/stl/multiset.hpp"
	"include/bj/binaryizer/stl/pair.hpp"
	"include/bj/binaryizer/stl/priority_queue.hpp"
	"include/bj/binaryizer/stl/queue.hpp"
	"include/bj/binaryizer/stl/set.hpp"
	"include/bj/binaryizer/stl/size.hpp"
	"include/bj/binaryizer/stl/stack.hpp"
	"include/bj/binaryizer/stl/tuple.hpp"
	"include/bj/binaryizer/stl/unique_ptr.hpp"
	"include/bj/binaryizer/stl/unordered_map.hpp"
	"include/bj/binaryizer/stl/unordered_multimap.hpp"
	"include/bj/binaryizer/stl/unordered_multiset.hpp"
	"include/bj/binaryizer/stl/unordered_set.hpp"
	"include/bj/binaryizer/stl/valarray.hpp"
	"include/bj/binaryizer/stl/vector.hpp"
	"include/bj/binaryizer/traits_n_concepts.hpp"
	"include/bj/binaryizer/stackstack.hpp"
)
pwropt_target_compile_options(binaryizer INTERFACE pwr_lefticus)
pwropt_target_cxx_latest(binaryizer INTERFACE)

if (${BINARYIZER_BUILD_TESTS})
	enable_testing()
	add_subdirectory("tests/unittests")
	add_subdirectory("tests/standalones")
endif()

if (${BINARYIZER_BUILD_BENCHMARKS})
	add_subdirectory("benchmarks")
endif()