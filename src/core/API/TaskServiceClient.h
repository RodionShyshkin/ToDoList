//
// Created by Rodion Shyshkin on 02.11.2020.
//

#ifndef TODOLIST_SRC_CORE_API_TASKSERVICECLIENT_H_
#define TODOLIST_SRC_CORE_API_TASKSERVICECLIENT_H_

#include <API/TaskServiceInterface.h>
#include <service.grpc.pb.h>

class TaskServiceClient : public TaskServiceInterface {
 public:
  std::optional<TaskDTO> GetTask(const unsigned int &) const override;
  std::vector<TaskDTO> GetAllTasks(const bool &) const override;
  std::vector<TaskDTO> GetTasksForToday(const bool &) const override;
  std::vector<TaskDTO> GetTasksForWeek(const bool &) const override;
  std::vector<TaskDTO> GetTasksByLabel(const std::string &, const bool &) const override;
  std::vector<TaskDTO> GetTasksByName(const std::string &, const bool &) const override;
  std::vector<TaskDTO> GetTasksByPriority(const Priority &) const override;

  OperationResult<StorageError> AddTask(const TaskDTO &) override;
  OperationResult<StorageError> AddSubtask(const unsigned int &, const TaskDTO &) override;
  OperationResult<StorageError> RemoveTask(const unsigned int &) override;

  bool CompleteTask(const unsigned int &) override;
  bool PostponeTask(const unsigned int &, const boost::gregorian::date &) override;

  OperationResult<PersistError> Save(const std::string &) override;
  OperationResult<PersistError> Load(const std::string &) override;

 private:
  std::unique_ptr<gRPCTaskService::Stub> request_;
};

#endif //TODOLIST_SRC_CORE_API_TASKSERVICECLIENT_H_
