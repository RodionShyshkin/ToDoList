//
// Created by rodion on 9/5/20.
//

#include <States/StateFactory.h>
#include "NewDateParamState.h"
#include "States/MainStates/ViewTaskState.h"
#include "States/MainStates/ViewTaskListState.h"

bool NewDateParamState::input() {
  ConsoleIO io;
  this->param_ = io.input();
  return true;
}

std::shared_ptr<StateInterface> NewDateParamState::run(std::shared_ptr<Context> &context) {
  this->output();

  if(!this->input()) return nullptr;

  auto parsed = this->parseParam();
  if(!parsed.has_value()) return nullptr;
  else {
    context->postpone_buffer_.setNewDate(parsed.value());
  }
  this->task_id_ = context->id_buffer_.getID().value();

  // Postpone.

  if(context->postpone_buffer_.getSingleTaskFlag()) return StateFactory::create(getStateTypeByCommand(Command::GETTASK));
  return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
}

void NewDateParamState::output() {
  ConsoleIO io;
  io.output("Enter new date (not required) [yyyy-mm-dd]: ");
}

StateType NewDateParamState::getType() {
  return StateType::POSTPONE_TASK_STATE;
}

std::optional<boost::gregorian::date> NewDateParamState::parseParam() const {
  boost::gregorian::date temporary_;
  try {
    temporary_ = boost::gregorian::from_string(this->param_);
  }
  catch(const std::invalid_argument&) {
    return std::nullopt;
  }
  return temporary_;
}