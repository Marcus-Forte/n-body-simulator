#pragma once

#include <array>

#include "grpcpp/grpcpp.h"
#include "points.grpc.pb.h"
#include "points.pb.h"

class BodyPublisher {
 public:
  BodyPublisher(std::string&& server_address, std::string&& system_name);
  void addBodyToScene(const std::array<double, 3> position, const std::array<double, 3> color = {1.0, 0, 0});
  void sendToStream();

 private:
  std::unique_ptr<addToScene::Stub> stub_;
  std::shared_ptr<grpc::Channel> channel_;
  PointCloud3 request_;
  std::unique_ptr<::grpc::ClientWriter<::PointCloud3>> stream_writer_;
  grpc::ClientContext context_;
};