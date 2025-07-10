cmake_minimum_required(VERSION 3.25.1)
project(libasm C CXX ASM)

set(CMAKE_CXX_COMPILER /usr/bin/c++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g3")
set(CMAKE_ASM_COMPILER /usr/bin/nasm)
set(CMAKE_ASM_FLAGS "-f elf64")
set(CMAKE_ASM_COMPILE_OBJECT "<CMAKE_ASM_COMPILER> <FLAGS> <DEFINES> <INCLUDES> -o <OBJECT> <SOURCE>")

## Assembly sources
file(GLOB ASM_SOURCES "${CMAKE_SOURCE_DIR}/src/*.s")

add_library(asm ${ASM_SOURCES})

find_package(GTest QUIET)
if(NOT GTest_FOUND)
  ## install gtest
  message(STATUS "GTest not found, fetching it")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  ## For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  FetchContent_GetProperties(googletest)
else()
  message(STATUS "GTest found")
endif()

enable_testing()
add_subdirectory(tests)