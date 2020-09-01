//
// Created by rodion on 8/26/20.
//

#include "StateFactory.h"
#include "GetTaskState.h"
#include "AddTaskState.h"
#include "AddSubtaskState.h"
#include "CompleteTaskState.h"
#include "PostponeTaskState.h"
#include "ExitState.h"
#include "RemoveTaskState.h"
#include "ViewTaskListState.h"
#include "StartState.h"

std::shared_ptr<StateInterface> StateFactory::create(const Command &operation) {
  if(operation == Command::UNKNOWN) return nullptr;
  if(operation == Command::GETTASK) {
    return std::make_shared<GetTaskState>();
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
    return std::make_shared<RemoveTaskState>(std::nullopt);
  }
  if(operation == Command::POSTPONETASK) {
    return std::make_shared<PostponeTaskState>(std::nullopt);
  }
  if(operation == Command::COMPLETETASK) {
    return std::make_shared<CompleteTaskState>(std::nullopt);
  }
  if(operation == Command::GETTASKLIST) {
    return std::make_shared<ViewTaskListState>();
  }
  if(operation == Command::MAINMENU) {
    return std::make_shared<StartState>();
  }
  return nullptr;
}