//
// Created by rodion on 9/5/20.
//

#include "NewDateParamState.h"

StateResult NewDateParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);

  context->postpone_buffer_.setNewDate(this->param_);
  auto id_from_buffer_ = context->id_buffer_.getID();
  if(!id_from_buffer_.has_value()) throw std::invalid_argument("I don't know such ID.");

  auto id = id_from_buffer_.value();
  auto result = context->service_->postponeTask(id, context->postpone_buffer_.getNewDate());
  if(!result.GetStatus()) return StateResult::create(ErrorType::OPERATION_ERROR, nullptr);

  if(context->postpone_buffer_.getSingleTaskFlag()) return StateResult::create(ErrorType::NO_ERRORS,
                                                                               StateFactory::create(getStateTypeByCommand(Command::GETTASK)));
  context->id_buffer_.clearBuffer();
  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST)));
}

bool NewDateParamState::input(const std::shared_ptr<IOInterface> &io_) {
  auto parsed = NewDateParamState::parseParam(io_->input());
  if(!parsed.has_value()) return false;
  this->param_ = parsed.value();
  return true;
}

void NewDateParamState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->output("Enter new date (not required) [yyyy-mm-dd]: ");
}

StateType NewDateParamState::getType() {
  return StateType::POSTPONE_TASK_STATE;
}

std::optional<boost::gregorian::date> NewDateParamState::parseParam(const std::string& param) {
  boost::gregorian::date temporary_;
  try {
    temporary_ = boost::gregorian::from_string(param);
  }
  catch(const std::invalid_argument&) {
    return std::nullopt;
  }
  return temporary_;
}