#include <memory>
#include <thread>

#include "Body.hh"
#include "BodySystem.hh"
#include "SystemTracer.hh"
#include "factory/BodySystemPublisherFactory.hh"
#include "grpc/publisher.hh"

int main() {
  BodySystem system(0.00000005);

  // Normalized values
  // 1.0 mass: solar mass
  // 1.0 distance: sun-earth distance: 149 MegaKM
  // velocity is expressed in units of sun-earth KM / second

  constexpr double sun_mass_unit = 149e6;
  constexpr double sun_mass = 1.0;

  constexpr double earth_mass = 1.0 / 332946.0;
  constexpr double earth_sun_dist = 1.0;

  constexpr double moon_mass = sun_mass / 27068510.0;
  constexpr double moon_earth_distance = 0.3844 / sun_mass_unit;

  constexpr double earth_orbital_speed = 29722.22 / sun_mass_unit;
  constexpr double moon_orbital_speed =
      earth_orbital_speed + 3600.0 / sun_mass_unit;

  constexpr double mars_orbital_speed = 24100 / sun_mass_unit;
  constexpr double jupiter_orbital_speed = 13069 / sun_mass_unit;

  auto sun = std::make_shared<Body>(sun_mass, Body::Vector3{0, 0, 0},
                                    Body::Vector3{0, 0, 0}, 50.0,
                                    Body::ColorT{0.992, 0.722, 0.075});
  auto earth = std::make_shared<Body>(earth_mass, Body::Vector3{1.0, 0, 0},
                                      Body::Vector3{0, earth_orbital_speed, 0},
                                      10.0, Body::ColorT{0.0, 0.0, 1.0});
  auto moon = std::make_shared<Body>(
      moon_mass,
      Body::Vector3{1.01 + moon_earth_distance, moon_earth_distance, 0},
      Body::Vector3{0, moon_orbital_speed, 0}, 5.0,
      Body::ColorT{0.9, 0.9, 0.9});

  auto mars = std::make_shared<Body>(earth_mass * 0.6, Body::Vector3{1.5, 0, 0},
                                     Body::Vector3{0, earth_orbital_speed, 0},
                                     10.0, Body::ColorT{1.0, 0.0, 0.0});

  auto jupiter =
      std::make_shared<Body>(317 * earth_mass, Body::Vector3{5.2, 0, 0},
                             Body::Vector3{0, jupiter_orbital_speed, 0}, 25.0,
                             Body::ColorT({0.89, 0.86, 0.79}));

  system.addBody("sun", sun, true);
  system.addBody("earth", earth);
  // system.addBody("moon", moon);
  system.addBody("mars", mars);
  system.addBody("jupiter", jupiter);

  constexpr int iterations = 1000000;

  auto console_publisher = factory::create_console_body_system_publisher();
  auto grpc_publisher = factory::create_grpc_publisher();

  auto system_tracer = SystemTracer(99);

  for (unsigned int it = 0; it < iterations; ++it) {
    system.step(50);
    console_publisher->publish(system);
    grpc_publisher->publish(system);

    system_tracer.capture(system);
    grpc_publisher->publish(system_tracer);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}