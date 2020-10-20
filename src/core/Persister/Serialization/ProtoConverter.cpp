//
// Created by rodion on 10/20/20.
//

#include "ProtoConverter.h"

TaskProto ProtoConverter::TaskToProto(const ModelTaskDTO &task) {
  auto newtask = std::make_unique<TaskProto>();
  newtask->set_name(task.getName());
  newtask->set_label(task.getLabel());
  newtask->set_priority(ProtoConverter::PriorityToProto(task.getPriority()));
  newtask->set_deadline(task.getDueDate().GetDate().day_number());
  newtask->set_completed(task.getStatus());

  auto parent = task.getParentID();
  if(parent == task.getID()) newtask->set_parent_id(0);
  else newtask->set_parent_id(parent.GetID());
  return *newtask;
}

TaskProto_Priority ProtoConverter::PriorityToProto(const Priority &priority) {
  if(Priority::EMPTY == priority) return TaskProto_Priority_EMPTY;
  else if(Priority::LOW == priority) return TaskProto_Priority_LOW;
  else if(Priority::MEDIUM == priority) return TaskProto_Priority_MEDIUM;
  else if(Priority::HIGH == priority) return TaskProto_Priority_HIGH;
  throw std::runtime_error("Invalid priority serialization.");
}

ModelTaskDTO ProtoConverter::ProtoToTask(const TaskProto &task) {
  if(task.deadline() == 0) {
    return ModelTaskDTO::createWithoutParent(TaskID{0}, task.name(), task.label(),
                                             ProtoConverter::ProtoToPriority(task.priority()),
                                             Date{boost::gregorian::date{task.deadline()}}, task.completed());
  }
  return ModelTaskDTO::createWithParent(TaskID{0}, task.name(), task.label(),
                                        ProtoConverter::ProtoToPriority(task.priority()),
                                        Date{boost::gregorian::date{task.deadline()}}, task.completed(),
                                        TaskID{task.parent_id()});
}

Priority ProtoConverter::ProtoToPriority(const TaskProto_Priority &priority) {
  if(TaskProto_Priority_EMPTY == priority) return Priority::EMPTY;
  else if(TaskProto_Priority_LOW == priority) return Priority::LOW;
  else if(TaskProto_Priority_MEDIUM == priority) return Priority::MEDIUM;
  else if(TaskProto_Priority_HIGH == priority) return Priority::HIGH;
  throw std::runtime_error("Invalid priority deserialization.");
}

void ProtoConverter::StorageToProto(const std::vector<ModelTaskDTO> &tasks, StorageProto& storage) {
  for(const auto& task : tasks) {
    auto* newTask = storage.add_tasks();
    TaskProto temporary;
    temporary = ProtoConverter::TaskToProto(task);
    *newTask = temporary;
  }
}

bool ProtoConverter::ProtoToModel(const StorageProto &storage_proto, TaskModelInterface& model) {
  for(const auto& task : storage_proto.tasks()) {
    auto model_dto = ProtoConverter::ProtoToTask(task);
    if(model_dto.getParentID() == model_dto.getID()) {
      auto result = model.AddTask(model_dto);
      if(result.GetError().has_value()) return false;
    }
    else model.AddSubtask(model_dto.getParentID(), model_dto);
  }
  return true;
}
