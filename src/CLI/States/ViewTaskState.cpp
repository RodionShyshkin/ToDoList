//
// Created by rodion on 8/21/20.
//
/*
#include "ViewTaskState.h"
#include "RemoveTaskState.h"

bool ViewTaskState::input() {
  std::string stringCommand;
//  std::cin >> stringCommand;
  stringCommand = "remove";
  command_ = parseCommand(stringCommand);
  return true;
}

std::unique_ptr<StateInterface> ViewTaskState::run() {
  input();
  if(command_ == Command::REMOVETASK) {
    std::cout << "going to be removed" << std::endl;
    return std::make_unique<RemoveTaskState>(false);
  }
  return nullptr;


}

void ViewTaskState::output() {

}
*/