//
// Created by rodion on 8/21/20.
//


#include <src/CLI/ParamStateMachineFactory.h>
#include <src/CLI/States/StateFactory.h>
#include "RemoveTaskState.h"

bool RemoveTaskState::input(const std::shared_ptr<IOInterface> &io) { return true; }

StateResult RemoveTaskState::run(std::shared_ptr<Context> context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine = ParamStateMachineFactory::ShowSingleTask::create(context);
    machine.execute();
 }

  auto id_from_buffer_ = context->id_buffer_.getID();
  //if(!id_from_buffer_.has_value()) throw std::invalid_argument("I don't know such ID.");
  task_id_ = id_from_buffer_.value();

  auto result = context->service_->RemoveTask(this->task_id_);
  if(result.GetError().has_value()) return StateResult::OPERATION_ERROR;

  context->id_buffer_.clearBuffer();

  if(context->show_list_buffer_.checkBufferFullness()) {
    task_list_flag_ = true;
    return StateResult::SUCCESS;
  }
  task_list_flag_ = false;
  return StateResult::SUCCESS;
}

void RemoveTaskState::output(const std::shared_ptr<IOInterface> &io) {}

StateType RemoveTaskState::getType() {
  return StateType::REMOVE_TASK;
}

std::unique_ptr<StateInterface> RemoveTaskState::switchState() {
  std::unique_ptr<StateInterface> newstate;
  if(task_list_flag_) newstate = StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  else newstate = StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
  return std::move(newstate);
}