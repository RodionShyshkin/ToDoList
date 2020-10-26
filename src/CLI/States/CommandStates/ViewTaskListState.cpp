//
// Created by rodion on 8/21/20.
//

#include <ParamStateMachineFactory.h>
#include <States/StateFactory.h>
#include <Commands/CommandParser.h>
#include <Commands/AvailableCommands.h>
#include <Commands/CommandToStateType.h>
#include "ViewTaskListState.h"

ViewTaskListState::ViewTaskListState() : command_(Command::UNKNOWN) {}

StateResult ViewTaskListState::run(std::shared_ptr<Context> context) {
  context->id_buffer_.clearBuffer();
  //Fulling buffer.
  if(!context->show_list_buffer_.checkBufferFullness()) {
    auto machine = ParamStateMachineFactory::ShowTasksList::create(context);
    machine.execute();
  }

  //Request to API.
  auto modifier = context->show_list_buffer_.getModifier();
  std::vector<TaskDTO> vector;
  if(modifier == ListModifier::ALL) {
    vector = context->service_->getAllTasks(context->show_list_buffer_.getSortedFlag());
  }
  else if(modifier == ListModifier::TODAY) {
    vector = context->service_->getTasksForToday(context->show_list_buffer_.getSortedFlag());
  }
  else if(modifier == ListModifier::WEEK) {
    vector = context->service_->getTasksForWeek(context->show_list_buffer_.getSortedFlag());
  }
  else if(modifier == ListModifier::BY_LABEL) {
    vector = context->service_->getTasksByLabel(context->show_list_buffer_.getLabel(), context->show_list_buffer_.getSortedFlag());
  }

  //Saving vector in context.
  context->show_list_buffer_.setList(vector);

  //Output.
  ViewTaskListState::showList(context->show_list_buffer_.getList(), context->io_);

  //Input.
  if(!input(context->io_)) return StateResult::INCORRECT_INPUT;
  if(context->show_list_buffer_.getList().empty() && command_ != Command::EXIT && command_ != Command::MAINMENU)
    return StateResult::INCORRECT_INPUT;

  return StateResult::SUCCESS;
}

bool ViewTaskListState::input(const std::shared_ptr<IOInterface> &io) {
  command_ = CommandParser::Parse(io->inputCommand());
  return AvailableCommands::IsCommandAvailable(getType(), command_);
}

void ViewTaskListState::output(const std::shared_ptr<IOInterface> &io) {  }

StateType ViewTaskListState::getType() {
  return StateType::SHOW_TASKS_LIST;
}

void ViewTaskListState::showList(const std::vector<TaskDTO>& list,
                                 const std::shared_ptr<IOInterface>& io) {
  if(!list.empty()) {
    for (unsigned int i = 0; i < list.size(); ++i) {
      std::string io_item = "[" + std::to_string(i) + "] Task name: " + list[i].getName();
      if (!list[i].getLabel().empty()) io_item += (" (" + list[i].getLabel() + ")");
      io_item += ". Priority: ";
      io_item += stringByPriority(list[i].getPriority());
      io_item += ". Deadline: ";
      io_item += boost::gregorian::to_simple_string(list[i].getDueDate());
      io_item += ". Status: ";
      io_item += std::to_string(list[i].getStatus());
      io->outputWithBreak(io_item);
    }
  } else io->outputWithBreak(" --> No tasks <--");
  io->outputWithBreak("------------------");
  io->outputWithBreak("You can do following operations:");
  io->outputWithBreak("> view, > add_subtask, > complete, > remove, > postpone, > mm, > exit");
  io->outputWithBreak("------------------");
}

std::unique_ptr<StateInterface> ViewTaskListState::switchState() {
  auto newstate = StateFactory::create(CommandToStateType::Convert(command_));
  return std::move(newstate);
}