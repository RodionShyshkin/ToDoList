//
// Created by rodion on 8/25/20.
//

#include "CompleteTaskState.h"

CompleteTaskState::CompleteTaskState(std::optional<unsigned int> task_id) {
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

bool CompleteTaskState::input() {
  if(!has_id_) {
//    std::cin >> task_id_;
    this->task_id_ = 1;
  }
  if(!validateParams(task_id_)) return false;
  return true;
}

std::shared_ptr<StateInterface> CompleteTaskState::run() {
  if(!input()) return nullptr;

  //completeTask(task_id_);

  if(this->has_id_) return std::make_shared<GetTaskListState>();
  else return std::make_shared<ViewTaskState>();
}

void CompleteTaskState::output() {
  std::cout << "[Output]: Completing task." << std::endl;
}

bool CompleteTaskState::validateParams(const unsigned int &param) {
  return true;
}