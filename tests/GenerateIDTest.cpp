//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "../src/GenerateID.h"

using testing::Eq;

class GenerateIDTest : public testing::Test {

};

TEST_F(GenerateIDTest, Comparing) {
  unsigned int lhs = 5;
  TaskID rhs = TaskID(5);

  ASSERT_EQ(lhs, rhs);
}