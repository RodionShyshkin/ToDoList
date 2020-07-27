//
// Created by rodion on 7/15/20.
//

#include <algorithm>
#include "TaskService.h"
#include "TaskOutput.h"

using Pointer = std::shared_ptr<FullTask>;
using Vector = std::vector<FullTaskDTO>;
using Multimap = std::multimap<Task::Priority, Pointer>;

TaskService::TaskService() : newID() {}
TaskService::~TaskService() = default;


std::vector<FullTaskDTO> TaskService::getAllTasks() const {
  std::vector<FullTaskDTO> searchResult;
  for (auto[key, value] : sortedTasks) {
    searchResult.push_back(FullTaskDTO(value));
  }
  return searchResult;
}

std::vector<FullTaskDTO> TaskService::getTasksForToday() const {
  std::vector<FullTaskDTO> todayTasks;
  for(auto [priority, task] : sortedTasks) {
    auto now = getCurrentTime();
    auto taskDate = task->getDueTime().getTime();

    if(now.getYear() == taskDate.getYear() && now.getMonth() == taskDate.getMonth() && now.getDay() == taskDate.getDay()) {
      todayTasks.push_back(FullTaskDTO(task));
    }
  }
  return todayTasks;
}

std::vector<FullTaskDTO> TaskService::getTasksForWeek() const {
  std::vector<FullTaskDTO> weekTasks;
  auto now = getCurrentTime();
  auto nowPlusWeek = addWeek(now);
  for (auto[priority, task] : sortedTasks) {
    auto taskDate = task->getDueTime();
    if (taskDate > now && taskDate < nowPlusWeek) weekTasks.push_back(FullTaskDTO(task));
  }
  return weekTasks;
}

std::vector<FullTaskDTO> TaskService::getTasksForLabel(const std::string &label) const {
  std::vector<FullTaskDTO> searchResult;
  for (auto[priority, sortingTask] : sortedTasks) {
    if (sortingTask->getLabel() == label) {
      searchResult.push_back(sortingTask);
    }
  }
  return searchResult;
}

std::shared_ptr<FullTask> TaskService::getTaskByID(const TaskID &id) const {
  for(auto task : tasks) {
    if(task->getUserID() == id) return task;
  }
}

void TaskService::addTask(const Task &task) {
  auto task_ptr = std::make_shared<FullTask>(task, newID.generateID());
  tasks.push_back(task_ptr);
  sortedTasks.insert(std::pair<Task::Priority, std::shared_ptr<FullTask>>(task.getPriority(), task_ptr));
}

void TaskService::addSubtask(const TaskID &id, const Task &subtask) {
  for (auto task : tasks) {
    if (task->getUserID() == id) {
      auto subptr = std::make_shared<FullTask>(subtask, id);
      task->AddSubtask(subptr);
      addTask(subtask);
      return;
    }
  }
}

void TaskService::removeTask(const TaskID &id) {
  auto taskToRemove = std::make_shared<FullTask>();
  size_t NumInVector;
  auto IteratorInMultimap = sortedTasks.begin();

  for (auto counter = 0; counter < tasks.size(); counter++) {
    if (tasks[counter]->getUserID() == id) {
      taskToRemove = tasks[counter];
      NumInVector = counter;
      break;
    }
  }
  for (auto it = sortedTasks.begin(); it != sortedTasks.end(); ++it) {
    if (it->second->getUserID() == id) {
      IteratorInMultimap = it;
      break;
    }
  }

  tasks.erase(tasks.begin() + NumInVector);
  sortedTasks.erase(IteratorInMultimap);
}

void TaskService::completeTask(const TaskID &id) {
  for(auto task : tasks) {
    if(task->getUserID() == id) {
      task->setComplete();
      return;
    }
  }
}

void TaskService::postponeTask(const TaskID &id, const DateTime &newtime) {
  for(auto task : tasks) {
    if(task->getUserID() == id) {
      auto newtask = Task(task->getName(), task->getLabel(), task->getPriority(), newtime);
      task->substituteTask(newtask);
   }
  }
}

