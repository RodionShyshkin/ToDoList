//
// Created by Rodion Shyshkin on 27.10.2020.
//

#include <States/ParamStates/PriorityParamState.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class PriorityParamStateTest : public ::testing::Test {
 public:
  void SetUp() override {
    auto service = std::make_shared<MockService>();
    io = std::make_shared<MockIO>();
    context = std::make_shared<Context>(
        service, io);
  }

  void TearDown() override {

  }

 protected:
  std::shared_ptr<MockIO> io;
  std::shared_ptr<Context> context;
};

TEST_F(PriorityParamStateTest, shouldAcceptCorrectInput) {
  auto state = PriorityParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("Low"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(PriorityParamStateTest, shouldNotAcceptIncorrectInput) {
  auto state = PriorityParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asdf"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(PriorityParamStateTest, shouldAcceptEmptyInput) {
  auto state = PriorityParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(PriorityParamStateTest, shouldOutput) {
  auto state = PriorityParamState{};

  EXPECT_CALL(*io, output).Times(1);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(PriorityParamStateTest, shouldHaveCorrectStateType) {
  auto state = PriorityParamState{};

  ASSERT_EQ(StateType::TASK_PRIORITY_PARAM, state.getType());
}

TEST_F(PriorityParamStateTest, shouldRunCorrectly) {
  auto state = PriorityParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("Medium"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_EQ(context->add_task_buffer_.getPriority(), Priority::MEDIUM);
}

TEST_F(PriorityParamStateTest, shouldNotRunIfIncorrectInput) {
  auto state = PriorityParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("zxcvz"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::INCORRECT_INPUT);
  ASSERT_EQ(context->add_task_buffer_.getPriority(), Priority::EMPTY);
}

TEST_F(PriorityParamStateTest, shouldNotSwitchState) {
  auto state = PriorityParamState{};

  ASSERT_EQ(nullptr, state.switchState());
}
