//
// Created by rodion on 8/25/20.
//

#include <src/CLI/ParamStateMachineFactory.h>
#include <src/CLI/States/StateFactory.h>
#include "PostponeTaskState.h"

bool PostponeTaskState::input(const std::shared_ptr<IOInterface> &io) {
  return true;
}

StateResult PostponeTaskState::run(std::shared_ptr<Context> context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine = ParamStateMachineFactory::ShowSingleTask::create(context);
    machine.execute();
  }

  auto machine = ParamStateMachineFactory::PostponeTask::create(context);
  machine.execute();

  auto id = context->id_buffer_.getID().value();
  auto newdate = context->postpone_buffer_.getNewDate();

  auto result = context->service_->postponeTask(id, newdate);
  if(!result) return StateResult::OPERATION_ERROR;

  if(context->postpone_buffer_.getSingleTaskFlag()) return StateResult::SUCCESS;

  context->id_buffer_.clearBuffer();
  return StateResult::SUCCESS;
}

void PostponeTaskState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: Postponing task.");
}

StateType PostponeTaskState::getType() {
  return StateType::POSTPONE_TASK;
}

std::unique_ptr<StateInterface> PostponeTaskState::switchState() {
  std::unique_ptr<StateInterface> newstate;
  if(task_list_flag_) newstate = StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  else newstate = StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
  return std::move(newstate);
}