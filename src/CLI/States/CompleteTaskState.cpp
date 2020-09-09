//
// Created by rodion on 8/25/20.
//

#include <StateMachine.h>
#include <StateFactory.h>
#include "CompleteTaskState.h"
#include "ViewTaskListState.h"
#include "ViewTaskState.h"

CompleteTaskState::CompleteTaskState() {
}

bool CompleteTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  CompleteTaskState::run(std::unique_ptr<Context> &context) {
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
    output();
  }
  this->task_id_ = context->id_buffer_.getID().value();

  //completeTask(task_id_);

  if(is_single_state) return StateFactory::create(getStateTypeByCommand(Command::GETTASK));
  else {
    context->id_buffer_.clearBuffer();
    return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  }
}

void CompleteTaskState::output() {
  std::cout << "[Output]: Completing task." << std::endl;
}

StateType CompleteTaskState::getType() {
  return StateType::COMPLETE_TASK_STATE;
}