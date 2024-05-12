#include "BodySystem.hh"

#include <memory>

#include "interfaces/IBodySystem.hh"

BodySystem::BodySystem(double gravity_constant)
    : IBodySystem(gravity_constant) {}

void BodySystem::step(double delta_t) const {
  for (const auto& body : bodies_) {
    if (static_bodies_.at(body.first)) continue;

    Body::Vector3 total_acceleration{0, 0, 0};

    for (const auto& other_bodies : bodies_) {
      if (other_bodies.first == body.first) continue;

      auto distance_vector =
          (other_bodies.second->getPosition() - body.second->getPosition());
      auto distance = distance_vector.norm();
      auto direction = distance_vector / distance;

      // compute acceleration due to gravity
      double acceleration =
          (gravity_constant_ * other_bodies.second->getMass()) /
          (distance * distance);
      total_acceleration += acceleration * direction;
    }
    body.second->update(total_acceleration, delta_t);
  }
}