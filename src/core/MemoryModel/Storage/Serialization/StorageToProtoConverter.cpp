//
// Created by rodion on 9/27/20.
//

#include "StorageToProtoConverter.h"

StorageProto StorageToProtoConverter::ConvertStorageToProto(const std::vector<TaskEntity> &tasks) {
  StorageProto storage;
  for(const auto& task : tasks) {
    auto* newTask = storage.add_tasks();
    TaskProto temporary;
    temporary = TaskToProtoConverter::ConvertTaskWithSubtasks(task);
    *newTask = temporary;
  }
  return storage;
}