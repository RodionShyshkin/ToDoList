//
// Created by rodion on 8/10/20.
//


#include <gtest/gtest.h>
#include "API/TaskDTO.h"

class TaskDTOTest : public ::testing::Test {
 public:
  Task validTask = Task::create("Name", "Valid task", Priority::EMPTY, Date(2090, 1, 1)).value();
};

TEST_F(TaskDTOTest, ExceptionWithInvalidID) {
  EXPECT_ANY_THROW(TaskDTO::create(TaskID::create(10000).value(), validTask, true));
  EXPECT_ANY_THROW(TaskDTO::create(TaskID::create(-100).value(), validTask, true));
}

TEST_F(TaskDTOTest, ExceptionWithInvalidTask) {
  EXPECT_ANY_THROW(TaskDTO::create(TaskID::create(900).value(),
                                   Task::create("", "Invalid task", Priority::EMPTY,
                                                Date(2090, 1, 1)).value(), true));
  EXPECT_ANY_THROW(TaskDTO::create(TaskID::create(900).value(),
                                   Task::create("Invalid", "", Priority::EMPTY,
                                                Date(2020, 9, 8)).value(), true));
}

TEST_F(TaskDTOTest, validTask) {
  TaskDTO dto;
  EXPECT_NO_THROW(dto = TaskDTO::create(TaskID::create(5).value(), validTask, false));

  ASSERT_EQ(validTask.GetName(), dto.getName());
  ASSERT_EQ(validTask.GetLabel(), dto.getLabel());
  ASSERT_EQ(validTask.GetPriority(), dto.getPriority());
  ASSERT_EQ(validTask.GetDate().GetDate(), dto.getDueDate().GetDate());
  ASSERT_EQ(TaskID::create(5).value(), dto.getID());
  ASSERT_EQ(false, dto.getStatus());
}

