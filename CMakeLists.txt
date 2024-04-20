cmake_minimum_required(VERSION 3.20)
project(n-body-simulator)

set(CMAKE_CXX_STANDARD 20)
option(USE_CLANG_TIDY "build with clang" ON)
option(BUILD_TESTS "Build simulator tests" OFF)
option(BUILD_GRPC_CLIENT "Build grpc data publisher" OFF)

if(USE_CLANG_TIDY)
  message(STATUS "Using clang-tidy")
  set(clangTidyChecks
      "clang-analyzer-*"
      "misc-*"
      "modernize-*"
      "performance-*"
      "readability-*"
      "-modernize-use-trailing-return-type"
    )
  string(REPLACE ";" "," clangTidyChecks "${clangTidyChecks}")
  set(CMAKE_CXX_CLANG_TIDY clang-tidy "--checks=${clangTidyChecks}")
endif()

if(BUILD_TESTS)
message(STATUS "Building tests")
add_subdirectory(test)
endif()

if(BUILD_GRPC_CLIENT)
message(STATUS "Building gRPC client")
add_subdirectory(grpc)
endif()


add_executable(main src/main.cpp)
