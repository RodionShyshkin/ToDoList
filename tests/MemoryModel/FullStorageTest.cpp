//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/Storage/FullStorage.h"

 class FullStorageTest : public ::testing::Test {
 public:
  FullStorage ts_storage;
  Task task = Task::create("Task", "test", Priority::HIGH, Date(2022, 4, 1)).value();
};

TEST_F(FullStorageTest, AddingTask) {
  ts_storage.AddTask(TaskDTO::create(TaskID::create(1).value(), task, false));
  auto tasks = ts_storage.GetTaskView().GetAllTasks();
  ASSERT_EQ(tasks.size(), 1);
}

TEST_F(FullStorageTest, GetTaskByID) {
  ts_storage.AddTask(TaskDTO::create(TaskID::create(1).value(), task, false));
  auto check = ts_storage.GetTaskStorage().GetTask(TaskID::create(1).value());
  ASSERT_EQ(check->GetName(), "Task");
  check = ts_storage.GetTaskStorage().GetTask(TaskID::create(2).value());
  ASSERT_EQ(check, nullptr);
}

TEST_F(FullStorageTest, AddSubtask) {
  ts_storage.AddTask(TaskDTO::create(TaskID::create(1).value(), task, false));
  ts_storage.AddSubtask(TaskID::create(1).value(),TaskDTO::create(TaskID::create(1).value(), task, false));

  auto check = ts_storage.GetTaskStorage().GetTask(TaskID::create(1).value());
  auto subcheck = ts_storage.GetTaskStorage().GetTask(TaskID::create(2).value());
}

TEST_F(FullStorageTest, getTodayTasks) {
  ts_storage.AddTask(TaskDTO::create(TaskID::create(1).value(), task, false));
  ASSERT_TRUE(ts_storage.GetTaskView().GetTodayTasks().empty());
}

TEST_F(FullStorageTest, getWeekTasks) {
  ts_storage.AddTask(TaskDTO::create(TaskID::create(1).value(), task, false));
  ASSERT_TRUE(ts_storage.GetTaskView().GetWeekTasks().empty());
}

TEST_F(FullStorageTest, getTasksByLabel) {
  ts_storage.AddTask(TaskDTO::create(TaskID::create(1).value(), task, false));
  ASSERT_EQ(ts_storage.GetTaskView().GetTasksByLabel("test").size(), 1);
}

TEST_F(FullStorageTest, getTasksByName) {
  ts_storage.AddTask(TaskDTO::create(TaskID::create(1).value(), task, false));
  ASSERT_EQ(ts_storage.GetTaskView().GetTasksByName("Task").size(), 1);
}