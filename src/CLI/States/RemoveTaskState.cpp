//
// Created by rodion on 8/21/20.
//


#include <StateMachine.h>
#include "RemoveTaskState.h"
#include "StartState.h"
#include "ViewTaskState.h"
#include "ViewTaskListState.h"

RemoveTaskState::RemoveTaskState() {
  available_operations_.clear();
  available_operations_.insert(Command::EXIT);
}

bool RemoveTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  RemoveTaskState::run(std::unique_ptr<Context> &context) {
  bool is_single_state = false;
  if(context->id_buffer_.has_id_) {
    is_single_state = true;
  }
  else {
    auto machine_ = StateMachine::create(StatesGraphType::VIEW_SINGLE_TASK);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
    }
    output();
  }
  this->task_id_ = context->id_buffer_.id_;

  std::cout << "removed " << this->task_id_ << std::endl;
  if(is_single_state) return std::make_unique<ViewTaskState>();
  else return std::make_unique<ViewTaskListState>();
}

void RemoveTaskState::output() {
  std::cout << "[Output]: Removes task." << std::endl;
}

StateType RemoveTaskState::getType() {
  return StateType::REMOVE_TASK_STATE;
}