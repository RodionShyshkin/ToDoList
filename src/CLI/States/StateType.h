//
// Created by rodion on 9/2/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_STATETYPE_H_
#define TODOLIST_SRC_CLI_STATES_STATETYPE_H_

/*
 * Represents all types of states which can be created.
 *
 * @see States/StateFactory.h
 *
 * @author Rodion Shyshkin
 */

enum class StateType {
  UNKNOWN_STATE,
  START_STATE,

  MAIN_MENU_STATE,
  ADD_TASK_STATE,
  ADD_SUBTASK_STATE,
  COMPLETE_TASK_STATE,
  VIEW_TASK_STATE,
  POSTPONE_TASK_STATE,
  REMOVE_TASK_STATE,
  VIEW_TASK_LIST_STATE,

  ADD_TASK_START_STATE,
  ADD_SUBTASK_START_STATE,
  ADD_TASK_NAME_PARAM_STATE,
  ADD_TASK_LABEL_PARAM_STATE,
  ADD_TASK_PRIORITY_PARAM_STATE,
  ADD_TASK_DATE_PARAM_STATE,
  ADD_TASK_PARENT_PARAM_STATE,

  SHOW_LIST_START_STATE,
  SHOW_LIST_MODIFIER_PARAM_STATE,
  SHOW_LIST_SORTED_PARAM_STATE,

  SHOW_SINGLE_START_STATE,
  SHOW_SINGLE_ID_PARAM_STATE,

  POSTPONE_TASK_NEW_DATE_PARAM_STATE,

  SAVE_TASKS_STATE,
  LOAD_TASKS_STATE,

  EXIT_STATE
};

#endif //TODOLIST_SRC_CLI_STATES_STATETYPE_H_
