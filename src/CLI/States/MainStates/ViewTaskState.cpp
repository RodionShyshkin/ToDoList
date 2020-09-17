//
// Created by rodion on 8/21/20.
//

#include <StateMachine.h>
#include <AvailableCommands.h>
#include "ViewTaskState.h"
#include "States/EditStates/RemoveTaskState.h"
#include "States/StateFactory.h"

bool ViewTaskState::input(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  this->command_ = parseCommand(io.inputCommand());
  if(!AvailableCommands::checkIsCommandAvailable(this->getType(), this->command_)) return false;
  return true;
}

std::shared_ptr<StateInterface>  ViewTaskState::run(std::shared_ptr<Context> &context) {
  if(context->show_list_buffer_.checkBufferFullness()) {
    if(context->show_list_buffer_.getList().empty()) return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
  }

  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_SINGLE_TASK, context);
    if(!machine_.execute()) return StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST));
 }

  if(!context->id_buffer_.checkBufferFullness()) throw std::invalid_argument("IDBuffer SM does not work correctly.");

  auto task_dto_ = context->service_->getTask(TaskID{context->id_buffer_.getID().value()});
  ViewTaskState::showTask(task_dto_);

//  context->show_list_buffer_.clearBuffer();
  if(!this->input(context->io_)) return StateFactory::create(this->getType());
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void ViewTaskState::output(const std::shared_ptr<IOInterface> &io_) {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Single task view mode.");
}

StateType ViewTaskState::getType() {
  return StateType::VIEW_TASK_STATE;
}

void ViewTaskState::showTask(const TaskDTO& task) {
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