//
// Created by rodion on 8/21/20.
//

/*
#include "RemoveTaskState.h"
#include "StartState.h"
#include "ViewTaskState.h"
#include "GetTaskListState.h"

RemoveTaskState::RemoveTaskState(const bool& has_id) {
  this->has_id = has_id;
}

bool RemoveTaskState::input() {
  if(this->has_id) {
//    std::cin >> task_id_;
    this->task_id_ = 1;
    if(!validateParams(task_id_)) return false;
  }
  return true;
}

std::unique_ptr<StateInterface> RemoveTaskState::run() {
  input();
  std::cout << "removed" << std::endl;
  if(this->has_id) std::make_unique<GetTaskListState>();
  else return std::make_unique<ViewTaskState>();
}

bool RemoveTaskState::validateParams(const unsigned int &param) {
  return true;
}

void RemoveTaskState::output() {

}
 */