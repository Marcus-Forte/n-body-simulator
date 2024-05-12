#include "SystemTracer.hh"

#include <iostream>
#include <string>

#include "interfaces/IBodySystem.hh"

SystemTracer::SystemTracer(unsigned int history_size)
    : IBodySystem(0.0), history_size_(history_size) {}

void SystemTracer::capture(const IBodySystem& system) {
  static int id = 0;
  auto bodies = system.getBodies();

  for (const auto& body : bodies) {
    // create a pixel object
    bodies_[std::to_string(id)] = std::make_shared<Body>(
        0.0, body.second->getPosition(), Body::Vector3{0, 0, 0}, 3.0,
        body.second->getColor());
    id++;
  }

  id = id++ % (history_size_ * bodies.size());
}