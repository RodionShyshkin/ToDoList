//
// Created by rodion on 8/21/20.
//

#include <StateMachine.h>
#include <AvailableCommands.h>
#include <gmock/gmock.h>
#include "ViewTaskListState.h"
#include "States/StateFactory.h"

bool ViewTaskListState::input() {
  ConsoleIO io;
  this->command_ = parseCommand(io.inputCommand());

  auto available = AvailableCommands::get(this->getType());
  if(available.find(this->command_) == available.end()) return false;
  return true;
}

std::shared_ptr<StateInterface> ViewTaskListState::run(std::shared_ptr<Context> &context) {
  //Fulling buffer.
  if(!context->show_list_buffer_.checkBufferFullness()) {
    auto machine_ = StateMachine::create(StatesGraphType::GET_TASKS_LIST, context);
    if (machine_.execute()) {
      std::cout << "task list got" << std::endl;
    } else {
      std::cout << "Error with getting tasks list!" << std::endl;
      return StateFactory::create(getStateTypeByCommand(Command::MAINMENU));
    }
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
  this->showList(context->show_list_buffer_.getList());

  //Input.
  if(!this->input()) return nullptr;
  return StateFactory::create(getStateTypeByCommand(this->command_));
}

void ViewTaskListState::output() {
  ConsoleIO io;
  io.outputWithBreak("[Output]: Tasks list view mode.");
}

StateType ViewTaskListState::getType() {
  return StateType::VIEW_TASK_LIST_STATE;
}

void ViewTaskListState::showList(const std::vector<TaskDTO>& list) const {
  ConsoleIO io;

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
      io.outputWithBreak(io_item_);
    }
  } else io.outputWithBreak(" --> No tasks <--");
  io.outputWithBreak("------------------");
  io.outputWithBreak("You can do following operations:");
  io.outputWithBreak("> view, > add_subtask, > complete, > remove, > postpone, > mm, > exit");
  io.outputWithBreak("------------------");
}