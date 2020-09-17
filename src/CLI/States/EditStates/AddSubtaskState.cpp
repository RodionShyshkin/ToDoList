//
// Created by rodion on 8/31/20.
//

#include "AddSubtaskState.h"
#include "States/StateFactory.h"
#include <StateMachine.h>

bool AddSubtaskState::input() {
  return true;
}

std::shared_ptr<StateInterface> AddSubtaskState::run(std::shared_ptr<Context> &context) {
  if(context->show_list_buffer_.checkBufferFullness()) {
    if(context->show_list_buffer_.getList().empty()) return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  }

  auto machine_ = StateMachine::create(StatesGraphType::ADDSUBTASK, context);
  if(!machine_.execute()) return StateFactory::create(getStateTypeByCommand(Command::GETTASK));

  if(!context->add_task_buffer_.checkBufferFullness()) throw std::invalid_argument("Invalid AddSubtask State Machine");

  auto id_ = TaskID{context->add_task_buffer_.getParent()};
  auto dto_ = TaskDTO::create(0, context->add_task_buffer_.getName(), context->add_task_buffer_.getLabel(),
                              context->add_task_buffer_.getPriority(), context->add_task_buffer_.getDate(), false);

  auto result = context->service_->addSubtask(id_, dto_);
  if(!result.GetStatus()) throw std::invalid_argument("Wrong AddSubtask validation.");

  context->add_task_buffer_.clearBuffer();

  if(context->show_list_buffer_.checkBufferFullness()) {
    context->id_buffer_.clearBuffer();
    return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  }
  context->show_list_buffer_.clearBuffer();
  return StateFactory::create(getStateTypeByCommand(Command::GETTASK));
}

void AddSubtaskState::output() {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Adding subtask for an existing task.");
}

StateType AddSubtaskState::getType() {
  return StateType::ADD_SUBTASK_STATE;
}