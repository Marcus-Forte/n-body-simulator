#include "publisher.hh"

#include <vector>

BodyPublisher::BodyPublisher(std::string&& server_address, std::string&& name) {
  channel_ = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
  stub_ = addToScene::NewStub(channel_);
  request_.set_entity_name(std::move(name));
  request_.set_point_size(25.0);
  google::protobuf::Empty reply;
  stream_writer_ = stub_->steamPointClouds(&context_, &reply);
}

void BodyPublisher::addBodyToScene(const std::array<double, 3> position, const std::array<double, 3> color) {
  auto body_pt = request_.add_points();

  body_pt->set_x(position[0]);
  body_pt->set_y(position[1]);
  body_pt->set_z(position[2]);
  body_pt->set_r(color[0]);
  body_pt->set_g(color[1]);
  body_pt->set_b(color[2]);
}

void BodyPublisher::sendToStream() {
  stream_writer_->Write(request_);
  request_.clear_points();
}
