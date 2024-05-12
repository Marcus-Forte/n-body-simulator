#pragma once

#include <Body.hh>
#include <memory>
#include <vector>

#include "interfaces/IBodySystem.hh"

class BodySystem : public IBodySystem {
 public:
  BodySystem(double gravity_constant);

  /// @brief Computes interactions of all bodies of the system.
  void step(double delta_t) const override;

 private:
};