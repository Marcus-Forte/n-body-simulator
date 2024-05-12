#pragma once

#include <format>
#include <iostream>

#include "interfaces/IBodySystem.hh"
#include "interfaces/IBodySystemPublisher.hh"

/**
 * @brief Empty publisher.
 *
 */
class NullBodySystemPublisher : public IBodySystemPublisher {
 public:
  void publish(const IBodySystem& system) const override {}
};

/**
 * @brief Simple console publisher.
 *
 */
class ConsoleBodySystemPublisher : public IBodySystemPublisher {
 public:
  void publish(const IBodySystem& system) const override;
};