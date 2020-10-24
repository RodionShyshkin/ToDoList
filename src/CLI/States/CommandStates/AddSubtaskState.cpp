//
// Created by rodion on 8/31/20.
//

#include <src/CLI/ParamStateMachineFactory.h>
#include <src/CLI/States/StateFactory.h>
#include "AddSubtaskState.h"

bool AddSubtaskState::input(const std::shared_ptr<IOInterface> &io) {
  return true;
}

StateResult AddSubtaskState::run(std::shared_ptr<Context> context) {
  auto machine = ParamStateMachineFactory::AddSubtask::create(context);
  machine.execute();

  if(context->add_task_buffer_.checkBufferFullness()) {
    auto id = context->add_task_buffer_.getParent();
    auto dto = TaskDTO::create(0, context->add_task_buffer_.getName(), context->add_task_buffer_.getLabel(),
                                context->add_task_buffer_.getPriority(), context->add_task_buffer_.getDate(), false);

    auto result = context->service_->addSubtask(id, dto);
    if (result.GetError().has_value()) throw std::invalid_argument("Wrong AddSubtask validation.");
  }

  context->add_task_buffer_.clearBuffer();

  if(context->show_list_buffer_.checkBufferFullness()) {
    context->id_buffer_.clearBuffer();
    task_list_flag_ = true;
    return StateResult::SUCCESS;
  }
  context->show_list_buffer_.clearBuffer();
  task_list_flag_ = false;
  return StateResult::SUCCESS;
}

void AddSubtaskState::output(const std::shared_ptr<IOInterface> &io) {  }

StateType AddSubtaskState::getType() {
  return StateType::ADD_SUBTASK;
}

std::unique_ptr<StateInterface> AddSubtaskState::switchState() {
  std::unique_ptr<StateInterface> newstate;
  if(task_list_flag_) newstate = StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  else newstate = StateFactory::create(getStateTypeByCommand(Command::GETTASK));
  return std::move(newstate);
}