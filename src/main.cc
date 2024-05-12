#include <memory>
#include <thread>

#include "BodySystem.hh"
#include "SystemTracer.hh"
#include "factory/BodySystemPublisherFactory.hh"
#include "grpc/publisher.hh"

int main() {
  BodySystem system(0.01);

  // Normalized values
  // 1.0 mass: solar mass
  // 1.0 distance: sun-earth distance: 150M KM

  constexpr double sun_mass = 1.0;

  constexpr double earth_mass = 1.0 / 330000.0;
  constexpr double earth_sun_dist = 1.0;

  constexpr double moon_mass = earth_mass / 81.0;
  constexpr double moon_earth_distance = 0.3844 / 150.4;

  auto sun = std::make_shared<Body>(sun_mass, Body::Vector3{0, 0, 0},
                                    Body::Vector3{0, 0, 0}, 50.0,
                                    Body::ColorT{0.992, 0.722, 0.075});
  auto earth = std::make_shared<Body>(earth_mass, Body::Vector3{1.0, 0, 0},
                                      Body::Vector3{0, 0.09, 0}, 10.0,
                                      Body::ColorT{0.0, 0.0, 1.0});
  auto moon = std::make_shared<Body>(
      moon_mass, Body::Vector3{1.0 + moon_earth_distance, 0, 0},
      Body::Vector3{0, 0.095, 0}, 5.0, Body::ColorT{0.9, 0.9, 0.9});

  system.addBody("sun", sun, true);
  system.addBody("earth", earth);
  system.addBody("moon", moon);

  // system.removeBody("moon");
  constexpr int iterations = 1000000;

  auto console_publisher = factory::create_console_body_system_publisher();
  auto grpc_publisher = factory::create_grpc_publisher();

  for (unsigned int it = 0; it < iterations; ++it) {
    system.step(.2);
    console_publisher->publish(system);
    grpc_publisher->publish(system);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}