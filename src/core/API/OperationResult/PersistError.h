//
// Created by rodion on 10/6/20.
//

#ifndef TODOLIST_SRC_CORE_API_OPERATIONRESULT_PERSISTERROR_H_
#define TODOLIST_SRC_CORE_API_OPERATIONRESULT_PERSISTERROR_H_

/*
 * Errors which appears while working with persisting.
 *
 * @author Rodion Shyshkin
 */

enum class PersistError {
  SAVE_ERROR,
  LOAD_ERROR
};

#endif //TODOLIST_SRC_CORE_API_OPERATIONRESULT_PERSISTERROR_H_
