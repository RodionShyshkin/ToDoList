//
// Created by rodion on 8/26/20.
//

#include "AddTaskStartState.h"
#include "NameParamState.h"
#include "ParentTaskParamState.h"

AddTaskStartState::AddTaskStartState(const bool &is_subtask) : is_subtask_(is_subtask) {}

bool AddTaskStartState::input() {
  return true;
}

std::shared_ptr<StateInterface> AddTaskStartState::run(std::unique_ptr<Context> &context) {
  output();
//  return nullptr;
  if(this->is_subtask_) return std::make_shared<ParentTaskParamState>();
  return std::make_shared<NameParamState>();
}

void AddTaskStartState::output() {
  std::cout << "[Output]: AddTask state machine / Start State" << std::endl;
}

StateType AddTaskStartState::getType() {
  return StateType::ADD_TASK_START_STATE;
}