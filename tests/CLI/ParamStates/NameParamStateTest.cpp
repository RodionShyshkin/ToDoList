//
// Created by Rodion Shyshkin on 27.10.2020.
//

#include <States/ParamStates/NameParamState.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class NameParamStateTest : public ::testing::Test {
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

TEST_F(NameParamStateTest, shouldNotAcceptIncorrectInput) {
  auto state = NameParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(NameParamStateTest, shouldAcceptCorrectInput) {
  auto state = NameParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("name"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(NameParamStateTest, shouldOutput) {
  auto state = NameParamState{};

  EXPECT_CALL(*io, output).Times(1);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(NameParamStateTest, shouldHaveCorrectStateType) {
  auto state = NameParamState{};

  ASSERT_EQ(StateType::TASK_NAME_PARAM, state.getType());
}

TEST_F(NameParamStateTest, shouldRunAndFillContextCorrectly) {
  auto state = NameParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("name"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_EQ(context->add_task_buffer_.getName(), "name");
}

TEST_F(NameParamStateTest, shouldNotRunIfIncorrectParam) {
  auto state = NameParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::INCORRECT_INPUT);
  ASSERT_EQ(context->add_task_buffer_.getName(), "");
}

TEST_F(NameParamStateTest, shouldNotSwitchState) {
  auto state = NameParamState{};

  ASSERT_EQ(nullptr, state.switchState());
}
