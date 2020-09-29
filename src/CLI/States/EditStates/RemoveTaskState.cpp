//
// Created by rodion on 8/21/20.
//


#include "RemoveTaskState.h"

bool RemoveTaskState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

StateResult RemoveTaskState::run(std::shared_ptr<Context> &context) {
  if(context->show_list_buffer_.checkBufferFullness()) {
    if(context->show_list_buffer_.getList().empty()) return StateResult::create(ErrorType::NO_ERRORS,
                                                                                StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST)));
  }

  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesMachineType::GET_SINGLE_TASK, context);
    if(!machine_.execute()) return StateResult::create(ErrorType::NO_ERRORS, nullptr);
 }
  auto id_from_buffer_ = context->id_buffer_.getID();
  if(!id_from_buffer_.has_value()) throw std::invalid_argument("I don't know such ID.");
  this->task_id_ = id_from_buffer_.value();

  auto result = context->service_->RemoveTask(this->task_id_);
  if(!result.GetStatus()) return StateResult::create(ErrorType::OPERATION_ERROR, nullptr);

  context->id_buffer_.clearBuffer();
  if(context->show_list_buffer_.checkBufferFullness()) return StateResult::create(ErrorType::NO_ERRORS,
                                                                          StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST)));
  context->show_list_buffer_.clearBuffer();
  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(getStateTypeByCommand(Command::MAINMENU)));
}

void RemoveTaskState::output(const std::shared_ptr<IOInterface> &io_) {}

StateType RemoveTaskState::getType() {
  return StateType::REMOVE_TASK_STATE;
}