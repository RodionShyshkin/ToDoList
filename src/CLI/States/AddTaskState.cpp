//
// Created by rodion on 8/21/20.
//

#include <States/AddingTask/AddTaskStartState.h>
#include "AddTaskState.h"
#include "StartState.h"
#include "ExitState.h"
#include "GetTaskState.h"
#include <StateMachine.h>

AddTaskState::AddTaskState() {
  available_operations_.clear();
  available_operations_.insert(Command::EXIT);
}

bool AddTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  AddTaskState::run(std::unique_ptr<Context> &context) {
  //AddTaskStateMachine machine_(false);
  auto machine_ = StateMachine::create(StatesGraphType::ADDTASK);
//  StateMachine<AddTaskContext, AddTaskStateInterface, AddTaskStartState> machine_;
  if(machine_.execute()) {
    std::cout << "task added" << std::endl;
  }
  else {
    std::cout << "Error with adding task!" << std::endl;
  }
  return StateFactory::create(Command::MAINMENU);
}

void AddTaskState::output() {
  std::cout << "[Output]: Adding new task." << std::endl;
}

StateType AddTaskState::getType() {
  return StateType::ADD_TASK_STATE;
}