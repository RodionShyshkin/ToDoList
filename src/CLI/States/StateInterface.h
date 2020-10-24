//
// Created by rodion on 8/19/20.
//

#ifndef TODOLIST_SRC_CLI_STATEINTERFACE_H_
#define TODOLIST_SRC_CLI_STATEINTERFACE_H_

#include <memory>
#include <set>
#include <Context/Context.h>
#include <States/StateType.h>
#include <States/StateResult.h>

/*
 * A common interface for all states.
 *
 * @see States/StateResult.h
 *
 * @author Rodion Shyshkin
 */

class StateInterface {
 public:
  ~StateInterface()                                                                             = default;

 public:
  /*
   * Method which does work of the state.
   *
   * @param shared_ptr<Context> context, which we should use to update system data.
   *
   * @return StateResult instance
   */
  virtual StateResult                         run(std::shared_ptr<Context> context)            = 0;

  virtual std::unique_ptr<StateInterface>     switchState()                                    = 0;

  /*
   * Method which just gets the type of concrete state.
   *
   * @return StateType object.
   */
  virtual StateType                           getType()                                         = 0;

 private:
  /*
   * Method which gets input and validate or parse data received from user using the IOInterface stream
   *
   * @param IOInterface which contains stream to get input.
   *
   * @return bool True if received data was validated or parsed successfully, False in another case.
   */
  virtual bool                                input(const std::shared_ptr<IOInterface> &io_)    = 0;

  /*
   * Method which shows output using the IOInterface stream.
   *
   * @param IOInterface which contains stream to get input.
   */

  virtual void                                output(const std::shared_ptr<IOInterface> &io_)   = 0;
};

#endif //TODOLIST_SRC_CLI_STATEINTERFACE_H_
