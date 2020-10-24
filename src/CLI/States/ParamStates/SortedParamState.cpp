//
// Created by rodion on 8/28/20.
//

#include "SortedParamState.h"

StateResult SortedParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  context->show_list_buffer_.setSortedFlag(param_);

  return StateResult::SUCCESS;
}

bool SortedParamState::input(const std::shared_ptr<IOInterface> &io) {
  auto parsed = SortedParamState::parseParam(io->input());
  if(!parsed.has_value()) return false;
  param_ = parsed.value();
  return true;
}

void SortedParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Do you want to sort list? [y/n]: ");
}

std::optional<bool> SortedParamState::parseParam(const std::string& param) {
  if(param == "y" || param == "yes") return true;
  else if(param == "n" || param == "no") return false;
  else return std::nullopt;
}

StateType SortedParamState::getType() {
  return StateType::LIST_SORTED_PARAM;
}

std::unique_ptr<StateInterface> SortedParamState::switchState() {
  return nullptr;
}