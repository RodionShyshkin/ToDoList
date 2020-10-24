//
// Created by rodion on 10/24/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_STATESMAP_H_
#define TODOLIST_SRC_CLI_STATES_STATESMAP_H_

#include <States/StateType.h>
#include <src/CLI/States/CommandStates/MainMenuState.h>
#include <src/CLI/States/CommandStates/AddTaskState.h>
#include <src/CLI/States/CommandStates/AddSubtaskState.h>
#include <src/CLI/States/CommandStates/CompleteTaskState.h>
#include <src/CLI/States/CommandStates/ViewTaskState.h>
#include <src/CLI/States/CommandStates/PostponeTaskState.h>
#include <src/CLI/States/CommandStates/RemoveTaskState.h>
#include <src/CLI/States/CommandStates/ViewTaskListState.h>
#include <src/CLI/States/CommandStates/PersistTasksState.h>
#include <src/CLI/States/ParamStates/ParentTaskParamState.h>
#include <src/CLI/States/ParamStates/NameParamState.h>
#include <src/CLI/States/ParamStates/LabelParamState.h>
#include <src/CLI/States/ParamStates/DateParamState.h>
#include <src/CLI/States/ParamStates/PriorityParamState.h>
#include <src/CLI/States/ParamStates/ModifierParamState.h>
#include <src/CLI/States/ParamStates/SortedParamState.h>
#include <src/CLI/States/ParamStates/IDParamState.h>
#include <src/CLI/States/ParamStates/FilenameParamState.h>
#include "ExitState.h"

namespace StatesMap {
  static std::map<StateType, std::unique_ptr<StateInterface>> create() {
    std::map<StateType, std::unique_ptr<StateInterface>> states;
    states[StateType::EXIT_STATE] = std::make_unique<ExitState>();

    states[StateType::MAIN_MENU] = std::make_unique<MainMenuState>();
    states[StateType::ADD_TASK] = std::make_unique<AddTaskState>();
    states[StateType::ADD_SUBTASK] = std::make_unique<AddSubtaskState>();
    states[StateType::COMPLETE_TASK] = std::make_unique<CompleteTaskState>();
    states[StateType::SHOW_TASK] = std::make_unique<ViewTaskState>();
    states[StateType::POSTPONE_TASK] = std::make_unique<PostponeTaskState>();
    states[StateType::REMOVE_TASK] = std::make_unique<RemoveTaskState>();
    states[StateType::SHOW_TASKS_LIST] = std::make_unique<ViewTaskListState>();
    states[StateType::SAVE_TASKS] = std::make_unique<PersistTasksState>(PersistType::SAVE);
    states[StateType::LOAD_TASKS] = std::make_unique<PersistTasksState>(PersistType::LOAD);

    states[StateType::TASK_NAME_PARAM] = std::make_unique<NameParamState>();
    states[StateType::TASK_LABEL_PARAM] = std::make_unique<LabelParamState>();
    states[StateType::TASK_PRIORITY_PARAM] = std::make_unique<PriorityParamState>();
    states[StateType::TASK_DATE_PARAM] = std::make_unique<DateParamState>();
    states[StateType::TASK_PARENT_PARAM] = std::make_unique<ParentTaskParamState>();
    states[StateType::LIST_MODIFIER_PARAM] = std::make_unique<ModifierParamState>();
    states[StateType::LIST_SORTED_PARAM] = std::make_unique<SortedParamState>();
    states[StateType::TASK_ID_PARAM] = std::make_unique<IDParamState>();
    states[StateType::FILENAME_PARAM] = std::make_unique<FilenameParamState>();

    return states;
  }
}

#endif //TODOLIST_SRC_CLI_STATES_STATESMAP_H_
