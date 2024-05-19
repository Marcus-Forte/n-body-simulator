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

  constexpr int iterations = 1000000;

  auto console_publisher = factory::create_console_body_system_publisher();
  auto grpc_publisher = factory::create_grpc_publisher();

  auto system_tracer = SystemTracer(200);

  for (unsigned int it = 0; it < iterations; ++it) {
    system->step(1e-3);
    console_publisher->publish(*system);
    grpc_publisher->publish(*system);

    system_tracer.capture(*system);
    grpc_publisher->publish(system_tracer);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}