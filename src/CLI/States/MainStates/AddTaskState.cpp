//
// Created by rodion on 8/21/20.
//

#include <States/AddingTask/AddTaskStartState.h>
#include "AddTaskState.h"
#include "MainMenuState.h"
#include <StateMachine.h>

bool AddTaskState::input() {
  return true;
}

std::shared_ptr<StateInterface>  AddTaskState::run(std::shared_ptr<Context> &context) {
  auto machine_ = StateMachine::create(StatesGraphType::ADDTASK, context);
  if(machine_.execute()) {
    std::cout << "task added" << std::endl;
  }
  else {
    std::cout << "Error with adding task!" << std::endl;
    return StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
  }
  if(!context->add_task_buffer_.checkBufferFullness()) return nullptr;

  auto dto_ = TaskDTO::create(0, context->add_task_buffer_.getName(), context->add_task_buffer_.getLabel(),
                              context->add_task_buffer_.getPriority(), context->add_task_buffer_.getDate(), false);

  auto result = context->service_->addTask(dto_);
  if(!result.GetStatus()) throw std::invalid_argument("Wrong AddTask validation");

  context->add_task_buffer_.clearBuffer();
  return StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
}

void AddTaskState::output() {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Adding new task.");
}

StateType AddTaskState::getType() {
  return StateType::ADD_TASK_STATE;
}