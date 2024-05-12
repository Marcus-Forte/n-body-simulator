#pragma once

#include "interfaces/IBodySystem.hh"

/**
 * @brief This class keeps a history of a system last N positions.
 * Hack: Inherits from IBodySystem to be used by the publishers.
 */

class SystemTracer : public IBodySystem {
 public:
  SystemTracer(unsigned int history_size);

  void capture(const IBodySystem& system);

 private:
  /**
   * @brief No operation.
   */
  inline void step(double delta) const override {}

 private:
  unsigned int history_size_;
};