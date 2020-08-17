//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/Task/Task.h"

class TaskTest : public ::testing::Test {

};

TEST_F(TaskTest, Constructor) {
  EXPECT_TRUE(Task::create("Name", "label_", Priority::EMPTY, Date(2044, 1, 1)).has_value());
  EXPECT_FALSE(Task::create("", "label_", Priority::LOW, Date(2044, 1, 10)).has_value());
  EXPECT_FALSE(Task::create("Name", "", Priority::MEDIUM, Date(2011, 3, 1)).has_value());
  EXPECT_FALSE(Task::create("", "", Priority::HIGH, Date(2010, 4, 2)).has_value());
}

TEST_F(TaskTest, getters) {
  auto check = Task::create("Test", "label_", Priority::MEDIUM, Date(1980, 7, 8)).value();
  ASSERT_EQ(check.GetName(), "Test");
  ASSERT_EQ(check.GetLabel(), "label_");
  ASSERT_EQ(check.GetPriority(), Priority::MEDIUM);
  ASSERT_EQ(check.GetDate().GetDate(), Date(1980, 7, 8).GetDate());
}


bool operator== (const Task& lhs, const Task& rhs) {
  if(lhs.GetName() == rhs.GetName() && lhs.GetLabel() == rhs.GetLabel() && lhs.GetPriority() == rhs.GetPriority() &&
      lhs.GetDate().GetDate() == rhs.GetDate().GetDate()) return true;
  return false;
}

/*TEST_F(TaskTest, CopyConstructor) {

  Task check = Task::create("name_", "", Priority::EMPTY, Date(1999, 1, 1)).value();
  Task copy = check;
  ASSERT_TRUE(copy == check);
}*/