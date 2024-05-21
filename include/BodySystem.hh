#pragma once

#include <Body.hh>
#include <memory>
#include <vector>

#include "interfaces/IBodySystem.hh"

/**
 * @brief Naive step calculator
 * 
 */
class BodySystem : public IBodySystem {
 public:
  BodySystem(double gravity_constant);

  void step(double delta_t) const override;
};