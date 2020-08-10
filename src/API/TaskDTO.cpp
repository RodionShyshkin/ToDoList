//
// Created by rodion on 7/21/20.
//

#include "TaskDTO.h"

TaskDTO::TaskDTO() = default;

TaskDTO::TaskDTO(const TaskID& id, const Task& task, const bool& status) {
  this->task_id_ = id;
  this->task_name_ = task.getName();
  this->task_label_ = task.getLabel();
  this->task_priority_ = task.getPriority();
  this->task_due_date_ = task.getDate();
  this->task_status_ = status;
}

TaskID TaskDTO::getID() const { return this->task_id_; }

std::string TaskDTO::getName() const { return this->task_name_; }

std::string TaskDTO::getLabel() const { return this->task_label_; }

Task::Priority TaskDTO::getPriority() const { return this->task_priority_; }

DateTime TaskDTO::getDueDate() const { return this->task_due_date_; }

bool TaskDTO::getStatus() const { return this->task_status_; }
