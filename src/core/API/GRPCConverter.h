//
// Created by Rodion Shyshkin on 30.10.2020.
//

#ifndef TODOLIST_SRC_CORE_API_GRPCCONVERTER_H_
#define TODOLIST_SRC_CORE_API_GRPCCONVERTER_H_

#include <MemoryModel/ModelAPI/ModelTaskDTO.h>
#include <API/ProtoConverter.h>
#include <requests.pb.h>
#include <storage_error.pb.h>
#include <API/OperationResult/StorageError.h>
#include <API/OperationResult/OperationResult.h>
#include <API/OperationResult/PersistError.h>

namespace grpc_converter {
  static std::optional<ModelTaskDTO>
      AddTaskRequestToModelDTO(const AddTaskRequest& request) {
    if(request.has_task()) {
      auto task = request.task();
      return proto_converter::TaskProtoToModelDTO(task);
    }
    else return std::nullopt;
  }

  static StorageResponse StorageResultToProto(const OperationResult<StorageError>& operation_result) {
    auto result = StorageResponse::default_instance().New();
    auto error = operation_result.GetError();
    if(error == std::nullopt) {
      result->set_error(ProtoStorageError::NO_ERRORS);
    }
    else result->set_error(proto_converter::StorageErrorToProto(error.value()));

    return *result;
  }

  static TasksListResponse ModelDTOVectorToResponse(const std::vector<ModelTaskDTO>& tasks) {
    auto result = TasksListResponse::default_instance().New();
    for(const auto& task : tasks) {
      auto* newTask = result->add_tasks();
      TaskProto temporary;
      temporary = proto_converter::ModelDTOToProto(task);
      *newTask = temporary;
    }
    return *result;
  }

  static std::vector<ModelTaskDTO> GetSortedByPriorityModelDTO(std::vector<ModelTaskDTO> vector) {
    sort(vector.begin(), vector.end(),
         [](const ModelTaskDTO& lhs, const ModelTaskDTO& rhs)
         { return lhs.GetPriority() < rhs.GetPriority(); });
    return vector;
  }
}

#endif //TODOLIST_SRC_CORE_API_GRPCCONVERTER_H_
