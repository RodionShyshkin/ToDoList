//
// Created by rodion on 8/21/20.
//

#include <States/AddingTask/AddTaskStateMachine.h>
#include "AddTaskState.h"
#include "StartState.h"
#include "ExitState.h"
#include "GetTaskState.h"

AddTaskState::AddTaskState() {
  available_operations_.clear();
  available_operations_.insert(Command::EXIT);
}

bool AddTaskState::input() {
  /*std::string parameters;
//  std::cin >> parameters;
  parameters = "Task label High 2002/10/10";*/
//  parseParameters(parameters);
  return true;
}

std::shared_ptr<StateInterface>  AddTaskState::run(std::unique_ptr<Context> &context) {

  AddTaskStateMachine machine_;
  if(machine_.execute()) {
    std::cout << "task added" << std::endl;
  }
  else {
    std::cout << "Error with adding task!" << std::endl;
  }
  return std::make_shared<StartState>();

/*  input();
  std::cout << "task added" << std::endl;
  return std::make_unique<StartState>();*/
}

void AddTaskState::output() {
  std::cout << "[Output]: Adding new task." << std::endl;
}