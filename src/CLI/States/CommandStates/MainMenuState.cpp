//
// Created by rodion on 8/21/20.
//

#include <States/StateFactory.h>
#include <AvailableCommands.h>
#include "MainMenuState.h"

MainMenuState::MainMenuState() : command_(Command::UNKNOWN) {}

StateResult MainMenuState::run(std::shared_ptr<Context> context) {
  context->clearAllBuffers();

  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  return StateResult::SUCCESS;
}

bool MainMenuState::input(const std::shared_ptr<IOInterface> &io) {
  command_ = parseCommand(io->inputCommand());
  if(!AvailableCommands::checkIsCommandAvailable(getType(), command_)) return false;
  return true;
}

void MainMenuState::output(const std::shared_ptr<IOInterface> &io) {
  io->outputWithBreak("------------------");
  io->outputWithBreak("Enter one of the following commands:");
  io->outputWithBreak("> save, > load, > add, > show, > exit");
  io->outputWithBreak("------------------");
}

StateType MainMenuState::getType() {
  return StateType::MAIN_MENU;
}

std::unique_ptr<StateInterface> MainMenuState::switchState() {
  auto newstate = StateFactory::create(getStateTypeByCommand(command_));
  return std::move(newstate);
}