cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME			UnoSemuxLightCoreWasm)
set(PROJECT_VERSION			0.1.1)
set(PROJECT_DESCRIPTION		"UnoSemuxLightCoreWasm")
set(PROJECT_NAME_DEFINE		UNOSEMUXLIGHTCOREWASM_LIBRARY)

#set(CMAKE_VERBOSE_MAKEFILE     ON)
set(CMAKE_BUILD_PARALLEL_LEVEL  1)
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find all *.cpp and *.hpp files in project
file (GLOB_RECURSE SOURCES *.cpp)
file (GLOB_RECURSE INCLUDES *.hpp)

if (BUILD_RELEASE_WASM32)
	set(NAME_OS						Browser)
	set(NAME_ARC					wasm32)
	set(CMAKE_BUILD_TYPE            Release)
	set(CMAKE_CXX_COMPILER          em++)
	set(CMAKE_C_COMPILER            emcc)
	set(EMSCRIPTEN_ROOT             $ENV{EMSDK}/upstream/emscripten)
	set(CMAKE_TOOLCHAIN_FILE        ${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections -fexceptions -fstrict-aliasing -fstack-clash-protection")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wdouble-promotion -Wswitch-default -Wswitch-enum -Wuninitialized")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-aliasing -Wfloat-equal -Wshadow -Wplacement-new -Wcast-align -Wconversion -Wlogical-op")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wduplicated-branches -Wrestrict -Wnull-dereference -Wno-terminate")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-warning-option -Wno-unused-command-line-argument -Wno-comment")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=0")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-string-literal-operator-template")
	project(${PROJECT_NAME} DESCRIPTION ${PROJECT_DESCRIPTION} LANGUAGES CXX)
	add_executable(${PROJECT_NAME} ${SOURCES})
	string(JOIN " " LINK_FLAGS
		-s WASM=1
		-s DISABLE_EXCEPTION_CATCHING=0
		-s ERROR_ON_UNDEFINED_SYMBOLS=1
		-s EXTRA_EXPORTED_RUNTIME_METHODS=["UTF16ToString","stringToUTF16"]
		-s ALLOW_MEMORY_GROWTH=1
		-s NO_EXIT_RUNTIME=0
		-O3
		-Wl
		--gc-sections
		--bind
	)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${LINK_FLAGS})
	target_link_libraries(${PROJECT_NAME}
		PUBLIC
			GpCore2
			utf8proc
			sodium
			GpCryptoCore
			UnoSemuxLightCore
	)
else()
	message(FATAL_ERROR "Unknown build type, please set -DBUILD_RELEASE_WASM32=ON")
endif()

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
			${BUILD_TYPE}_BUILD
			${PROJECT_NAME_DEFINE}
			HAVE_NETINET_IN_H
			_GLIBCXX_USE_NANOSLEEP
	)

#------------------------ FILES LOCATIONS ---------------------
set(CMAKE_INSTALL_PREFIX	"${CMAKE_SOURCE_DIR}/../.." CACHE PATH "..." FORCE)
set(TARGET_LIB_DIR          "${CMAKE_INSTALL_PREFIX}/bin")
set(TARGET_EXT_INCLUDE_DIR	"${CMAKE_INSTALL_PREFIX}/inc")

if (NOT EXISTS "${TARGET_EXT_INCLUDE_DIR}")
	file(MAKE_DIRECTORY "${TARGET_EXT_INCLUDE_DIR}")
endif()

set(SP _)
set(OUT_BIN_DIR "${TARGET_LIB_DIR}/${CMAKE_BUILD_TYPE}${SP}${NAME_OS}${SP}${NAME_ARC}")
set(LIBRARY_OUTPUT_PATH ${OUT_BIN_DIR})

#------------------------ LIBS ---------------------
target_include_directories(${PROJECT_NAME}
	PRIVATE
		"${TARGET_EXT_INCLUDE_DIR}"
	)

set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION   ${PROJECT_VERSION})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})

set_target_properties(${PROJECT_NAME}
							PROPERTIES
								OUTPUT_NAME	${PROJECT_NAME}
								SUFFIX		".js"
								ARCHIVE_OUTPUT_DIRECTORY ${OUT_BIN_DIR}
								LIBRARY_OUTPUT_DIRECTORY ${OUT_BIN_DIR}
								RUNTIME_OUTPUT_DIRECTORY ${OUT_BIN_DIR})

message(STATUS "[${PROJECT_NAME}]: ***************** Build mode ${BUILD_TYPE} *****************")
message(STATUS "[${PROJECT_NAME}]: Target name:      " ${PROJECT_NAME}${MODE_SUFFIX} " version " ${PROJECT_VERSION})
message(STATUS "[${PROJECT_NAME}]: Target arch:      " ${NAME_ARC})
message(STATUS "[${PROJECT_NAME}]: Target OS:        " ${NAME_OS})
message(STATUS "[${PROJECT_NAME}]: Build directory:  " ${LIBRARY_OUTPUT_PATH})
message(STATUS "[${PROJECT_NAME}]: C++ standart:     " ${CMAKE_CXX_STANDARD})
message(STATUS "[${PROJECT_NAME}]: GCC C compiler:   " ${CMAKE_C_COMPILER})
message(STATUS "[${PROJECT_NAME}]: GCC C++ compiler: " ${CMAKE_CXX_COMPILER})
message(STATUS "[${PROJECT_NAME}]: GCC linker:       " ${CMAKE_LINKER})

target_link_directories(${PROJECT_NAME}
	PUBLIC
		${LIBRARY_OUTPUT_PATH}
)

#------------------------ INSTALL ---------------------
install(DIRECTORY        "${CMAKE_SOURCE_DIR}"
		DESTINATION      "${TARGET_EXT_INCLUDE_DIR}"
		FILES_MATCHING
				PATTERN "*.hpp"
				PATTERN "*.h"
				PATTERN "CMake*" EXCLUDE
				PATTERN ".git"   EXCLUDE
		)
