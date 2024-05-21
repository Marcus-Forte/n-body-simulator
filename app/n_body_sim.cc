#include <filesystem>
#include <memory>
#include <thread>

#include "BodySystem.hh"
#include "SystemTracer.hh"
#include "factory/BodySystemFactory.hh"
#include "factory/BodySystemPublisherFactory.hh"
#include "grpc/publisher.hh"

int main(int argc, char** argv) {
  std::filesystem::path system_json = "system.json";

  if (argc == 2) {
    system_json = argv[1];
  }

  auto system = factory::create_bodysystem(system_json);

  constexpr unsigned long iterations = 10000000000; // likely eternal

  auto console_publisher = factory::create_console_body_system_publisher();
  auto grpc_publisher = factory::create_grpc_publisher(false);


  auto grpc_puslibher_persistent = factory::create_grpc_publisher(true);
  auto system_tracer = SystemTracer(1);

  for (unsigned long it = 0; it < iterations; ++it) {
    system->step(1e-5); // the smaller the number, the more stable the results.

    // console_publisher->publish(*system);
    grpc_publisher->publish(*system);

    system_tracer.capture(*system);

    if (it % 250 == 0) // Publish paths
      grpc_puslibher_persistent->publish(system_tracer);
  }
}