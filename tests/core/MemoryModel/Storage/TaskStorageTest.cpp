//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/Storage/TaskStorage.h"

class StorageTest : public ::testing::Test {
 public:
  void SetUp() override {
    check = TaskEntity::createTask(Task::create("Task", "test", Priority::HIGH,
                                                Date{"1990-2-2"}).value(), TaskID{1});
    second = TaskEntity::createTask(Task::create("Task 2", "test", Priority::LOW,
                                                 Date{"2022-8-8"}).value(), TaskID{2});
    invalidTask = TaskEntity::createTask(Task::create("Invalid task", "test", Priority::MEDIUM,
                                                      Date{"2088-9-11"}).value(), TaskID{1});
  }

  void TearDown() override {

  }

  TaskStorage storage;
  TaskEntity check;
  TaskEntity second;
  TaskEntity invalidTask;
};

TEST_F(StorageTest, pushTask) {
  ASSERT_TRUE(storage.AddTask(std::make_shared<TaskEntity>(check)));
  ASSERT_FALSE(storage.AddTask(std::make_shared<TaskEntity>(invalidTask)));
}

TEST_F(StorageTest, getTask) {
  storage.AddTask(std::make_shared<TaskEntity>(check));
  std::shared_ptr<TaskEntity> kek;
  EXPECT_NO_THROW(kek = storage.GetTask(TaskID{1}));
  ASSERT_NE(kek, nullptr);
  ASSERT_EQ(kek->GetName(), "Task");
}

TEST_F(StorageTest, removeTask) {
  storage.AddTask(std::make_shared<TaskEntity>(check));
  storage.AddTask(std::make_shared<TaskEntity>(second));

  ASSERT_FALSE(storage.RemoveTask(500));
  ASSERT_TRUE(storage.RemoveTask(1));

  ASSERT_EQ(storage.GetTask(1), nullptr);
  ASSERT_NE(storage.GetTask(2), nullptr);
}
