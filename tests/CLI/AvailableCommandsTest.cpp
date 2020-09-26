//
// Created by rodion on 9/17/20.
//

#include <gtest/gtest.h>
#include <AvailableCommands.h>

 class AvailableCommandsTest : public ::testing::Test {
};

TEST_F(AvailableCommandsTest, checkMainMenuCommands) {
  StateType type = StateType::MAIN_MENU_STATE;

  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::ADDTASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::GETTASKLIST));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::EXIT));

  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::GETTASK));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::ADDSUBTASK));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::COMPLETETASK));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::REMOVETASK));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::POSTPONETASK));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::MAINMENU));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::UNKNOWN));
}

TEST_F(AvailableCommandsTest, checkViewSingleTaskCommands) {
  StateType type = StateType::VIEW_TASK_STATE;

  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::EXIT));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::ADDSUBTASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::COMPLETETASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::REMOVETASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::POSTPONETASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::MAINMENU));

  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::GETTASK));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::UNKNOWN));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::ADDTASK));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::GETTASKLIST));
}

TEST_F(AvailableCommandsTest, checkViewListOfTasksCommands) {
  StateType type = StateType::VIEW_TASK_LIST_STATE;

  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::EXIT));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::GETTASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::ADDSUBTASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::COMPLETETASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::REMOVETASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::POSTPONETASK));
  ASSERT_EQ(true, AvailableCommands::checkIsCommandAvailable(type, Command::MAINMENU));

  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::UNKNOWN));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::ADDTASK));
  ASSERT_EQ(false, AvailableCommands::checkIsCommandAvailable(type, Command::GETTASKLIST));
}
