#include <iostream>
#include <memory>
#include <thread>
#include <unordered_map>

#include "BodySystem.hh"
#include "grpc/publisher.hh"

const std::unordered_map<std::string, std::array<double, 3>> color_map = {
    {"earth", {0.0, 0.0, 1.0}}, {"sun", {0.992, 0.722, 0.075}}, {"moon", {0.1, 0.1, 0.1}}};

int main() {
  BodySystem system(0.01);

  // Normalized values
  // 1.0 mass: solar mass
  // 1.0 distance: sun-earth distance: 150M KM

  constexpr double earth_mass = 1.0 / 330000.0;
  constexpr double earth_sun_dist = 1.0;

  constexpr double moon_mass = earth_mass / 81.0;
  constexpr double moon_earth_distance = 0.3844 / 150.4;

  auto sun = std::make_shared<Body>(1, Body::Vector2{0, 0}, Body::Vector2{0, 0});
  auto earth = std::make_shared<Body>(earth_mass, Body::Vector2{1.0, 0}, Body::Vector2{0, 0.09});
  auto moon = std::make_shared<Body>(moon_mass, Body::Vector2{1.0 + moon_earth_distance, 0}, Body::Vector2{0, 0.095});

  system.addBody("sun", sun, true);
  system.addBody("earth", earth);
  system.addBody("moon", moon);

  // system.addBody("mars", mars);
  // system.addBody("jupiter", jupiter);
  constexpr int iterations = 1000000;

  BodyPublisher publisher("host.docker.internal:50051", "system");

  for (unsigned int it = 0; it < iterations; ++it) {
    system.step(.2);
    system.printCoordinates();
    const auto bodies = system.getBodies();

    // Print bodies on
    for (auto &body : bodies) {
      const auto coordinate = body.second->getPosition();
      publisher.addBodyToScene({coordinate[0], coordinate[1], 0}, color_map.at(body.first));
    }
    publisher.sendToStream();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}