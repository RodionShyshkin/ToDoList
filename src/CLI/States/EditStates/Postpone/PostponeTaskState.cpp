//
// Created by rodion on 8/25/20.
//

#include <StateMachine.h>
#include <States/StateFactory.h>
#include "PostponeTaskState.h"
#include "States/MainStates/ViewTaskListState.h"
#include "States/MainStates/ViewTaskState.h"
#include "NewDateParamState.h"

bool PostponeTaskState::input(const std::shared_ptr<IOInterface> &io_) {
  return true;
}

std::shared_ptr<StateInterface>  PostponeTaskState::run(std::shared_ptr<Context> &context) {
  if(context->show_list_buffer_.checkBufferFullness()) {
    if(context->show_list_buffer_.getList().empty()) return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  }

  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(!machine_.execute()) return StateFactory::create(this->getType());
  }
  return StateFactory::create(StateType::POSTPONE_TASK_NEW_DATE_PARAM_STATE);
}

void PostponeTaskState::output(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Postponing task.");
}

StateType PostponeTaskState::getType() {
  return StateType::POSTPONE_TASK_STATE;
}