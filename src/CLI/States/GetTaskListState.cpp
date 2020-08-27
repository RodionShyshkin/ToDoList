//
// Created by rodion on 8/21/20.
//

#include "GetTaskListState.h"
#include "ViewTaskListState.h"

GetTaskListState::GetTaskListState() {
  available_operations_.clear();
  available_operations_.insert(Command::EXIT);
}

bool GetTaskListState::input() {
  std::string paramFirst;
  std::string paramSecond;
//  std::cin >> paramFirst >> paramSecond;
  paramFirst = "all";
  paramSecond = "yes";
  this->modifier_ = parseModifier(paramFirst);
  this->is_sorted_ = parseFlag(paramSecond);
  return true;
}

std::shared_ptr<StateInterface> GetTaskListState::run() {
  input();

  if(this->modifier_ == ListModifier::ALL) {
    std::cout << "view all";
  }
  else if(this->modifier_ == ListModifier::TODAY) {
    std::cout << "view today";
  }
  else if(this->modifier_ == ListModifier::WEEK) {
    std::cout << "view week";
  }
  else if(this->modifier_ == ListModifier::BY_LABEL) {
    std::cout << "view by label";
  }
  else {
    std::cout << "error";
    return nullptr;
  }
  return std::make_shared<ViewTaskListState>();
}

void GetTaskListState::output() {
  std::cout << "[Output]: Getting tasks list." << std::endl;

}

ListModifier GetTaskListState::parseModifier(const std::string &mod) {
  if(mod == "all") return ListModifier::ALL;
  else if(mod == "today") return ListModifier::TODAY;
  else if(mod == "this_week") return ListModifier::WEEK;
  else if(mod == "label") return ListModifier::BY_LABEL;
  else return ListModifier::UNKNOWN;
}

bool GetTaskListState::parseFlag(const std::string &flag) {
  if(flag == "yes") return true;
  else return false;
}