# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/binaryizer
# for details.

# This simply tests that each header file can be ideally be used in isolation.

function(bjb_standalone name)
	set(app ${name}_standalone)
	file(WRITE "standalone.cpp" "#include <bj/binaryizer/${name}.hpp>")
	add_library(${app} "standalone.cpp")
	target_compile_definitions(${app} PRIVATE STANDALONE_HEADER=${name})
	pwropt_target_compile_options(${app} PRIVATE pwr_wall pwr_werror)
	pwropt_target_cxx_latest(${app} PRIVATE)
	target_link_libraries(${app} PRIVATE bj::binaryizer)
endfunction()

file(GLOB headers "../../include/bj/binaryizer/*.hpp")
foreach(header ${headers})
	get_filename_component(cleanheader "${header}" NAME_WE)
	bjb_standalone(${cleanheader})
endforeach()