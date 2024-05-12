#include "BodySystemPublisher.hh"

#include "interfaces/IBodySystem.hh"

void ConsoleBodySystemPublisher::publish(const IBodySystem& system) const {
  if (system.getBodies().empty()) {
    std::cout << "No bodies!" << std::endl;
    return;
  }

  for (const auto& body : system.getBodies()) {
    const auto& body_pos = body.second->getPosition();

    std::cout << std::format("{} is at ({},{},{})", body.first, body_pos[0],
                             body_pos[1], body_pos[2])
              << std::endl;
  }
}