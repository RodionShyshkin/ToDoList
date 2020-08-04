//
// Created by rodion on 8/2/20.
//

#include "TaskView.h"

void TaskView::addTask(const std::shared_ptr<TaskEntity> &task) {
  priority_sorted.insert(std::make_pair(task->getPriority(), task));
  name_sorted.insert(std::make_pair(task->getName(), task));
  label_sorted.insert(std::make_pair(task->getLabel(), task));
  date_sorted.insert(std::make_pair(task->getDueTime(), task));
}


std::vector<TaskEntity> TaskView::getAllTasks() {
  std::vector<TaskEntity> searchResult;
  for(auto [key, value] : priority_sorted) {
    searchResult.push_back(*value);
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getTodayTasks() {
  std::vector<TaskEntity> searchResult;
  auto now = getCurrentTime();
  for(auto [date, task] : date_sorted) {
    if (now.getYear() == date.getTime().getYear() && now.getMonth() == date.getTime().getMonth()
        && now.getDay() == date.getTime().getDay()) {
      searchResult.push_back(*task);
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getWeekTasks() {
  std::vector<TaskEntity> searchResult;
  auto leftBorder = getCurrentTime();
  auto rightBorder = addWeek(leftBorder);
  for(auto [date, task] : date_sorted) {
    if(date > leftBorder && date < rightBorder) searchResult.push_back(*task);
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getTasksByPriority(const Task::Priority &priority) {
  auto first = priority_sorted.find(priority);
  std::vector<TaskEntity> searchResult;

  if(first == priority_sorted.end()) return searchResult;
  else {
    for(auto it = first; it != priority_sorted.end(); ++it) {
      if(it->first != priority) break;
      searchResult.push_back(*it->second);
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getTasksByName(const std::string &name) {
  auto first = name_sorted.find(name);
  std::vector<TaskEntity> searchResult;
  for(auto it = first; it != name_sorted.end(); ++it) {
    if(it->first != name) break;
    searchResult.push_back(*it->second);
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::getTasksByLabel(const std::string &label) {
  auto first = label_sorted.find(label);
  std::vector<TaskEntity> searchResult;
  for(auto it = first; it != label_sorted.end(); ++it) {
    if(it->first != label) break;
    searchResult.push_back(*it->second);
  }
  return searchResult;
}