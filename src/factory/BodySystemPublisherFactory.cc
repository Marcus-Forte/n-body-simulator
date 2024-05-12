#include "factory/BodySystemPublisherFactory.hh"

#include <memory>

#include "BodySystemPublisher.hh"

namespace factory {
std::unique_ptr<IBodySystemPublisher> create_null_body_system_publisher() {
  return std::make_unique<NullBodySystemPublisher>();
}

std::unique_ptr<IBodySystemPublisher> create_console_body_system_publisher() {
  return std::make_unique<ConsoleBodySystemPublisher>();
}

}  // namespace factory