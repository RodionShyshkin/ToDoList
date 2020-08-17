//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/Storage/TaskStorage.h"

class StorageTest : public ::testing::Test {
 public:
  TaskStorage storage;
  TaskEntity check = TaskEntity::createTask(Task::create("Task", "test", Priority::HIGH,
                                                         Date(1990, 2, 2)).value(), TaskID::create(1).value());
};

TEST_F(StorageTest, pushTask) {
  EXPECT_NO_THROW(storage.AddTask(std::make_shared<TaskEntity>(check)));
}

TEST_F(StorageTest, getTask) {
  storage.AddTask(std::make_shared<TaskEntity>(check));
  EXPECT_NO_THROW(storage.GetTask(TaskID::create(1).value()));
  auto check = storage.GetTask(TaskID::create(1).value());
  ASSERT_NE(check, nullptr);
  ASSERT_EQ(check->GetName(), "Task");
}

TEST_F(StorageTest, ifExist) {
  storage.AddTask(std::make_shared<TaskEntity>(check));
  ASSERT_TRUE(storage.HasTask(TaskID::create(1).value()));
  ASSERT_FALSE(storage.HasTask(TaskID::create(2).value()));
}
