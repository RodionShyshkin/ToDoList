//
// Created by rodion on 9/10/20.
//

#ifndef TODOLIST_SRC_CLI_IOINTERFACE_H_
#define TODOLIST_SRC_CLI_IOINTERFACE_H_

#include <string>

class IOInterface {
 public:
  virtual ~IOInterface() {}

 public:
  virtual std::string     input()                               = 0;
  virtual std::string     inputCommand()                        = 0;
  virtual void            output(const std::string&)            = 0;
  virtual void            outputWithBreak(const std::string&)   = 0;
};

#endif //TODOLIST_SRC_CLI_IOINTERFACE_H_
