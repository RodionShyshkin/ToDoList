//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/TaskServiceStorage.h"

 class TaskServiceStorageTest : public ::testing::Test {
 public:
  TaskServiceStorage ts_storage;
  Task task = Task::create("Task", "test", Priority::HIGH, DateTime(2022, 4, 1));
};

TEST_F(TaskServiceStorageTest, AddingTask) {
  ts_storage.AddTask(task);
  auto tasks = ts_storage.getAllTasks();
  ASSERT_EQ(tasks.size(), 1);
}

TEST_F(TaskServiceStorageTest, GetTaskByID) {
  ts_storage.AddTask(task);
  auto check = ts_storage.getTaskByID(1);
  ASSERT_EQ(check.value().getName(), "Task");
  check = ts_storage.getTaskByID(2);
  ASSERT_FALSE(check.has_value());
}

TEST_F(TaskServiceStorageTest, AddSubtask) {
  ts_storage.AddTask(task);
  ts_storage.AddSubtask(1, task);
  auto check = ts_storage.getTaskByID(1);
  auto subcheck = ts_storage.getTaskByID(2);
}

TEST_F(TaskServiceStorageTest, getTodayTasks) {
  ts_storage.AddTask(task);
  ASSERT_TRUE(ts_storage.getTasksForToday().empty());
}

TEST_F(TaskServiceStorageTest, getWeekTasks) {
  ts_storage.AddTask(task);
  ASSERT_TRUE(ts_storage.getTasksForWeek().empty());
}

TEST_F(TaskServiceStorageTest, getTasksByLabel) {
  ts_storage.AddTask(task);
  ASSERT_EQ(ts_storage.getTasksForLabel("test").size(), 1);
}

TEST_F(TaskServiceStorageTest, getTasksByName) {
  ts_storage.AddTask(task);
  ASSERT_EQ(ts_storage.getTasksForName("Task").size(), 1);
}