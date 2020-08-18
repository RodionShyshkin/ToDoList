//
// Created by rodion on 8/2/20.
//

#include "TaskView.h"

template <typename T>
bool findByID(const TaskID& id, std::map<T, std::map<TaskID, std::weak_ptr<TaskEntity>>> map) {
  for(const auto& [type, tasks] : map) {
    for(const auto& [ID, task] : tasks) {
      if (ID == id) return true;
    }
  }
  return false;
}

template <typename T>
bool removeFromMap(const TaskID& id, std::map<T, std::map<TaskID, std::weak_ptr<TaskEntity>>>& map) {
  for(auto& [type, tasks] : map) {
    for(const auto& [ID, task] : tasks) {
      if(ID == id) {
        tasks.erase(ID);
        return true;
      }
    }
  }
  return false;
}

bool TaskView::AddTask(const std::weak_ptr<TaskEntity> &task) {
  auto id = task.lock()->GetID();
  auto pairTask = std::make_pair(task.lock()->GetID(), task);

  if(findByID(id, priority_sorted_) || findByID(id, name_sorted_) ||
    findByID(id, label_sorted_) || findByID(id, date_sorted_)) return false;
  priority_sorted_[task.lock()->GetPriority()].insert(std::make_pair(task.lock()->GetID(), task));
  name_sorted_[task.lock()->GetName()].insert(std::make_pair(task.lock()->GetID(), task));
  label_sorted_[task.lock()->GetLabel()].insert(std::make_pair(task.lock()->GetID(), task));
  date_sorted_[task.lock()->GetDueTime()].insert(std::make_pair(task.lock()->GetID(), task));
  return true;
}

bool TaskView::RemoveTask(const TaskID& id) {
  if(!removeFromMap(id, priority_sorted_) || !removeFromMap(id, name_sorted_)
        || !removeFromMap(id, label_sorted_) || !removeFromMap(id, date_sorted_)) return false;
  return true;
}

std::vector<TaskEntity> TaskView::GetAllTasks() {
  std::vector<TaskEntity> searchResult;
  for(const auto& [priority, tasks] : date_sorted_) {
    for(const auto& [ID, task] : tasks) {
      searchResult.push_back(*(task.lock()));
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTodayTasks() {
  std::vector<TaskEntity> searchResult;
  auto today = Date::GetCurrentDate();
  for(const auto& [date, tasks] : date_sorted_) {
    if(date.GetDate() == today.GetDate()) {
      for(const auto& [ID, task] : tasks) {
        searchResult.push_back(*task.lock());
      }
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetWeekTasks() {
  std::vector<TaskEntity> searchResult;
  for(const auto& [date, tasks] : date_sorted_) {
    if(Date::CheckWeek(date)) {
      for(const auto& [ID, task] : tasks) {
        searchResult.push_back(*task.lock());
      }
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTasksByPriority(const Priority &priority) {
  std::vector<TaskEntity> searchResult;

  if(priority_sorted_.find(priority) == priority_sorted_.end()) return searchResult;
  else {
    for(const auto& [ID, task] : priority_sorted_[priority]) {
      searchResult.push_back(*task.lock());
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTasksByName(const std::string &name) {
  auto first = name_sorted_.find(name);
  std::vector<TaskEntity> searchResult;

  if(name_sorted_.find(name) == name_sorted_.end()) return searchResult;
  else {
    for(const auto& [ID, task] : name_sorted_[name]) {
      searchResult.push_back(*task.lock());
    }
  }
  return searchResult;
}

std::vector<TaskEntity> TaskView::GetTasksByLabel(const std::string &label) {
  std::vector<TaskEntity> searchResult;

  if(label_sorted_.find(label) == label_sorted_.end()) return searchResult;
  else {
    for(const auto& [ID, task] : label_sorted_[label]) {
      searchResult.push_back(*task.lock());
    }
  }
  return searchResult;
}