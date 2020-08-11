//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include "MemoryModel/Error.h"

 class ErrorTest : public ::testing::Test {
/* public:
  ErrorCode error = Error(Error::Code::TASK_NOT_FOUND);
  ErrorCode second_error = Error(Error::Code::INVALID_DATE);*/
};

TEST_F(ErrorTest, GetErrorCode) {
//  ASSERT_EQ(error.get_code(), 2);
}

TEST_F(ErrorTest, ConvertToString) {
/*  ASSERT_EQ(Error::code_to_string(second_error.get_code()), "Invalid date.");
  ASSERT_EQ(Error::code_to_string(error.get_code()), "Task not found.");*/
}

TEST_F(ErrorTest, GetStringError) {
//  ASSERT_EQ(error.what(), "Task not found.");
}
