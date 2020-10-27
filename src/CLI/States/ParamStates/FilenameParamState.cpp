//
// Created by rodion on 10/24/20.
//

#include <States/Validator.h>
#include "FilenameParamState.h"

StateResult FilenameParamState::run(std::shared_ptr<Context> context) {
  output(context->io_);
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;

  context->filepath_buffer_.setFilepath(filename_);

  return StateResult::SUCCESS;
}

StateType FilenameParamState::getType() {
  return StateType::FILENAME_PARAM;
}

std::unique_ptr<StateInterface> FilenameParamState::switchState() {
  return nullptr;
}

bool FilenameParamState::input(const std::shared_ptr<IOInterface> &io) {
  filename_ = io->input();
  return Validator::ValidateFilename(filename_);
}

void FilenameParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter filepath: ");
}
