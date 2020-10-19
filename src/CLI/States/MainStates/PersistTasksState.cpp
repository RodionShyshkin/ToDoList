//
// Created by rodion on 10/19/20.
//

#include "PersistTasksState.h"

PersistTasksState::PersistTasksState(const PersistType &type) : type_(type) {}

StateResult PersistTasksState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);


  if(PersistType::SAVE == this->type_) {
    auto result = context->service_->Save(this->filepath_);
    if(result.GetError().has_value()) return StateResult::create(ErrorType::OPERATION_ERROR, nullptr);
  }
  else if(PersistType::LOAD == this->type_) {
    auto result = context->service_->Load(this->filepath_);
    if(result.GetError().has_value()) return StateResult::create(ErrorType::OPERATION_ERROR, nullptr);
  }

  return StateResult::create(ErrorType::NO_ERRORS, StateFactory::create(getStateTypeByCommand(Command::MAINMENU)));
}

StateType PersistTasksState::getType() {
  if(PersistType::SAVE == this->type_) return StateType::SAVE_TASKS_STATE;
  else if(PersistType::LOAD == this->type_) return StateType::LOAD_TASKS_STATE;
  throw std::runtime_error("Not full if coverage of enum class in PersistTasksState");
}

bool PersistTasksState::input(const std::shared_ptr<IOInterface> &io) {
  this->filepath_ = io->input();
  return true;
}

void PersistTasksState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter a pathfile: ");
}