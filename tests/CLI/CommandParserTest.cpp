//
// Created by rodion on 9/17/20.
//
/*
#include <gtest/gtest.h>
#include <command_parser.h>

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
  ASSERT_EQ(Command::SAVETASKS, parseCommand("save"));
  ASSERT_EQ(Command::LOADTASKS, parseCommand("load"));
  ASSERT_EQ(Command::EXIT, parseCommand("exit"));
}

TEST_F(CommandParserTest, getStateTypeByCommand) {
  ASSERT_EQ(StateType::MAIN_MENU, getStateTypeByCommand(Command::MAINMENU));
  ASSERT_EQ(StateType::ADD_TASK, getStateTypeByCommand(Command::ADDTASK));
  ASSERT_EQ(StateType::ADD_SUBTASK, getStateTypeByCommand(Command::ADDSUBTASK));
  ASSERT_EQ(StateType::SHOW_TASK, getStateTypeByCommand(Command::GETTASK));
  ASSERT_EQ(StateType::SHOW_TASKS_LIST, getStateTypeByCommand(Command::GETTASKLIST));
  ASSERT_EQ(StateType::COMPLETE_TASK, getStateTypeByCommand(Command::COMPLETETASK));
  ASSERT_EQ(StateType::REMOVE_TASK, getStateTypeByCommand(Command::REMOVETASK));
  ASSERT_EQ(StateType::POSTPONE_TASK, getStateTypeByCommand(Command::POSTPONETASK));
  ASSERT_EQ(StateType::SAVE_TASKS, getStateTypeByCommand(Command::SAVETASKS));
  ASSERT_EQ(StateType::LOAD_TASKS, getStateTypeByCommand(Command::LOADTASKS));
  ASSERT_EQ(StateType::EXIT_STATE, getStateTypeByCommand(Command::EXIT));
  ASSERT_EQ(StateType::UNKNOWN_STATE, getStateTypeByCommand(Command::UNKNOWN));
}
*/