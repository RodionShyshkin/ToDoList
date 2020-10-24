//
// Created by rodion on 8/25/20.
//

#include <src/CLI/ParamStateMachineFactory.h>
#include <src/CLI/States/StateFactory.h>
#include "CompleteTaskState.h"

bool CompleteTaskState::input(const std::shared_ptr<IOInterface> &io) { return true; }

StateResult CompleteTaskState::run(std::shared_ptr<Context> context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine = ParamStateMachineFactory::ShowSingleTask::create(context);
    machine.execute();
 }

  auto id_from_buffer = context->id_buffer_.getID();
  //if(!id_from_buffer_.has_value()) throw std::invalid_argument("I don't know such ID.");
  task_id_ = id_from_buffer.value();

  auto result = context->service_->completeTask(this->task_id_);
  if(!result) return StateResult::OPERATION_ERROR;

  if(context->show_list_buffer_.checkBufferFullness()) {
    task_list_flag_ = true;
    context->id_buffer_.clearBuffer();
    return StateResult::SUCCESS;
  }
  task_list_flag_ = false;
  context->show_list_buffer_.clearBuffer();
  return StateResult::SUCCESS;
}

void CompleteTaskState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: Completing task.");
}

StateType CompleteTaskState::getType() {
  return StateType::COMPLETE_TASK;
}

std::unique_ptr<StateInterface> CompleteTaskState::switchState() {
  std::unique_ptr<StateInterface> newstate;
  if(task_list_flag_) newstate = StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  else newstate = StateFactory::create(getStateTypeByCommand(Command::GETTASK));
  return std::move(newstate);
}

