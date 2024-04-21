#include "BodySystem.hh"

#include <format>
#include <iostream>

BodySystem::BodySystem(double gravity_constant) : gravity_constant_(gravity_constant) {}
void BodySystem::step(double delta_t) {
  for (const auto& body : bodies_) {
    if (static_bodies_.at(body.first)) continue;
    Body::Vector2 total_force{0, 0};

    for (const auto& other_bodies : bodies_) {
      if (other_bodies.first == body.first) continue;

      auto distance_vector = (other_bodies.second->getPosition() - body.second->getPosition());
      auto distance = distance_vector.norm();
      auto direction = distance_vector / distance;
      // Acc due to gravity
      double acceleration = (gravity_constant_ * other_bodies.second->getMass()) / (distance * distance);
      Body::Vector2 acceleration_vector = acceleration * direction;

      body.second->updateVelocity(acceleration_vector, delta_t);
      std::cout << std::format("Computing force from {} to {}\n", other_bodies.first, body.first);
      // std::cout << std::format("acceleration: {}, direction: ({},{})\n", acceleration, direction[0], direction[1]);

      body.second->updatePosition(delta_t);
    }
  }
  std::cout << std::endl << std::endl;
}

void BodySystem::printCoordinates() const {
  for (const auto& body : bodies_) {
    auto position = body.second->getPosition();
    std::cout << std::format("{} is at {},{}\n", body.first, position[0], position[1]);
  }
}