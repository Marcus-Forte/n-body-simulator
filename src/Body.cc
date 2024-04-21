#include "Body.hh"

Body::Body(double mass, Vector2 position, Vector2 velocity)
    : mass_(mass), position_{std::move(position)}, velovity_{std::move(velocity)} {}

void Body::updatePosition(double delta_t) { position_ = position_ + velovity_ * delta_t; }

void Body::updateVelocity(Vector2 acceleration, double delta_t) { velovity_ = velovity_ + delta_t * acceleration; }

Body::Vector2 Body::getPosition() const { return position_; }

double Body::getMass() const { return mass_; }