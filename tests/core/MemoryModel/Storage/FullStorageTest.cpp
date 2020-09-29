//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MemoryModel/Storage/TaskModel.h"

 class FullStorageTest : public ::testing::Test {
 public:
  void SetUp() override {
    task = Task::create("Task", "test", Priority::HIGH, Date{"2022-4-1"}).value();

    dto_ = TaskDTO::create(1, "Task", "label", Priority::MEDIUM,
                           boost::gregorian::date{2020-10-10}, false);

    dto_subtask_ = TaskDTO::create(2, "Subtask", "", Priority::LOW,
                                   boost::gregorian::date{2020-10-10}, true);
  }

  void TearDown() override {

  }

 protected:
  TaskModel ts_storage;
  Task task;

  TaskDTO dto_;
  TaskDTO dto_subtask_;
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
  TaskModel fst(MockStorage{}, MockView{});


}*/


TEST_F(FullStorageTest, AddingTask) {
  ts_storage.AddTask(TaskDTO::create(1, task.GetName(), task.GetLabel(), task.GetPriority(),
                                     task.GetDate().GetDate(), false));
  auto tasks = ts_storage.GetTaskView().GetAllTasks();
  ASSERT_EQ(tasks.size(), 1);
}

TEST_F(FullStorageTest, GetTaskByID) {
  ts_storage.AddTask(TaskDTO::create(1, task.GetName(), task.GetLabel(), task.GetPriority(),
                                     task.GetDate().GetDate(), false));
  auto check = ts_storage.GetTaskStorage().GetTask(TaskID{1});
  ASSERT_EQ(check->GetName(), "Task");
  check = ts_storage.GetTaskStorage().GetTask(TaskID{2});
  ASSERT_EQ(check, nullptr);
}

TEST_F(FullStorageTest, AddSubtask) {
  ts_storage.AddTask(TaskDTO::create(1, task.GetName(), task.GetLabel(), task.GetPriority(),
                                     task.GetDate().GetDate(), false));
  ts_storage.AddSubtask(TaskID{1},TaskDTO::create(1, task.GetName(), task.GetLabel(),
                                                  task.GetPriority(), task.GetDate().GetDate(), false));

  auto check = ts_storage.GetTaskStorage().GetTask(TaskID{1});
  auto subcheck = ts_storage.GetTaskStorage().GetTask(TaskID{2});
}

TEST_F(FullStorageTest, getTodayTasks) {
  ts_storage.AddTask(TaskDTO::create(1, task.GetName(), task.GetLabel(), task.GetPriority(),
                                     task.GetDate().GetDate(), false));
  ASSERT_TRUE(ts_storage.GetTaskView().GetTodayTasks().empty());
}

TEST_F(FullStorageTest, getWeekTasks) {
  ts_storage.AddTask(TaskDTO::create(1, task.GetName(), task.GetLabel(), task.GetPriority(),
                                     task.GetDate().GetDate(), false));
  ASSERT_TRUE(ts_storage.GetTaskView().GetWeekTasks().empty());
}

TEST_F(FullStorageTest, getTasksByLabel) {
  ts_storage.AddTask(TaskDTO::create(1, task.GetName(), task.GetLabel(), task.GetPriority(),
                                     task.GetDate().GetDate(), false));
  ASSERT_EQ(ts_storage.GetTaskView().GetTasksByLabel("test").size(), 1);
}

TEST_F(FullStorageTest, getTasksByName) {
  ts_storage.AddTask(TaskDTO::create(1, task.GetName(), task.GetLabel(), task.GetPriority(),
                                     task.GetDate().GetDate(), false));
  ASSERT_EQ(ts_storage.GetTaskView().GetTasksByName("Task").size(), 1);
}

TEST_F(FullStorageTest, saveToDisk) {
  ts_storage.AddTask(dto_);
  ts_storage.AddSubtask(TaskID{1}, dto_subtask_);

  auto result = ts_storage.SaveToDisk("testDoc.txt");

  auto shouldResult = OperationResult{ErrorCode::NO_ERRORS};
  ASSERT_EQ(result.GetError(), shouldResult.GetError());
}

TEST_F(FullStorageTest, shouldNotLoadFromUnexistingFile) {
  ts_storage.AddTask(dto_);
  auto result = ts_storage.LoadFromDisk("unknown_file.txt");

  ASSERT_EQ(result.GetError(), ErrorCode::DESERIALIZATION_ERROR);
}

TEST_F(FullStorageTest, shouldLoadFromEmptyFile) {
  ts_storage.AddTask(dto_);
  auto result = ts_storage.LoadFromDisk("empty_file.txt");
  ASSERT_TRUE(result.GetStatus());
  ASSERT_EQ(result.GetError(), std::nullopt);

  auto tasks = ts_storage.GetTaskView().GetAllTasks();
  ASSERT_EQ(tasks.size(), 0);
}

TEST_F(FullStorageTest, shouldLoadFromFileCorrectly) {
  ts_storage.AddTask(dto_);

  ts_storage.LoadFromDisk("testDoc.txt");

  auto tasks = ts_storage.GetTaskView().GetAllTasks();
  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].GetTask().GetName(), "Task");
  ASSERT_EQ(tasks[0].GetSubtasks().size(), 1);
  ASSERT_EQ(tasks[0].GetSubtasks().at(TaskID{2}).lock()->GetName(), "Subtask");
  ASSERT_EQ(tasks[0].GetSubtasks().at(TaskID{2}).lock()->GetStatus(), true);
  ASSERT_EQ(tasks[0].GetStatus(), false);
}

//TEST_F(FullStorageTest, shouldNot)