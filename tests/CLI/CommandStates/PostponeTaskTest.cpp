//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <gtest/gtest.h>
#include <States/CommandStates/PostponeTaskState.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class PostponeTaskStateTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(PostponeTaskStateTest, shouldInput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PostponeTaskState{};

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(PostponeTaskStateTest, shouldOutput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PostponeTaskState{};

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(PostponeTaskStateTest, shouldHaveCorrectStateType) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PostponeTaskState{};

  ASSERT_EQ(StateType::POSTPONE_TASK, state.getType());
}

TEST_F(PostponeTaskStateTest, shouldRunCorrectlyWithoutIDInBuffer) {
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

  auto state = PostponeTaskState{};

  EXPECT_CALL(*service, postponeTask).Times(1).WillOnce(testing::Return(true));

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("0"))
                                      .WillOnce(testing::Return("2012-12-12"));
  EXPECT_CALL(*io, output).Times(2);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(PostponeTaskStateTest, shouldRunCorrectlyWithIDInBuffer) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  context->id_buffer_.setID(1);

  auto state = PostponeTaskState{};

  EXPECT_CALL(*service, postponeTask).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("2012-12-12"));
  EXPECT_CALL(*io, output).Times(1);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(PostponeTaskStateTest, shouldNotRunIfOperationError) {
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

  auto state = PostponeTaskState{};

  EXPECT_CALL(*service, postponeTask).Times(1).WillOnce(testing::Return(false));

  EXPECT_CALL(*io, input).Times(2).WillOnce(testing::Return("0"))
      .WillOnce(testing::Return("2012-12-12"));
  EXPECT_CALL(*io, output).Times(2);

  ASSERT_EQ(state.run(context), StateResult::OPERATION_ERROR);
}

TEST_F(PostponeTaskStateTest, shouldSwitchState) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = PostponeTaskState{};

  ASSERT_NE(nullptr, state.switchState());
}