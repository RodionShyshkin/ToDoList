//
// Created by rodion on 10/24/20.
//

#ifndef TODOLIST_SRC_CLI_STATES_PARAMSTATEMACHINEFACTORY_H_
#define TODOLIST_SRC_CLI_STATES_PARAMSTATEMACHINEFACTORY_H_

#include "ParamStateMachine.h"

namespace ParamStateMachineFactory {
  namespace AddTask {
    static ParamStateMachine create(const std::shared_ptr<Context>& context) {
      std::queue<StateType> params;
      params.push(StateType::TASK_NAME_PARAM);
      params.push(StateType::TASK_LABEL_PARAM);
      params.push(StateType::TASK_PRIORITY_PARAM);
      params.push(StateType::TASK_DATE_PARAM);

      return ParamStateMachine::create(std::move(params), context);
    }
  }

  namespace AddSubtask {
    static ParamStateMachine create(const std::shared_ptr<Context>& context) {
      std::queue<StateType> params;
      params.push(StateType::TASK_NAME_PARAM);
      params.push(StateType::TASK_LABEL_PARAM);
      params.push(StateType::TASK_PRIORITY_PARAM);
      params.push(StateType::TASK_DATE_PARAM);

      return ParamStateMachine::create(std::move(params), context);
    }
  }

  namespace ShowTasksList {
    static ParamStateMachine create(const std::shared_ptr<Context>& context) {
      std::queue<StateType> params;
      params.push(StateType::LIST_MODIFIER_PARAM);
      params.push(StateType::LIST_SORTED_PARAM);
      params.push(StateType::TASK_LABEL_PARAM);

      return ParamStateMachine::create(std::move(params), context);
    }
  }

  namespace ShowSingleTask {
    static ParamStateMachine  create(const std::shared_ptr<Context>& context) {
      std::queue<StateType> params;
      params.push(StateType::TASK_ID_PARAM);

      return ParamStateMachine::create(std::move(params), context);
    }
  }

  namespace PostponeTask {
    static ParamStateMachine  create(const std::shared_ptr<Context>& context) {
      std::queue<StateType> params;
      params.push(StateType::TASK_DATE_PARAM);

      return ParamStateMachine::create(std::move(params), context);
    }
  }

  namespace PersistTasks {
    static ParamStateMachine create(const std::shared_ptr<Context>& context) {
      std::queue<StateType> params;
      params.push(StateType::FILENAME_PARAM);

      return ParamStateMachine::create(std::move(params), context);
    }
  }
}

#endif //TODOLIST_SRC_CLI_STATES_PARAMSTATEMACHINEFACTORY_H_
