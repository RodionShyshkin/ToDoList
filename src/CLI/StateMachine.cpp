//
// Created by rodion on 8/21/20.
//

#include "StateMachine.h"
#include <States/MainStates/MainMenuState.h>
#include <iostream>
#include <States/MainStates/ExitState.h>
#include <States/AddingTask/AddTaskStartState.h>
#include <States/GetTasksList/ShowListStartState.h>
#include <States/GetSingleTask/SingleTaskStartState.h>
#include <States/MainStates/StartState.h>

StateMachine StateMachine::create(const StatesGraphType &type, std::shared_ptr<Context>& context) {
  if(type == StatesGraphType::MAIN) {
    return StateMachine{std::make_shared<StartState>(), context};
  }
  else if(type == StatesGraphType::ADDTASK) {
    return StateMachine{std::make_shared<AddTaskStartState>(false), context};
  }
  else if(type == StatesGraphType::ADDSUBTASK) {
    return StateMachine{std::make_shared<AddTaskStartState>(true), context};
  }
  else if(type == StatesGraphType::GET_TASKS_LIST) {
    return StateMachine{std::make_shared<ShowListStartState>(), context};
  }
  else if(type == StatesGraphType::GET_SINGLE_TASK) {
    return StateMachine{std::make_shared<SingleTaskStartState>(), context};
  }
}

StateMachine::StateMachine(std::shared_ptr<StateInterface>&& start_state,
                           std::shared_ptr<Context>& context) : start_state_(start_state) {
  this->state_ = start_state_;
  this->context_ = context;
}

bool StateMachine::execute() {
  while(this->state_->getType() != StateType::EXIT_STATE) {
    if(this->state_ == nullptr) {
      std::cout << "ERROR" << std::endl;
      return false;
    }
    this->state_ = std::move(state_->run(context_));
  }
  std::cout << "State machine finished." << std::endl;
  return true;
}
