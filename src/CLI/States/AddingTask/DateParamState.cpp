//
// Created by rodion on 8/27/20.
//

#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include "DateParamState.h"
#include "AddTaskExitState.h"

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

std::shared_ptr<AddTaskStateInterface> DateParamState::run(std::unique_ptr<AddTaskContext> &context) {
  output();
  input();
  auto validated = parseParam();
  if(!validated.has_value()) return nullptr;
  else {
    //context->date_ = validated.value();
    context->updateContext(context->getName(), context->getLabel(), context->getPriority(), validated.value(),
                           context->getParent());
    return std::make_shared<AddTaskExitState>();
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