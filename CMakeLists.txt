cmake_minimum_required(VERSION 3.20)
project(n-body-simulator)

set(CMAKE_CXX_STANDARD 20)
option(USE_CLANG_TIDY "build with clang tidy" OFF)
option(BUILD_TESTS "Build simulator tests" OFF)
option(BUILD_GRPC_CLIENT "Build grpc data publisher" OFF)

find_package(Eigen3 REQUIRED)

if(USE_CLANG_TIDY)
  message(STATUS "Using clang-tidy")
  set(clangTidyChecks
      "clang-analyzer-*"
      "misc-*"
      "modernize-*"
      "performance-*"
      "readability-*"
      "-modernize-use-trailing-return-type"
      "-header-filter=.*"
    )
  string(REPLACE ";" "," clangTidyChecks "${clangTidyChecks}")
  set(CMAKE_CXX_CLANG_TIDY clang-tidy "--checks=${clangTidyChecks}")
  add_compile_options(
    "-Werror"
    "-Wno-unused-variable"
  )
endif()

add_executable(simulator 
  src/main.cc
  src/Body.cc
  src/BodySystem.cc)
target_include_directories(simulator PUBLIC include)
target_link_libraries(simulator Eigen3::Eigen)

if(BUILD_TESTS)
message(STATUS "Building tests")
add_subdirectory(tst)
endif()

if(BUILD_GRPC_CLIENT)
message(STATUS "Building gRPC client")
add_subdirectory(grpc)
target_link_libraries(simulator publisher)
endif()

# Format
file(GLOB_RECURSE sourcefiles
"include/*.hh"
"src/*.cc"
"tst/*.cc"

)
string (REPLACE ";" " " sourcefiles "${sourcefiles}")
add_custom_target(format ALL
COMMAND sh -c "clang-format -i ${sourcefiles} --verbose"

VERBATIM)
