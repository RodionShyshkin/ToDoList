//
// Created by rodion on 8/21/20.
//

#include <States/AddingTask/AddTaskStartState.h>
#include "AddTaskState.h"
#include "MainMenuState.h"
#include <StateMachine.h>

AddTaskState::AddTaskState() {
}

bool AddTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  AddTaskState::run(std::shared_ptr<Context> &context) {
  auto machine_ = StateMachine::create(StatesGraphType::ADDTASK, context);
  if(machine_.execute()) {
    std::cout << "task added" << std::endl;
  }
  else {
    std::cout << "Error with adding task!" << std::endl;
  }
  return StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
}

void AddTaskState::output() {
  std::cout << "[Output]: Adding new task." << std::endl;
}

StateType AddTaskState::getType() {
  return StateType::ADD_TASK_STATE;
}