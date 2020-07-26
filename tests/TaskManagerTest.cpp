//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "../src/API/TaskManager.h"
#include "../src/API/TaskManagerDTO.h"

using testing::Eq;

class TaskManagerTest : public testing::Test {
};

TEST_F(TaskManagerTest, addTask) {
  auto dir = std::make_shared<TaskManager>(TaskManager());
  TaskManagerDTO check(dir);

  dir->addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2020, 10, 10, 10, 10)));

  auto tasksAmount = check.getTasksAmount();
  auto task = check.getTask(1);

  ASSERT_EQ(1, tasksAmount);
  ASSERT_EQ("Eat", task.getName());
  ASSERT_EQ("fish", task.getLabel());
  ASSERT_EQ(Task::Priority::HIGH, task.getPriority());
  ASSERT_EQ(DateTime(2020, 10, 10, 10, 10), task.getDueTime());
  ASSERT_EQ(false, task.getStatus());
}

TEST_F(TaskManagerTest, addSubtask) {
  auto dir = std::make_shared<TaskManager>(TaskManager());
  TaskManagerDTO check(dir);

  dir->addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));
  dir->addSubtask(1, Task("Subtask", "SubtaskLabel", Task::Priority::MEDIUM, DateTime(2021, 8, 8, 8, 8)));

  auto tasksAmount = check.getTasksAmount();
  auto task = check.getTask(1);

  ASSERT_EQ(2, tasksAmount);
  ASSERT_EQ(1, task.getUserID());
  ASSERT_EQ(1, task.getSubtasksAmount());
}

TEST_F(TaskManagerTest, removeTaskWithoutSubtasks) {
  auto dir = std::make_shared<TaskManager>(TaskManager());
  TaskManagerDTO check(dir);
  dir->addTask(Task("One", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir->addTask(Task("Two", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir->removeTask(1);

  auto vec = check.getAllTasks();
  ASSERT_EQ(1, check.getTasksAmount());
  ASSERT_EQ(2, vec[0]->getUserID());
}

/*TEST_F(TaskManagerTest, removeTaskWithSomeSubtasks) {
  autio dir = std::make_shared<TaskManager>(TaskManager());
  TaskManagerDTO check(dir);
  dir->addTask(Task("One", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir->addTask(Task("Two", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir->addTask(Task("Three", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir->addSubtask(1, Task("Three", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10, 10, 10)));
  dir->removeTask(1);

  auto vec = check.getAllTasks();
  ASSERT_EQ(1, check.getTasksAmount());
//  ASSERT_EQ(2, vec[0]->getUserID());
}*/

TEST_F(TaskManagerTest, completeTask) {
  auto dir = std::make_shared<TaskManager>(TaskManager());
  TaskManagerDTO check(dir);
  dir->addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));

  auto task = check.getTask(1);

  ASSERT_EQ(false, task.getStatus());
  dir->completeTask(1);
  ASSERT_EQ(true, task.getStatus());
}

TEST_F(TaskManagerTest, postponeTask) {
  DateTime oldtime = DateTime(2021, 8, 8, 8, 8);
  DateTime newtime = DateTime(2021, 10, 10, 10, 10);

  auto dir = std::make_shared<TaskManager>(TaskManager());
  TaskManagerDTO check(dir);
  dir->addTask(Task("Eat", "fish", Task::Priority::HIGH, oldtime));

  auto task = check.getTask(1);

  ASSERT_EQ(oldtime, task.getDueTime());
  dir->postponeTask(1, newtime);
  ASSERT_EQ(newtime, task.getDueTime());
}

