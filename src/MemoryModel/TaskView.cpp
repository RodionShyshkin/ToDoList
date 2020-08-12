//
// Created by rodion on 8/2/20.
//

#include "TaskView.h"

void TaskView::AddTask(const std::shared_ptr<TaskEntity> &task) {
  priority_sorted_.insert(std::make_pair(task->GetPriority(), task));
  name_sorted_.insert(std::make_pair(task->GetName(), task));
  label_sorted_.insert(std::make_pair(task->GetLabel(), task));
  date_sorted_.insert(std::make_pair(task->GetDueTime(), task));
}


std::vector<TaskEntity> TaskView::GetAllTasks() {
  std::vector<TaskEntity> searchResult;
  for(auto [key, value] : priority_sorted_) {
    searchResult.push_back(*value.lock());
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTodayTasks() {
  std::vector<TaskEntity> searchResult;
  auto today = Date::GetCurrentDate();
  for(auto [date, task] : date_sorted_) {
    if(date.GetDate() == today.GetDate()) searchResult.push_back(*task.lock());
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetWeekTasks() {
  std::vector<TaskEntity> searchResult;
  for(auto [date, task] : date_sorted_) {
    if(Date::CheckWeek(date)) searchResult.push_back(*task.lock());
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTasksByPriority(const Priority &priority) {
  auto first = priority_sorted_.find(priority);
  std::vector<TaskEntity> searchResult;

  if(first == priority_sorted_.end()) return searchResult;
  else {
    for(auto it = first; it != priority_sorted_.end(); ++it) {
      if(it->first != priority) break;
      searchResult.push_back(*it->second.lock());
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTasksByName(const std::string &name) {
  auto first = name_sorted_.find(name);
  std::vector<TaskEntity> searchResult;
  for(auto it = first; it != name_sorted_.end(); ++it) {
    if(it->first != name) break;
    searchResult.push_back(*it->second.lock());
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTasksByLabel(const std::string &label) {
  auto first = label_sorted_.find(label);
  std::vector<TaskEntity> searchResult;
  for(auto it = first; it != label_sorted_.end(); ++it) {
    if(it->first != label) break;
    searchResult.push_back(*it->second.lock());
  }
  return searchResult;
}