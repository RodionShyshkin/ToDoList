//
// Created by rodion on 8/31/20.
//

#include "AddSubtaskState.h"

bool AddSubtaskState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

StateResult AddSubtaskState::run(std::shared_ptr<Context> &context) {
  if(context->show_list_buffer_.checkBufferFullness()) {
    if(context->show_list_buffer_.getList().empty()) return StateResult::create(ErrorType::NO_ERRORS,
                                                                                StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST)));
  }

  auto machine_ = StateMachine::create(StatesMachineType::ADDSUBTASK, context);
  if(!machine_.execute()) return StateResult::create(ErrorType::FATAL_ERROR, nullptr);

  if(context->add_task_buffer_.checkBufferFullness()) {

    auto id = context->add_task_buffer_.getParent();
    auto dto = TaskDTO::create(0, context->add_task_buffer_.getName(), context->add_task_buffer_.getLabel(),
                                context->add_task_buffer_.getPriority(), context->add_task_buffer_.getDate(), false);

    auto result = context->service_->addSubtask(id, dto);
    if (!result.GetStatus()) throw std::invalid_argument("Wrong AddSubtask validation.");
  }

  context->add_task_buffer_.clearBuffer();

  if(context->show_list_buffer_.checkBufferFullness()) {
    context->id_buffer_.clearBuffer();
    return StateResult::create(ErrorType::NO_ERRORS,
                               StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST)));
  }
  context->show_list_buffer_.clearBuffer();
  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(getStateTypeByCommand(Command::GETTASK)));
}

void AddSubtaskState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: Adding subtask for an existing task.");
}

StateType AddSubtaskState::getType() {
  return StateType::ADD_SUBTASK_STATE;
}