//
// Created by rodion on 8/27/20.
//

#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <States/MainStates/ExitState.h>
#include <States/StateFactory.h>
#include "DateParamState.h"

bool DateParamState::input() {
  ConsoleIO io;
  this->param_ = io.input();
  return true;
}

std::shared_ptr<StateInterface> DateParamState::run(std::shared_ptr<Context> &context) {
  this->output();
  if(!this->input()) return nullptr;

  auto validated = this->parseParam();
  if(!validated.has_value()) return nullptr;

  context->add_task_buffer_.setDate(validated.value());
  return StateFactory::create(StateType::EXIT_STATE);
}

void DateParamState::output() {
  ConsoleIO io;
  io.output("[Output]: AddTask state machine / Enter date");
}

std::optional<boost::gregorian::date> DateParamState::parseParam() const {
  try{
    boost::gregorian::date d = boost::gregorian::from_string(param_);
    return std::make_optional<boost::gregorian::date>(d);
  }
  catch(const std::out_of_range &e) {
    return std::nullopt;
  }
}

StateType DateParamState::getType() {
  return StateType::ADD_TASK_STATE;
}