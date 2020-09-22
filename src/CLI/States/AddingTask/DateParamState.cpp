//
// Created by rodion on 8/27/20.
//

#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <States/MainStates/ExitState.h>
#include <States/StateFactory.h>
#include "DateParamState.h"

StateResult DateParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);

  context->add_task_buffer_.setDate(this->param_);

  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::EXIT_STATE));
}

bool DateParamState::input(const std::shared_ptr<IOInterface> &io_) {
  auto parsed = DateParamState::parseParam(io_->input());
  if(!parsed.has_value()) return false;
  this->param_ = parsed.value();
  return true;
}

void DateParamState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->output("Enter task deadline (not required): ");
}

std::optional<boost::gregorian::date> DateParamState::parseParam(const std::string& param) {
  try{
    boost::gregorian::date result;
    if(param.empty()) result = boost::gregorian::date{boost::gregorian::not_a_date_time};
    else result = boost::gregorian::from_string(param);
    return std::make_optional<boost::gregorian::date>(result);
  }
  catch(const std::out_of_range&) {
    return std::nullopt;
  }
  catch(const std::invalid_argument&) {
    return std::nullopt;
  }
  catch(const boost::bad_lexical_cast&) {
    return std::nullopt;
  }
}

StateType DateParamState::getType() {
  return StateType::ADD_TASK_DATE_PARAM_STATE;
}