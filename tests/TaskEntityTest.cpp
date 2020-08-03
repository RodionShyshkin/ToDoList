//
// Created by rodion on 7/25/20.
//


#include <gtest/gtest.h>
#include "TaskEntity.h"

using testing::Eq;

class TaskEntityTest : public testing::Test {

};

TEST_F(TaskEntityTest, AddSubtask) {
  auto check_task = TaskEntity(Task("Task", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)), 1);
  auto check_subtask = TaskEntity(Task("Subtask", "test", Task::Priority::EMPTY, DateTime(2021, 10, 10, 10, 10)), 2);

  auto old_subtasks = check_task.getSubtasks();
  check_task.AddSubtask(std::make_shared<TaskEntity>(check_subtask));
  auto new_subtasks = check_task.getSubtasks();

  ASSERT_NE(old_subtasks.size(), new_subtasks.size());
  ASSERT_EQ(old_subtasks.size() + 1, new_subtasks.size());
}
