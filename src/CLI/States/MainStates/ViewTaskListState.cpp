//
// Created by rodion on 8/21/20.
//

#include <StateMachine.h>
#include <AvailableCommands.h>
#include "ViewTaskListState.h"
#include "States/StateFactory.h"

ViewTaskListState::ViewTaskListState() {
}

bool ViewTaskListState::input() {
  std::string stringCommand;

  std::random_device rd;
  std::mt19937 mersenne(rd());
  auto k = mersenne() % 5;
  if(k == 0) stringCommand = "view";
  if(k == 1) stringCommand = "remove";
  else if(k == 2) stringCommand = "postpone";
  else if(k == 3) stringCommand = "complete";
  else stringCommand = "exit";
  //stringCommand = "complete";

  this->command_ = parseCommand(stringCommand);
  auto available = AvailableCommands::get(this->getType());
  if(available.find(this->command_) == available.end()) return false;
  return true;
}

std::shared_ptr<StateInterface>  ViewTaskListState::run(std::shared_ptr<Context> &context) {
  if(!context->show_list_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_TASKS_LIST, context);
    if (machine_.execute()) {
      std::cout << "task list got" << std::endl;
    } else {
      std::cout << "Error with getting tasks list!" << std::endl;
    }
  }
  input();
  output();
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void ViewTaskListState::output() {
  std::cout << "[Output]: Tasks list view mode." << std::endl;
}

StateType ViewTaskListState::getType() {
  return StateType::VIEW_TASK_LIST_STATE;
}