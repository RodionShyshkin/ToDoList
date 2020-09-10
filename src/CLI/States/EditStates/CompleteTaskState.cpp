//
// Created by rodion on 8/25/20.
//

#include <StateMachine.h>
#include <States/StateFactory.h>
#include "CompleteTaskState.h"
#include "States/MainStates/ViewTaskListState.h"
#include "States/MainStates/ViewTaskState.h"

CompleteTaskState::CompleteTaskState() {
}

bool CompleteTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  CompleteTaskState::run(std::shared_ptr<Context> &context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
    }
    output();
  }
  auto id_from_buffer_ = context->id_buffer_.getID();
  this->task_id_ = id_from_buffer_.value();

  // Request to TaskService

  if(context->show_list_buffer_.checkBufferFullness()) {
    context->id_buffer_.clearBuffer();
    return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  }
  context->show_list_buffer_.clearBuffer();
  return StateFactory::create(getStateTypeByCommand(Command::GETTASK));
}

void CompleteTaskState::output() {
  std::cout << "[Output]: Completing task." << std::endl;
}

StateType CompleteTaskState::getType() {
  return StateType::COMPLETE_TASK_STATE;
}