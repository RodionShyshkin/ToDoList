//
// Created by Rodion Shyshkin on 26.10.2020.
//

#include <CommandStateMachine.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Mocks/MockIO.h>
#include <Mocks/MockService.h>

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
