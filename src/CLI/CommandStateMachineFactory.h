//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_SRC_CLI_COMMANDSTATEMACHINEFACTORY_H_
#define TODOLIST_SRC_CLI_COMMANDSTATEMACHINEFACTORY_H_

#include <IO/ConsoleIO.h>
#include <States/StateFactory.h>
#include "CommandStateMachine.h"

namespace CommandStateMachineFactory {
  static CommandStateMachine StartCLI() {
    std::shared_ptr<Context> context = std::make_shared<Context>(
        std::make_shared<TaskService>(), std::make_shared<ConsoleIO>());
    auto start_state = StateType::MAIN_MENU;
    return CommandStateMachine::create(std::move(start_state), std::move(context));
  }
}

#endif //TODOLIST_SRC_CLI_COMMANDSTATEMACHINEFACTORY_H_
