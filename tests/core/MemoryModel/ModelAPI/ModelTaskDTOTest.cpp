//
// Created by rodion on 10/6/20.
//

#include <MemoryModel/ModelAPI/ModelTaskDTO.h>
#include <gtest/gtest.h>
#include <MemoryModel/Task/Task.h>

class ModelTaskDTOTest : public ::testing::Test {
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(ModelTaskDTOTest, validTask) {
  Task task = Task::create("name", "label", Priority::MEDIUM, Date{2020, 10, 6}).value();

  ModelTaskDTO dto;
  EXPECT_NO_THROW(dto = ModelTaskDTO::CreateWithParent(
      TaskID{5}, task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate(), false, TaskID{1}));

  ASSERT_EQ(task.GetName(), dto.GetName());
  ASSERT_EQ(task.GetLabel(), dto.GetLabel());
  ASSERT_EQ(task.GetPriority(), dto.GetPriority());
  ASSERT_EQ(task.GetDate().GetDate(), dto.GetDueDate().GetDate());
  ASSERT_EQ(TaskID{5}, dto.GetID());
  ASSERT_EQ(TaskID{1}, dto.GetParentID());
  ASSERT_EQ(false, dto.GetStatus());
}
