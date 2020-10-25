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

  MAIN_MENU,
  ADD_TASK,
  ADD_SUBTASK,
  COMPLETE_TASK,
  SHOW_TASK,
  POSTPONE_TASK,
  REMOVE_TASK,
  SHOW_TASKS_LIST,
  SAVE_TASKS,
  LOAD_TASKS,

  TASK_ID_PARAM,
  TASK_NAME_PARAM,
  TASK_LABEL_PARAM,
  TASK_PRIORITY_PARAM,
  TASK_DATE_PARAM,
  LIST_MODIFIER_PARAM,
  LIST_SORTED_PARAM,
  FILENAME_PARAM,

  EXIT_STATE
};

#endif //TODOLIST_SRC_CLI_STATES_STATETYPE_H_
