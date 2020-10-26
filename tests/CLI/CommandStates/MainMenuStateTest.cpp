//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <gtest/gtest.h>
#include <States/CommandStates/MainMenuState.h>
#include <Mocks/MockService.h>
#include <Mocks/MockIO.h>

class MainMenuStateTest : public ::testing::Test {
 public:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(MainMenuStateTest, ShouldNotAcceptIncorrectCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = MainMenuState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("asdf"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(MainMenuStateTest, shouldOutput) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = MainMenuState{};

  EXPECT_CALL(*io, outputWithBreak).Times(4);

  ASSERT_NO_THROW(state.output(context->io_));
}

TEST_F(MainMenuStateTest, shouldHaveCorrectStateType) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = MainMenuState{};

  ASSERT_EQ(StateType::MAIN_MENU, state.getType());
}

TEST_F(MainMenuStateTest, ShouldNotAcceptCommandFromOtherMenu) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = MainMenuState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("add_subtask"));

  ASSERT_FALSE(state.input(context->io_));
}

TEST_F(MainMenuStateTest, ShouldAcceptCorrectCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = MainMenuState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("add"));

  ASSERT_TRUE(state.input(context->io_));
}

TEST_F(MainMenuStateTest, shouldRunSuccessIfCommandIsCorrect) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = MainMenuState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("add"));
  EXPECT_CALL(*io, outputWithBreak).Times(4);

  ASSERT_EQ(state.run(context), StateResult::SUCCESS);
}

TEST_F(MainMenuStateTest, shouldNotRunSuccessIfCommandIsIncorrect) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = MainMenuState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("asdf"));
  EXPECT_CALL(*io, outputWithBreak).Times(4);

  ASSERT_EQ(state.run(context), StateResult::INCORRECT_INPUT);
}

TEST_F(MainMenuStateTest, ShouldNotSwitchStateIfThereAreNoCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = MainMenuState{};
  ASSERT_EQ(nullptr, state.switchState());
}

TEST_F(MainMenuStateTest, ShouldSwitchStateIfThereIsCorrectCommand) {
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  auto context = std::make_shared<Context>(
      service, io);

  auto state = MainMenuState{};

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(testing::Return("add"));
  EXPECT_CALL(*io, outputWithBreak).Times(4);

  state.run(context);

  ASSERT_NE(nullptr, state.switchState());
}