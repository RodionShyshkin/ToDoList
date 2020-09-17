//
// Created by rodion on 9/17/20.
//

#include <gtest/gtest.h>
#include <States/MainStates/MainMenuState.h>

 class MainMenuTest : public ::testing::Test {
 public:
  MainMenuState state_;
};

TEST_F(MainMenuTest, rightStateType) {
  ASSERT_EQ(state_.getType(), StateType::MAIN_MENU_STATE);
}