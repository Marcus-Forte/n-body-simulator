#pragma once

#include <array>
#include <memory>

#include "grpcpp/grpcpp.h"
#include "points.grpc.pb.h"
#include "points.pb.h"

#include "interfaces/IBodySystemPublisher.hh"

class BodyPublisher : public IBodySystemPublisher {
 public:
  BodyPublisher(std::string&& server_address);

  void publish(const IBodySystem& system) const override;

 private:
   void writeBodyToStream(const std::string& name, const Body& body) const;

  std::unique_ptr<addToScene::Stub> stub_;
  std::shared_ptr<grpc::Channel> channel_;
  std::unique_ptr<::grpc::ClientWriter<::NamedPoint3>> stream_writer_;
  grpc::ClientContext context_;
};

namespace factory {
  inline std::unique_ptr<IBodySystemPublisher> create_grpc_publisher() {
  // use `host.docker.internal:50051` when running this app from inside
  // container and gRPC server is running in the host.
    return std::make_unique<BodyPublisher>("host.docker.internal:50051");
  }
}