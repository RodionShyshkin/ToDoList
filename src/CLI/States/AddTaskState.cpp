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
/*
void AddTaskState::parseParameters(const std::string& params) {
  int spaceNum = 0;
  std::string temp;
  for(int i = 0; i < params.length(); i++) {
    if(params[i] == ' ') {
      spaceNum++;
    }
    else {
      if(spaceNum == 0) {
        this->task_name_ += params[i];
      }
      else if(spaceNum == 1) {
        this->task_label_ += params[i];
      }
      else if(spaceNum == 2) {
        this->task_priority_ += params[i];
      }
      else if(spaceNum == 3) {
        this->task_deadline_ += params[i];
      }
      else break;
    }
  }
}
*/
void AddTaskState::output() {
  std::cout << "[Output]: Adding new task." << std::endl;
}