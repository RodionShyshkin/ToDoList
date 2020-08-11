//
// Created by rodion on 8/10/20.
//


#include <gtest/gtest.h>
#include "API/TaskDTO.h"

class TaskDTOTest : public ::testing::Test {

};

TEST_F(TaskDTOTest, Constructor) {
  EXPECT_NO_THROW(TaskDTO());
  EXPECT_NO_THROW(TaskDTO::create(TaskID(1), Task::create("Task", "test", Priority::LOW, DateTime(2019, 12, 31)), true));
}

TEST_F(TaskDTOTest, Getters) {
  auto check = TaskDTO::create(TaskID(1), Task::create("Task", "test", Priority::LOW, DateTime(2008, 3, 8)), true);
  ASSERT_EQ(check.getID(), 1);
  ASSERT_EQ(check.getName(), "Task");
  ASSERT_EQ(check.getLabel(), "test");
  ASSERT_EQ(check.getPriority(), Priority::LOW);
  ASSERT_EQ(check.getDueDate().get_date(), DateTime(2008, 3, 8).get_date());
  ASSERT_EQ(check.getStatus(), true);
}
