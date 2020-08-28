//
// Created by rodion on 8/21/20.
//

#include <States/ShowTasksLIst/ShowListStateMachine.h>
#include "GetTaskListState.h"
#include "ViewTaskListState.h"
#include "StartState.h"

GetTaskListState::GetTaskListState() {
  available_operations_.clear();
  available_operations_.insert(Command::EXIT);
}

bool GetTaskListState::input() {
/*  std::string paramFirst;
  std::string paramSecond;*/
//  std::cin >> paramFirst >> paramSecond;
/*  paramFirst = "all";
  paramSecond = "yes";
  this->modifier_ = parseModifier(paramFirst);
  this->is_sorted_ = parseFlag(paramSecond);*/
  return true;
}

std::shared_ptr<StateInterface>  GetTaskListState::run(std::unique_ptr<Context> &context) {
  ShowListStateMachine machine_;
  if(machine_.execute()) {
    std::cout << "task list got" << std::endl;
  }
  else {
    std::cout << "Error with getting tasks list!" << std::endl;
  }
  return std::make_shared<StartState>();
}

void GetTaskListState::output() {
  std::cout << "[Output]: Getting tasks list." << std::endl;

}
