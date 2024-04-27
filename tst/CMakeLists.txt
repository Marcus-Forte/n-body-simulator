enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests test.cc)
target_link_libraries(tests GTest::gtest_main)
gtest_discover_tests(tests)