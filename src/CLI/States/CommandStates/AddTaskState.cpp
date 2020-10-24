//
// Created by rodion on 8/21/20.
//

#include <ParamStateMachineFactory.h>
#include <States/StateFactory.h>
#include "AddTaskState.h"

bool AddTaskState::input(const std::shared_ptr<IOInterface> &io) { return true; }

StateResult AddTaskState::run(std::shared_ptr<Context> context) {
  auto machine = ParamStateMachineFactory::AddTask::create(context);
  machine.execute();

  if(!context->add_task_buffer_.checkBufferFullness()) throw std::invalid_argument("Invalid AddTask State machine");

  auto dto = TaskDTO::create(0, context->add_task_buffer_.getName(), context->add_task_buffer_.getLabel(),
                              context->add_task_buffer_.getPriority(), context->add_task_buffer_.getDate(), false);
  auto result = context->service_->addTask(dto);
  if(result.GetError().has_value()) return StateResult::OPERATION_ERROR;

  context->add_task_buffer_.clearBuffer();

  return StateResult::SUCCESS;
}

void AddTaskState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: Adding new task.");
}

StateType AddTaskState::getType() {
  return StateType::ADD_TASK;
}

std::unique_ptr<StateInterface> AddTaskState::switchState() {
  auto newstate = StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
  return std::move(newstate);
}