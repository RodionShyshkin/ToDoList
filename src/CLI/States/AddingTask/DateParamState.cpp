//
// Created by rodion on 8/27/20.
//

#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <States/ExitState.h>
#include "DateParamState.h"

bool DateParamState::input() {
  std::string stringParam;
//  std::cin >> stringCommand;
//  std::getline(std::cin, stringCommand);
  srand(time(NULL));
  auto k = rand() % 4;
  stringParam = "2019-1-1";
  param_ = stringParam;
  return true;
}

std::shared_ptr<StateInterface> DateParamState::run(std::unique_ptr<Context> &context) {
  output();
  input();
  auto validated = parseParam();
  if(!validated.has_value()) return nullptr;
  else {
    //context->date_ = validated.value();
    context->add_task_buffer_.setDate(validated.value());
    return std::make_shared<ExitState>();
  }
}

void DateParamState::output() {
  std::cout << "[Output]: AddTask state machine / Enter date" << std::endl;
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