//
// Created by rodion on 8/25/20.
//

#include <ParamStateMachineCreator.h>
#include <States/StateFactory.h>
#include <Commands/CommandToStateType.h>
#include "CompleteTaskState.h"

bool CompleteTaskState::input(const std::shared_ptr<IOInterface> &io) { return true; }

StateResult CompleteTaskState::run(std::shared_ptr<Context> context) {
  //Filling context.
  task_list_flag_ = false;
  if(!context->id_buffer_.checkBufferFullness()) {
    task_list_flag_ = true;
    auto machine = param_state_machine_creator::get_single_task_graph::create(context);
    machine.execute();
 }

  //Request to Core.
  auto id = context->id_buffer_.getID().value();
  auto result = context->service_->CompleteTask(id);
  if(!result) return StateResult::OPERATION_ERROR;

  //Clearing context.
  if(context->show_list_buffer_.checkBufferFullness()) {
    return StateResult::SUCCESS;
  }

  context->show_list_buffer_.clearBuffer();
  return StateResult::SUCCESS;
}

void CompleteTaskState::output(const std::shared_ptr<IOInterface> &io) { }

StateType CompleteTaskState::getType() {
  return StateType::COMPLETE_TASK;
}

std::unique_ptr<StateInterface> CompleteTaskState::switchState() {
  std::unique_ptr<StateInterface> newstate;
  if(task_list_flag_) newstate = StateFactory::create(command_to_state_type::Convert(Command::GETTASKLIST));
  else newstate = StateFactory::create(command_to_state_type::Convert(Command::GETTASK));
  return std::move(newstate);
}

