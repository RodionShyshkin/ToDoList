//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/TaskStorage.h"

class StorageTest : public ::testing::Test {
 public:
  TaskStorage storage;
  TaskEntity check = TaskEntity::create(Task::create("Task", "test", Priority::HIGH,
                                                     Date(1990, 2, 2)), 1);
};

TEST_F(StorageTest, pushTask) {

  EXPECT_NO_THROW(storage.PushTask(std::make_pair(1, std::make_shared<TaskEntity>(check))));
  EXPECT_THROW(storage.PushTask(std::make_pair(2, std::make_shared<TaskEntity>(check))), std::invalid_argument);
}

TEST_F(StorageTest, getTask) {
  storage.PushTask(std::make_pair(1, std::make_shared<TaskEntity>(check)));
  EXPECT_NO_THROW(storage.GetTask(1));
  auto check = storage.GetTask(1);
  ASSERT_EQ(check.value()->GetName(), "Task");
}

TEST_F(StorageTest, ifExist) {
  storage.PushTask(std::make_pair(1, std::make_shared<TaskEntity>(check)));
  ASSERT_TRUE(storage.HasTask(TaskID(1)));
  ASSERT_FALSE(storage.HasTask(TaskID(2)));
}
