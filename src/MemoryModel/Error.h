//
// Created by rodion on 8/10/20.
//

#ifndef TODOLIST_SRC_MEMORYMODEL_ERROR_H_
#define TODOLIST_SRC_MEMORYMODEL_ERROR_H_

#include <iostream>

class Error {
 public:
  enum Code {
    MEMORY_LIMIT = 1,
    TASK_NOT_FOUND,
    PARENT_NOT_FOUND,
    INVALID_DATE
  };

 public:
  Error(Code code);

  static std::string    code_to_string(const Code& code);

  std::string           what() const;
  Error::Code           get_code() const;

 private:
  Error::Code           error_code_;
};

#endif //TODOLIST_SRC_MEMORYMODEL_ERROR_H_
