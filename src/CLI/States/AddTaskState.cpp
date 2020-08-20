//
// Created by rodion on 8/19/20.
//

#include "AddTaskState.h"

bool AddTaskState::input() {
//  std::cin >> command_;
  std::cout << "ATS";
  return true;
}

bool AddTaskState::run() {
return true;
}

void AddTaskState::output() {
  std::cout << "AddTask State" << std::endl;
}
/*
bool AddTaskState::validateCommand(const std::string &) {
return true;
}*/