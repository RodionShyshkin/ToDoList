//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/Task.h"

class TaskTest : public ::testing::Test {

};

TEST_F(TaskTest, Constructor) {
  EXPECT_NO_THROW(Task("Name", "label", Task::Priority::EMPTY, DateTime(2044, 1, 1)));
  EXPECT_ANY_THROW(Task("", "label", Task::Priority::LOW, DateTime(2044, 1, 10)));
  EXPECT_NO_THROW(Task("Name", "", Task::Priority::MEDIUM, DateTime(2011, 3, 1)));
  EXPECT_ANY_THROW(Task("", "", Task::Priority::HIGH, DateTime(2010, 4, 2)));
}

TEST_F(TaskTest, getters) {
  auto check = Task("Test", "label", Task::Priority::MEDIUM, DateTime(1980, 7, 8));
  ASSERT_EQ(check.getName(), "Test");
  ASSERT_EQ(check.getLabel(), "label");
  ASSERT_EQ(check.getPriority(), Task::Priority::MEDIUM);
  ASSERT_EQ(check.getDate().get_date(), DateTime(1980, 7, 8).get_date());
}


bool operator== (const Task& lhs, const Task& rhs) {
  if(lhs.getName() == rhs.getName() && lhs.getLabel() == rhs.getLabel() && lhs.getPriority() == rhs.getPriority() &&
      lhs.getDate().get_date() == rhs.getDate().get_date()) return true;
  return false;
}

TEST_F(TaskTest, CopyConstructor) {

  Task check("name", "", Task::Priority::EMPTY, DateTime(1999, 1, 1));
  Task copy = check;
  ASSERT_TRUE(copy == check);
}