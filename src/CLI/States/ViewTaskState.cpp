//
// Created by rodion on 8/21/20.
//

#include "ViewTaskState.h"
#include "ExitState.h"

bool ViewTaskState::input() {
  unsigned int parameter;
//  std::cin >> parameter;
  parameter = 1;
  task_id_ = parameter;
  return true;
}

std::unique_ptr<StateInterface> ViewTaskState::run() {
  input();

  std::cout << "The task #" << task_id_ << " was shown." << std::endl;
  return std::make_unique<ExitState>();
}

void ViewTaskState::output() {
  std::cout << "Task was got." << std::endl;
}