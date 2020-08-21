//
// Created by rodion on 8/21/20.
//

#include "AddTaskState.h"
#include "StartState.h"
#include "ExitState.h"
#include "GetTaskState.h"

bool AddTaskState::input() {
  std::string parameters;
//  std::cin >> parameters;
  parameters = "Task label High 2002/10/10";
  parseParameters(parameters);
  return true;
}

std::unique_ptr<StateInterface> AddTaskState::run() {
  input();
  std::cout << "task added" << std::endl;
  return std::make_unique<GetTaskState>();
}

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

void AddTaskState::output() {

}