//
// Created by Rodion Shyshkin on 27.10.2020.
//

#include <States/ParamStates/ModifierParamState.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class ModifierParamStateTest : public ::testing::Test {
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

TEST_F(ModifierParamStateTest, shouldAcceptCorrectInput) {
  auto state = ModifierParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("all"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(ModifierParamStateTest, shouldNotAcceptIncorrectInput) {
  auto state = ModifierParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asdf"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(ModifierParamStateTest, shouldNotAcceptEmptyInput) {
  auto state = ModifierParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(ModifierParamStateTest, shouldOutput) {
  auto state = ModifierParamState{};

  EXPECT_CALL(*io, output).Times(1);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(ModifierParamStateTest, shouldHaveCorrectStateType) {
  auto state = ModifierParamState{};

  ASSERT_EQ(StateType::LIST_MODIFIER_PARAM, state.getType());
}

TEST_F(ModifierParamStateTest, shouldRunCorrectly) {
  auto state = ModifierParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("all"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_EQ(context->show_list_buffer_.getModifier(), ListModifier::ALL);
}

TEST_F(ModifierParamStateTest, shouldNotRunIfIncorrectInput) {
  auto state = ModifierParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::INCORRECT_INPUT);
  ASSERT_EQ(context->show_list_buffer_.getModifier(), ListModifier::UNKNOWN);
}

TEST_F(ModifierParamStateTest, shouldNotSwitchState) {
  auto state = ModifierParamState{};

  ASSERT_EQ(nullptr, state.switchState());
}
