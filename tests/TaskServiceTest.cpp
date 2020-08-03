//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "TaskService.h"

using testing::Eq;

class TaskServiceTest : public testing::Test {
};

TEST_F(TaskServiceTest, addTask) {
/*  TaskService dir;

  dir.addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2020, 10, 10, 10, 10)));

  auto tasksAmount = dir.getAllTasks().size();
  auto task = dir.getTaskByID(1);

  ASSERT_EQ(1, tasksAmount);
  ASSERT_EQ("Eat", task->getName());
  ASSERT_EQ("fish", task->getLabel());
  ASSERT_EQ(Task::Priority::HIGH, task->getPriority());
  ASSERT_EQ(DateTime(2020, 10, 10, 10, 10), task->getDueTime());
  ASSERT_EQ(false, task->getStatus());*/
}

TEST_F(TaskServiceTest, addSubtask) {
/*  TaskService dir;

  dir.addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));
//  dir.addSubtask(1, Task("Subtask", "SubtaskLabel", Task::Priority::MEDIUM, DateTime(2021, 8, 8, 8, 8)));

  auto tasksAmount = dir.getAllTasks().size();
  auto task = dir.getTaskByID(1);

  ASSERT_EQ(2, tasksAmount);
  ASSERT_EQ(1, task->getUserID());
  ASSERT_EQ(1, task->getSubtasks().size());*/
}

TEST_F(TaskServiceTest, removeTaskWithoutSubtasks) {
/*  TaskService dir;
  dir.addTask(Task("One", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir.addTask(Task("Two", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir.removeTask(1);

  auto allTasks = dir.getAllTasks();
  ASSERT_EQ(1, dir.getAllTasks().size());
  ASSERT_EQ(2, allTasks[0].getUserID());*/
}

TEST_F(TaskServiceTest, completeTask) {
/*  TaskService dir;
  dir.addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));

  auto task = dir.getTaskByID(1);

  ASSERT_EQ(false, task->getStatus());
  dir.completeTask(1);
  ASSERT_EQ(true, task->getStatus());*/
}

TEST_F(TaskServiceTest, postponeTask) {
/*  DateTime oldtime = DateTime(2021, 8, 8, 8, 8);
  DateTime newtime = DateTime(2021, 10, 10, 10, 10);

  TaskService dir;
  dir.addTask(Task("Eat", "fish", Task::Priority::HIGH, oldtime));

  auto task = dir.getTaskByID(1);

  ASSERT_EQ(oldtime, task->getDueTime());
  dir.postponeTask(1, newtime);
  ASSERT_EQ(newtime, task->getDueTime());*/
}

