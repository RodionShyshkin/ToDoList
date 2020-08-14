//
// Created by rodion on 8/2/20.
//

#ifndef TODOLIST_SRC_API_TASKVIEW_H_
#define TODOLIST_SRC_API_TASKVIEW_H_

#include <map>
#include <MemoryModel/Task/TaskEntity.h>

class TaskView {
 public:
  bool                                                        AddTask(const std::weak_ptr<TaskEntity>& task);
  bool                                                        RemoveTask(const TaskID& id);

 public:
  std::vector<TaskEntity>                                     GetTodayTasks();
  std::vector<TaskEntity>                                     GetWeekTasks();

  std::vector<TaskEntity>                                     GetAllTasks();
  std::vector<TaskEntity>                                     GetTasksByLabel(const std::string& label);
  std::vector<TaskEntity>                                     GetTasksByName(const std::string& name);
  std::vector<TaskEntity>                                     GetTasksByPriority(const Priority& priority);

 private:
  std::multimap<Priority, std::pair<TaskID, std::weak_ptr<TaskEntity>>>          priority_sorted_;
  std::multimap<std::string, std::pair<TaskID, std::weak_ptr<TaskEntity>>>       name_sorted_;
  std::multimap<std::string, std::pair<TaskID, std::weak_ptr<TaskEntity>>>       label_sorted_;
  std::multimap<Date, std::pair<TaskID, std::weak_ptr<TaskEntity>>>              date_sorted_;
};

template<typename T>
bool checkIDUniqness(const TaskID& id, std::multimap<T, std::pair<TaskID, std::weak_ptr<TaskEntity>>> map);

#endif //TODOLIST_SRC_API_TASKVIEW_H_
