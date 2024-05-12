#include "publisher.hh"

#include <vector>
#include "interfaces/IBodySystem.hh"

BodyPublisher::BodyPublisher(std::string&& server_address) {
  channel_ = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
  stub_ = addToScene::NewStub(channel_);
  google::protobuf::Empty reply;
  stream_writer_ = stub_->streamNamedPoints(&context_, &reply);

  grpc::ClientContext context; // 1 per call
  google::protobuf::Empty empty_rep;
  stub_->resetScene(&context, {}  , &empty_rep);
}

void BodyPublisher::writeBodyToStream(const std::string& name, const Body& body)  const {
 NamedPoint3 request;
 auto body_pt = request.mutable_point();
  request.set_size(body.getVolume());
  request.set_name(name);
  body_pt->set_x(body.getPosition()[0]);
  body_pt->set_y(body.getPosition()[1]);
  body_pt->set_z(body.getPosition()[2]);
  body_pt->set_r(body.getColor()[0]);
  body_pt->set_g(body.getColor()[1]);
  body_pt->set_b(body.getColor()[2]);
  stream_writer_->Write(request);

}

void BodyPublisher::publish(const IBodySystem& system) const {
 for (auto &body : system.getBodies()) {
      const auto coordinate = body.second->getPosition();
      writeBodyToStream(body.first, *body.second);
    }
}
