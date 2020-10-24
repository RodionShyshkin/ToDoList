//
// Created by rodion on 9/2/20.
//

#include "IDParamState.h"

StateResult IDParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  auto list = context->show_list_buffer_.getList();
  if(param_ >= list.size()) return StateResult::INCORRECT_INPUT;

  context->id_buffer_.setID(list[param_].getID());

  return StateResult::SUCCESS;
}

bool IDParamState::input(const std::shared_ptr<IOInterface> &io) {
  try {
    param_ = std::stoi(io->input());
  }
  catch(const std::invalid_argument&) {
    return false;
  }
  catch(const std::out_of_range&) {
    return false;
  }
  return true;
}

void IDParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter task ID: ");
}

StateType IDParamState::getType() {
  return StateType::TASK_ID_PARAM;
}

std::unique_ptr<StateInterface> IDParamState::switchState() {
  return nullptr;
}