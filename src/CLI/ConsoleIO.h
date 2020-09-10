//
// Created by rodion on 9/10/20.
//

#ifndef TODOLIST_SRC_CLI_CONSOLEIO_H_
#define TODOLIST_SRC_CLI_CONSOLEIO_H_

#include <IOInterface.h>

class ConsoleIO : public IOInterface {
 public:
  std::string input() const override;
  void output(const std::string&) const override;
};

#endif //TODOLIST_SRC_CLI_CONSOLEIO_H_
