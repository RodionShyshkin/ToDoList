//
// Created by Rodion Shyshkin on 30.10.2020.
//

#ifndef TODOLIST_SRC_CORE_API_GRPCSERVER_H_
#define TODOLIST_SRC_CORE_API_GRPCSERVER_H_

#include <service.grpc.pb.h>
#include <MemoryModel/ModelAPI/TaskModelInterface.h>

 class GRPCServer final : public ::gRPCTaskService::Service {
 public:
  GRPCServer(std::unique_ptr<TaskModelInterface> model);

 public:
  ::grpc::Status AddTask(::grpc::ServerContext *context, const ::AddTaskRequest *request, ::StorageResponse *response) override;
  ::grpc::Status AddSubtask(::grpc::ServerContext *context, const ::AddSubtaskRequest *request, ::StorageResponse *response) override;
  ::grpc::Status RemoveTask(::grpc::ServerContext *context, const ::RemoveTaskRequest *request, ::StorageResponse *response) override;

  ::grpc::Status GetTask(::grpc::ServerContext *context, const ::GetTaskRequest *request, ::GetTaskResponse *response) override;
  ::grpc::Status GetAllTasks(::grpc::ServerContext *context, const ::GetAllTasksRequest *request, ::TasksListResponse *response) override;
  ::grpc::Status GetTodayTasks(::grpc::ServerContext *context, const ::GetTodayTasksRequest *request, ::TasksListResponse *response) override;
  ::grpc::Status GetWeekTasks(::grpc::ServerContext *context, const ::GetWeekTasksRequest *request, ::TasksListResponse *response) override;

  ::grpc::Status GetTasksByLabel(::grpc::ServerContext *context, const ::GetTasksByLabelRequest *request, ::TasksListResponse *response) override;
  ::grpc::Status GetTasksByName(::grpc::ServerContext *context, const ::GetTasksByNameRequest *request, ::TasksListResponse *response) override;
  ::grpc::Status GetTasksByPriority(::grpc::ServerContext *context, const ::GetTasksByPriorityRequest *request, ::TasksListResponse *response) override;

  ::grpc::Status GetSubtasks(::grpc::ServerContext *context, const ::GetSubtasksRequest *request, ::TasksListResponse *response) override;

  ::grpc::Status CompleteTask(::grpc::ServerContext *context, const ::CompleteTaskRequest *request, ::BoolResponse *response) override;
  ::grpc::Status PostponeTask(::grpc::ServerContext *context, const ::PostponeTaskRequest *request, ::BoolResponse *response) override;

  ::grpc::Status Save(::grpc::ServerContext *context, const ::SaveTasksRequest *request, ::PersistResponse *response) override;
  ::grpc::Status Load(::grpc::ServerContext *context, const ::LoadTasksRequest *request, ::PersistResponse *response) override;

 private:
  std::unique_ptr<TaskModelInterface> model_;
};

#endif //TODOLIST_SRC_CORE_API_GRPCSERVER_H_
