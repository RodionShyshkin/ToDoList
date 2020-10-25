//
// Created by rodion on 10/19/20.
//

#include <States/StateFactory.h>
#include <ParamStateMachineFactory.h>
#include <Commands/CommandToStateType.h>
#include "PersistTasksState.h"

PersistTasksState::PersistTasksState(const PersistType &type) : type_(type) {}

StateResult PersistTasksState::run(std::shared_ptr<Context> context) {
  //Filling context.
  auto machine = ParamStateMachineFactory::PersistTasks::create(context);
  machine.execute();

  //Request to Core.
  auto filepath = context->filepath_buffer_.getFilepath();
  if(PersistType::SAVE == type_) {
    auto result = context->service_->Save(filepath);
    if(result.GetError().has_value()) return StateResult::OPERATION_ERROR;
  }
  else if(PersistType::LOAD == type_) {
    auto result = context->service_->Load(filepath);
    if(result.GetError().has_value()) return StateResult::OPERATION_ERROR;
  }

  //Clearing context.
  context->filepath_buffer_.clearBuffer();
  return StateResult::SUCCESS;
}

StateType PersistTasksState::getType() {
  if(PersistType::SAVE == this->type_) return StateType::SAVE_TASKS;
  else if(PersistType::LOAD == this->type_) return StateType::LOAD_TASKS;
  throw std::runtime_error("Not full if coverage of enum class in PersistTasksState");
}

bool PersistTasksState::input(const std::shared_ptr<IOInterface> &io) {
  return true;
}

void PersistTasksState::output(const std::shared_ptr<IOInterface> &io) {

}

std::unique_ptr<StateInterface> PersistTasksState::switchState() {
  auto newstate = StateFactory::create(CommandToStateType::Convert(Command::MAINMENU));
  return std::move(newstate);
}