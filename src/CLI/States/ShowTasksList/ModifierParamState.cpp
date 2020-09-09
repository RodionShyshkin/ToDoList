//
// Created by rodion on 8/28/20.
//

#include <random>
#include "ModifierParamState.h"
#include "SortedParamState.h"

bool ModifierParamState::input() {
  std::string stringParam;
//  std::cin >> stringCommand;
//  std::getline(std::cin, stringCommand);
  std::cout << "RUNS" << std::endl;
  std::random_device rd;
  std::mt19937 mersenne(rd());
  auto k = mersenne() % 4;
  if(k == 0) stringParam = "all";
  else if(k == 1) stringParam = "today";
  else if(k == 2) stringParam = "week";
  else stringParam = "by_label";
  stringParam = "all";

  this->param_ = stringParam;
  return true;
}

std::shared_ptr<StateInterface> ModifierParamState::run(std::shared_ptr<Context> &context) {
  output();
  input();
  auto parsed = parseParam();
  if(parsed == ListModifier::UNKNOWN) return nullptr;
  context->show_list_buffer_.setModifier(parsed);
  return std::make_shared<SortedParamState>();
}

void ModifierParamState::output() {
  std::cout << "[Output]: ShowTasksList state machine / getting parameter" << std::endl;
}

ListModifier ModifierParamState::parseParam() const {
  if(param_ == "all") return ListModifier::ALL;
  else if(param_ == "today") return ListModifier::TODAY;
  else if(param_ == "week") return ListModifier::WEEK;
  else if(param_ == "by_label") return ListModifier::BY_LABEL;
  return ListModifier::UNKNOWN;
}

StateType ModifierParamState::getType() {
  return StateType::SHOW_LIST_MODIFIER_PARAM_STATE;
}