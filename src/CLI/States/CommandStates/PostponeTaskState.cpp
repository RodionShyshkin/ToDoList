//
// Created by rodion on 8/25/20.
//

#include <ParamStateMachineFactory.h>
#include <States/StateFactory.h>
#include <Commands/CommandToStateType.h>
#include "PostponeTaskState.h"

bool PostponeTaskState::input(const std::shared_ptr<IOInterface> &io) {
  return true;
}

StateResult PostponeTaskState::run(std::shared_ptr<Context> context) {
  //Filling context.
  if(!context->id_buffer_.checkBufferFullness()) {
    task_list_flag_ = true;
    auto machine = ParamStateMachineFactory::ShowSingleTask::create(context);
    machine.execute();
  } else task_list_flag_ = false;

  auto machine = ParamStateMachineFactory::PostponeTask::create(context);
  machine.execute();

  //Request to Core.
  auto id = context->id_buffer_.getID().value();
  auto newdate = context->postpone_buffer_.getNewDate();
  auto result = context->service_->postponeTask(id, newdate);
  if(!result) return StateResult::OPERATION_ERROR;

  //Clearing context.
  if(task_list_flag_) {
    context->id_buffer_.clearBuffer();
    return StateResult::SUCCESS;
  }
  return StateResult::SUCCESS;
}

void PostponeTaskState::output(const std::shared_ptr<IOInterface> &io) {
}

StateType PostponeTaskState::getType() {
  return StateType::POSTPONE_TASK;
}

std::unique_ptr<StateInterface> PostponeTaskState::switchState() {
  std::unique_ptr<StateInterface> newstate;
  if(task_list_flag_) newstate = StateFactory::create(CommandToStateType::Convert(Command::GETTASKLIST));
  else newstate = StateFactory::create(CommandToStateType::Convert(Command::GETTASK));
  return std::move(newstate);
}