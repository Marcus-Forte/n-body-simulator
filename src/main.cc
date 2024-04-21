#include <iostream>
#include <memory>
#include <thread>

#include "BodySystem.hh"
#include "grpc/publisher.hh"

int main() {
  BodySystem system(0.01);
  auto body1 = std::make_shared<Body>(2500, Body::Vector2{0, 0}, Body::Vector2{0, 0});
  auto body2 = std::make_shared<Body>(8, Body::Vector2{10.0, 0}, Body::Vector2{0, 1.0});
  auto body3 = std::make_shared<Body>(4, Body::Vector2{-10.0, 0}, Body::Vector2{0, -1.0});
  auto body4 = std::make_shared<Body>(18, Body::Vector2{0.0, 20}, Body::Vector2{1.0, 0.0});
  system.addBody("sun", body1, true);
  system.addBody("earth", body2);
  system.addBody("mars", body3);
  system.addBody("jupiter", body4);
  constexpr int iterations = 1000000;

  BodyPublisher publisher("host.docker.internal:50051");

  for (unsigned int it = 0; it < iterations; ++it) {
    system.step(0.2);
    system.printCoordinates();
    const auto bodies = system.getBodies();

    // Print bodies on
    for (auto &body : bodies) {
      const auto coordinate = body.second->getPosition();
      publisher.addPointToScene({coordinate[0], coordinate[1]}, body.first);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}