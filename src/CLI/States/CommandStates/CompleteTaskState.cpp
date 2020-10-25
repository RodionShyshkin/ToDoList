//
// Created by rodion on 8/25/20.
//

#include <ParamStateMachineFactory.h>
#include <States/StateFactory.h>
#include "CompleteTaskState.h"

bool CompleteTaskState::input(const std::shared_ptr<IOInterface> &io) { return true; }

StateResult CompleteTaskState::run(std::shared_ptr<Context> context) {
  task_list_flag_ = false;
  std::cout << context->id_buffer_.checkBufferFullness() << std::endl;
  if(!context->id_buffer_.checkBufferFullness()) {
    task_list_flag_ = true;
    auto machine = ParamStateMachineFactory::ShowSingleTask::create(context);
    machine.execute();
 }

  task_id_ = context->id_buffer_.getID().value();

  auto result = context->service_->completeTask(task_id_);
  if(!result) return StateResult::OPERATION_ERROR;

  if(context->show_list_buffer_.checkBufferFullness()) {
    return StateResult::SUCCESS;
  }

  context->show_list_buffer_.clearBuffer();
  return StateResult::SUCCESS;
}

void CompleteTaskState::output(const std::shared_ptr<IOInterface> &io_) { }

StateType CompleteTaskState::getType() {
  return StateType::COMPLETE_TASK;
}

std::unique_ptr<StateInterface> CompleteTaskState::switchState() {
  std::unique_ptr<StateInterface> newstate;
  if(task_list_flag_) newstate = StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  else newstate = StateFactory::create(getStateTypeByCommand(Command::GETTASK));
  return std::move(newstate);
}

