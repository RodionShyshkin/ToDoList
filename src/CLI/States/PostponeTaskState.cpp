//
// Created by rodion on 8/25/20.
//

#include "PostponeTaskState.h"
#include "ViewTaskListState.h"
#include "ViewTaskState.h"

PostponeTaskState::PostponeTaskState(std::optional<unsigned int> task_id) {
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

bool PostponeTaskState::input() {
  if(!has_id_) {
//    std::cin >> task_id_;
    this->task_id_ = 1;
  }
  if(!validateParams(task_id_)) return false;
  return true;
}

std::shared_ptr<StateInterface>  PostponeTaskState::run(std::unique_ptr<Context> &context) {
  if(!input()) return nullptr;

  //postponeTask(task_id_, new_date_);

  if(this->has_id_) return std::make_shared<ViewTaskListState>();
  else return std::make_shared<ViewTaskState>();
  return nullptr;
}

void PostponeTaskState::output() {
  std::cout << "[Output]: Postponing task." << std::endl;
}

bool PostponeTaskState::validateParams(const unsigned int &param) {
  return true;
}