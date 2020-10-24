//
// Created by rodion on 8/28/20.
//

#include "ModifierParamState.h"

StateResult ModifierParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  context->show_list_buffer_.setModifier(param_);

  return StateResult::SUCCESS;
}

bool ModifierParamState::input(const std::shared_ptr<IOInterface> &io) {
  param_ = ModifierParamState::parseParam(io->input());
  if(param_ == ListModifier::UNKNOWN) return false;
  return true;
}

void ModifierParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter modifier [all/today/week/by_label]: ");
}

ListModifier ModifierParamState::parseParam(const std::string& param) {
  if(param == "all") return ListModifier::ALL;
  else if(param == "today") return ListModifier::TODAY;
  else if(param == "week") return ListModifier::WEEK;
  else if(param == "by_label") return ListModifier::BY_LABEL;
  return ListModifier::UNKNOWN;
}

StateType ModifierParamState::getType() {
  return StateType::LIST_MODIFIER_PARAM;
}

std::unique_ptr<StateInterface> ModifierParamState::switchState() {
  return nullptr;
}