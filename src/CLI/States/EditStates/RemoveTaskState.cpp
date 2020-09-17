//
// Created by rodion on 8/21/20.
//


#include <StateMachine.h>
#include "RemoveTaskState.h"
#include "States/MainStates/MainMenuState.h"

bool RemoveTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  RemoveTaskState::run(std::shared_ptr<Context> &context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(!machine_.execute()) return StateFactory::create(this->getType());
 }
  auto id_from_buffer_ = context->id_buffer_.getID();
  if(!id_from_buffer_.has_value()) throw std::invalid_argument("I don't know such ID.");
  this->task_id_ = id_from_buffer_.value();

  auto id_ = TaskID{this->task_id_};
  auto result = context->service_->RemoveTask(id_);
  if(!result.GetStatus()) return nullptr;

  context->id_buffer_.clearBuffer();
  if(context->show_list_buffer_.checkBufferFullness()) return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  context->show_list_buffer_.clearBuffer();
  return StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
}

void RemoveTaskState::output() {}

StateType RemoveTaskState::getType() {
  return StateType::REMOVE_TASK_STATE;
}