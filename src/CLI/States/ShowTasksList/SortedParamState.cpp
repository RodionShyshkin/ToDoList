//
// Created by rodion on 8/28/20.
//

#include <random>
#include "SortedParamState.h"
#include "ShowListExitState.h"

bool SortedParamState::input() {
  std::string stringParam;
//  std::cin >> stringCommand;
//  std::getline(std::cin, stringCommand);
  std::cout << "RUNS" << std::endl;
  std::random_device rd;
  std::mt19937 mersenne(rd());
  auto k = mersenne() % 2;
  if(k == 0) stringParam = "no_sort";
  else if(k == 1) stringParam = "sort";
//  stringParam = "no_sort";

  this->param_ = stringParam;
  return true;
}

std::shared_ptr<ShowListStateInterface> SortedParamState::run(std::unique_ptr<ShowListContext> &context) {
  output();
  input();
  auto parsed = parseParam();
  if(!parsed.has_value()) return nullptr;
  else {
    context->updateContext(context->getModifier(), parsed.value());
  }
  return std::make_shared<ShowListExitState>();
}

void SortedParamState::output() {
  std::cout << "[Output]: ShowTasksList state machine / Sorted parameter" << std::endl;
}

std::optional<bool> SortedParamState::parseParam() const {
  if(this->param_ == "sort") return true;
  else if(this->param_ == "no_sort") return false;
  else return std::nullopt;
}