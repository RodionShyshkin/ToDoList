//
// Created by rodion on 9/27/20.
//

#include "ProtoToStorageConverter.h"
#include "ProtoToTaskConverter.h"

std::vector<ModelTaskDTO> ProtoToStorageConverter::Convert(const StorageProto &storage_proto) {
  std::vector<ModelTaskDTO> result;
  for(const auto& task : storage_proto.tasks()) {
    auto model_dto = ProtoToTaskConverter::ConvertProtoToModelDTO(task);
    result.push_back(model_dto);
  }
  return result;
}
