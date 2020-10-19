//
// Created by rodion on 10/19/20.
//

#include "SaveTasksState.h"

SaveTasksState::SaveTasksState(const PersisterType &type) : type_(type) {}

StateResult SaveTasksState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);


  if(PersisterType::SAVE == this->type_) {
    auto result = context->service_->Save(this->filepath_);
    if(result.GetError().has_value()) return StateResult::create(ErrorType::OPERATION_ERROR, nullptr);
  }
  else if(PersisterType::LOAD == this->type_) {
    auto result = context->service_->Load(this->filepath_);
    if(result.GetError().has_value()) return StateResult::create(ErrorType::OPERATION_ERROR, nullptr);
  }

  return StateResult::create(ErrorType::NO_ERRORS, StateFactory::create(getStateTypeByCommand(Command::MAINMENU)));
}

StateType SaveTasksState::getType() {
  if(PersisterType::SAVE == this->type_) return StateType::SAVE_TASKS_STATE;
  else if(PersisterType::LOAD == this->type_) return StateType::LOAD_TASKS_STATE;
  throw std::runtime_error("Not full if coverage of enum class in SaveTasksState");
}

bool SaveTasksState::input(const std::shared_ptr<IOInterface> &io) {
  this->filepath_ = io->input();
  return true;
}

void SaveTasksState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter a pathfile: ");
}