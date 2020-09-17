//
// Created by rodion on 9/11/20.
//

#include "FakeService.h"

TaskDTO FakeService::getTask(const TaskID &id) const {
  for(const auto& item : this->fake_tasks_) {
    if(item.getID() == id) return item;
  }
  return TaskDTO::create(0, "", "", Priority::EMPTY,
                         boost::gregorian::date{boost::gregorian::not_a_date_time},
                         false);
}

std::vector<TaskDTO> FakeService::getAllTasks(const bool &sortByPriority) const {
  return this->fake_tasks_;
}

std::vector<TaskDTO> FakeService::getTasksForToday(const bool &sortByPriority) const {
  return this->fake_tasks_;
}

std::vector<TaskDTO> FakeService::getTasksForWeek(const bool &sortByPriority) const {
  return this->fake_tasks_;
}

std::vector<TaskDTO> FakeService::getTasksByPriority(const Priority &priority) const {
  return this->fake_tasks_;
}

std::vector<TaskDTO> FakeService::getTasksByLabel(const std::string &label, const bool &sortByPriority) const {
  return this->fake_tasks_;
}

std::vector<TaskDTO> FakeService::getTasksByName(const std::string &name, const bool &sortByPriority) const {
  return this->fake_tasks_;
}

OperationResult FakeService::addTask(const TaskDTO &task) {
  srand(time(NULL));
  unsigned int fake_id_ = rand() % 10000;
  TaskDTO task_to_add_ = TaskDTO::create(fake_id_, task.getName(), task.getLabel(),
                                         task.getPriority(), task.getDueDate(),
                                         task.getStatus());
  this->fake_tasks_.push_back(task_to_add_);
  return ErrorCode::NO_ERRORS;
}

OperationResult FakeService::addSubtask(const TaskID &id, const TaskDTO &subtask) {
  srand(time(NULL));
  unsigned int fake_id_ = rand() % 10000;
  TaskDTO subtask_to_add_ = TaskDTO::create(fake_id_, subtask.getName(), subtask.getLabel(),
                                         subtask.getPriority(), subtask.getDueDate(),
                                         subtask.getStatus());
  this->fake_tasks_.push_back(subtask_to_add_);
  return ErrorCode::NO_ERRORS;
}

OperationResult FakeService::RemoveTask(const TaskID &id) {
  std::vector<TaskDTO>::const_iterator it;
  it = this->fake_tasks_.begin();
  while(it != this->fake_tasks_.end()) {
    if(it->getID() == id) {
      this->fake_tasks_.erase(it);
      break;
    }
    ++it;
  }
  return ErrorCode::NO_ERRORS;
}

OperationResult FakeService::postponeTask(const TaskID &id, const Date &newdate) {
  for(auto& item : this->fake_tasks_) {
    if(item.getID() == id) {
      item = TaskDTO::create(item.getID(), item.getName(), item.getLabel(), item.getPriority(), newdate.GetDate(),
                             item.getStatus());
    }
  }
  return ErrorCode::NO_ERRORS;
}

OperationResult FakeService::completeTask(const TaskID &id) {
  for(auto& item : this->fake_tasks_) {
    if(item.getID() == id) {
      item = TaskDTO::create(item.getID(), item.getName(), item.getLabel(), item.getPriority(), item.getDueDate(),
                             true);
    }
  }
  return ErrorCode::NO_ERRORS;
}
