//
// Created by Rodion Shyshkin on 01.11.2020.
//

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <MemoryModel/ModelAPI/TaskModelInterface.h>
#include <API/GRPCServer.h>
#include <MemoryModel/ModelAPI/TaskModel.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

/*void RunServer(std::unique_ptr<TaskModelInterface> model) {
  std::string server_address("0.0.0.0:50051");
  GRPCServer service(std::move(model));

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc_impl::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}
*/
int main() {
  std::string server_address("0.0.0.0:50051");
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  auto model = std::make_unique<TaskModel>();
  GRPCServer service(std::move(model));

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}