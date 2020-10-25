//
// Created by rodion on 8/10/20.
//

#include <gtest/gtest.h>
#include <API/OperationResult/OperationResult.h>
#include <API/OperationResult/StorageError.h>
#include <API/OperationResult/PersistError.h>

class OperationResultTest : public ::testing::Test {

};

TEST_F(OperationResultTest, ConstructorAndGetters) {
  auto first_result = OperationResult<StorageError>::Fail(StorageError::INVALID_TASK);
  auto second_result = OperationResult<PersistError>::Fail(PersistError::SAVE_ERROR);
  auto third_result = OperationResult<StorageError>::Success();

  ASSERT_EQ(first_result.GetError(), StorageError::INVALID_TASK);
  ASSERT_EQ(second_result.GetError(), PersistError::SAVE_ERROR);
  ASSERT_EQ(third_result.GetError(), std::nullopt);
}