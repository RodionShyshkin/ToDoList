//
// Created by rodion on 8/21/20.
//

#include <StateMachine.h>
#include <AvailableCommands.h>
#include <gmock/gmock.h>
#include "ViewTaskListState.h"
#include "States/StateFactory.h"



StateResult ViewTaskListState::run(std::shared_ptr<Context> &context) {
  //Fulling buffer.
  if(!context->show_list_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_TASKS_LIST, context);
    if(!machine_.execute()) return StateResult::create(ErrorType::FATAL_ERROR, nullptr);
  }
  if(!context->show_list_buffer_.checkBufferFullness()) throw std::invalid_argument("State machine does not work correctly.");

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
  if(!this->input(context->io_)) return StateResult::create(ErrorType::INCORRECT_INPUT, nullptr);

  return StateResult::create(ErrorType::NO_ERRORS,
                             StateFactory::create(getStateTypeByCommand(this->command_)));
}

bool ViewTaskListState::input(const std::shared_ptr<IOInterface> &io_) {
  this->command_ = parseCommand(io_->inputCommand());
  if(!AvailableCommands::checkIsCommandAvailable(this->getType(), this->command_)) return false;
  return true;
}

void ViewTaskListState::output(const std::shared_ptr<IOInterface> &io_) {
  io_->outputWithBreak("[Output]: Tasks list view mode.");
}

StateType ViewTaskListState::getType() {
  return StateType::VIEW_TASK_LIST_STATE;
}

void ViewTaskListState::showList(const std::vector<TaskDTO>& list,
                                 const std::shared_ptr<IOInterface>& io) {
  if(!list.empty()) {
    for (unsigned int i = 0; i < list.size(); ++i) {
      std::string io_item_ = "[" + std::to_string(i) + "] Task name: " + list[i].getName();
      if (!list[i].getLabel().empty()) io_item_ = io_item_ + (" (" + list[i].getLabel() + ")");
      io_item_ += ". Priority: ";
      io_item_ += stringByPriority(list[i].getPriority());
      io_item_ += ". Deadline: ";
      io_item_ += boost::gregorian::to_simple_string(list[i].getDueDate());
      io_item_ += ". Status: ";
      io_item_ += std::to_string(list[i].getStatus());
      io->outputWithBreak(io_item_);
    }
  } else io->outputWithBreak(" --> No tasks <--");
  io->outputWithBreak("------------------");
  io->outputWithBreak("You can do following operations:");
  io->outputWithBreak("> view, > add_subtask, > complete, > remove, > postpone, > mm, > exit");
  io->outputWithBreak("------------------");
}