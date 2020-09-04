//
// Created by rodion on 8/25/20.
//

#include <StateMachine.h>
#include "CompleteTaskState.h"
#include "ViewTaskListState.h"
#include "ViewTaskState.h"

CompleteTaskState::CompleteTaskState() {
  available_operations_.clear();
  available_operations_.insert(Command::EXIT);
}

bool CompleteTaskState::input() {
//    std::cin >> task_id_;
  return true;
}

std::shared_ptr<StateInterface>  CompleteTaskState::run(std::unique_ptr<Context> &context) {
  bool is_single_state = false;
  if(context->id_buffer_.has_id_) {
    is_single_state = true;
  }
  else {
    auto machine_ = StateMachine::create(StatesGraphType::VIEW_SINGLE_TASK);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
    }
    output();
  }
  this->task_id_ = context->id_buffer_.id_;

  //completeTask(task_id_);

  if(is_single_state) return std::make_shared<ViewTaskState>();
  else return std::make_shared<ViewTaskListState>();
}

void CompleteTaskState::output() {
  std::cout << "[Output]: Completing task." << std::endl;
}

StateType CompleteTaskState::getType() {
  return StateType::COMPLETE_TASK_STATE;
}