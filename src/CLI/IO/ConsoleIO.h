//
// Created by rodion on 9/10/20.
//

#ifndef TODOLIST_SRC_CLI_CONSOLEIO_H_
#define TODOLIST_SRC_CLI_CONSOLEIO_H_

#include <IO/IOInterface.h>

/*
 * Realization of input-output using console.
 *
 * @see IO/IOInterface.h
 *
 * @author Rodion Shyshkin
 */

class ConsoleIO : public IOInterface {
 public:
  std::string     input()                                 override;
  std::string     inputCommand()                          override;
  void            output(const std::string&)              override;
  void            outputWithBreak(const std::string &)    override;
};

#endif //TODOLIST_SRC_CLI_CONSOLEIO_H_
