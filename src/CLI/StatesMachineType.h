//
// Created by rodion on 9/1/20.
//

#ifndef TODOLIST_SRC_CLI_STATESMACHINETYPE_H_
#define TODOLIST_SRC_CLI_STATESMACHINETYPE_H_

/*
 * Represents all possible types of StateMachine.
 *
 * @see StateMachine.h
 *
 * @author Rodion Shyshkin
 */

enum class StatesMachineType {
  MAIN,
  ADDTASK,
  ADDSUBTASK,
  GET_SINGLE_TASK,
  GET_TASKS_LIST
};

#endif //TODOLIST_SRC_CLI_STATESMACHINETYPE_H_
