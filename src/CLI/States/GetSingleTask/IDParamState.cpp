//
// Created by rodion on 9/2/20.
//

#include "IDParamState.h"

StateResult IDParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);

  auto list = context->show_list_buffer_.getList();
  if(this->param_ >= list.size()) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);

  context->id_buffer_.setID(list[this->param_].getID());

  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::EXIT_STATE));
}

bool IDParamState::input(const std::shared_ptr<IOInterface> &io_) {
  try {
    this->param_ = std::stoi(io_->input());
  }
  catch(const std::invalid_argument&) {
    return false;
  }
  catch(const std::out_of_range&) {
    return false;
  }
  return true;
}

void IDParamState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->output("Enter task ID: ");
}

StateType IDParamState::getType() {
  return StateType::SHOW_SINGLE_ID_PARAM_STATE;
}