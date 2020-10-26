//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <gtest/gtest.h>
#include <States/CommandStates/AddTaskState.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class AddTaskStateTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(AddTaskStateTest, shouldInput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddTaskState{};

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(AddTaskStateTest, shouldOutput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddTaskState{};

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(AddTaskStateTest, shouldHaveCorrectStateType) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddTaskState{};

  ASSERT_EQ(StateType::ADD_TASK, state.getType());
}

TEST_F(AddTaskStateTest, shouldNotRunIfOperationError) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddTaskState{};

  EXPECT_CALL(*service, addTask).Times(1).WillOnce(testing::Return(
      OperationResult<StorageError>::Fail(StorageError::INVALID_TASK)));

  EXPECT_CALL(*io, input).Times(4).WillOnce(testing::Return("name"))
                                      .WillOnce(testing::Return(""))
                                      .WillOnce(testing::Return(""))
                                      .WillOnce(testing::Return(""));
  EXPECT_CALL(*io, output).Times(4);

  ASSERT_EQ(state.run(context), StateResult::OPERATION_ERROR);
}

TEST_F(AddTaskStateTest, shouldRunCorrectly) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddTaskState{};

  EXPECT_CALL(*service, addTask).Times(1).WillOnce(testing::Return(
      OperationResult<StorageError>::Success()));

  EXPECT_CALL(*io, input).Times(4).WillOnce(testing::Return("name"))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""));
  EXPECT_CALL(*io, output).Times(4);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
  ASSERT_FALSE(context->add_task_buffer_.checkBufferFullness());
}

TEST_F(AddTaskStateTest, shouldSwitchState) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddTaskState{};

  ASSERT_NE(nullptr, state.switchState());
}