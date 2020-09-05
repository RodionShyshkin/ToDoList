//
// Created by rodion on 8/25/20.
//

#include <StateMachine.h>
#include "PostponeTaskState.h"
#include "ViewTaskListState.h"
#include "ViewTaskState.h"
#include "NewDateParamState.h"

PostponeTaskState::PostponeTaskState() {
  available_operations_.clear();
  available_operations_.insert(Command::EXIT);
}

bool PostponeTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  PostponeTaskState::run(std::unique_ptr<Context> &context) {
  bool is_single_state = false;
  if(context->id_buffer_.has_id_) {
    is_single_state = true;
  }
  else {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
    }
    output();
  }
  context->postpone_date_.id_ = context->id_buffer_.id_;
  if(is_single_state) context->postpone_date_.is_single_task_ = true;
  else context->postpone_date_.is_single_task_ = false;

  return std::make_shared<NewDateParamState>();
}

void PostponeTaskState::output() {
  std::cout << "[Output]: Postponing task." << std::endl;
}

StateType PostponeTaskState::getType() {
  return StateType::POSTPONE_TASK_STATE;
}