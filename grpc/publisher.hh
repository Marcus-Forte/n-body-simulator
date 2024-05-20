#pragma once

#include <array>
#include <memory>

#include "grpcpp/grpcpp.h"
#include "interfaces/IBodySystemPublisher.hh"
#include "points.grpc.pb.h"
#include "points.pb.h"

class gRPCBodyPublisher : public IBodySystemPublisher {
 public:
  gRPCBodyPublisher(std::string&& server_address, bool persistent_draw = false);

  void publish(const IBodySystem& system) const override;

 private:
  void writeBodyToStream(const Body& body, const std::string& name) const;

  std::unique_ptr<addToScene::Stub> stub_;
  std::shared_ptr<grpc::Channel> channel_;
  std::unique_ptr<::grpc::ClientWriter<::NamedPoint3>> stream_writer_;
  grpc::ClientContext context_;

  bool persitent_drawing_;
};

namespace factory {
inline std::unique_ptr<IBodySystemPublisher> create_grpc_publisher(
    bool persistent_drawing) {
  // use `host.docker.internal:50051` when running this app from inside
  // container and gRPC server is running in the host.
  return std::make_unique<gRPCBodyPublisher>("host.docker.internal:50051",
                                             persistent_drawing);
}
}  // namespace factory