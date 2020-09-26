//
// Created by rodion on 8/26/20.
//

#include "AddTaskStartState.h"

AddTaskStartState::AddTaskStartState(const bool &is_subtask) : is_subtask_(is_subtask) {}

bool AddTaskStartState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

StateResult AddTaskStartState::run(std::shared_ptr<Context> &context) {
  if(this->is_subtask_) {
    if(context->show_list_buffer_.checkBufferFullness()) {
      if (context->show_list_buffer_.getList().empty()) return StateResult::create(ErrorType::NO_ERRORS,
                                                                                   StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST)));
    }
    return StateResult::create(ErrorType::NO_ERRORS,
                               StateFactory::create(StateType::ADD_TASK_PARENT_PARAM_STATE));
  }
  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::ADD_TASK_NAME_PARAM_STATE));
}

void AddTaskStartState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: AddTask state machine / Start State");
}

StateType AddTaskStartState::getType() {
  return StateType::ADD_TASK_START_STATE;
}