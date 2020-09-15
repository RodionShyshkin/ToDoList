//
// Created by rodion on 8/21/20.
//

#include <StateMachine.h>
#include <AvailableCommands.h>
#include "ViewTaskState.h"
#include "States/EditStates/RemoveTaskState.h"
#include "States/StateFactory.h"

bool ViewTaskState::input() {
  ConsoleIO io;
  this->command_ = parseCommand(io.inputCommand());

  auto available = AvailableCommands::get(this->getType());
  if(available.find(this->command_) == available.end()) return false;
  return true;
}

std::shared_ptr<StateInterface>  ViewTaskState::run(std::shared_ptr<Context> &context) {
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(machine_.execute()) {
      std::cout << "task got" << std::endl;

      //getting task
    }
    else {
      std::cout << "Error with getting task!" << std::endl;
      return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
    }
  }
  std::cout << context->id_buffer_.getID().value() << std::endl;
  if(!context->id_buffer_.checkBufferFullness()) throw std::invalid_argument("IDBuffer SM does not work correctly.");

  auto task_dto_ = context->service_->getTask(TaskID{context->id_buffer_.getID().value()});

  this->showTask(task_dto_);

  context->show_list_buffer_.clearBuffer();
  if(!input()) return nullptr;
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void ViewTaskState::output() {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Single task view mode.");
}

StateType ViewTaskState::getType() {
  return StateType::VIEW_TASK_STATE;
}

void ViewTaskState::showTask(const TaskDTO& task) const {
  ConsoleIO io;
  io.outputWithBreak("Task ID: " + std::to_string(task.getID()));
  io.outputWithBreak("Task Name: " + task.getName());
  io.outputWithBreak("Task Label: " + task.getLabel());
  io.outputWithBreak("Task Priority: " + stringByPriority(task.getPriority()));
  io.outputWithBreak("Task Deadline: " + boost::gregorian::to_simple_string(task.getDueDate()));
  io.outputWithBreak("Task Status: " + std::to_string(task.getStatus()));
  io.outputWithBreak("------------------");
  io.outputWithBreak("You can do following operations:");
  io.outputWithBreak(">add_subtask, > complete, > remove, > postpone, > mm, > exit");
  io.outputWithBreak("------------------");
}