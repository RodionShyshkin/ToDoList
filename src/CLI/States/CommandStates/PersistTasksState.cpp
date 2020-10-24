//
// Created by rodion on 10/19/20.
//

#include <States/StateFactory.h>
#include "PersistTasksState.h"

PersistTasksState::PersistTasksState(const PersistType &type) : type_(type) {}

StateResult PersistTasksState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;


  if(PersistType::SAVE == type_) {
    auto result = context->service_->Save(filepath_);
    if(result.GetError().has_value()) return StateResult::OPERATION_ERROR;
  }
  else if(PersistType::LOAD == type_) {
    auto result = context->service_->Load(filepath_);
    if(result.GetError().has_value()) return StateResult::OPERATION_ERROR;
  }

  return StateResult::SUCCESS;
}

StateType PersistTasksState::getType() {
  if(PersistType::SAVE == this->type_) return StateType::SAVE_TASKS;
  else if(PersistType::LOAD == this->type_) return StateType::LOAD_TASKS;
  throw std::runtime_error("Not full if coverage of enum class in PersistTasksState");
}

bool PersistTasksState::input(const std::shared_ptr<IOInterface> &io) {
  this->filepath_ = io->input();
  return true;
}

void PersistTasksState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter a pathfile: ");
}

std::unique_ptr<StateInterface> PersistTasksState::switchState() {
  auto newstate = StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
  return std::move(newstate);
}