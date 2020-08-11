//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/TaskStorage.h"

class StorageTest : public ::testing::Test {
 public:
  TaskStorage storage;
  TaskEntity check = TaskEntity::create(Task::create("Task", "test", Priority::HIGH,
                                                     DateTime(1990, 2, 2)), 1);
};

TEST_F(StorageTest, pushTask) {

  EXPECT_NO_THROW(storage.pushTask(std::make_pair(1, std::make_shared<TaskEntity>(check))));
  EXPECT_THROW(storage.pushTask(std::make_pair(2, std::make_shared<TaskEntity>(check))), std::invalid_argument);
}

TEST_F(StorageTest, getTask) {
  storage.pushTask(std::make_pair(1, std::make_shared<TaskEntity>(check)));
  EXPECT_NO_THROW(storage.getTask(1));
  auto check = storage.getTask(1);
  ASSERT_EQ(check.value()->getName(), "Task");
}

TEST_F(StorageTest, ifExist) {
  storage.pushTask(std::make_pair(1, std::make_shared<TaskEntity>(check)));
  ASSERT_TRUE(storage.if_exist(TaskID(1)));
  ASSERT_FALSE(storage.if_exist(TaskID(2)));
}
