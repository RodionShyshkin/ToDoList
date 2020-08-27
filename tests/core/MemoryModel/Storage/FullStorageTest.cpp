//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MemoryModel/Storage/FullStorage.h"

 class FullStorageTest : public ::testing::Test {
 public:
  void SetUp() override {
    task = Task::create("Task", "test", Priority::HIGH, Date{"2022-4-1"}).value();
  }

  void TearDown() override {

  }

  FullStorage ts_storage;
  Task task;
};

class MockView : public TaskViewInterface {
 public:
  MOCK_METHOD(bool, AddTask, (const std::weak_ptr<TaskEntity>&), (override));
  MOCK_METHOD(bool, RemoveTask, (const TaskID&), (override));

  MOCK_METHOD(std::vector<TaskEntity>, GetTodayTasks, (), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetWeekTasks, (), (override));

  MOCK_METHOD(std::vector<TaskEntity>, GetAllTasks, (), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetTasksByLabel, (const std::string&), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetTasksByName, (const std::string&), (override));
  MOCK_METHOD(std::vector<TaskEntity>, GetTasksByPriority, (const Priority&), (override));
};

class MockStorage : public TaskStorageInterface {
 public:
  MOCK_METHOD(bool, AddTask, (const std::shared_ptr<TaskEntity>&), (override));
  MOCK_METHOD(bool, RemoveTask, (const TaskID&), (override));

  MOCK_METHOD(std::shared_ptr<TaskEntity>, GetTask, (const TaskID&), (override));
};

class MockIDGenerator : public IDGeneratorInterface {
 public:
  MOCK_METHOD(std::optional<TaskID>, GenerateID, (), (override));
};
/*
TEST_F(FullStorageTest, AddingTask) {
  FullStorage fst(MockStorage{}, MockView{});


}*/


TEST_F(FullStorageTest, AddingTask) {
  ts_storage.AddTask(TaskDTO::create(TaskID{1}, task, false));
  auto tasks = ts_storage.GetTaskView().GetAllTasks();
  ASSERT_EQ(tasks.size(), 1);
}

TEST_F(FullStorageTest, GetTaskByID) {
  ts_storage.AddTask(TaskDTO::create(TaskID{1}, task, false));
  auto check = ts_storage.GetTaskStorage().GetTask(TaskID{1});
  ASSERT_EQ(check->GetName(), "Task");
  check = ts_storage.GetTaskStorage().GetTask(TaskID{2});
  ASSERT_EQ(check, nullptr);
}

TEST_F(FullStorageTest, AddSubtask) {
  ts_storage.AddTask(TaskDTO::create(TaskID{1}, task, false));
  ts_storage.AddSubtask(TaskID{1},TaskDTO::create(TaskID{1}, task, false));

  auto check = ts_storage.GetTaskStorage().GetTask(TaskID{1});
  auto subcheck = ts_storage.GetTaskStorage().GetTask(TaskID{2});
}

TEST_F(FullStorageTest, getTodayTasks) {
  ts_storage.AddTask(TaskDTO::create(TaskID{1}, task, false));
  ASSERT_TRUE(ts_storage.GetTaskView().GetTodayTasks().empty());
}

TEST_F(FullStorageTest, getWeekTasks) {
  ts_storage.AddTask(TaskDTO::create(TaskID{1}, task, false));
  ASSERT_TRUE(ts_storage.GetTaskView().GetWeekTasks().empty());
}

TEST_F(FullStorageTest, getTasksByLabel) {
  ts_storage.AddTask(TaskDTO::create(TaskID{1}, task, false));
  ASSERT_EQ(ts_storage.GetTaskView().GetTasksByLabel("test").size(), 1);
}

TEST_F(FullStorageTest, getTasksByName) {
  ts_storage.AddTask(TaskDTO::create(TaskID{1}, task, false));
  ASSERT_EQ(ts_storage.GetTaskView().GetTasksByName("Task").size(), 1);
}