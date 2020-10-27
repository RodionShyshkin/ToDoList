//
// Created by Rodion Shyshkin on 27.10.2020.
//

#include <States/ParamStates/SortedParamState.h>
#include <gtest/gtest.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class SortedParamStateTest : public ::testing::Test {
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

TEST_F(SortedParamStateTest, shouldAcceptCorrectInput) {
  auto state = SortedParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("no"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(SortedParamStateTest, shouldNotAcceptIncorrectInput) {
  auto state = SortedParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asdf"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(SortedParamStateTest, shouldNotAcceptEmptyInput) {
  auto state = SortedParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return(""));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(SortedParamStateTest, shouldOutput) {
  auto state = SortedParamState{};

  EXPECT_CALL(*io, output).Times(1);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(SortedParamStateTest, shouldHaveCorrectStateType) {
  auto state = SortedParamState{};

  ASSERT_EQ(StateType::LIST_SORTED_PARAM, state.getType());
}

TEST_F(SortedParamStateTest, shouldRunCorrectly) {
  auto state = SortedParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("yes"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::SUCCESS);
  ASSERT_EQ(context->show_list_buffer_.getSortedFlag(), true);
}

TEST_F(SortedParamStateTest, shouldNotRunIfIncorrectInput) {
  auto state = SortedParamState{};

  EXPECT_CALL(*io, input).Times(1).WillOnce(testing::Return("asfd"));
  EXPECT_CALL(*io, output).Times(1);

  auto result = state.run(context);

  ASSERT_EQ(result, StateResult::INCORRECT_INPUT);
}

TEST_F(SortedParamStateTest, shouldNotSwitchState) {
  auto state = SortedParamState{};

  ASSERT_EQ(nullptr, state.switchState());
}
