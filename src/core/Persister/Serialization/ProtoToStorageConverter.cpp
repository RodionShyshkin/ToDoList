//
// Created by rodion on 9/27/20.
//

#include "ProtoToStorageConverter.h"
#include "ProtoToTaskConverter.h"

void ProtoToStorageConverter::ConvertProtoToStorage(const StorageProto &storage_proto, TaskModelInterface& model) {
  for(const auto& task : storage_proto.tasks()) {
    auto model_dto = ProtoToTaskConverter::ConvertProtoToTask(task);
    if(model_dto.getParentID() == model_dto.getID()) {
      model.AddTask(model_dto);
    }
    else model.AddSubtask(model_dto.getParentID(), model_dto);
  }
}
