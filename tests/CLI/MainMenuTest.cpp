//
// Created by rodion on 9/17/20.
//

#include <States/MainStates/MainMenuState.h>
#include <IO/IOInterface.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::Pointee;
using ::testing::Return;

class MainMenuTest : public ::testing::Test {
 public:
  MainMenuState state_;
};
/*
class MockIO : public IOInterface {
 public:
  MOCK_METHOD(std::string, input, (), (override));
  MOCK_METHOD(std::string, inputCommand, (), (override));
  MOCK_METHOD(void, output, (const std::string&), (override));
  MOCK_METHOD(void, outputWithBreak, (const std::string&), (override));
};*/

TEST_F(MainMenuTest, rightInput) {
  /*auto io = std::make_shared<MockIO>();
  EXPECT_CALL(*io, input()).Times(1).WillOnce(Return("show"));
  EXPECT_CALL(*io, inputCommand()).Times(1).WillOnce(Return("add"));*/
/*
  if(2 + 2 == 4) {
    MockIO io;
  }
  */
  //EXPECT_CALL(MockIO{}, input()).Times(1).WillOnce(Return("show"));

// state_.input(io);

}


TEST_F(MainMenuTest, rightStateType) {
  ASSERT_EQ(StateType::MAIN_MENU_STATE, state_.getType());
}