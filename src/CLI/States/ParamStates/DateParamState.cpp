//
// Created by rodion on 8/27/20.
//

#include "DateParamState.h"

StateResult DateParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  context->add_task_buffer_.setDate(param_);

  return StateResult::SUCCESS;
}

bool DateParamState::input(const std::shared_ptr<IOInterface> &io) {
  auto parsed = DateParamState::parseParam(io->input());
  if(!parsed.has_value()) return false;
  param_ = parsed.value();
  return true;
}

void DateParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter deadline: ");
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
  return StateType::TASK_DATE_PARAM;
}

std::unique_ptr<StateInterface> DateParamState::switchState() {
  return nullptr;
}