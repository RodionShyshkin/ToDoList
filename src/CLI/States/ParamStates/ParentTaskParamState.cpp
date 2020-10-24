//
// Created by rodion on 9/1/20.
//

#include <ParamStateMachineFactory.h>
#include "ParentTaskParamState.h"

bool ParentTaskParamState::input(const std::shared_ptr<IOInterface> &io) {
  return true;
}

StateResult ParentTaskParamState::run(std::shared_ptr<Context> context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine = ParamStateMachineFactory::ShowSingleTask::create(context);
    machine.execute();
  }

  return StateResult::SUCCESS;
}

void ParentTaskParamState::output(const std::shared_ptr<IOInterface> &io) {
  io->output("Enter parent task ID: ");
}

StateType ParentTaskParamState::getType() {
  return StateType::TASK_PARENT_PARAM;
}

std::unique_ptr<StateInterface> ParentTaskParamState::switchState() {
  return nullptr;
}