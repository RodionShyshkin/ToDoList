//
// Created by rodion on 9/1/20.
//

#include <src/CLI/ParamStateMachineFactory.h>
#include "ParentTaskParamState.h"

bool ParentTaskParamState::input(const std::shared_ptr<IOInterface> &io) {
  return true;
}

StateResult ParentTaskParamState::run(std::shared_ptr<Context> context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    //auto machine_ = StateMachine::create(StatesMachineType::GET_SINGLE_TASK, context);
    auto machine = ParamStateMachineFactory::ShowSingleTask::create(context);
    machine.execute();
  }

  auto id_from_buffer_ = context->id_buffer_.getID();
  if(!id_from_buffer_.has_value()) throw std::invalid_argument("Invalid IDBuffer State Machine.");

  context->add_task_buffer_.setParent(id_from_buffer_.value());

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