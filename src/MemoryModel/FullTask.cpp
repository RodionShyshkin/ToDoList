//
// Created by rodion on 7/16/20.
//

#include "FullTask.h"

FullTask::FullTask() = default;

FullTask::FullTask(const Task &task, const TaskID &id) {
  this->user_id = id;
  this->task = std::make_shared<Task>(task);
  this->status = false;
}

TaskID FullTask::getUserID() const { return user_id; }
std::string FullTask::getName() const { return task->getName(); }
std::string FullTask::getLabel() const { return task->getLabel(); }
Task::Priority FullTask::getPriority() const { return task->getPriority(); }
DueTime FullTask::getTime() const { return task->getDate(); }
bool FullTask::getStatus() const { return status; }
Task FullTask::getTask() const { return *task; }
std::vector<std::shared_ptr<FullTask>> FullTask::getSubtasks() const { return subtasks; }


void FullTask::AddSubtask(const std::shared_ptr<FullTask> &task) {
  subtasks.push_back(task);
}

void FullTask::setComplete() {
  this->status = true;
}

void FullTask::substituteTask(const Task &newtask) {
  this->task = std::make_shared<Task>(newtask);
}
