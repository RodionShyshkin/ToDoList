//
// Created by rodion on 8/21/20.
//

#include "AddTaskState.h"

bool AddTaskState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

StateResult AddTaskState::run(std::shared_ptr<Context> &context) {
  auto machine_ = StateMachine::create(StatesMachineType::ADDTASK, context);
  if(!machine_.execute()) return StateResult::create(
      ErrorType::FATAL_ERROR,
      nullptr
      );

  if(!context->add_task_buffer_.checkBufferFullness()) throw std::invalid_argument("Invalid AddTask State machine");

  auto dto_ = TaskDTO::create(0, context->add_task_buffer_.getName(), context->add_task_buffer_.getLabel(),
                              context->add_task_buffer_.getPriority(), context->add_task_buffer_.getDate(), false);
  auto result = context->service_->addTask(dto_);
  if(result.GetError().has_value()) throw std::invalid_argument("Wrong AddTask validation");

  context->add_task_buffer_.clearBuffer();

  return StateResult::create(
      ErrorType::NO_ERRORS,
      StateFactory::create(getStateTypeByCommand(Command::MAINMENU))
      );
}

void AddTaskState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: Adding new task.");
}

StateType AddTaskState::getType() {
  return StateType::ADD_TASK_STATE;
}