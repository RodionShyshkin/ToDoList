//
// Created by rodion on 8/28/20.
//

#include <random>
#include <States/MainStates/ExitState.h>
#include <States/StateFactory.h>
#include "SortedParamState.h"



StateResult SortedParamState::run(std::shared_ptr<Context> &context) {
  this->output(context->io_);
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);

  context->show_list_buffer_.setSortedFlag(this->param_);
  if(context->show_list_buffer_.getByLabelFlag()) return StateResult::create(ErrorType::NO_ERRORS,
                                                                                     StateFactory::create(StateType::ADD_TASK_LABEL_PARAM_STATE));

  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(StateType::EXIT_STATE));
}

bool SortedParamState::input(const std::shared_ptr<IOInterface> &io_) {
  auto parsed = SortedParamState::parseParam(io_->input());
  if(!parsed.has_value()) return false;
  this->param_ = parsed.value();
  return true;
}

void SortedParamState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->output("Do you want to sort list? [y/n]: ");
}

std::optional<bool> SortedParamState::parseParam(const std::string& param) {
  if(param == "y" || param == "yes") return true;
  else if(param == "n" || param == "no") return false;
  else return std::nullopt;
}

StateType SortedParamState::getType() {
  return StateType::SHOW_LIST_SORTED_PARAM_STATE;
}