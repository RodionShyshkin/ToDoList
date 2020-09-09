//
// Created by rodion on 8/26/20.
//

#include <States/AddingTask/AddTaskStartState.h>
#include <States/AddingTask/NameParamState.h>
#include <States/AddingTask/LabelParamState.h>
#include <States/AddingTask/PriorityParamState.h>
#include <States/AddingTask/DateParamState.h>
#include <States/ShowTasksList/ShowListStartState.h>
#include <States/ShowTasksList/ModifierParamState.h>
#include <States/ShowTasksList/SortedParamState.h>
#include <States/GetSingleTask/SingleTaskStartState.h>
#include <States/GetSingleTask/IDParamState.h>
#include <States/NewDateParamState.h>
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
/*
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
*/
std::shared_ptr<StateInterface> StateFactory::create(const StateType &type) {
  if(type == StateType::UNKNOWN_STATE) {
    return nullptr;
  }
  else if(type == StateType::START_STATE) {
    return std::make_shared<StartState>();
  }
  else if(type == StateType::ADD_TASK_STATE) {
    return std::make_shared<AddTaskState>();
  }
  else if(type == StateType::ADD_SUBTASK_STATE) {
    return std::make_shared<AddSubtaskState>();
  }
  else if(type == StateType::COMPLETE_TASK_STATE) {
    return std::make_shared<CompleteTaskState>();
  }
  else if(type == StateType::VIEW_TASK_STATE) {
    return std::make_shared<ViewTaskState>();
  }
  else if(type == StateType::POSTPONE_TASK_STATE) {
    return std::make_shared<PostponeTaskState>();
  }
  else if(type == StateType::REMOVE_TASK_STATE) {
    return std::make_shared<RemoveTaskState>();
  }
  else if(type == StateType::VIEW_TASK_LIST_STATE) {
    return std::make_shared<ViewTaskListState>();
  }
  else if(type == StateType::ADD_TASK_START_STATE) {
    return std::make_shared<AddTaskStartState>(false);
  }
  else if(type == StateType::ADD_SUBTASK_START_STATE) {
    return std::make_shared<AddTaskStartState>(true);
  }
  else if(type == StateType::ADD_TASK_NAME_PARAM_STATE) {
    return std::make_shared<NameParamState>();
  }
  else if(type == StateType::ADD_TASK_LABEL_PARAM_STATE) {
    return std::make_shared<LabelParamState>();
  }
  else if(type == StateType::ADD_TASK_PRIORITY_PARAM_STATE) {
    return std::make_shared<PriorityParamState>();
  }
  else if(type == StateType::ADD_TASK_DATE_PARAM_STATE) {
    return std::make_shared<DateParamState>();
  }
  else if(type == StateType::SHOW_LIST_START_STATE) {
    return std::make_shared<ShowListStartState>();
  }
  else if(type == StateType::SHOW_LIST_MODIFIER_PARAM_STATE) {
    return std::make_shared<ModifierParamState>();
  }
  else if(type == StateType::SHOW_LIST_SORTED_PARAM_STATE) {
    return std::make_shared<SortedParamState>();
  }
  else if(type == StateType::SHOW_SINGLE_START_STATE) {
    return std::make_shared<SingleTaskStartState>();
  }
  else if(type == StateType::SHOW_SINGLE_ID_PARAM_STATE) {
    return std::make_shared<IDParamState>();
  }
  else if(type == StateType::POSTPONE_TASK_NEW_DATE_PARAM_STATE) {
    return std::make_shared<NewDateParamState>();
  }
  else if(type == StateType::EXIT_STATE) {
    return std::make_shared<ExitState>();
  }
}