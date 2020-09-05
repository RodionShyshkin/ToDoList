//
// Created by rodion on 9/5/20.
//

#include "NewDateParamState.h"
#include "ViewTaskState.h"
#include "ViewTaskListState.h"

bool NewDateParamState::input() {
  std::string stringParam;
  stringParam = "2020-10-10";
  param_ = stringParam;
  return true;
}

std::shared_ptr<StateInterface> NewDateParamState::run(std::unique_ptr<Context> &context) {
  input();
  output();
  auto parsed = parseParam();
  if(!parsed.has_value()) return nullptr;
  else {
    context->postpone_date_.new_date_ = parsed.value();
  }

  // Postpone.

  if(context->postpone_date_.is_single_task_) return std::make_shared<ViewTaskState>();
  else return std::make_shared<ViewTaskListState>();
}

void NewDateParamState::output() {
  std::cout << "[Output]: Getting date for postpone." << std::endl;
}

StateType NewDateParamState::getType() {
  return StateType::POSTPONE_TASK_STATE;
}
/*
bool NewDateParamState::validateParam() const {
  try {
    boost::gregorian::date temporary_ = boost::gregorian::from_string(this->param_);
  }
  catch(const std::invalid_argument&) {
    return false;
  }
  return true;
}*/

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