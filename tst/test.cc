#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

class TestA : public Test {};

TEST_F(TestA, AA) { FAIL(); }