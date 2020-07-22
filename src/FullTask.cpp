//
// Created by rodion on 7/16/20.
//

#include "FullTask.h"

FullTask::FullTask() = default;

FullTask::FullTask(const Task &task, const TaskID &id) {
  this->user_id = id;
  this->task = std::make_shared<Task>(task);
  this->status = false;
  this->id = UUID();
}

UUID FullTask::getUUID() const { return this->id; }
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

void FullTask::postponeTask(const Task &newtask) {
  this->task = std::make_shared<Task>(newtask);
}

void FullTask::showTask() {
  std::cout << "Task " << getUserID() << ": " << task->getName() << " (" << task->getLabel() << "), Priority: "
            << task->getPriority() << ". Deadline: " << task->getDate()
            << ". Subtasks number is " << getSubtasks().size() << ". Status: " << getStatus() << std::endl;
}

