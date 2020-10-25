//
// Created by rodion on 10/23/20.
//

#include "CommandStateMachine.h"
#include "States/StateFactory.h"

CommandStateMachine CommandStateMachine::create(StateType &&start_state, std::shared_ptr<Context>&& context) {
  return CommandStateMachine(std::move(start_state), std::move(context));
}

CommandStateMachine::CommandStateMachine(const StateType &start_state, std::shared_ptr<Context>&& context)
:
context_(context) {
  state_ = StateFactory::create(start_state);
}

void CommandStateMachine::execute() {
  while(state_->getType() != StateType::EXIT_STATE) {
    auto result = state_->run(context_);
    if(result == StateResult::SUCCESS) {
      state_ = state_->switchState();
    }
    else if(result == StateResult::INCORRECT_INPUT) {
      context_->io_->outputWithBreak("Incorrect input!");
    }
    else if(result == StateResult::OPERATION_ERROR) {
      context_->io_->outputWithBreak("Operation error!");
      return;
    }
    else if(result == StateResult::FATAL_ERROR) {
      context_->io_->outputWithBreak("Fatal error!");
      return;
    }
    else throw std::runtime_error("Not all enum is coveraged by if-else in CommandStateMachine.");
  }
}