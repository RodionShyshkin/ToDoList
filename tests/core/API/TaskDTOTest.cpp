//
// Created by rodion on 8/10/20.
//


#include <gtest/gtest.h>
#include <API/TaskDTO.h>

class TaskDTOTest : public ::testing::Test {
 public:
  void SetUp() override {
    validTask = Task::create("Name", "Valid task", Priority::EMPTY, Date{"2090-1-1"}).value();
  }

  void TearDown() override {

  }

  Task validTask;
};

TEST_F(TaskDTOTest, ExceptionWithInvalidTask) {
  EXPECT_NO_THROW(TaskDTO::create(900, "", "invalid task", Priority::EMPTY, boost::gregorian::date{2010-10-10}, true));
}

TEST_F(TaskDTOTest, validTask) {
  TaskDTO dto;
  EXPECT_NO_THROW(dto = TaskDTO::create(5, validTask.GetName(), validTask.GetLabel(),
                                        validTask.GetPriority(), validTask.GetDate().GetDate(), false));
  EXPECT_NO_THROW(TaskDTO::create(900,
                                   "Invalid", "", Priority::EMPTY,
                                                boost::gregorian::date{2020-9-8}, true));

  ASSERT_EQ(validTask.GetName(), dto.getName());
  ASSERT_EQ(validTask.GetLabel(), dto.getLabel());
  ASSERT_EQ(validTask.GetPriority(), dto.getPriority());
  ASSERT_EQ(validTask.GetDate().GetDate(), dto.getDueDate());
  ASSERT_EQ(TaskID{5}, dto.getID());
  ASSERT_EQ(false, dto.getStatus());
}

