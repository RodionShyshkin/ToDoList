//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <gtest/gtest.h>
#include <States/CommandStates/RemoveTaskState.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class RemoveTaskStateTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(RemoveTaskStateTest, shouldInput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = RemoveTaskState{};

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(RemoveTaskStateTest, shouldOutput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = RemoveTaskState{};

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(RemoveTaskStateTest, shouldHaveCorrectStateType) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = RemoveTaskState{};

  ASSERT_EQ(StateType::REMOVE_TASK, state.getType());
}

TEST_F(RemoveTaskStateTest, shouldRunCorrectlyWithoutIDInBuffer) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  vector.push_back(TaskDTO::create(1, "parent", "label", Priority::EMPTY,
                                   boost::gregorian::date{2020-10-10}, true));

  context->show_list_buffer_.setList(vector);
  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);

  auto state = RemoveTaskState{};

  EXPECT_CALL(*service, RemoveTask).Times(1).WillOnce(testing::Return(
      OperationResult<StorageError>::Success()
      ));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("0"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(RemoveTaskStateTest, shouldRunCorrectlyWithIDInBuffer) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  context->id_buffer_.setID(1);

  auto state = RemoveTaskState{};

  EXPECT_CALL(*service, RemoveTask).Times(1).WillOnce(testing::Return(
      OperationResult<StorageError>::Success()
      ));

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(RemoveTaskStateTest, shouldNotRunIfOperationError) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  vector.push_back(TaskDTO::create(1, "parent", "label", Priority::EMPTY,
                                   boost::gregorian::date{2020-10-10}, true));

  context->show_list_buffer_.setList(vector);
  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);

  auto state = RemoveTaskState{};

  EXPECT_CALL(*service, RemoveTask).Times(1).WillOnce(testing::Return(
      OperationResult<StorageError>::Fail(StorageError::TASK_NOT_FOUND)
      ));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("0"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::OPERATION_ERROR);
}

TEST_F(RemoveTaskStateTest, shouldSwitchState) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = RemoveTaskState{};

  ASSERT_NE(nullptr, state.switchState());
}