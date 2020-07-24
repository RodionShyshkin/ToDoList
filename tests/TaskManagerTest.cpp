//
// Created by rodion on 7/18/20.
//

#include <gtest/gtest.h>
#include "../src/TaskManager.h"
#include "../src/TaskManagerDTO.h"

using testing::Eq;

class TaskManagerTest : public testing::Test {
};

TEST_F(TaskManagerTest, addTask) {
  auto dir = std::make_shared<TaskManager>(TaskManager());
  TaskManagerDTO check(dir);

  dir->addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));

  auto vecNum = check.getTasksAmount();

  ASSERT_EQ(1, vecNum);

  auto vec = check.getAllTasks();

  ASSERT_EQ(1, vec[0]->getUserID());

  auto task = check.getTask(1);

  ASSERT_EQ("Eat", task.getName());
  ASSERT_EQ("fish", task.getLabel());
  ASSERT_EQ(Task::Priority::HIGH, task.getPriority());
  ASSERT_EQ(DateTime(2021, 8, 8, 8, 8), task.getDueTime());
  ASSERT_EQ(false, task.getStatus());
}

TEST_F(TaskManagerTest, addSubtask) {
  auto dir = std::make_shared<TaskManager>(TaskManager());
  TaskManagerDTO check(dir);

  dir->addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));
  dir->addSubtask(1, Task("Subtask", "SubtaskLabel", Task::Priority::MEDIUM, DateTime(2021, 8, 8, 8, 8)));

  auto vec = check.getAllTasks();

  ASSERT_EQ(2, vec.size());
  ASSERT_EQ(1, vec[0]->getUserID());
  ASSERT_EQ(2, vec[1]->getUserID());

  auto task = check.getTask(1);

  ASSERT_EQ(1, task.getSubtasksAmount());
}

TEST_F(TaskManagerTest, removeTask) {
  TaskManager dir;
  dir.addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));
  dir.addTask(Task("One", "first", Task::Priority::EMPTY, DateTime(2021, 8, 8, 8, 8)));
  dir.addTask(Task("Two", "second", Task::Priority::LOW, DateTime(2021, 8, 8, 8, 8)));

  dir.removeTask(1);

  TaskManagerDTO check(std::make_shared<TaskManager>(dir));
  ASSERT_EQ(2, check.getTasksAmount());

  auto vec = check.getAllTasks();
  ASSERT_EQ(2, vec[0]->getUserID());
  ASSERT_EQ(3, vec[1]->getUserID());
}

TEST_F(TaskManagerTest, completeTask) {
  TaskManager dir;
  dir.addTask(Task("Eat", "fish", Task::Priority::HIGH, DateTime(2021, 8, 8, 8, 8)));

  TaskManagerDTO check(std::make_shared<TaskManager>(dir));
  auto task = check.getTask(1);

  ASSERT_EQ(false, task.getStatus());
  dir.completeTask(1);
  ASSERT_EQ(true, task.getStatus());
}

TEST_F(TaskManagerTest, postponeTask) {
  DateTime oldtime = DateTime(2021, 8, 8, 8, 8);
  DateTime newtime = DateTime(2021, 10, 10, 10, 10);

  TaskManager dir;
  dir.addTask(Task("Eat", "fish", Task::Priority::HIGH, oldtime));

  TaskManagerDTO check(std::make_shared<TaskManager>(dir));
  auto task = check.getTask(1);

  ASSERT_EQ(oldtime, task.getDueTime());
  dir.postponeTask(1, newtime);
  ASSERT_EQ(newtime, task.getDueTime());
}

