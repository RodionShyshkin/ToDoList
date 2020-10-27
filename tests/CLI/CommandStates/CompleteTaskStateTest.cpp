//
// Created by Rodion Shyshkin on 26.10.2020.
//


#include <gtest/gtest.h>
#include <States/CommandStates/CompleteTaskState.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class CompleteTaskStateTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(CompleteTaskStateTest, shouldInput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = CompleteTaskState{};

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(CompleteTaskStateTest, shouldOutput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = CompleteTaskState{};

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(CompleteTaskStateTest, shouldHaveCorrectStateType) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = CompleteTaskState{};

  ASSERT_EQ(StateType::COMPLETE_TASK, state.getType());
}

TEST_F(CompleteTaskStateTest, shouldRunCorrectlyWithoutIDInBuffer) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  vector.push_back(TaskDTO::Create(1, "parent", "label", Priority::EMPTY,
                                   boost::gregorian::date{2020 - 10 - 10}, true));

  context->show_list_buffer_.setList(vector);
  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);

  auto state = CompleteTaskState{};

  EXPECT_CALL(*service, CompleteTask).Times(1).WillOnce(testing::Return(true));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("0"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(CompleteTaskStateTest, shouldRunCorrectlyWithIDInBuffer) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  context->id_buffer_.setID(1);

  auto state = CompleteTaskState{};

  EXPECT_CALL(*service, CompleteTask).Times(1).WillOnce(testing::Return(true));

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(CompleteTaskStateTest, shouldNotRunIfOperationError) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  std::vector<TaskDTO> vector;
  vector.push_back(TaskDTO::Create(1, "parent", "label", Priority::EMPTY,
                                   boost::gregorian::date{2020 - 10 - 10}, true));

  context->show_list_buffer_.setList(vector);
  context->show_list_buffer_.setModifier(ListModifier::ALL);
  context->show_list_buffer_.setSortedFlag(true);

  auto state = CompleteTaskState{};

  EXPECT_CALL(*service, CompleteTask).Times(1).WillOnce(testing::Return(false));

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("0"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::OPERATION_ERROR);
}

TEST_F(CompleteTaskStateTest, shouldSwitchState) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = CompleteTaskState{};

  ASSERT_NE(nullptr, state.switchState());
}