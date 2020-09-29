//
// Created by rodion on 9/27/20.
//

#include "ProtoToStorageConverter.h"
#include "ProtoToTaskConverter.h"

std::unique_ptr<TaskModel> ProtoToStorageConverter::ConvertFromProto(const StorageProto &storage_proto) {
  auto temp_storage_ = std::make_unique<TaskModel>();
  for(const auto& task : storage_proto.tasks()) {
    auto task_ = ProtoToTaskConverter::ConvertProtoToTaskEntity(task);
    if(!task_.has_value()) return nullptr;
    TaskDTO dto_ = TaskDTO::create(0, task_->GetName(), task_->GetLabel(), task_->GetPriority(),
                                   task_->GetDueTime().GetDate(), task_->GetStatus());

    OperationResult result{ErrorCode::NO_ERRORS};
    if(task.parent_id() == 0) {
      result = temp_storage_->AddTask(dto_);
    }
    else {
      result = temp_storage_->AddSubtask(TaskID{task.parent_id()}, dto_);
    }
    if(!result.GetStatus()) return nullptr;
  }
  return temp_storage_;
}