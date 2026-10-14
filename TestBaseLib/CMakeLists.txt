# Linux build of TestBaseLib (BaseLib + TestLib + TestBaseLib).
#
# BaseLib is 32-bit only, so everything is built with -m32 (needs g++-multilib).
#
#   cmake -S test/TestBaseLib -B build/TestBaseLib -G Ninja -DCMAKE_BUILD_TYPE=Debug
#   cmake --build build/TestBaseLib
#   ctest --test-dir build/TestBaseLib --output-on-failure
#
# Add -DBASELIB_ASAN=ON for AddressSanitizer / LeakSanitizer (TestBaseLib.cpp
# calls __lsan_do_leak_check() when built with it).
#
# Source lists are read from the .vcxproj files so Visual Studio stays the
# source of truth.  Test directories contain .cpp files that are test data
# (e.g. SDCard.cpp), so never glob *.cpp to find sources.

cmake_minimum_required(VERSION 3.16)
project(TestBaseLib CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

option(BASELIB_ASAN "Build with AddressSanitizer and LeakSanitizer" OFF)

get_filename_component(CODAPHELA_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
set(COMMON_DIR "${CODAPHELA_ROOT}/commonlibraries")
set(BASELIB_DIR "${COMMON_DIR}/BaseLib")
set(TESTLIB_DIR "${COMMON_DIR}/TestLib")
set(TESTBASELIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/TestBaseLib")


# Reads <ClCompile Include="..."/> entries from a .vcxproj and resolves them
# against the files on disk case-insensitively (Windows paths are not
# case-sensitive, e.g. the project says CPPWhitespace.cpp but the file is
# CPPWhiteSpace.cpp).  Files named in EXCLUDE (paths relative to the project,
# any case) are left out.
function(vcxproj_sources OUT_VAR VCXPROJ)
	cmake_parse_arguments(ARG "" "" "EXCLUDE" ${ARGN})
	get_filename_component(PROJ_DIR "${VCXPROJ}" DIRECTORY)

	file(GLOB_RECURSE DISK_FILES RELATIVE "${PROJ_DIR}" "${PROJ_DIR}/*.cpp")
	foreach(DISK_FILE ${DISK_FILES})
		string(TOLOWER "${DISK_FILE}" KEY)
		set("DISK_${KEY}" "${DISK_FILE}")
	endforeach()

	set(EXCLUDED "")
	foreach(EXCLUDE_FILE ${ARG_EXCLUDE})
		string(TOLOWER "${EXCLUDE_FILE}" KEY)
		list(APPEND EXCLUDED "${KEY}")
	endforeach()

	file(STRINGS "${VCXPROJ}" LINES REGEX "<ClCompile Include=\"[^\"]+\"")
	set(SOURCES "")
	foreach(LINE ${LINES})
		string(REGEX REPLACE ".*<ClCompile Include=\"([^\"]+)\".*" "\\1" SOURCE "${LINE}")
		string(REPLACE "\\" "/" SOURCE "${SOURCE}")
		string(TOLOWER "${SOURCE}" KEY)
		if(KEY IN_LIST EXCLUDED)
			continue()
		endif()
		if(NOT DEFINED "DISK_${KEY}")
			message(FATAL_ERROR "${VCXPROJ} lists ${SOURCE} but it was not found on disk")
		endif()
		list(APPEND SOURCES "${PROJ_DIR}/${DISK_${KEY}}")
	endforeach()

	set(${OUT_VAR} ${SOURCES} PARENT_SCOPE)
endfunction()


vcxproj_sources(BASELIB_SOURCES "${BASELIB_DIR}/BaseLib.vcxproj"
	EXCLUDE
		# Winsock.
		Socket.cpp
		ConnectSocket.cpp
		ListenSocket.cpp
		# Win32 only.
		WindowsError.cpp
)

vcxproj_sources(TESTLIB_SOURCES "${TESTLIB_DIR}/TestLib.vcxproj")

vcxproj_sources(TESTBASELIB_SOURCES "${TESTBASELIB_DIR}/TestBaseLib.vcxproj"
	EXCLUDE
		TestWindowsFiles.cpp
)


# Matches the Visual Studio configurations, except BREAK_ON_ERROR and
# BREAK_ON_WARNING: on Linux BREAK() raises SIGINT, which kills the test run
# when no debugger is attached.
add_library(baselib_options INTERFACE)
target_include_directories(baselib_options INTERFACE "${COMMON_DIR}")
target_compile_definitions(baselib_options INTERFACE
	LINUX_GNU_32
	$<$<CONFIG:Debug>:_DEBUG>
	$<$<CONFIG:Debug>:DEBUG>
	$<$<NOT:$<CONFIG:Debug>>:NDEBUG>
)
target_compile_options(baselib_options INTERFACE -m32 -fpermissive -w)
target_link_options(baselib_options INTERFACE -m32)
if(BASELIB_ASAN)
	target_compile_options(baselib_options INTERFACE -fsanitize=address -fno-omit-frame-pointer)
	target_link_options(baselib_options INTERFACE -fsanitize=address)
endif()


add_library(BaseLib STATIC ${BASELIB_SOURCES})
target_link_libraries(BaseLib PUBLIC baselib_options)

# Uses AVX intrinsics unconditionally; MSVC allows that without a flag, g++ does not.
set_source_files_properties("${BASELIB_DIR}/FastMemcpy.cpp" PROPERTIES COMPILE_OPTIONS -mavx)

add_library(TestLib STATIC ${TESTLIB_SOURCES})
target_link_libraries(TestLib PUBLIC BaseLib)

add_executable(TestBaseLib ${TESTBASELIB_SOURCES})
target_link_libraries(TestBaseLib PRIVATE TestLib BaseLib)

# The tests read their input (Input/, Finder/, *.xml ...) relative to the
# project directory, as Visual Studio does.
enable_testing()
add_test(NAME TestBaseLib COMMAND TestBaseLib WORKING_DIRECTORY "${TESTBASELIB_DIR}")
