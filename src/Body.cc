#include "Body.hh"

Body::Body(double mass, Vector3 position, Vector3 velocity, double volume,
           ColorT color)
    : mass_(mass),
      position_{std::move(position)},
      velocity_{std::move(velocity)},
      volume_(volume),
      color_(color) {}

void Body::update(Vector3 acceleration, double delta_t) {
  position_ = position_ + velocity_ * delta_t;
  velocity_ = velocity_ + acceleration * delta_t;
}

Body::Vector3 Body::getPosition() const { return position_; }

double Body::getMass() const { return mass_; }

unsigned int Body::getVolume() const { return volume_; }

Body::ColorT Body::getColor() const { return color_; }