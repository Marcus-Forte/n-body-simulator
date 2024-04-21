#include <iostream>
#include <memory>
#include <thread>

#include "BodySystem.hh"
#include "grpc/publisher.hh"

int main() {
  BodySystem system(0.1);
  auto body1 = std::make_shared<Body>(100, Body::Vector2{0, 0}, Body::Vector2{0, 0});
  auto body2 = std::make_shared<Body>(3, Body::Vector2{10.0, 0}, Body::Vector2{0, 1.0});
  auto body3 = std::make_shared<Body>(2, Body::Vector2{-10.0, 0}, Body::Vector2{0, 1.0});
  system.addBody("sun", body1, true);
  system.addBody("earth", body2);
  // system.addBody("mars", body3);
  constexpr int iterations = 1000000;

  BodyPublisher publisher("host.docker.internal:50051");

  for (unsigned int it = 0; it < iterations; ++it) {
    system.step(0.1);
    system.printCoordinates();
    const auto bodies = system.getBodies();

    // Print bodies on
    for (auto &body : bodies) {
      const auto coordinate = body.second->getPosition();
      publisher.addPointToScene({coordinate[0], coordinate[1]}, body.first);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}