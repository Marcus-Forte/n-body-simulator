#pragma once

#include <Eigen/Dense>  // TODO improve coupling

class Body {
 public:
  using Vector3 = Eigen::Vector3d;
  using ColorT = std::array<double, 3>;

  explicit Body(double mass, Vector3 position, Vector3 velocity, double volume,
                ColorT color);

  Vector3 getPosition() const;
  double getMass() const;
  void updatePosition(double delta_t);
  void updateVelocity(Vector3 acceleration, double delta_t);

  ColorT getColor() const;
  unsigned int getVolume() const;

 private:
  double mass_;
  Vector3 position_;
  Vector3 velocity_;

  /**
   * @brief volume representation in INT. Relatable to the size of a pixel.
   *
   */
  double volume_;
  std::array<double, 3> color_;
};
