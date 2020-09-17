//
// Created by rodion on 9/17/20.
//

#include <gtest/gtest.h>
#include <CommandParser.h>

class CommandParserTest : public ::testing::Test {
 public:
  void SetUp() override {
  }

  void TearDown() override {

  }

};

TEST_F(CommandParserTest, parseCommand) {
  ASSERT_EQ(Command::UNKNOWN, parseCommand(""));
  ASSERT_EQ(Command::UNKNOWN, parseCommand("asdf"));
  ASSERT_EQ(Command::MAINMENU, parseCommand("mm"));
  ASSERT_EQ(Command::MAINMENU, parseCommand("mainmenu"));
  ASSERT_EQ(Command::ADDTASK, parseCommand("add"));
  ASSERT_EQ(Command::ADDSUBTASK, parseCommand("add_subtask"));
  ASSERT_EQ(Command::GETTASK, parseCommand("view"));
  ASSERT_EQ(Command::GETTASKLIST, parseCommand("show"));
  ASSERT_EQ(Command::COMPLETETASK, parseCommand("complete"));
  ASSERT_EQ(Command::REMOVETASK, parseCommand("remove"));
  ASSERT_EQ(Command::POSTPONETASK, parseCommand("postpone"));
  ASSERT_EQ(Command::EXIT, parseCommand("exit"));
}

TEST_F(CommandParserTest, getStateTypeByCommand) {
  ASSERT_EQ(StateType::MAIN_MENU_STATE, getStateTypeByCommand(Command::MAINMENU));
  ASSERT_EQ(StateType::ADD_TASK_STATE, getStateTypeByCommand(Command::ADDTASK));
  ASSERT_EQ(StateType::ADD_SUBTASK_STATE, getStateTypeByCommand(Command::ADDSUBTASK));
  ASSERT_EQ(StateType::VIEW_TASK_STATE, getStateTypeByCommand(Command::GETTASK));
  ASSERT_EQ(StateType::VIEW_TASK_LIST_STATE, getStateTypeByCommand(Command::GETTASKLIST));
  ASSERT_EQ(StateType::COMPLETE_TASK_STATE, getStateTypeByCommand(Command::COMPLETETASK));
  ASSERT_EQ(StateType::REMOVE_TASK_STATE, getStateTypeByCommand(Command::REMOVETASK));
  ASSERT_EQ(StateType::POSTPONE_TASK_STATE, getStateTypeByCommand(Command::POSTPONETASK));
  ASSERT_EQ(StateType::EXIT_STATE, getStateTypeByCommand(Command::EXIT));
  ASSERT_EQ(StateType::UNKNOWN_STATE, getStateTypeByCommand(Command::UNKNOWN));
}
