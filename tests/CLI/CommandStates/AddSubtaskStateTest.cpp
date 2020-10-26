//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <gtest/gtest.h>
#include <States/CommandStates/AddSubtaskState.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class AddSubtaskStateTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(AddSubtaskStateTest, shouldInput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddSubtaskState{};

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(AddSubtaskStateTest, shouldOutput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddSubtaskState{};

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(AddSubtaskStateTest, shouldHaveCorrectStateType) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddSubtaskState{};

  ASSERT_EQ(StateType::ADD_SUBTASK, state.getType());
}

TEST_F(AddSubtaskStateTest, shouldRunCorrectlyWithID) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  context->id_buffer_.setID(1);

  auto state = AddSubtaskState{};

  EXPECT_CALL(*service, addSubtask).Times(1).WillOnce(testing::Return(
      OperationResult<StorageError>::Success()));

  EXPECT_CALL(*io, input).Times(4).WillOnce(testing::Return("name"))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""));
  EXPECT_CALL(*io, output).Times(4);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
  ASSERT_FALSE(context->add_task_buffer_.checkBufferFullness());
}

TEST_F(AddSubtaskStateTest, shouldRunCorrectlyWithoutID) {
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

  auto state = AddSubtaskState{};

  EXPECT_CALL(*service, addSubtask).Times(1).WillOnce(testing::Return(
      OperationResult<StorageError>::Success()));

  EXPECT_CALL(*io, input).Times(5).WillOnce(testing::Return("0"))
      .WillOnce(testing::Return("name"))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""));
  EXPECT_CALL(*io, output).Times(5);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
  ASSERT_FALSE(context->add_task_buffer_.checkBufferFullness());
}

TEST_F(AddSubtaskStateTest, shouldNotRunIfOperationError) {
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

  auto state = AddSubtaskState{};

  EXPECT_CALL(*service, addSubtask).Times(1).WillOnce(testing::Return(
      OperationResult<StorageError>::Fail(StorageError::INVALID_TASK)));

  EXPECT_CALL(*io, input).Times(5).WillOnce(testing::Return("0"))
      .WillOnce(testing::Return("name"))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""))
      .WillOnce(testing::Return(""));
  EXPECT_CALL(*io, output).Times(5);

  ASSERT_EQ(state.run(context), StateResult::OPERATION_ERROR);
}

TEST_F(AddSubtaskStateTest, shouldSwitchState) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = AddSubtaskState{};

  ASSERT_NE(nullptr, state.switchState());
}