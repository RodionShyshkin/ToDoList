//
// Created by Rodion Shyshkin on 27.10.2020.
//

#ifndef TODOLIST_SRC_CORE_API_APICONVERTER_H_
#define TODOLIST_SRC_CORE_API_APICONVERTER_H_

#include <MemoryModel/ModelAPI/ModelTaskDTO.h>
#include "API/Priority.h"
#include "API/TaskDTO.h"

/*
 * Toolkit for convertions between {ModelTaskDTO} & {TaskDTO},
 * and for sorting {TaskDTO} vectors by priority.
 */

namespace api_converter {

  static std::vector<TaskDTO> GetSortedByPriority(std::vector<TaskDTO> vector) {
    sort(vector.begin(), vector.end(),
         [](const TaskDTO& lhs, const TaskDTO& rhs)
         { return lhs.getPriority() < rhs.getPriority(); });
    return vector;
  }

  static TaskDTO ConvertFromModelDTO(const ModelTaskDTO& model_dto) {
    return TaskDTO::Create(model_dto.GetID().GetID(), model_dto.GetName(),
                           model_dto.GetLabel(), model_dto.GetPriority(),
                           model_dto.GetDueDate().GetDate(), model_dto.GetStatus());
  }

  static ModelTaskDTO ConvertToModelDTO(const TaskDTO& dto) {
    return ModelTaskDTO::CreateWithoutParent(TaskID{dto.getID()}, dto.getName(),
                                             dto.getLabel(), dto.getPriority(),
                                             Date{dto.getDueDate()}, dto.getStatus());
  }

}

#endif //TODOLIST_SRC_CORE_API_APICONVERTER_H_
