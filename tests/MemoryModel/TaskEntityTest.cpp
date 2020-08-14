//
// Created by rodion on 7/25/20.
//


#include <gtest/gtest.h>
#include "MemoryModel/Task/TaskEntity.h"

 class TaskEntityTest : public ::testing::Test {
 public:
/*   TaskEntity check = TaskEntity::createTask(Task::create("Task", "test", Priority::EMPTY,
                                                          Date(2020, 10, 10)), 1);
   TaskEntity subtask = TaskEntity::createTask(Task::create("Subtask", "test", Priority::HIGH,
                                                            Date(2090, 1, 1)), 2);*/
};

TEST_F(TaskEntityTest, Getters) {
/*  ASSERT_EQ(check.GetName(), "Task");
  ASSERT_EQ(check.GetLabel(), "test");
  ASSERT_EQ(check.GetPriority(), Priority::EMPTY);
  ASSERT_EQ(check.GetDueTime().GetDate(), Date(2020, 10, 10).GetDate());
  ASSERT_EQ(check.GetID(), 1);
  ASSERT_FALSE(check.GetStatus());
  EXPECT_NO_THROW(check.GetTask());
  EXPECT_NO_THROW(check.GetSubtasks());*/
}

TEST_F(TaskEntityTest, AddSubtask) {
/*
  ASSERT_EQ(check.GetSubtasks().size(), 0);
  check.AddSubtask(std::make_shared<TaskEntity>(subtask));
  ASSERT_EQ(check.GetSubtasks().size(), 1);*/
}

TEST_F(TaskEntityTest, defaultConstructor) {
  EXPECT_NO_THROW(TaskEntity());//
}
