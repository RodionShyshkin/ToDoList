//
// Created by rodion on 7/16/20.
//

#include "TaskEntity.h"

TaskEntity::TaskEntity() = default;

TaskEntity::TaskEntity(const Task &task, const TaskID &id) {
  this->user_id = id;
  this->task = task;
  this->status = false;
}

TaskEntity TaskEntity::create(const Task &task, const TaskID &id) {
  return TaskEntity(task, id);
}

TaskID TaskEntity::getID() const { return user_id; }
std::string TaskEntity::getName() const { return task.getName(); }
std::string TaskEntity::getLabel() const { return task.getLabel(); }
Priority TaskEntity::getPriority() const { return task.getPriority(); }
DateTime TaskEntity::getDueTime() const { return task.getDate(); }
bool TaskEntity::getStatus() const { return status; }
Task TaskEntity::getTask() const { return task; }
std::vector<std::shared_ptr<TaskEntity>> TaskEntity::getSubtasks() const { return subtasks; }


void TaskEntity::AddSubtask(const std::shared_ptr<TaskEntity> &task) {
  subtasks.push_back(task);
}
