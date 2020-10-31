//
// Created by Rodion Shyshkin on 30.10.2020.
//

#ifndef TODOLIST_SRC_CORE_API_GRPCCONVERTER_H_
#define TODOLIST_SRC_CORE_API_GRPCCONVERTER_H_

#include <MemoryModel/ModelAPI/ModelTaskDTO.h>
#include <requests.pb.h>
#include <storage_error.pb.h>
#include <API/OperationResult/StorageError.h>
#include <API/OperationResult/OperationResult.h>
#include <API/OperationResult/PersistError.h>

namespace grpc_converter {
  static ProtoPriority PriorityToProto(const Priority& priority) {
    if(Priority::EMPTY == priority) return ProtoPriority::EMPTY;
    else if(Priority::LOW == priority) return ProtoPriority::LOW;
    else if(Priority::MEDIUM == priority) return ProtoPriority::MEDIUM;
    else if(Priority::HIGH == priority) return ProtoPriority::HIGH;
    throw std::runtime_error("Invalid priority convertion.");
  }
  static Priority ProtoToPriority(const ProtoPriority& priority) {
    if(ProtoPriority::EMPTY == priority) return Priority::EMPTY;
    else if(ProtoPriority::LOW == priority) return Priority::LOW;
    else if(ProtoPriority::MEDIUM == priority) return Priority::MEDIUM;
    else if(ProtoPriority::HIGH == priority) return Priority::HIGH;
    throw std::runtime_error("Invalid priority convertion.");
  }

  static ModelTaskDTO TaskProtoToModelDTO(const TaskProto& task) {
    auto dto = ModelTaskDTO{};
    if(task.has_parent_id()) {
      dto = ModelTaskDTO::CreateWithParent(0,
                                           task.name(),
                                           task.label(),
                                           grpc_converter::ProtoToPriority(task.priority()),
                                           boost::gregorian::date{task.deadline().date()},
                                           task.completed(),
                                           task.parent_id().id());
    }
    else {
      dto = ModelTaskDTO::CreateWithoutParent(0,
                                              task.name(),
                                              task.label(),
                                              grpc_converter::ProtoToPriority(task.priority()),
                                              boost::gregorian::date{task.deadline().date()},
                                              task.completed());
    }
    return dto;
  }

  static std::optional<ModelTaskDTO>
      AddTaskRequestToModelDTO(const AddTaskRequest& request) {
    if(request.has_task()) {
      auto task = request.task();
      return grpc_converter::TaskProtoToModelDTO(task);
    }
    else return std::nullopt;
  }

  static TaskID ProtoTaskIDToID(const ProtoTaskID& id) {
    return TaskID{id.id()};
  }

  static TaskProto ModelDTOToProto(const ModelTaskDTO& task) {
    auto newtask = std::make_unique<TaskProto>();
    newtask->set_name(task.GetName());
    newtask->set_label(task.GetLabel());
    newtask->set_priority(PriorityToProto(task.GetPriority()));
    newtask->mutable_deadline()->set_date(task.GetDueDate().GetDate().day_number());
    newtask->set_completed(task.GetStatus());

    auto parent = task.GetParentID();
    if(parent == task.GetID()) newtask->mutable_parent_id()->set_id(0);
    else newtask->mutable_parent_id()->set_id(parent.GetID());
    return *newtask;
  }



  static ProtoStorageError StorageErrorToProto(const StorageError& error) {
    if(error == StorageError::WRONG_TASK_ID) return ProtoStorageError::WRONG_TASK_ID;
    else if(error == StorageError::INVALID_TASK) return ProtoStorageError::INVALID_TASK;
    else if(error == StorageError::TASK_NOT_FOUND) return ProtoStorageError::TASK_NOT_FOUND;
    else if(error == StorageError::PARENT_NOT_FOUND) return ProtoStorageError::PARENT_NOT_FOUND;
    throw std::runtime_error("Invalid StorageError convertion.");
  }
  static ProtoPersistError PersistErrorToProto(const PersistError& error) {
    if(error == PersistError::SAVE_ERROR) return ProtoPersistError::SAVE_ERROR;
    else if(error == PersistError::LOAD_ERROR) return ProtoPersistError::LOAD_ERROR;
    throw std::runtime_error("Invalid PersistError convertion.");
  }

  static StorageResponse StorageResultToProto(const OperationResult<StorageError>& operation_result) {
    auto result = StorageResponse::default_instance().New();
    auto error = operation_result.GetError();
    if(error == std::nullopt) return *result;

    result->set_error(grpc_converter::StorageErrorToProto(error.value()));
    return *result;
  }
  static PersistResponse PersistResultToProto(const OperationResult<PersistError>& operation_result) {
    auto result = PersistResponse::default_instance().New();
    auto error = operation_result.GetError();
    if(error == std::nullopt) return *result;

    result->set_error(grpc_converter::PersistErrorToProto(error.value()));
    return *result;
  }

  static TasksListResponse ModelDTOVectorToResponse(const std::vector<ModelTaskDTO>& tasks) {
    auto result = TasksListResponse::default_instance().New();
    for(const auto& task : tasks) {
      auto* newTask = result->add_tasks();
      TaskProto temporary;
      temporary = grpc_converter::ModelDTOToProto(task);
      *newTask = temporary;
    }
  }

  static std::vector<ModelTaskDTO> GetSortedByPriorityModelDTO(std::vector<ModelTaskDTO> vector) {
    sort(vector.begin(), vector.end(),
         [](const ModelTaskDTO& lhs, const ModelTaskDTO& rhs)
         { return lhs.GetPriority() < rhs.GetPriority(); });
    return vector;
  }
}

#endif //TODOLIST_SRC_CORE_API_GRPCCONVERTER_H_
