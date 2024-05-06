#pragma once

#include <array>

#include "grpcpp/grpcpp.h"
#include "points.grpc.pb.h"
#include "points.pb.h"

class BodyPublisher {
 public:
  BodyPublisher(std::string&& server_address);
  void writeBodyToStream(const std::string& name, const std::array<double, 3> position, const std::array<double, 3> color, float size);

 private:
  std::unique_ptr<addToScene::Stub> stub_;
  std::shared_ptr<grpc::Channel> channel_;
  std::unique_ptr<::grpc::ClientWriter<::NamedPoint3>> stream_writer_;
  grpc::ClientContext context_;
};