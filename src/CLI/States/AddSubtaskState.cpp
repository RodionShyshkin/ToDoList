//
// Created by rodion on 8/31/20.
//

#include <States/AddingTask/AddTaskStateMachine.h>
#include "AddSubtaskState.h"
#include "StateFactory.h"

bool AddSubtaskState::input() {
  available_operations_.clear();
  available_operations_.insert(Command::EXIT);
  return true;
}

std::shared_ptr<StateInterface> AddSubtaskState::run(std::unique_ptr<Context> &context) {
  AddTaskStateMachine machine_(true);
  if(machine_.execute()) {
    std::cout << "subtask added" << std::endl;
  }
  else {
    std::cout << "Error with adding subtask!" << std::endl;
  }
  return StateFactory::create(Command::GETTASK);
}

void AddSubtaskState::output() {
  std::cout << "[Output]: Adding subtask for an existing task." << std::endl;
}