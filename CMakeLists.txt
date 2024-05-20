cmake_minimum_required(VERSION 3.20)
project(n-body-simulator)

set(CMAKE_CXX_STANDARD 20)
option(USE_CLANG_TIDY "build with clang tidy" OFF)
option(BUILD_TESTS "Build simulator tests" OFF)
option(BUILD_GRPC_CLIENT "Build grpc data publisher" OFF)

find_package(Eigen3 REQUIRED)
find_package(jsoncpp REQUIRED)

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

set(GRPC_PUBLISHER_LIB "")
if(BUILD_GRPC_CLIENT)
  message(STATUS "Building gRPC client")
  add_subdirectory(grpc)
  set(GRPC_PUBLISHER_LIB "grpc_publisher")
endif()

add_library(threebody
  src/Body.cc
  src/BodySystem.cc
  src/BodySystemPublisher.cc
  src/SystemTracer.cc
  src/factory/BodySystemPublisherFactory.cc
  src/factory/BodySystemFactory.cc)
target_include_directories(threebody PUBLIC include)
target_link_libraries(threebody Eigen3::Eigen ${GRPC_PUBLISHER_LIB} jsoncpp)

configure_file(systems_json/system.json ${CMAKE_BINARY_DIR} COPYONLY)

# Apps
add_executable(solar_system
 app/solar_system.cc)
target_link_libraries(solar_system threebody)

add_executable(threebodysystem
app/three_body.cc)
target_link_libraries(threebodysystem threebody)

if(BUILD_TESTS)
message(STATUS "Building tests")
add_subdirectory(tst)
endif()

# Format
file(GLOB_RECURSE sourcefiles
  "include/*.hh"
  "src/*.cc"
  "tst/*.cc"
  "grpc/*.cc"
  "grpc/*.hh")
string (REPLACE ";" " " sourcefiles "${sourcefiles}")
add_custom_target(format ALL
COMMAND sh -c "clang-format -i ${sourcefiles} --verbose"
VERBATIM)
