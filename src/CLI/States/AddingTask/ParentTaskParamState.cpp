//
// Created by rodion on 9/1/20.
//

#include <StateMachine.h>
#include <StatesGraphType.h>
#include <States/StateFactory.h>
#include "ParentTaskParamState.h"
#include "NameParamState.h"

bool ParentTaskParamState::input() {
  return true;
}

std::shared_ptr<StateInterface> ParentTaskParamState::run(std::shared_ptr<Context> &context) {
  this->output();
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
    }
  }
  auto id_from_buffer_ = context->id_buffer_.getID();
  if(!id_from_buffer_.has_value()) throw;
  context->add_task_buffer_.setParent(id_from_buffer_.value());

  return StateFactory::create(StateType::ADD_TASK_NAME_PARAM_STATE);
}

void ParentTaskParamState::output() {
  ConsoleIO io;
  io.output("Enter parent task ID: ");
}

StateType ParentTaskParamState::getType() {
  return StateType::ADD_TASK_PARENT_PARAM_STATE;
}