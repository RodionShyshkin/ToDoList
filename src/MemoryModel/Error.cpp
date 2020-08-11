//
// Created by rodion on 8/10/20.
//

#include "Error.h"

/*
 * Class which keeps error code and represents its value.
 *
 * @author Rodion Shyshkin
 */

//Error::Error(Code code) : error_code_(code) {}

/*
 * Converting error code to string.
 *
 * @param Code instance (the code of the error
 *
 * @return std::string which tells what the error means.
 */
/*
std::string Error::code_to_string(const Code& code) {
  switch(code) {
    case Error::MEMORY_LIMIT:
      return "You do not have enough memory.";
    case Error::TASK_NOT_FOUND:
      return "Task not found.";
    case Error::PARENT_NOT_FOUND:
      return "Parent task not found.";
    case Error::INVALID_DATE:
      return "Invalid date.";
  }
  return "Unknown error.";
}

Error::Code Error::get_code() const {
  return this->error_code_;
}
*/
/*
 * @return std::string. A value of the concrete error.
 */
/*
std::string Error::what() const {
  return Error::code_to_string(this->error_code_);
}*/