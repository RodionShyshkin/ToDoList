//
// Created by rodion on 8/21/20.
//


#include "RemoveTaskState.h"
#include "StartState.h"
#include "ViewTaskState.h"
#include "ViewTaskListState.h"

RemoveTaskState::RemoveTaskState(std::optional<unsigned int> task_id) {
  available_operations_.clear();
  available_operations_.insert(Command::EXIT);

  if(task_id.has_value()) {
    this->task_id_ = task_id.value();
    this->has_id_ = true;
  }
  else {
    this->task_id_ = 0;
    this->has_id_ = false;
  }
}

bool RemoveTaskState::input() {
  if(!has_id_) {
//    std::cin >> task_id_;
    this->task_id_ = 1;
  }
  if(!validateParams(task_id_)) return false;
  return true;
}

std::shared_ptr<StateInterface>  RemoveTaskState::run(std::unique_ptr<Context> &context) {
  if(!input()) return nullptr;
  std::cout << "removed" << std::endl;
  if(this->has_id_) return std::make_unique<ViewTaskListState>();
  else return std::make_unique<ViewTaskState>();
}

bool RemoveTaskState::validateParams(const unsigned int &param) {
  return true;
}

void RemoveTaskState::output() {
  std::cout << "[Output]: Removes task." << std::endl;
}
