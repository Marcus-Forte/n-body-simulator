#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Body.hh"

class IBodySystem {
 public:
  IBodySystem(double gravity_constant) : gravity_constant_(gravity_constant) {}
  virtual ~IBodySystem() = default;

  inline void reset() { bodies_.clear(); }

  inline void addBody(const std::string& name, std::shared_ptr<Body> body,
                      bool static_body = false) {
    bodies_.insert({name, body});
    static_bodies_.insert({name, static_body});
  }

  inline void removeBody(const std::string& name) {
    bodies_.erase(name);
    static_bodies_.erase(name);
  }

  inline const std::unordered_map<std::string, std::shared_ptr<Body>>&
  getBodies() const {
    return bodies_;
  }

  /**
   * @brief Computes interactions of all bodies of the system.
   *
   * @param delta delta time.
   */
  virtual void step(double delta) const = 0;

 protected:
  std::unordered_map<std::string, std::shared_ptr<Body>> bodies_;
  std::unordered_map<std::string, bool> static_bodies_;
  const double gravity_constant_;
};