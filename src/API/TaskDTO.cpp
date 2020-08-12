//
// Created by rodion on 7/21/20.
//

#include "TaskDTO.h"

TaskDTO::TaskDTO() = default;

TaskDTO::TaskDTO(const TaskID& id, const Task& task, const bool& status) {
  this->task_id_ = id;
  this->task_name_ = task.GetName();
  this->task_label_ = task.GetLabel();
  this->task_priority_ = task.GetPriority();
  this->task_due_date_ = task.GetDate();
  this->task_status_ = status;
}

TaskDTO TaskDTO::create(const TaskID &id, const Task &task, const bool &status) {
  return TaskDTO(id, task, status);
}

TaskID TaskDTO::getID() const { return this->task_id_; }

std::string TaskDTO::getName() const { return this->task_name_; }

std::string TaskDTO::getLabel() const { return this->task_label_; }

Priority TaskDTO::getPriority() const { return this->task_priority_; }

Date TaskDTO::getDueDate() const { return this->task_due_date_; }

bool TaskDTO::getStatus() const { return this->task_status_; }
