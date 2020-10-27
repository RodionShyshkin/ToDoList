//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <CommandStateMachine.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Mocks/MockIO.h>
#include <Mocks/MockService.h>
#include <States/StateFactory.h>

using ::testing::Return;

class CommandStateMachineTest : public ::testing::Test {
 public:
  void SetUp() override {
  }
  void TearDown() override {

  }

 protected:
};

TEST_F(CommandStateMachineTest, shouldCreateByStartStateAndContext) {
  auto start_state = StateType::COMPLETE_TASK;
  std::shared_ptr<Context> context = std::make_shared<Context>(
      std::make_shared<MockService>(), std::make_shared<MockIO>());

  ASSERT_NO_THROW(CommandStateMachine::create(std::move(start_state),
                                              std::move(context)));
}

TEST_F(CommandStateMachineTest, shouldSwitchStatesCorrectly) {
  auto start_state = StateType::MAIN_MENU;
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  std::shared_ptr<Context> context = std::make_shared<Context>(
      service, io);

  EXPECT_CALL(*io, inputCommand).Times(2).WillOnce(Return("add"))
                                              .WillOnce(Return("exit"));

  EXPECT_CALL(*io, input).Times(4).WillOnce(Return("name"))
                         .WillOnce(Return("label"))
                         .WillOnce(Return(""))
                         .WillOnce(Return(""));

  EXPECT_CALL(*io, output).Times(4);
  EXPECT_CALL(*io, outputWithBreak).Times(8);
  EXPECT_CALL(*service, AddTask).Times(1).WillOnce(
      Return(OperationResult<StorageError>::Success()));

  auto machine = CommandStateMachine::create(std::move(start_state),
                                              std::move(context));
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(CommandStateMachineTest, shouldExitStateMachineIfOperationError) {
  auto start_state = StateType::MAIN_MENU;
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  std::shared_ptr<Context> context = std::make_shared<Context>(
      service, io);

  EXPECT_CALL(*io, inputCommand).Times(1).WillOnce(Return("add"));

  EXPECT_CALL(*io, input).Times(4).WillOnce(Return("name"))
      .WillOnce(Return(""))
      .WillOnce(Return(""))
      .WillOnce(Return(""));

  EXPECT_CALL(*io, output).Times(4);
  EXPECT_CALL(*io, outputWithBreak).Times(5);
  EXPECT_CALL(*service, AddTask).Times(1).WillOnce(
      Return(OperationResult<StorageError>::Fail(StorageError::INVALID_TASK)));

  auto machine = CommandStateMachine::create(std::move(start_state),
                                             std::move(context));
  ASSERT_NO_THROW(machine.execute());
}

TEST_F(CommandStateMachineTest, shouldNotExitStateMachineIfIncorrectInput) {
  auto start_state = StateType::MAIN_MENU;
  auto service = std::make_shared<MockService>();
  auto io = std::make_shared<MockIO>();
  std::shared_ptr<Context> context = std::make_shared<Context>(
      service, io);

  EXPECT_CALL(*io, inputCommand).Times(2).WillOnce(Return("adfadsq"))
                                              .WillOnce(Return("exit"));

  EXPECT_CALL(*io, outputWithBreak).Times(9);

  auto machine = CommandStateMachine::create(std::move(start_state),
                                             std::move(context));
  ASSERT_NO_THROW(machine.execute());
}