//
// Created by rodion on 9/2/20.
//

#include "SingleTaskStartState.h"

StateResult SingleTaskStartState::run(std::shared_ptr<Context> &context) {
  if(!context->show_list_buffer_.checkBufferFullness()) return StateResult::create(ErrorType::FATAL_ERROR, nullptr);

  if(context->show_list_buffer_.getList().empty()) return StateResult::create(ErrorType::NO_ERRORS,
                                                                              StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST)));
  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::SHOW_SINGLE_ID_PARAM_STATE));
}

bool SingleTaskStartState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

void SingleTaskStartState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: Show single task / Start");
}

StateType SingleTaskStartState::getType() {
  return StateType::SHOW_SINGLE_START_STATE;
}