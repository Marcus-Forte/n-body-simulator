#pragma once

#include "interfaces/IBodySystem.hh"

/**
 * @brief This class keeps a history of a system last N positions.
 *
 */

class SystemTracer : public IBodySystem {
  SystemTracer(unsigned int history_size);

 private:
  unsigned int history_size_;
};