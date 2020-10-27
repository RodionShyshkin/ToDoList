//
// Created by rodion on 8/21/20.
//


#include <ParamStateMachineCreator.h>
#include <States/StateFactory.h>
#include <Commands/CommandToStateType.h>
#include "RemoveTaskState.h"

bool RemoveTaskState::input(const std::shared_ptr<IOInterface> &io) { return true; }

StateResult RemoveTaskState::run(std::shared_ptr<Context> context) {
  //Filling context.
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine = param_state_machine_creator::get_single_task_graph::create(context);
    machine.execute();
 }

  //Request to Core.
  auto id = context->id_buffer_.getID().value();
  auto result = context->service_->RemoveTask(id);
  if(result.GetError().has_value()) {
    return StateResult::OPERATION_ERROR;
  }

  //Clearing context.
  context->id_buffer_.clearBuffer();

  if(context->show_list_buffer_.checkBufferFullness()) {
    task_list_flag_ = true;
    return StateResult::SUCCESS;
  }
  task_list_flag_ = false;
  return StateResult::SUCCESS;
}

void RemoveTaskState::output(const std::shared_ptr<IOInterface> &io) {}

StateType RemoveTaskState::getType() const {
  return StateType::REMOVE_TASK;
}

std::unique_ptr<StateInterface> RemoveTaskState::switchState() {
  std::unique_ptr<StateInterface> newstate;
  if(task_list_flag_) newstate = StateFactory::create(command_to_state_type::Convert(Command::GETTASKLIST));
  else newstate = StateFactory::create(command_to_state_type::Convert(Command::MAINMENU));
  return std::move(newstate);
}