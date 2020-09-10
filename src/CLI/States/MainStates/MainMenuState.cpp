//
// Created by rodion on 8/21/20.
//

#include <iostream>
#include <AvailableCommands.h>
#include "MainMenuState.h"

bool MainMenuState::input() {
  ConsoleIO console_io;
  std::string stringCommand = console_io.input();

  this->command_ = parseCommand(stringCommand);
  auto available = AvailableCommands::get(this->getType());

  if(available.find(this->command_) == available.end()) return false;
  return true;
}

std::shared_ptr<StateInterface> MainMenuState::run(std::shared_ptr<Context> &context) {
  auto inputResult = input();
  if(!inputResult) return nullptr;
  this->output();

  std::cout << "WORKS" << std::endl;
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void MainMenuState::output() {
  ConsoleIO io;
  io.output("[Output]: Main menu.");
}

StateType MainMenuState::getType() {
  return StateType::MAIN_MENU_STATE;
}