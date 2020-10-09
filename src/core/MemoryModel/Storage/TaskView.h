//
// Created by rodion on 8/2/20.
//

#ifndef TODOLIST_SRC_API_TASKVIEW_H_
#define TODOLIST_SRC_API_TASKVIEW_H_

#include <map>
#include <MemoryModel/Task/TaskEntity.h>
#include <MemoryModel/Storage/TaskViewInterface.h>

class TaskView : public TaskViewInterface {
 public:
  bool                                        AddTask(const std::weak_ptr<TaskEntity>& task) override;
  bool                                        RemoveTask(const TaskID& id) override;

 public:
  std::vector<TaskEntity>                     GetTodayTasks() override;
  std::vector<TaskEntity>                     GetWeekTasks() override;

  std::vector<TaskEntity>                     GetAllTasks() override;
  std::vector<TaskEntity>                     GetTasksByLabel(const std::string& label) override;
  std::vector<TaskEntity>                     GetTasksByName(const std::string& name) override;
  std::vector<TaskEntity>                     GetTasksByPriority(const Priority& priority) override;

 private:
  std::map<Priority, std::map<TaskID, std::weak_ptr<TaskEntity>>>       priority_sorted_;
  std::map<std::string, std::map<TaskID, std::weak_ptr<TaskEntity>>>    name_sorted_;
  std::map<std::string, std::map<TaskID, std::weak_ptr<TaskEntity>>>    label_sorted_;
  std::map<Date, std::map<TaskID, std::weak_ptr<TaskEntity>>>           date_sorted_;
};

#endif //TODOLIST_SRC_API_TASKVIEW_H_
