//
// Created by rodion on 8/28/20.
//

#include "ModifierParamState.h"

StateResult ModifierParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);

  context->show_list_buffer_.setModifier(this->param_);
  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::SHOW_LIST_SORTED_PARAM_STATE));
}

bool ModifierParamState::input(const std::shared_ptr<IOInterface> &io_) {
  this->param_ = ModifierParamState::parseParam(io_->input());
  if(this->param_ == ListModifier::UNKNOWN) return false;
  return true;
}

void ModifierParamState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->output("Enter modifier [all/today/week/by_label]: ");
}

ListModifier ModifierParamState::parseParam(const std::string& param) {
  if(param == "all") return ListModifier::ALL;
  else if(param == "today") return ListModifier::TODAY;
  else if(param == "week") return ListModifier::WEEK;
  else if(param == "by_label") return ListModifier::BY_LABEL;
  return ListModifier::UNKNOWN;
}

StateType ModifierParamState::getType() {
  return StateType::SHOW_LIST_MODIFIER_PARAM_STATE;
}