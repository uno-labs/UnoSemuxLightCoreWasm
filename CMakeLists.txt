cmake_minimum_required(VERSION 3.16)

project(UnoSemuxLightCoreWasm
	VERSION 0.1.0
	DESCRIPTION "C++ common utilities and types library"
	LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE		ON)
set(CMAKE_BUILD_PARALLEL_LEVEL	3)

set(CMAKE_SYSTEM_NAME Emscripten)
set(CMAKE_SYSTEM_PROCESSOR wasm32)
set(CMAKE_BUILD_TYPE Release)

set(EMSCRIPTEN_ROOT             $ENV{EMSDK}/upstream/emscripten)
set(CMAKE_TOOLCHAIN_FILE        ${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake)
set(CMAKE_CXX_COMPILER          em++)
set(CMAKE_C_COMPILER            emcc)
set(CMAKE_CXX_STANDARD			20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_RELEASE               "" CACHE STRING "Uno-labs-overridden CMAKE_C_FLAGS_RELEASE" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE	"" CACHE STRING "Uno-labs-overridden CMAKE_SHARED_LINKER_FLAGS_RELEASE" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_RELEASE	"" CACHE STRING "Uno-labs-overridden CMAKE_SHARED_LINKER_FLAGS_RELEASE" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE      "" CACHE STRING "Uno-labs-overridden CMAKE_SHARED_LINKER_FLAGS_RELEASE" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE             "" CACHE STRING "Uno-labs-overridden CMAKE_CXX_FLAGS_RELEASE" FORCE)

string(JOIN " " COMPILE_FLAGS
	-std=gnu++20
	-O3
	
	-s WASM=1
	-s ALLOW_MEMORY_GROWTH=1
	-s DISABLE_EXCEPTION_CATCHING=0

	-fexceptions
	-fvisibility=hidden
	-fvisibility-inlines-hidden
	-ffunction-sections
	-fdata-sections
	-fstrict-aliasing
    -fstack-clash-protection

    -Wall
    -Wextra
    -Wdouble-promotion
    -Wswitch-default
    -Wswitch-enum
    -Wuninitialized
    -Wstrict-aliasing
    -Wfloat-equal
    -Wshadow
    -Wplacement-new
    -Wcast-align
    -Wconversion
    -Wlogical-op
    -Wduplicated-cond
    -Wduplicated-branches
    -Wrestrict
    -Wnull-dereference
    -Wno-terminate
    -Wno-unknown-warning-option
    -Wno-unused-command-line-argument
    -Wno-comment
	)

string(JOIN " " LINK_FLAGS
	-s WASM=1
	-s DISABLE_EXCEPTION_CATCHING=0
	-s FULL_ES2=1
	-s ERROR_ON_UNDEFINED_SYMBOLS=1 
	-s EXTRA_EXPORTED_RUNTIME_METHODS=["UTF16ToString","stringToUTF16"]
	-s ALLOW_MEMORY_GROWTH=1
    -s NO_EXIT_RUNTIME=0
	
    -O3
	-Wl

	--gc-sections
	--bind
	)

# Find all *.cpp files in project
file (GLOB_RECURSE SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
	UNOSEMUXLIGHTCOREWASM_LIBRARY
	HAVE_NETINET_IN_H
	_GLIBCXX_USE_NANOSLEEP
	__EMSCRIPTEN__
	RELEASE_BUILD
	NDEBUG
	)

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${LINK_FLAGS})

set(CMAKE_INSTALL_PREFIX    "${CMAKE_SOURCE_DIR}/../.." CACHE PATH "..." FORCE)
set(TARGET_BIN_DIR          "${CMAKE_INSTALL_PREFIX}/bin")
set(TARGET_LIB_DIR          "${CMAKE_INSTALL_PREFIX}/lib")
set(TARGET_EXT_INCLUDE_DIR	"${CMAKE_INSTALL_PREFIX}/inc")

set(CMAKE_BINARY_DIR				${TARGET_BIN_DIR})
set(EXECUTABLE_OUTPUT_PATH			${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH				${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY	${CMAKE_BINARY_DIR})

set(GPCORE2	        GpCore2)
set(UTF8PROC        utf8proc)
set(LIBSODIUM       sodium)
set(GPCRYPTOCORE    GpCryptoCore)
set(SEMUXLIGHTCORE  UnoSemuxLightCore)

target_include_directories(${PROJECT_NAME}
	PRIVATE 
	    "${TARGET_EXT_INCLUDE_DIR}"
        "${TARGET_EXT_INCLUDE_DIR}/${GPCORE2}"
        "${TARGET_EXT_INCLUDE_DIR}/${UTF8PROC}"
	    "${TARGET_EXT_INCLUDE_DIR}/${LIBSODIUM}"
        "${TARGET_EXT_INCLUDE_DIR}/${GPCRYPTOCORE}"
	    "${TARGET_EXT_INCLUDE_DIR}/${SEMUXLIGHTCORE}"
	)

target_link_directories(${PROJECT_NAME}
	PUBLIC ${TARGET_LIB_DIR}
	)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${GPCORE2}
		${UTF8PROC}
        ${LIBSODIUM}
		${GPCRYPTOCORE}
		${SEMUXLIGHTCORE}
	)

message(STATUS "[${PROJECT_NAME}]: Target name:              " ${PROJECT_NAME})
message(STATUS "[${PROJECT_NAME}]: Target arch:              " ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "[${PROJECT_NAME}]: Target OS:                " ${CMAKE_SYSTEM_NAME})
message(STATUS "[${PROJECT_NAME}]: Build directory:          " ${LIBRARY_OUTPUT_PATH})
message(STATUS "[${PROJECT_NAME}]: C++ standart:             " ${CMAKE_CXX_STANDARD})
message(STATUS "[${PROJECT_NAME}]: GCC C compiler version:   " ${CMAKE_C_COMPILER})
message(STATUS "[${PROJECT_NAME}]: GCC C++ compiler version: " ${CMAKE_CXX_COMPILER})
