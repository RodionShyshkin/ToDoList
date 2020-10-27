//
// Created by rodion on 8/10/20.
//


#include <gtest/gtest.h>
#include <API/TaskDTO.h>

class TaskDTOTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(TaskDTOTest, validTask) {
  unsigned int id = 4;
  boost::gregorian::date date{2020-10-6};

  TaskDTO dto;
  EXPECT_NO_THROW(dto = TaskDTO::Create(id, "name", "label", Priority::MEDIUM, date, false));

  ASSERT_EQ("name", dto.getName());
  ASSERT_EQ("label", dto.getLabel());
  ASSERT_EQ(Priority::MEDIUM, dto.getPriority());
  ASSERT_EQ(date, dto.getDueDate());
  ASSERT_EQ(id, dto.getID());
  ASSERT_EQ(false, dto.getStatus());
}

