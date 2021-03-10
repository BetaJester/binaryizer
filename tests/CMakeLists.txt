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
FetchContent_MakeAvailable(Catch2)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${Catch2_SOURCE_DIR}/contrib")
include(Catch)
include(CTest)
FetchContent_MakeAvailable(pwropt Catch2)

add_executable(binaryizer_tests "main.cpp" "stream_tests.cpp")
pwropt_target_compile_options(binaryizer_tests PRIVATE pwr_werror pwr_lefticus)
pwropt_target_cxx_latest(binaryizer_tests PRIVATE)
target_link_libraries(binaryizer_tests PRIVATE Catch2::Catch2 bj::binaryizer)

catch_discover_tests(binaryizer_tests)

