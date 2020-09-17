//
// Created by rodion on 9/5/20.
//

#include <States/StateFactory.h>
#include "NewDateParamState.h"
#include "States/MainStates/ViewTaskState.h"
#include "States/MainStates/ViewTaskListState.h"

bool NewDateParamState::input(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  this->param_ = io.input();
  return true;
}

std::shared_ptr<StateInterface> NewDateParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return nullptr;

  auto parsed = this->parseParam();
  if(!parsed.has_value()) return StateFactory::create(this->getType());

  context->postpone_buffer_.setNewDate(parsed.value());
  auto id_from_buffer_ = context->id_buffer_.getID();
  if(!id_from_buffer_.has_value()) throw std::invalid_argument("I don't know such ID.");

  auto id_ = TaskID{id_from_buffer_.value()};
  auto result = context->service_->postponeTask(id_, context->postpone_buffer_.getNewDate());
  if(!result.GetStatus()) return nullptr;

  if(context->postpone_buffer_.getSingleTaskFlag()) return StateFactory::create(getStateTypeByCommand(Command::GETTASK));
  context->id_buffer_.clearBuffer();
  return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
}

void NewDateParamState::output(const std::shared_ptr<IOInterface> &io_) {
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