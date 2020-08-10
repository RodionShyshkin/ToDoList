//
// Created by rodion on 7/25/20.
//


#include <gtest/gtest.h>
#include "MemoryModel/TaskEntity.h"

 class TaskEntityTest : public ::testing::Test {
 public:
   TaskEntity check = TaskEntity(Task("Task", "test", Task::Priority::EMPTY, DateTime(2020, 10, 10)), 1);
   TaskEntity subtask = TaskEntity(Task("Subtask", "test", Task::Priority::HIGH, DateTime(2090, 1, 1)), 2);
};

/*TEST_F(TaskEntityTest, Constructor) {
//  EXPECT_NO_THROW()
}*/

TEST_F(TaskEntityTest, Getters) {
  ASSERT_EQ(check.getName(), "Task");
  ASSERT_EQ(check.getLabel(), "test");
  ASSERT_EQ(check.getPriority(), Task::Priority::EMPTY);
  ASSERT_EQ(check.getDueTime().get_date(), DateTime(2020, 10, 10).get_date());
  ASSERT_EQ(check.getID(), 1);
  ASSERT_FALSE(check.getStatus());
  EXPECT_NO_THROW(check.getTask());
  EXPECT_NO_THROW(check.getSubtasks());
}

TEST_F(TaskEntityTest, AddSubtask) {

  ASSERT_EQ(check.getSubtasks().size(), 0);
  check.AddSubtask(std::make_shared<TaskEntity>(subtask));
  ASSERT_EQ(check.getSubtasks().size(), 1);
}

TEST_F(TaskEntityTest, defaultConstructor) {
  EXPECT_NO_THROW(TaskEntity());
}
