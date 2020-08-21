//
// Created by rodion on 8/21/20.
//

#include <iostream>
#include "StartState.h"
#include "ExitState.h"

bool StartState::input() {
  return true;
}



std::unique_ptr<StateInterface> StartState::run() {
  std::cout << "runned" << std::endl;
  return std::make_unique<ExitState>();
}



void StartState::output() {
  std::cout << "S";
}
