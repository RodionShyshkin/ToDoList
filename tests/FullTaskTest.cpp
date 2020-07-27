//
// Created by rodion on 7/25/20.
//


#include <gtest/gtest.h>
#include "../src/MemoryModel/FullTask.h"
#include "../src/API/TaskService.h"

using testing::Eq;

class FullTaskTest : public testing::Test {

};

TEST_F(FullTaskTest, AddSubtask) {
  auto checkTask = FullTask(Task("Task", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)), 1);
  auto checkSubtask = FullTask(Task("Subtask", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)), 2);

  auto oldSubtasks = checkTask.getSubtasks();
  checkTask.AddSubtask(std::make_shared<FullTask>(checkSubtask));
  auto newSubtasks = checkTask.getSubtasks();

  ASSERT_NE(oldSubtasks.size(), newSubtasks.size());
}

TEST_F(FullTaskTest, SetComplete) {
  auto checkTask = FullTask(Task("Task", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)), 1);

  auto oldStatus = checkTask.getStatus();
  checkTask.setComplete();
  auto newStatus = checkTask.getStatus();

  ASSERT_NE(oldStatus, newStatus);
}

TEST_F(FullTaskTest, PostponeTask) {
  auto checkTask = FullTask(Task("Task", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)), 1);

  auto oldTask = checkTask.getTask();
  checkTask.substituteTask(Task("Changed Task", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  auto newTask = checkTask.getTask();

  ASSERT_NE(oldTask.getName(), newTask.getName());
  ASSERT_EQ("Changed Task", newTask.getName());
}
