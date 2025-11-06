cmake_minimum_required(VERSION 3.15)

project(
  hash_table
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(cuckoo_hash STATIC src/cuckoo_hash.cc)
target_include_directories(
  cuckoo_hash PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                     $<INSTALL_INTERFACE:include>)

add_library(linear_probing STATIC src/linear_probing.cc)
target_include_directories(
  linear_probing PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                        $<INSTALL_INTERFACE:include>)

option(ENABLE_TESTS "Enable tests" ON)

if(ENABLE_TESTS)
  message(STATUS "Tests enabled")

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  enable_testing()

  add_executable(cuckoo_hash_test tests/cuckoo_hash_test.cc)
  target_link_libraries(cuckoo_hash_test PRIVATE cuckoo_hash GTest::gtest_main)
  add_test(NAME cuckoo_hash_test COMMAND cuckoo_hash_test)

  add_executable(linear_probing_test tests/linear_probing_test.cc)
  target_link_libraries(linear_probing_test PRIVATE linear_probing
                                                    GTest::gtest_main)
  add_test(NAME linear_probing_test COMMAND linear_probing_test)
endif(ENABLE_TESTS)
