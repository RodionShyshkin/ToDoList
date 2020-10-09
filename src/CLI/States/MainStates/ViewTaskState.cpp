//
// Created by rodion on 8/21/20.
//

#include "ViewTaskState.h"

StateResult ViewTaskState::run(std::shared_ptr<Context> &context) {
  if(!context->show_list_buffer_.checkBufferFullness()) return StateResult::create(ErrorType::FATAL_ERROR, nullptr);
  if(context->show_list_buffer_.getList().empty()) return StateResult::create(ErrorType::NO_ERRORS,
                                                                              StateFactory::create(getStateTypeByCommand(Command::GETTASKLIST)));

  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesMachineType::GET_SINGLE_TASK, context);
    if(!machine_.execute()) return StateResult::create(ErrorType::FATAL_ERROR, nullptr);
 }

  if(!context->id_buffer_.checkBufferFullness()) throw std::invalid_argument("IDBuffer SM does not work correctly.");

  auto task_dto_ = context->service_->getTask(context->id_buffer_.getID().value());
  ViewTaskState::showTask(task_dto_, context->io_);

//  context->show_list_buffer_.clearBuffer();
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);
  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(getStateTypeByCommand(this->command_)));
}

bool ViewTaskState::input(const std::shared_ptr<IOInterface> &io_) {
  this->command_ = parseCommand(io_->inputCommand());
  if(!AvailableCommands::checkIsCommandAvailable(this->getType(), this->command_)) return false;
  return true;
}

void ViewTaskState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: Single task view mode.");
}

StateType ViewTaskState::getType() {
  return StateType::VIEW_TASK_STATE;
}

void ViewTaskState::showTask(const TaskDTO& task,
                             const std::shared_ptr<IOInterface>& io) {
  io->outputWithBreak("Task ID: " + std::to_string(task.getID()));
  io->outputWithBreak("Task Name: " + task.getName());
  io->outputWithBreak("Task Label: " + task.getLabel());
  io->outputWithBreak("Task Priority: " + stringByPriority(task.getPriority()));
  io->outputWithBreak("Task Deadline: " + boost::gregorian::to_simple_string(task.getDueDate()));
  io->outputWithBreak("Task Status: " + std::to_string(task.getStatus()));
  io->outputWithBreak("------------------");
  io->outputWithBreak("You can do following operations:");
  io->outputWithBreak(">add_subtask, > complete, > remove, > postpone, > mm, > exit");
  io->outputWithBreak("------------------");
}