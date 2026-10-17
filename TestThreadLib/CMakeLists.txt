# Linux build of TestThreadLib (BaseLib + TestLib + ThreadLib + TestThreadLib).
#
# BaseLib is 32-bit only, so everything is built with -m32 (needs g++-multilib).
#
#   cmake -S test/TestThreadLib -B build/TestThreadLib -G Ninja -DCMAKE_BUILD_TYPE=Debug
#   cmake --build build/TestThreadLib
#   ctest --test-dir build/TestThreadLib -V
#
# TestThreadLib must be run as 'TestThreadLib --test param1 --param:2' (TestMainProcessDirector
# checks those parameters); the other redirects are
# the child processes that the tests start.
#
# Add -DBASELIB_ASAN=ON for AddressSanitizer and LeakSanitizer.
#
# Source lists are read from the .vcxproj files so Visual Studio stays the
# source of truth.  Building re-runs the configure step automatically when a
# .vcxproj changes.  Test directories can contain .cpp files that are test data,
# so never glob *.cpp to find sources.

cmake_minimum_required(VERSION 3.16)
project(TestThreadLib CXX)

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
set(THREADLIB_DIR "${COMMON_DIR}/ThreadLib")
set(TESTTHREADLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/TestThreadLib")


# Reads <ClCompile Include="..."/> entries from a .vcxproj and resolves them
# against the files on disk case-insensitively (Windows paths are not
# case-sensitive).  Files named in EXCLUDE (paths relative to the project,
# any case) are left out.
function(vcxproj_sources OUT_VAR VCXPROJ)
	cmake_parse_arguments(ARG "" "" "EXCLUDE" ${ARGN})
	get_filename_component(PROJ_DIR "${VCXPROJ}" DIRECTORY)

	# Re-run the configure step when Visual Studio adds or removes files.
	set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${VCXPROJ}")

	file(GLOB_RECURSE DISK_FILES RELATIVE "${PROJ_DIR}" "${PROJ_DIR}/*.cpp" "${PROJ_DIR}/*.c")
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


vcxproj_sources(BASELIB_SOURCES "${BASELIB_DIR}/BaseLib.vcxproj")

vcxproj_sources(TESTLIB_SOURCES "${TESTLIB_DIR}/TestLib.vcxproj")

vcxproj_sources(THREADLIB_SOURCES "${THREADLIB_DIR}/ThreadLib.vcxproj")

vcxproj_sources(TESTTHREADLIB_SOURCES "${TESTTHREADLIB_DIR}/TestThreadLib.vcxproj")


# Matches the Visual Studio configurations, except BREAK_ON_ERROR and
# BREAK_ON_WARNING: on Linux BREAK() raises SIGTRAP, which kills the test run
# when no debugger is attached.
add_library(baselib_options INTERFACE)
target_include_directories(baselib_options INTERFACE "${COMMON_DIR}")
target_compile_definitions(baselib_options INTERFACE
	LINUX_GNU_32
	$<$<CONFIG:Debug>:_DEBUG>
	$<$<CONFIG:Debug>:DEBUG>
	$<$<NOT:$<CONFIG:Debug>>:NDEBUG>
)
# -msse2 -mfpmath=sse: MSVC uses SSE2 for 32-bit code.  The x87 FPU keeps float
# constants at long double precision, so float comparisons would differ.
# -fno-strict-aliasing: MSVC never optimises on the strict aliasing rule and the
# code relies on that (e.g. (CUnknown**)&pcTyped), so optimised builds break without it.
# -Wno-ignored-attributes: g++ drops ALIGN_64 when int64/uint64/float64 is a
# template argument.  Templates that store such a type by value use MSVC_ALIGN
# instead (see PrimitiveTypes.h), so the warning only reports the drop.
target_compile_options(baselib_options INTERFACE -m32 -msse2 -mfpmath=sse -fno-strict-aliasing -Wno-ignored-attributes -w)
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

find_package(Threads REQUIRED)

add_library(ThreadLib STATIC ${THREADLIB_SOURCES})
target_link_libraries(ThreadLib PUBLIC BaseLib Threads::Threads)

add_executable(TestThreadLib ${TESTTHREADLIB_SOURCES})
target_link_libraries(TestThreadLib PRIVATE TestLib ThreadLib BaseLib)

# The tests read their input relative to the project directory, as Visual
# Studio does.
enable_testing()
add_test(NAME TestThreadLib COMMAND TestThreadLib --test param1 --param:2 WORKING_DIRECTORY "${TESTTHREADLIB_DIR}")
