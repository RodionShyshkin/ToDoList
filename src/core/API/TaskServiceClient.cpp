//
// Created by Rodion Shyshkin on 02.11.2020.
//

#include "TaskServiceClient.h"

std::optional<TaskDTO> TaskServiceClient::GetTask(const unsigned int &id) const {
  grpc::ClientContext context;

  auto request = GetTaskRequest::default_instance().New();
  auto id_param = ProtoTaskID::default_instance().New();
  id_param->set_id(id);
  request->set_allocated_id(id_param);

  auto response = GetTaskResponse::default_instance().New();

  auto result = request_->GetTask(&context, *request, response);
  if(result.ok()) {
    if(response->has_task()) {}
  }
  else return std::nullopt;
}