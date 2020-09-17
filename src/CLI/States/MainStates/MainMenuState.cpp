//
// Created by rodion on 8/21/20.
//

#include <AvailableCommands.h>
#include "MainMenuState.h"

bool MainMenuState::input() {
  ConsoleIO console_io;
  this->command_ = parseCommand(console_io.inputCommand());
  if(!AvailableCommands::checkIsCommandAvailable(this->getType(), this->command_)) return false;
  return true;
}

std::shared_ptr<StateInterface> MainMenuState::run(std::shared_ptr<Context> &context) {
  context->clearAllBuffers();

  this->output();
  if(!this->input()) return StateFactory::create(this->getType());
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void MainMenuState::output() {
  ConsoleIO io;
  io.outputWithBreak("------------------");
  io.outputWithBreak("Enter one of the following commands:");
  io.outputWithBreak("> add, > show, > exit");
  io.outputWithBreak("------------------");
}

StateType MainMenuState::getType() {
  return StateType::MAIN_MENU_STATE;
}