include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

#..:: libasmtest ::..
add_executable(libasmtest ${TEST_SOURCES})

if(GTest_FOUND)
  target_link_libraries(libasmtest asm GTest::GTest GTest::Main)
else()
  target_link_libraries(libasmtest asm gtest gtest_main)
endif()

target_include_directories(libasmtest PRIVATE 
  ${CMAKE_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR}
)

# ..:: GoogleTest ::..
gtest_add_tests(TARGET libasmtest)
