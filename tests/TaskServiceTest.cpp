//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "TaskService.h"

using testing::Eq;

class TaskServiceTest : public testing::Test {
};

TEST_F(TaskServiceTest, addTask) {
  TaskService service;

  service.addTask(Task("Task", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));

  auto tasksAmount = service.getAllTasks().size();
  auto task = service.getTaskByID(1);

  ASSERT_EQ(1, tasksAmount);
  ASSERT_EQ(1, tasksAmount);
  ASSERT_EQ("Task", task.getName());
  ASSERT_EQ("test", task.getLabel());
  ASSERT_EQ(Task::Priority::EMPTY, task.getPriority());
  ASSERT_EQ(DateTime(2020, 10, 10, 10, 10), task.getDueTime());
  ASSERT_EQ(false, task.getStatus());
}

/*TEST_F(TaskServiceTest, removeTaskWithoutSubtasks) {
  TaskService dir;
  dir.addTask(Task("One", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir.addTask(Task("Two", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir.removeTask(1);

  auto allTasks = dir.getAllTasks();
  ASSERT_EQ(1, dir.getAllTasks().size());
  ASSERT_EQ(2, allTasks[0].getUserID());
}
*/
