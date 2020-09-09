//
// Created by rodion on 8/21/20.
//


#include <StateMachine.h>
#include "RemoveTaskState.h"
#include "StartState.h"
#include "ViewTaskState.h"
#include "ViewTaskListState.h"

RemoveTaskState::RemoveTaskState() {
}

bool RemoveTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  RemoveTaskState::run(std::unique_ptr<Context> &context) {
  bool is_single_state = false;
  if(context->id_buffer_.checkBufferFullness()) {
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
  }
  this->task_id_ = context->id_buffer_.getID().value();

  output();

  context->id_buffer_.clearBuffer();
  return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
}

void RemoveTaskState::output() {
  std::cout << "[Output]: Removes task." << std::endl;
}

StateType RemoveTaskState::getType() {
  return StateType::REMOVE_TASK_STATE;
}