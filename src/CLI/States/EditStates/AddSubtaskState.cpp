//
// Created by rodion on 8/31/20.
//

#include "AddSubtaskState.h"
#include "States/StateFactory.h"
#include <StateMachine.h>

bool AddSubtaskState::input() {
  return true;
}

std::shared_ptr<StateInterface> AddSubtaskState::run(std::shared_ptr<Context> &context) {
  auto machine_ = StateMachine::create(StatesGraphType::ADDSUBTASK, context);
  if(machine_.execute()) {
    std::cout << "subtask added" << std::endl;
  }
  else {
    std::cout << "Error with adding subtask!" << std::endl;
  }
  return StateFactory::create(getStateTypeByCommand(Command::GETTASK));
}

void AddSubtaskState::output() {
  std::cout << "[Output]: Adding subtask for an existing task." << std::endl;
}

StateType AddSubtaskState::getType() {
  return StateType::ADD_SUBTASK_STATE;
}