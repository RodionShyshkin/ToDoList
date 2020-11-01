//
// Created by Rodion Shyshkin on 01.11.2020.
//

#ifndef TODOLIST_SRC_CORE_API_PROTOCONVERTER_H_
#define TODOLIST_SRC_CORE_API_PROTOCONVERTER_H_

#include <priority.pb.h>
#include <API/Priority.h>
#include <MemoryModel/ModelAPI/ModelTaskDTO.h>
#include <storage_error.pb.h>
#include <API/OperationResult/StorageError.h>
#include <API/OperationResult/PersistError.h>
#include <persist_error.pb.h>

namespace proto_converter {
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

  static TaskProto ModelDTOToProto(const ModelTaskDTO& task) {
    auto newtask = std::make_unique<TaskProto>();
    newtask->set_name(task.GetName());
    newtask->set_label(task.GetLabel());
    newtask->set_priority(proto_converter::PriorityToProto(task.GetPriority()));
    newtask->mutable_deadline()->set_date(task.GetDueDate().GetDate().day_number());
    newtask->set_completed(task.GetStatus());

    auto parent = task.GetParentID();
    if(parent == task.GetID()) newtask->mutable_parent_id()->set_id(0);
    else newtask->mutable_parent_id()->set_id(parent.GetID());
    return *newtask;
  }

  static ModelTaskDTO TaskProtoToModelDTO(const TaskProto& task) {
    auto dto = ModelTaskDTO{};
    if(task.has_parent_id()) {
      dto = ModelTaskDTO::CreateWithParent(0,
                                           task.name(),
                                           task.label(),
                                           proto_converter::ProtoToPriority(task.priority()),
                                           boost::gregorian::date{task.deadline().date()},
                                           task.completed(),
                                           task.parent_id().id());
    }
    else {
      dto = ModelTaskDTO::CreateWithoutParent(0,
                                              task.name(),
                                              task.label(),
                                              proto_converter::ProtoToPriority(task.priority()),
                                              boost::gregorian::date{task.deadline().date()},
                                              task.completed());
    }
    return dto;
  }

  static ProtoStorageError StorageErrorToProto(const StorageError& error) {
    if(error == StorageError::WRONG_TASK_ID) return ProtoStorageError::WRONG_TASK_ID;
    else if(error == StorageError::INVALID_TASK) return ProtoStorageError::INVALID_TASK;
    else if(error == StorageError::TASK_NOT_FOUND) return ProtoStorageError::TASK_NOT_FOUND;
    else if(error == StorageError::PARENT_NOT_FOUND) return ProtoStorageError::PARENT_NOT_FOUND;
    throw std::runtime_error("Invalid StorageError convertion.");
  }

  static TaskID ProtoTaskIDToID(const ProtoTaskID& id) {
    return TaskID{id.id()};
  }
}

#endif //TODOLIST_SRC_CORE_API_PROTOCONVERTER_H_
