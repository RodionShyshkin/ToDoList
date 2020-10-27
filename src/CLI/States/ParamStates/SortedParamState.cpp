//
// Created by rodion on 8/28/20.
//

#include <States/Validator.h>
#include "SortedParamState.h"

StateResult SortedParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  context->show_list_buffer_.setSortedFlag(param_);

  return StateResult::SUCCESS;
}

bool SortedParamState::input(const std::shared_ptr<IOInterface> &io) {
  auto parsed = validator::ParseBoolFlag(io->input());
  if(!parsed.has_value()) return false;
  param_ = parsed.value();
  return true;
}

void SortedParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Do you want to sort list? [y/n]: ");
}

StateType SortedParamState::getType() const {
  return StateType::LIST_SORTED_PARAM;
}

std::unique_ptr<StateInterface> SortedParamState::switchState() {
  return nullptr;
}