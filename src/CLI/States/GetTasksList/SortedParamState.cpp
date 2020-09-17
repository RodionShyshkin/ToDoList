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
  this->output();
  if(!this->input()) return nullptr;
  auto parsed = this->parseParam();
  if(!parsed.has_value()) return StateFactory::create(this->getType());

  context->show_list_buffer_.setSortedFlag(parsed.value());
  if(context->show_list_buffer_.getModifier() == ListModifier::BY_LABEL) return StateFactory::create(StateType::ADD_TASK_LABEL_PARAM_STATE);
  return StateFactory::create(StateType::EXIT_STATE);
}

void SortedParamState::output() {
  ConsoleIO io;
  io.output("Do you want to sort list? [y/n]: ");
}

std::optional<bool> SortedParamState::parseParam() const {
  if(this->param_ == "y" || this->param_ == "yes") return true;
  else if(this->param_ == "n" || this->param_ == "no") return false;
  else return std::nullopt;
}

StateType SortedParamState::getType() {
  return StateType::SHOW_LIST_SORTED_PARAM_STATE;
}