//
// Created by rodion on 8/21/20.
//

#include "GetTaskListState.h"
#include "ViewTaskListState.h"

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

  if(this->modifier_ == Modifier::ALL) {
    std::cout << "view all";
  }
  if(this->modifier_ == Modifier::TODAY) {
    std::cout << "view today";
  }
  if(this->modifier_ == Modifier::WEEK) {
    std::cout << "view week";
  }
  if(this->modifier_ == Modifier::BY_LABEL) {
    std::cout << "view by label";
  }
  return std::make_shared<ViewTaskListState>();
}

void GetTaskListState::output() {
  std::cout << "[Output]: Getting tasks list." << std::endl;

}

Modifier GetTaskListState::parseModifier(const std::string &mod) {
  if(mod == "all") return Modifier::ALL;
  else if(mod == "today") return Modifier::TODAY;
  else if(mod == "this_week") return Modifier::WEEK;
  else if(mod == "label") return Modifier::BY_LABEL;
}

bool GetTaskListState::parseFlag(const std::string &flag) {
  if(flag == "yes") return true;
  else return false;
}