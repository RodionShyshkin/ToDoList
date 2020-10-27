//
// Created by Rodion Shyshkin on 25.10.2020.
//

#ifndef TODOLIST_SRC_CORE_MEMORYMODEL_MODELAPI_MODELTASKDTOCONVERTER_H_
#define TODOLIST_SRC_CORE_MEMORYMODEL_MODELAPI_MODELTASKDTOCONVERTER_H_

#include <MemoryModel/Task/TaskEntity.h>
#include "ModelTaskDTO.h"

namespace model_task_dto_converter {
  static ModelTaskDTO Convert(const TaskEntity& task) {
    if(task.GetID().GetID() != task.GetParentID().GetID())
      return ModelTaskDTO::CreateWithParent(task.GetID(), task.GetName(),
                                            task.GetLabel(), task.GetPriority(),
                                            task.GetDueTime(), task.GetStatus(),
                                            task.GetParentID());
    return ModelTaskDTO::CreateWithoutParent(task.GetID(), task.GetName(),
                                             task.GetLabel(), task.GetPriority(),
                                             task.GetDueTime(), task.GetStatus());
  }
}

#endif //TODOLIST_SRC_CORE_MEMORYMODEL_MODELAPI_MODELTASKDTOCONVERTER_H_
