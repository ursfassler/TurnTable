cmake_minimum_required(VERSION 3.18.4)

project(feature_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# see: https://github.com/cucumber/cucumber-cpp/issues/36
# see: https://github.com/cucumber/cucumber-cpp/blob/c7ad59e5bc304f35b16e2230640d47172bc2cfe8/examples/FeatureShowcase/CMakeLists.txt
function(add_cucumber_executable target_name)
	add_executable(${target_name} ${ARGN})
	foreach(file_name ${ARGN})
		get_filename_component(prefix ${file_name} NAME_WE)
		set_source_files_properties(${file_name} PROPERTIES COMPILE_FLAGS "-DCUKE_OBJECT_PREFIX=_${prefix}")
	endforeach()
endfunction()

# Note: For the moment there are no source files #####################
#file(GLOB_RECURSE all_cpp_files CONFIGURE_DEPENDS REGEX "src/*.cpp")
set(src_files "")
#foreach(cpp_file ${all_cpp_files})
#	list(APPEND src_files ${cpp_file})
#endforeach()

file(GLOB_RECURSE all_cpp_files CONFIGURE_DEPENDS REGEX "features/*.cpp")
set(step_files "")
foreach(cpp_file ${all_cpp_files})
	if(${cpp_file} MATCHES "__steps.cpp$")
		list(APPEND step_files ${cpp_file})
	else()
		list(APPEND src_files ${cpp_file})
	endif()
endforeach()

file(GLOB_RECURSE h_files CONFIGURE_DEPENDS "src/*.h")
set(include_dirs "")
foreach(h_file_path ${h_files})
	get_filename_component(dir_path ${h_file_path} PATH)
	set(include_dirs ${include_dirs} ${dir_path})
endforeach()

set(mock_include_dirs "features/steps/mocks" )

# Note:
# To prevent ambiguous error: An executable is built for every step-file.
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY steps)
foreach(step_file ${step_files})
	get_filename_component(target_name ${step_file} NAME_WE)
	add_cucumber_executable(${target_name} ${step_file} ${src_files})
	target_include_directories(${target_name} PRIVATE ${include_dirs})
	target_include_directories(${target_name} PRIVATE ${mock_include_dirs})
	target_link_libraries(${target_name} PRIVATE
		cucumber-cpp
		gtest
		boost_system
		boost_program_options
	)
	target_compile_options(
		${target_name}
		PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Werror
		-Wno-deprecated
		-Wno-deprecated-declarations
		-fmax-errors=3
	)
endforeach()