//
// Created by rodion on 8/2/20.
//

#include "TaskFactory.h"

TaskFactory::TaskFactory() : newID(GenerateID()) {}

TaskFactory::~TaskFactory() = default;

std::shared_ptr<TaskEntity> TaskFactory::addTask(const Task &task) {
  auto newid = newID.generateID();
  auto task_ptr = std::make_shared<TaskEntity>(task, newid);
  tasks.insert(std::make_pair(newid, task_ptr));
  return task_ptr;
}

std::optional<std::shared_ptr<TaskEntity>> TaskFactory::addSubtask(const TaskID &id, const Task &subtask) {
  if(tasks.find(id) != tasks.end()) {
    auto newid = newID.generateID();
    auto task_ptr = std::make_shared<TaskEntity>(subtask, newid);
    tasks.insert(std::make_pair(newid, task_ptr));
  }
  return std::nullopt;
}
