//
// Created by rodion on 10/20/20.
//

#ifndef TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_
#define TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_

#include <task.pb.h>
#include <MemoryModel/ModelAPI/ModelTaskDTO.h>
#include <MemoryModel/ModelAPI/TaskModelInterface.h>

/*
 * \brief Toolkit for converting proto tasks to memory model structures and vice versa.
 *
 * @author Rodion Shyshkin
 */

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


  static TaskProto TaskToProto(const ModelTaskDTO& task) {
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

  static ModelTaskDTO ProtoToTask(const TaskProto& task) {
    return ModelTaskDTO::CreateWithParent(TaskID{0}, task.name(), task.label(),
                                          proto_converter::ProtoToPriority(task.priority()),
                                          Date{boost::gregorian::date{task.deadline().date()}}, task.completed(),
                                          TaskID{task.parent_id().id()});
  }

  static void StorageToProto(const std::vector<ModelTaskDTO>& tasks, StorageProto& storage) {
    for(const auto& task : tasks) {
      auto* newTask = storage.add_tasks();
      TaskProto temporary;
      temporary = proto_converter::TaskToProto(task);
      *newTask = temporary;
    }
  }
  static bool ProtoToModel(const StorageProto& storage_proto, TaskModelInterface& model) {
    for(const auto& task : storage_proto.tasks()) {
      auto model_dto = proto_converter::ProtoToTask(task);
      if(model_dto.GetParentID() == model_dto.GetID()) {
        auto result = model.AddTask(model_dto);
        if(result.GetError().has_value()) return false;
      }
      else {
        auto result = model.AddSubtask(model_dto.GetParentID(), model_dto);
        if(result.GetError().has_value()) return false;
      }
    }
    return true;
  }
}

#endif //TODOLIST_SRC_CORE_PERSISTER_SERIALIZATION_PROTOCONVERTER_H_
