//
// Created by Rodion Shyshkin on 02.11.2020.
//

#include <grpcpp/grpcpp.h>
#include <service.grpc.pb.h>

class TaskServiceClient {
 public:
  explicit TaskServiceClient(const std::shared_ptr<grpc::Channel>& channel)
      : stub_(gRPCTaskService::NewStub(channel)) {}

 private:
  std::unique_ptr<gRPCTaskService::Stub> stub_;
};


int main() {
  std::string server_address("0.0.0.0:50051");
  TaskServiceClient client(grpc::CreateChannel(
      server_address, grpc::InsecureChannelCredentials()));
  return 0;
}