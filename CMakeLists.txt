# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
# for details.

cmake_minimum_required(VERSION 3.18)

project(binaryizer)

include(FetchContent)
FetchContent_Declare(
	pwropt
	GIT_REPOSITORY https://github.com/BetaJester/pwropt.git
	GIT_TAG main
)
FetchContent_MakeAvailable(pwropt)

add_library(binaryizer INTERFACE)
target_include_directories(binaryizer INTERFACE "include")
target_sources(binaryizer INTERFACE "include/binaryizer/binaryizer.hpp" "include/binaryizer/fstream_binaryizer.hpp")
pwropt_target_compile_options(binaryizer INTERFACE pwr_lefticus)
pwropt_target_cxx_latest(binaryizer INTERFACE)