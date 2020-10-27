//
// Created by rodion on 8/21/20.
//

#include <ParamStateMachineCreator.h>
#include <States/StateFactory.h>
#include <Commands/CommandToStateType.h>
#include "AddTaskState.h"

bool AddTaskState::input(const std::shared_ptr<IOInterface> &io) { return true; }

StateResult AddTaskState::run(std::shared_ptr<Context> context) {
  //Filling context.
  auto machine = param_state_machine_creator::add_task_graph::create(context);
  machine.execute();

  //Request to core.
  auto dto = TaskDTO::Create(0, context->add_task_buffer_.getName(), context->add_task_buffer_.getLabel(),
                             context->add_task_buffer_.getPriority(), context->add_task_buffer_.getDate(), false);
  auto result = context->service_->AddTask(dto);
  if(result.GetError().has_value()) return StateResult::OPERATION_ERROR;

  //Clearing context.
  context->add_task_buffer_.clearBuffer();

  return StateResult::SUCCESS;
}

void AddTaskState::output(const std::shared_ptr<IOInterface> &io) {
}

StateType AddTaskState::getType() {
  return StateType::ADD_TASK;
}

std::unique_ptr<StateInterface> AddTaskState::switchState() {
  auto newstate = StateFactory::create(command_to_state_type::Convert(Command::MAINMENU));
  return std::move(newstate);
}