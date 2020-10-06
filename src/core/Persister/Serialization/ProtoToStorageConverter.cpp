//
// Created by rodion on 9/27/20.
//

#include "ProtoToStorageConverter.h"
#include "ProtoToTaskConverter.h"

TaskModel& ProtoToStorageConverter::Convert(const StorageProto &storage_proto) {
  TaskModel result;
  for(const auto& task : storage_proto.tasks()) {
    auto model_dto = ProtoToTaskConverter::ConvertProtoToModelDTO(task);
    if(model_dto.getParentID() == model_dto.getID()) {
      result.AddTask(model_dto);
    }
    else result.AddSubtask(model_dto.getParentID(), model_dto);
  }
  return result;
}
