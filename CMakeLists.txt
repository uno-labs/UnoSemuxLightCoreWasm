cmake_minimum_required(VERSION 3.16)

project(UnoSemuxLightCoreWasm
        VERSION 0.1.0
        DESCRIPTION "C++ common utilities and types library"
        LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE      ON)
set(CMAKE_BUILD_PARALLEL_LEVEL  3)

set(CMAKE_SYSTEM_NAME Emscripten)
set(CMAKE_SYSTEM_PROCESSOR wasm32)
set(CMAKE_BUILD_TYPE Release)

set(EMSCRIPTEN_ROOT             $ENV{EMSDK}/upstream/emscripten)
set(CMAKE_TOOLCHAIN_FILE        ${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake)
set(CMAKE_CXX_COMPILER          em++)
set(CMAKE_C_COMPILER            emcc)
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_RELEASE               "" CACHE STRING "Uno-labs-overridden CMAKE_C_FLAGS_RELEASE" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE   "" CACHE STRING "Uno-labs-overridden CMAKE_SHARED_LINKER_FLAGS_RELEASE" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_RELEASE   "" CACHE STRING "Uno-labs-overridden CMAKE_SHARED_LINKER_FLAGS_RELEASE" FORCE)
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
    -Wno-comment )

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
    --bind )

# Find all *.cpp files in project
file (GLOB_RECURSE SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
        UNOSEMUXLIGHTCOREWASM_LIBRARY
        HAVE_NETINET_IN_H
        _GLIBCXX_USE_NANOSLEEP
        __EMSCRIPTEN__
        RELEASE_BUILD
        NDEBUG )

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${LINK_FLAGS})

#------------------------ RELEASE ---------------------
message(STATUS "[${PROJECT_NAME}]: ***************** Build mode ${MODE_BUILD} *****************")
string(TOUPPER ${CMAKE_BUILD_TYPE} MODE_BUILD)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${MODE_BUILD}_BUILD)

#------------------------ LIBS ---------------------
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${GpCore2_INCLUDES} 
        ${utf8proc_INCLUDES}
        ${sodium_INCLUDES}
        ${GpCryptoCore_INCLUDES}
        ${UnoSemuxLightCore_INCLUDES} )

target_link_directories(${PROJECT_NAME}
    PRIVATE
        ${GpCore2_LIBS} 
        ${utf8proc_LIBS}
        ${sodium_LIBS}
        ${GpCryptoCore_LIBS}
        ${UnoSemuxLightCore_LIBS} )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        GpCore2
        utf8proc
        sodium 
        GpCryptoCore
        UnoSemuxLightCore )

message(STATUS "[${PROJECT_NAME}]: Target name:              " ${PROJECT_NAME})
message(STATUS "[${PROJECT_NAME}]: Target arch:              " ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "[${PROJECT_NAME}]: Target OS:                " ${CMAKE_SYSTEM_NAME})
message(STATUS "[${PROJECT_NAME}]: C++ standart:             " ${CMAKE_CXX_STANDARD})
message(STATUS "[${PROJECT_NAME}]: GCC C compiler version:   " ${CMAKE_C_COMPILER})
message(STATUS "[${PROJECT_NAME}]: GCC C++ compiler version: " ${CMAKE_CXX_COMPILER})


#------------------------ INSTALL  ---------------------
set(DISTDIR "${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin/${DISTDIR} )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/UnoSemuxLightCoreWasm.wasm
        DESTINATION bin/${DISTDIR} )