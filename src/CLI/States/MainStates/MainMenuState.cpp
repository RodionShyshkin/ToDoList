//
// Created by rodion on 8/21/20.
//

#include <AvailableCommands.h>
#include "MainMenuState.h"

std::shared_ptr<StateInterface> MainMenuState::run(std::shared_ptr<Context> &context) {
  context->clearAllBuffers();

  this->output(context->io_);
  if(!this->input(context->io_)) return StateFactory::create(this->getType());
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

bool MainMenuState::input(const std::shared_ptr<IOInterface> &io_) {
  this->command_ = parseCommand(io_->inputCommand());
  if(!AvailableCommands::checkIsCommandAvailable(this->getType(), this->command_)) return false;
  return true;
}

void MainMenuState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("------------------");
  io_->outputWithBreak("Enter one of the following commands:");
  io_->outputWithBreak("> add, > show, > exit");
  io_->outputWithBreak("------------------");
}

StateType MainMenuState::getType() {
  return StateType::MAIN_MENU_STATE;
}