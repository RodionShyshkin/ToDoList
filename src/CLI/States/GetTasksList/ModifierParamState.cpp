//
// Created by rodion on 8/28/20.
//

#include <random>
#include <States/StateFactory.h>
#include "ModifierParamState.h"
#include "SortedParamState.h"

bool ModifierParamState::input(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  this->param_ = io.input();
  return true;
}

std::shared_ptr<StateInterface> ModifierParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return nullptr;
  auto parsed = this->parseParam();
  if(parsed == ListModifier::UNKNOWN) return StateFactory::create(this->getType());

  context->show_list_buffer_.setModifier(parsed);
  return StateFactory::create(StateType::SHOW_LIST_SORTED_PARAM_STATE);
}

void ModifierParamState::output(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  io.output("Enter modifier [all/today/week/by_label]: ");
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