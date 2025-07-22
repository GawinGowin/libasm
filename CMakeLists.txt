cmake_minimum_required(VERSION 3.25.1)
project(libasm C CXX ASM)

set(CMAKE_CXX_COMPILER /usr/bin/c++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g3")

add_custom_target(build_libasm ALL
    COMMAND make bonus
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building libasm.a using Makefile"
)

set(LIBASM_PATH ${CMAKE_SOURCE_DIR}/libasm.a)

add_library(asm STATIC IMPORTED)
set_target_properties(asm PROPERTIES IMPORTED_LOCATION ${LIBASM_PATH})

add_dependencies(asm build_libasm)

add_custom_target(clean_libasm
    COMMAND make clean && rm -f ${LIBASM_PATH}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Cleaning libasm.a using Makefile"
)

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