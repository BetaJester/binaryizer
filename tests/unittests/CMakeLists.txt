# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
# for details.

include(FetchContent)
FetchContent_Declare(
	pwropt
	GIT_REPOSITORY https://github.com/BetaJester/pwropt.git
	GIT_TAG main
)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.x
)
FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG master
)
FetchContent_MakeAvailable(Catch2 fmt)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${Catch2_SOURCE_DIR}/contrib")
include(Catch)
include(CTest)
FetchContent_MakeAvailable(pwropt Catch2)

add_executable(binaryizer_tests 
	"carray.cpp"
	"compare_arrays.hpp"
	"county.hpp"
	"emplace.cpp"
	"emplacey.hpp" 
	"endian.cpp"
	"expbin.cpp"
	"external.cpp"
	"exttester.hpp"
	"main.cpp"
	"midiint.cpp"
	"nobin.hpp"
	"readme.cpp"
	"stackstack.cpp"
	"stl/array.cpp"
	"stl/basic_string.cpp"
	"stl/bitset.cpp"
	"stl/deque.cpp"
	"stl/forward_list.cpp"
	"stl/list.cpp"
	"stl/map.cpp"
	"stl/multimap.cpp"
	"stl/multiset.cpp"
	"stl/priority_queue.cpp"
	"stl/queue.cpp"
	"stl/set.cpp"
	"stl/stack.cpp"
	"stl/tuple.cpp"
	"stl/unique_ptr.cpp"
	"stl/unordered_map.cpp"
	"stl/unordered_multimap.cpp"
	"stl/unordered_multiset.cpp"
	"stl/unordered_set.cpp"
	"stl/valarray.cpp"
	"stl/vector.cpp"
	"stream.cpp"
	"test_iobin.hpp"
	)
pwropt_target_compile_options(binaryizer_tests PRIVATE pwr_werror pwr_lefticus)
pwropt_target_cxx_latest(binaryizer_tests PRIVATE)
target_link_libraries(binaryizer_tests PRIVATE Catch2::Catch2 bj::binaryizer fmt::fmt)

catch_discover_tests(binaryizer_tests)

