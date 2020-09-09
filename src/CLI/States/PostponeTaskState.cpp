//
// Created by rodion on 8/25/20.
//

#include <StateMachine.h>
#include <StateFactory.h>
#include "PostponeTaskState.h"
#include "ViewTaskListState.h"
#include "ViewTaskState.h"
#include "NewDateParamState.h"

PostponeTaskState::PostponeTaskState() {
}

bool PostponeTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  PostponeTaskState::run(std::unique_ptr<Context> &context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
    }
    output();
  }
  return StateFactory::create(StateType::POSTPONE_TASK_NEW_DATE_PARAM_STATE);
}

void PostponeTaskState::output() {
  std::cout << "[Output]: Postponing task." << std::endl;
}

StateType PostponeTaskState::getType() {
  return StateType::POSTPONE_TASK_STATE;
}