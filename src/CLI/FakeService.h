//
// Created by rodion on 9/11/20.
//

#ifndef TODOLIST_SRC_CLI_FAKESERVICE_H_
#define TODOLIST_SRC_CLI_FAKESERVICE_H_

#include <API/TaskServiceInterface.h>

class FakeService : public TaskServiceInterface {
 public:
  TaskDTO                           getTask(const TaskID& id) const override;
  std::vector<TaskDTO>              getAllTasks(const bool& sortByPriority) const override;
  std::vector<TaskDTO>              getTasksForToday(const bool& sortByPriority) const override;
  std::vector<TaskDTO>              getTasksForWeek(const bool& sortByPriority) const override;
  std::vector<TaskDTO>              getTasksByLabel(const std::string &label, const bool& sortByPriority) const override;
  std::vector<TaskDTO>              getTasksByName(const std::string& name, const bool& sortByPriority) const override;
  std::vector<TaskDTO>              getTasksByPriority(const Priority& priority) const override;
  OperationResult                   addTask(const TaskDTO& task) override;
  OperationResult                   addSubtask(const TaskID &id, const TaskDTO& subtask) override;
  OperationResult                   RemoveTask(const TaskID& id) override;
  OperationResult                   postponeTask(const TaskID& id, const Date& newdate) override;
  OperationResult                   completeTask(const TaskID& id) override;

 private:
  std::vector<TaskDTO> fake_tasks_;
};

#endif //TODOLIST_SRC_CLI_FAKESERVICE_H_
