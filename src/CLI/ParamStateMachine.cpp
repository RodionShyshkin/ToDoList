//
// Created by rodion on 10/24/20.
//

#include "ParamStateMachine.h"
#include "src/CLI/States/StateFactory.h"

ParamStateMachine ParamStateMachine::create(std::queue<StateType> &&states, std::shared_ptr<Context> context) {
  return ParamStateMachine{std::move(states), context};
}

ParamStateMachine::ParamStateMachine(std::queue<StateType> &&states, std::shared_ptr<Context> context)
: states_queue_(std::move(states)), context_(context) {}

void ParamStateMachine::execute() {
  while(!states_queue_.empty()) {
    auto current_state = StateFactory::create(states_queue_.front());
    auto result = current_state->run(context_);
    if(result == StateResult::SUCCESS) {
      states_queue_.pop();
    }
    else {
      std::cout << "error" << std::endl;
      continue;
    }
  }
}