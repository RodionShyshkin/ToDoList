//
// Created by rodion on 8/21/20.
//


#include "GetTaskState.h"
#include "ExitState.h"
#include "ViewTaskState.h"

bool GetTaskState::input() {
  unsigned int parameter;
//  std::cin >> parameter;
  parameter = 1;
  task_id_ = parameter;
  return true;
}

std::shared_ptr<StateInterface> GetTaskState::run() {
  input();

  std::cout << "The task #" << task_id_ << " was shown." << std::endl;

//  return std::make_unique<ViewTaskState>();
return nullptr;
}

void GetTaskState::output() {
  std::cout << "Task was got." << std::endl;
}