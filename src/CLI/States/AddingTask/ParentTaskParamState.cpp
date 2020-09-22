//
// Created by rodion on 9/1/20.
//

#include <StateMachine.h>
#include <StatesGraphType.h>
#include <States/StateFactory.h>
#include "ParentTaskParamState.h"
#include "NameParamState.h"

bool ParentTaskParamState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

StateResult ParentTaskParamState::run(std::shared_ptr<Context> &context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(!machine_.execute()) return StateResult::create(ErrorType::FATAL_ERROR, nullptr);
  }

  auto id_from_buffer_ = context->id_buffer_.getID();
  if(!id_from_buffer_.has_value()) throw std::invalid_argument("Invalid IDBuffer State Machine.");

  context->add_task_buffer_.setParent(id_from_buffer_.value());

  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::ADD_TASK_NAME_PARAM_STATE));
}

void ParentTaskParamState::output(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  io.output("Enter parent task ID: ");
}

StateType ParentTaskParamState::getType() {
  return StateType::ADD_TASK_PARENT_PARAM_STATE;
}