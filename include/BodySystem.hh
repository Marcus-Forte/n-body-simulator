#pragma once

#include <Body.hh>
#include <memory>
#include <vector>

class BodySystem {
 public:
  BodySystem(double gravity_constant);
  void reset() { bodies_.clear(); }
  void addBody(std::string name, std::shared_ptr<Body> body,
               bool static_body = false);

  /// @brief Computes interactions of all bodies of the system.
  void step(double delta_t);

  /// @brief print coordinates of all bodies.
  void printCoordinates() const;

  inline const std::unordered_map<std::string, std::shared_ptr<Body>>&
  getBodies() const {
    return bodies_;
  }

 private:
  std::unordered_map<std::string, std::shared_ptr<Body>> bodies_;
  std::unordered_map<std::string, bool> static_bodies_;
  double gravity_constant_;
};