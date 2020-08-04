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

TaskID TaskEntity::getID() const { return user_id; }
std::string TaskEntity::getName() const { return task.getName(); }
std::string TaskEntity::getLabel() const { return task.getLabel(); }
Task::Priority TaskEntity::getPriority() const { return task.getPriority(); }
DueTime TaskEntity::getDueTime() const { return task.getDate(); }
bool TaskEntity::getStatus() const { return status; }
Task TaskEntity::getTask() const { return task; }
std::vector<std::shared_ptr<TaskEntity>> TaskEntity::getSubtasks() const { return subtasks; }


void TaskEntity::AddSubtask(const std::shared_ptr<TaskEntity> &task) {
  subtasks.push_back(task);
}

/*void TaskEntity::setComplete() {
  this->status = true;
}

void TaskEntity::substituteTask(const Task &newtask) {
  this->task = newtask;
}
*/