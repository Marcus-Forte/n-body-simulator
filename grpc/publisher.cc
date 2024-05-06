#include "publisher.hh"

#include <vector>

BodyPublisher::BodyPublisher(std::string&& server_address) {
  channel_ = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
  stub_ = addToScene::NewStub(channel_);
  google::protobuf::Empty reply;
  stream_writer_ = stub_->streamNamedPoints(&context_, &reply);
}

void BodyPublisher::writeBodyToStream(const std::string& name, const std::array<double, 3> position, const std::array<double, 3> color, float size) {
 NamedPoint3 request;
 auto body_pt = request.mutable_point();
  request.set_size(size);
  request.set_name(name);
  body_pt->set_x(position[0]);
  body_pt->set_y(position[1]);
  body_pt->set_z(position[2]);
  body_pt->set_r(color[0]);
  body_pt->set_g(color[1]);
  body_pt->set_b(color[2]);
  stream_writer_->Write(request);

}
