//
// Created by rodion on 8/21/20.
//

#include <ParamStateMachineFactory.h>
#include <States/StateFactory.h>
#include <Commands/CommandParser.h>
#include <Commands/AvailableCommands.h>
#include <Commands/CommandToStateType.h>
#include "ViewTaskState.h"

ViewTaskState::ViewTaskState() : command_(Command::UNKNOWN) {}

StateResult ViewTaskState::run(std::shared_ptr<Context> context) {
  //Filling context.
  if(!context->id_buffer_.checkBufferFullness()) {
    auto machine = ParamStateMachineFactory::ShowSingleTask::create(context);
    machine.execute();
  }

  //Request to Core.
  auto task_dto = context->service_->getTask(context->id_buffer_.getID().value());
  if(!task_dto.has_value()) return StateResult::OPERATION_ERROR;
  ViewTaskState::showTask(task_dto.value(), context->io_);

  //Waiting for command.
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;
  return StateResult::SUCCESS;
}

bool ViewTaskState::input(const std::shared_ptr<IOInterface> &io) {
  command_ = CommandParser::Parse(io->inputCommand());
  return AvailableCommands::IsCommandAvailable(getType(), command_);
}

void ViewTaskState::output(const std::shared_ptr<IOInterface> &io) {
}

StateType ViewTaskState::getType() {
  return StateType::SHOW_TASK;
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
  io->outputWithBreak("> add_subtask, > complete, > remove, > postpone, > show, > mm, > exit");
  io->outputWithBreak("------------------");
}

std::unique_ptr<StateInterface> ViewTaskState::switchState() {
  auto newstate = StateFactory::create(CommandToStateType::Convert(command_));
  return std::move(newstate);
}