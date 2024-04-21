#pragma once

#include "grpcpp/grpcpp.h"
#include "points.grpc.pb.h"
#include "points.pb.h"

class BodyPublisher {
 public:
  BodyPublisher(std::string&& server_address);
  void addPointToScene(const std::vector<double> point, std::string name);

 private:
  std::unique_ptr<addToScene::Stub> stub_;
  std::shared_ptr<grpc::Channel> channel_;
};