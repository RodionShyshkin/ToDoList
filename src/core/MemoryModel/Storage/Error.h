//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_ERRORCODE_H_
#define TODOLIST_SRC_MEMORYMODEL_ERRORCODE_H_

/*
 * Class which keeps error code and represents its value.
 *
 * @author Rodion Shyshkin
 */

enum class StorageError {
  NO_ERRORS = 0,
  MEMORY_LIMIT,
  TASK_NOT_FOUND,
  PARENT_NOT_FOUND,
  INVALID_DATE,
  WRONG_TASK_ID,
  COMPLETED_TASK,
  INVALID_TASK
};

#endif //TODOLIST_SRC_MEMORYMODEL_ERROR_H_
