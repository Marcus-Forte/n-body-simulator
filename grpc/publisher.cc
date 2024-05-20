#include "publisher.hh"

#include <vector>

#include "interfaces/IBodySystem.hh"

gRPCBodyPublisher::gRPCBodyPublisher(std::string&& server_address,
                                     bool persistent_drawing)
    : persitent_drawing_(persistent_drawing) {
  channel_ =
      grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
  stub_ = addToScene::NewStub(channel_);
  google::protobuf::Empty reply;
  stream_writer_ = stub_->streamNamedPoints(&context_, &reply);

  grpc::ClientContext context;  // 1 per call
  google::protobuf::Empty empty_rep;
  stub_->resetScene(&context, {}, &empty_rep);
}

void gRPCBodyPublisher::writeBodyToStream(const Body& body,
                                          const std::string& name) const {
  NamedPoint3 request;
  auto body_pt = request.mutable_point();
  request.set_size(body.getVolume());
  if (!name.empty()) request.set_name(name);
  body_pt->set_x(body.getPosition()[0]);
  body_pt->set_y(body.getPosition()[1]);
  body_pt->set_z(body.getPosition()[2]);
  body_pt->set_r(body.getColor()[0]);
  body_pt->set_g(body.getColor()[1]);
  body_pt->set_b(body.getColor()[2]);
  stream_writer_->Write(request);
}

void gRPCBodyPublisher::publish(const IBodySystem& system) const {
  if (persitent_drawing_) {
    for (auto& body : system.getBodies()) {
      // Empty names are given unique names at renderer, effectively persisting
      // their drawing on the scene.
      writeBodyToStream(*body.second, "");
    }
  } else {
    for (auto& body : system.getBodies()) {
      writeBodyToStream(*body.second, body.first);
    }
  }
}
