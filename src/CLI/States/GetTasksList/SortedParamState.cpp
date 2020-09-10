//
// Created by rodion on 8/28/20.
//

#include <random>
#include <States/MainStates/ExitState.h>
#include <States/StateFactory.h>
#include "SortedParamState.h"

bool SortedParamState::input() {
  ConsoleIO io;
  this->param_ = io.input();
  return true;
}

std::shared_ptr<StateInterface> SortedParamState::run(std::shared_ptr<Context> &context) {
  if(!this->input()) return nullptr;
  auto parsed = this->parseParam();
  if(!parsed.has_value()) return nullptr;
  this->output();

  context->show_list_buffer_.setSortedFlag(parsed.value());
  return StateFactory::create(StateType::EXIT_STATE);
}

void SortedParamState::output() {
  ConsoleIO io;
  io.output("[Output]: ShowTasksList state machine / Sorted parameter");
}

std::optional<bool> SortedParamState::parseParam() const {
  if(this->param_ == "sort") return true;
  else if(this->param_ == "no_sort") return false;
  else return std::nullopt;
}

StateType SortedParamState::getType() {
  return StateType::SHOW_LIST_SORTED_PARAM_STATE;
}