//
// Created by rodion on 10/6/20.
//

#ifndef TODOLIST_SRC_CORE_API_OPERATIONRESULT_STORAGEERROR_H_
#define TODOLIST_SRC_CORE_API_OPERATIONRESULT_STORAGEERROR_H_

/*
 * \brief Errors which appears while working with storage.
 *
 * @author Rodion Shyshkin
 */

enum class StorageError {
  INVALID_TASK,
  TASK_NOT_FOUND,
  PARENT_NOT_FOUND,
  WRONG_TASK_ID
};

#endif //TODOLIST_SRC_CORE_API_OPERATIONRESULT_STORAGEERROR_H_
