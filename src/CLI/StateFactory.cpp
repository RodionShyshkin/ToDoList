//
// Created by rodion on 8/26/20.
//

#include "StateFactory.h"
#include "States/AddTaskState.h"
#include "States/AddSubtaskState.h"
#include "States/CompleteTaskState.h"
#include "States/PostponeTaskState.h"
#include "States/ExitState.h"
#include "States/RemoveTaskState.h"
#include "States/ViewTaskListState.h"
#include "States/StartState.h"
#include "States/ViewTaskState.h"

std::shared_ptr<StateInterface> StateFactory::create(const Command &operation) {
  if(operation == Command::UNKNOWN) return nullptr;
  if(operation == Command::GETTASK) {
    return std::make_shared<ViewTaskState>();
  }
  if(operation == Command::ADDTASK) {
    return std::make_shared<AddTaskState>();
  }
  if(operation == Command::ADDSUBTASK) {
    return std::make_shared<AddSubtaskState>();
  }
  if(operation == Command::EXIT) {
    return std::make_shared<ExitState>();
  }
  if(operation == Command::REMOVETASK) {
    return std::make_shared<RemoveTaskState>();
  }
  if(operation == Command::POSTPONETASK) {
    return std::make_shared<PostponeTaskState>();
  }
  if(operation == Command::COMPLETETASK) {
    return std::make_shared<CompleteTaskState>();
  }
  if(operation == Command::GETTASKLIST) {
    return std::make_shared<ViewTaskListState>();
  }
  if(operation == Command::MAINMENU) {
    return std::make_shared<StartState>();
  }
  return nullptr;
}
