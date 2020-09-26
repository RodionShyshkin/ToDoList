//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/Task/Task.h"

class TaskTest : public ::testing::Test {

};

TEST_F(TaskTest, invalidTaskWithoutName) {
  std::optional<Task> task;
  EXPECT_NO_THROW(task = Task::create("", "label", Priority::MEDIUM, Date(2044, 1, 1)));
  ASSERT_FALSE(task.has_value());
}

TEST_F(TaskTest, invalidTaskWithoutLabel) {
  std::optional<Task> task;
  EXPECT_NO_THROW(task = Task::create("Name", "", Priority::MEDIUM, Date(2044, 1, 1)));
  ASSERT_TRUE(task.has_value());
}

TEST_F(TaskTest, ValidTask) {
  EXPECT_TRUE(Task::create("Name", "label_", Priority::EMPTY, Date(2044, 1, 1)).has_value());
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

TEST_F(TaskTest, CopyConstructor) {
  Task check = Task::create("name_", "label", Priority::EMPTY, Date(1999, 1, 1)).value();
  Task copy = check;
  ASSERT_TRUE(copy == check);
}