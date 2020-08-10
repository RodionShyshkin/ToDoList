//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/TaskID.h"

class TaskIDTest : public ::testing::Test {
 public:
  TaskID lhs = TaskID(3);
  TaskID lhs_equal = TaskID(3);
  TaskID rhs = TaskID(4);
  unsigned int rhs_equal = 4;
};

TEST_F(TaskIDTest, defaultConstructor) {
  EXPECT_NO_THROW(TaskID());
}

TEST_F(TaskIDTest, Operators) {
  ASSERT_TRUE(lhs < rhs);
  ASSERT_TRUE(lhs == lhs_equal);
  ASSERT_TRUE(rhs == rhs_equal);
}