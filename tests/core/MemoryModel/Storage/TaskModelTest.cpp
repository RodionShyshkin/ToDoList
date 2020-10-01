//
// Created by rodion on 10/1/20.
//

#include <MemoryModel/Storage/TaskModel.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

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

class MockGenerator : public IDGeneratorInterface {
 public:
  MOCK_METHOD(std::optional<TaskID>, GenerateID, (), (override));
};

class TaskModelTest : public ::testing::Test {
 public:
  void SetUp() override {
  }

  void TearDown() override {

  }

 protected:
  std::unique_ptr<TaskModel> model_;
};

TEST_F()

