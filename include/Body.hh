#pragma once

#include <Eigen/Dense>

class Body {
 public:
  using Vector2 = Eigen::Vector2d;
  Body(double mass, Vector2 position, Vector2 velocity);

  Vector2 getPosition() const;
  double getMass() const;
  /// @brief
  void updatePosition(double delta_t);
  void updateVelocity(Vector2 acceleration, double delta_t);

 private:
  double mass_;
  Vector2 position_;
  Vector2 velovity_;
};