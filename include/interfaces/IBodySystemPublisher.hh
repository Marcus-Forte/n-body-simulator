#pragma once

#include "IBodySystem.hh"

/**
 * @brief BodySystem Publisher interface.
 *
 */
class IBodySystemPublisher {
 public:
  /**
   * @brief Publishes/Renders the information of the system bodies.
   *
   * @param system
   */
  virtual void publish(const IBodySystem& system) const = 0;
};