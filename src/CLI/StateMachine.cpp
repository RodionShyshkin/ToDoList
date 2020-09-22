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
    auto result = state_->run(context_);
    if(result.getError() == ErrorType::NO_ERRORS) {
      this->state_ = std::move(result.getNextState());
      if(this->state_ == nullptr) throw std::invalid_argument("Beda s bashkoy");
    }
    else if(result.getError() == ErrorType::OPERATION_ERROR) {
      this->context_->io_->outputWithBreak("Error while running this operation!");
    }
    else if(result.getError() == ErrorType::INCORRECT_INPUT) {
      this->context_->io_->outputWithBreak("Incorrect input!");
    }
    else if(result.getError() == ErrorType::FATAL_ERROR) {
      this->context_->io_->outputWithBreak("Fatal error!");
      return false;
    }
  }
  std::cout << "State machine finished." << std::endl;
  return true;
}
