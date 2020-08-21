//
// Created by rodion on 8/21/20.
//

#include "TaskState.h"
#include "RemoveTaskState.h"

bool TaskState::input() {
  std::string stringCommand;
//  std::cin >> stringCommand;
  stringCommand = "remove";
  command_ = parseCommand(stringCommand);
  return true;
}

std::unique_ptr<StateInterface> TaskState::run() {
  input();
  if(command_ == Command::REMOVETASK) {
    std::cout << "going to be removed" << std::endl;
    return std::make_unique<RemoveTaskState>(false);
  }
  return nullptr;


}

void TaskState::output() {

}