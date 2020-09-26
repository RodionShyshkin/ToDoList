//
// Created by rodion on 9/10/20.
//

#ifndef TODOLIST_SRC_CLI_IOINTERFACE_H_
#define TODOLIST_SRC_CLI_IOINTERFACE_H_

#include <string>

/*
 * Interface which defines methods of input & output.
 *
 * @see CLI/Context.h
 *
 * @author Rodion Shyshkin
 */

class IOInterface {
 public:
  virtual ~IOInterface() {}

 public:
  /*
   * Gets some string from user, not command.
   *
   * @return std::string Received string.
   */
  virtual std::string     input()                               = 0;

  /*
   * Gets some command from user ( ">> command" ).
   *
   * @return std::string Received command.
   */
  virtual std::string     inputCommand()                        = 0;

  /*
   * Show some string for user without line break.
   *
   * @param std::string String
   */
  virtual void            output(const std::string&)            = 0;

  /*
   * SHow some string for user with line break.
   *
   * @param std::string String.
   */
  virtual void            outputWithBreak(const std::string&)   = 0;
};

#endif //TODOLIST_SRC_CLI_IOINTERFACE_H_
