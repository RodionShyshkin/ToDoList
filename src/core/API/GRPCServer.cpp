//
// Created by Rodion Shyshkin on 30.10.2020.
//

#include <future>
#include <Persister/PersisterInterface.h>
#include <Persister/FilePersister.h>
#include <MemoryModel/ModelAPI/TaskModel.h>
#include "GRPCServer.h"
#include "GRPCConverter.h"
#include "ApiConverter.h"

GRPCServer::GRPCServer(std::unique_ptr<TaskModelInterface> model)
: model_(std::move(model)) {  }

::grpc::Status GRPCServer::AddTask(::grpc::ServerContext *context,
                                   const ::AddTaskRequest *request,
                                   ::StorageResponse *response) {
  auto converted_request = grpc_converter::AddTaskRequestToModelDTO(*request);
  if(!converted_request.has_value()) return ::grpc::Status::CANCELLED;

  auto task = converted_request.value();
  auto result = model_->AddTask(task);

  *response = grpc_converter::StorageResultToProto(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::AddSubtask(::grpc::ServerContext *context,
                                      const ::AddSubtaskRequest *request,
                                      ::StorageResponse *response) {
  if(!request->has_task()) return ::grpc::Status::CANCELLED;
  if(!request->has_parent()) return ::grpc::Status::CANCELLED;
  auto converted_task = grpc_converter::TaskProtoToModelDTO(request->task());
  auto converted_id = grpc_converter::ProtoTaskIDToID(request->parent());

  auto result = model_->AddSubtask(converted_id, converted_task);

  *response = grpc_converter::StorageResultToProto(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::RemoveTask(::grpc::ServerContext *context,
                                      const ::RemoveTaskRequest *request,
                                      ::StorageResponse *response) {
  if(!request->has_id()) return ::grpc::Status::CANCELLED;
  auto converted_id = grpc_converter::ProtoTaskIDToID(request->id());

  auto result = model_->RemoveTask(converted_id);

  *response = grpc_converter::StorageResultToProto(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::GetTask(::grpc::ServerContext *context,
                                   const ::GetTaskRequest *request,
                                   ::GetTaskResponse *response) {
  if(!request->has_id()) return ::grpc::Status::CANCELLED;
  auto converted_id = grpc_converter::ProtoTaskIDToID(request->id());

  auto result = model_->GetTask(converted_id);

  if(result.has_value()) {
    auto proto_task = grpc_converter::ModelDTOToProto(result.value());
    auto proto_task_ptr = std::make_unique<TaskProto>(proto_task);
    response->set_allocated_task(proto_task_ptr.get());
  }
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::GetAllTasks(::grpc::ServerContext *context,
                                       const ::GetAllTasksRequest *request,
                                       ::TasksListResponse *response) {
  auto result = model_->GetAllTasks();
  if(request->is_sorted_by_priority()) {
    result = grpc_converter::GetSortedByPriorityModelDTO(result);
  }

  *response = grpc_converter::ModelDTOVectorToResponse(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::GetTodayTasks(::grpc::ServerContext *context,
                                         const ::GetTodayTasksRequest *request,
                                         ::TasksListResponse *response) {
  auto result = model_->GetTasksForToday();
  if(request->is_sorted_by_priority()) {
    result = grpc_converter::GetSortedByPriorityModelDTO(result);
  }

  *response = grpc_converter::ModelDTOVectorToResponse(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::GetWeekTasks(::grpc::ServerContext *context,
                                        const ::GetWeekTasksRequest *request,
                                        ::TasksListResponse *response) {
  auto result = model_->GetTasksForWeek();
  if(request->is_sorted_by_priority()) {
    result = grpc_converter::GetSortedByPriorityModelDTO(result);
  }

  *response = grpc_converter::ModelDTOVectorToResponse(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::GetTasksByLabel(::grpc::ServerContext *context,
                                           const ::GetTasksByLabelRequest *request,
                                           ::TasksListResponse *response) {
  auto result = model_->GetTasksByLabel(request->label());
  if(request->is_sorted_by_priority()) {
    result = grpc_converter::GetSortedByPriorityModelDTO(result);
  }

  *response = grpc_converter::ModelDTOVectorToResponse(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::GetTasksByName(::grpc::ServerContext *context,
                                          const ::GetTasksByNameRequest *request,
                                          ::TasksListResponse *response) {
  auto result = model_->GetTasksByName(request->name());
  if(request->is_sorted_by_priority()) {
    result = grpc_converter::GetSortedByPriorityModelDTO(result);
  }

  *response = grpc_converter::ModelDTOVectorToResponse(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::GetTasksByPriority(::grpc::ServerContext *context,
                                              const ::GetTasksByPriorityRequest *request,
                                              ::TasksListResponse *response) {
  auto converted_priority = grpc_converter::ProtoToPriority(request->priority());

  auto result = model_->GetTasksByPriority(converted_priority);

  *response = grpc_converter::ModelDTOVectorToResponse(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::CompleteTask(::grpc::ServerContext *context,
                                        const ::CompleteTaskRequest *request,
                                        ::BoolResponse *response) {
  if(!request->has_id()) return ::grpc::Status::CANCELLED;
  auto converted_id = grpc_converter::ProtoTaskIDToID(request->id());

  auto result = model_->CompleteTask(converted_id);

  response->set_status(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::PostponeTask(::grpc::ServerContext *context,
                                        const ::PostponeTaskRequest *request,
                                        ::BoolResponse *response) {
  if(!request->has_id()) return ::grpc::Status::CANCELLED;
  if(!request->has_date()) return ::grpc::Status::CANCELLED;
  auto converted_id = grpc_converter::ProtoTaskIDToID(request->id());
  auto converted_date = boost::gregorian::date{request->date().date()};

  auto result = model_->PostponeTask(converted_id, converted_date);

  response->set_status(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::GetSubtasks(::grpc::ServerContext *context,
                                       const ::GetSubtasksRequest *request,
                                       ::TasksListResponse *response) {
  if(!request->has_id()) return ::grpc::Status::CANCELLED;
  auto converted_id = grpc_converter::ProtoTaskIDToID(request->id());

  auto result = model_->GetSubtasks(converted_id);

  *response = grpc_converter::ModelDTOVectorToResponse(result);
  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::Save(::grpc::ServerContext *context,
                                const ::SaveTasksRequest *request,
                                ::PersistResponse *response) {
  std::fstream file(request->filepath(), std::ios::out);
  auto persister = std::make_unique<FilePersister>(std::move(file), *model_);
  auto future = std::async(std::bind(&PersisterInterface::Save, persister.get()));
  future.wait();


  if(!future.get()) response->set_error(ProtoPersistError::SAVE_ERROR);

  return ::grpc::Status::OK;
}

::grpc::Status GRPCServer::Load(::grpc::ServerContext *context,
                                const ::LoadTasksRequest *request,
                                ::PersistResponse *response) {
  std::fstream file(request->filepath(), std::ios::in);
  std::unique_ptr<TaskModelInterface> newmodel = std::make_unique<TaskModel>();
  auto persister = std::make_unique<FilePersister>(std::move(file), *newmodel);


  auto future = std::async(std::bind(&PersisterInterface::Load, persister.get()));
  if(!future.get()) {
    response->set_error(ProtoPersistError::LOAD_ERROR);
    return ::grpc::Status::OK;
  }
  std::swap(model_, newmodel);
  return ::grpc::Status::OK;
}