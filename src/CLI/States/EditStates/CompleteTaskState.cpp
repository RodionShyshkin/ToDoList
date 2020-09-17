//
// Created by rodion on 8/25/20.
//

#include <StateMachine.h>
#include <States/StateFactory.h>
#include "CompleteTaskState.h"
#include "States/MainStates/ViewTaskListState.h"
#include "States/MainStates/ViewTaskState.h"

bool CompleteTaskState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

std::shared_ptr<StateInterface>  CompleteTaskState::run(std::shared_ptr<Context> &context) {
  if(context->show_list_buffer_.checkBufferFullness()) {
    if(context->show_list_buffer_.getList().empty()) return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  }

  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(!machine_.execute()) return StateFactory::create(this->getType());
 }

  auto id_from_buffer_ = context->id_buffer_.getID();
  if(!id_from_buffer_.has_value()) throw std::invalid_argument("I don't know such ID.");
  this->task_id_ = id_from_buffer_.value();

  auto result = context->service_->completeTask(TaskID{this->task_id_});
  if(!result.GetStatus()) return nullptr;

  if(context->show_list_buffer_.checkBufferFullness()) {
    context->id_buffer_.clearBuffer();
    return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  }
  context->show_list_buffer_.clearBuffer();
  return StateFactory::create(getStateTypeByCommand(Command::GETTASK));
}

void CompleteTaskState::output(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Completing task.");
}

StateType CompleteTaskState::getType() {
  return StateType::COMPLETE_TASK_STATE;
}