#include "publisher.hh"

#include <vector>

BodyPublisher::BodyPublisher(std::string&& server_address) {
  channel_ = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
  stub_ = addToScene::NewStub(channel_);
}

void BodyPublisher::addPointToScene(const std::vector<double> point, std::string name) {
  grpc::ClientContext context;

  PointCloud3 request;
  google::protobuf::Empty reply;
  auto body_pt = request.add_points();
  request.set_entity_name(std::move(name));
  body_pt->set_x(point[0]);
  body_pt->set_y(point[1]);
  body_pt->set_z(point[2]);
  body_pt->set_r(1.0);
  body_pt->set_g(0.0);
  body_pt->set_b(0.0);
  stub_->addPointCloud(&context, request, &reply);
}
