//
// Created by rodion on 8/21/20.
//

#include "StateMachine.h"
#include <States/StartState.h>
#include <iostream>
#include <States/ExitState.h>
#include <States/AddingTask/AddTaskStartState.h>
#include <States/ShowTasksList/ShowListStartState.h>
#include <States/GetSingleTask/SingleTaskStartState.h>

StateMachine StateMachine::create(const StatesGraphType &type) {
  if(type == StatesGraphType::MAIN) {
    return StateMachine{std::make_shared<StartState>()};
  }
  else if(type == StatesGraphType::ADDTASK) {
    return StateMachine{std::make_shared<AddTaskStartState>(false)};
  }
  else if(type == StatesGraphType::ADDSUBTASK) {
    return StateMachine{std::make_shared<AddTaskStartState>(true)};
  }
  else if(type == StatesGraphType::GET_TASKS_LIST) {
    return StateMachine{std::make_shared<ShowListStartState>()};
  }
  else if(type == StatesGraphType::GET_SINGLE_TASK) {
    return StateMachine{std::make_shared<SingleTaskStartState>()};
  }
}

StateMachine::StateMachine(std::shared_ptr<StateInterface> start_state) : start_state_(start_state) {
  this->state_ = start_state_;
  this->context_ = std::make_unique<Context>();
}

bool StateMachine::execute() {
  while(this->state_->getType() != StateType::EXIT_STATE) {
    if(this->state_ == nullptr) {
      std::cout << "ERROR" << std::endl;
      return false;
    }
    if(this->state_->getType() == StateType::VIEW_TASK_STATE) {
      std::cout << "VIEW" << std::endl;
    }
    this->state_ = std::move(state_->run(context_));
  }
  std::cout << "State machine finished." << std::endl;
  return true;
}
