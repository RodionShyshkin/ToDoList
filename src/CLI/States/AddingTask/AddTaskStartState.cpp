//
// Created by rodion on 8/26/20.
//

#include <States/StateFactory.h>
#include "AddTaskStartState.h"

AddTaskStartState::AddTaskStartState(const bool &is_subtask) : is_subtask_(is_subtask) {}

bool AddTaskStartState::input() {
  return true;
}

std::shared_ptr<StateInterface> AddTaskStartState::run(std::shared_ptr<Context> &context) {
  if(this->is_subtask_) return StateFactory::create(StateType::ADD_TASK_PARENT_PARAM_STATE);
  return StateFactory::create(StateType::ADD_TASK_NAME_PARAM_STATE);
}

void AddTaskStartState::output() {
  ConsoleIO io;
  io.outputWithBreak("[Output]: AddTask state machine / Start State");
}

StateType AddTaskStartState::getType() {
  return StateType::ADD_TASK_START_STATE;
}