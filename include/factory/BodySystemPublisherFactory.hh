#pragma once

#include <memory>

#include "interfaces/IBodySystemPublisher.hh"

namespace factory {
std::unique_ptr<IBodySystemPublisher> create_null_body_system_publisher();
std::unique_ptr<IBodySystemPublisher> create_console_body_system_publisher();
}  // namespace factory
