//
// Created by rodion on 9/10/20.
//

#ifndef TODOLIST_SRC_CLI_IOINTERFACE_H_
#define TODOLIST_SRC_CLI_IOINTERFACE_H_

#include <string>
class IOInterface {
 public:
  ~IOInterface() = default;

 public:
  virtual std::string input() const = 0;
  virtual std::string inputCommand() const = 0;
  virtual void output(const std::string&) const = 0;
  virtual void outputWithBreak(const std::string&) const = 0;
};

#endif //TODOLIST_SRC_CLI_IOINTERFACE_H_
