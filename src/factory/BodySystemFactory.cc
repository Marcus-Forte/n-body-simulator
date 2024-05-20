#include "factory/BodySystemFactory.hh"

#include <jsoncpp/json/json.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "BodySystem.hh"

// form a list of names and body properties from json.
using JsonBody = std::pair<std::string, std::shared_ptr<Body>>;
using JsonBodies = std::list<JsonBody>;

const std::set<std::string> g_validFields = {"name",  "pos",    "vel",
                                             "color", "volume", "mass"};

// Specialize for our object.
namespace Json {
template <>
JsonBodies Value::as<JsonBodies>() const {
  JsonBodies bodies;
  const auto& jsonvalue = *this;
  assert(jsonvalue.isArray());
  // validate

  for (const auto item : jsonvalue) {
    for (const auto& field : g_validFields) {
      if (!item.isMember(field)) {
        throw std::runtime_error(std::format("Member not found: {}", field));
      }
    }

    auto name = item["name"].asString();
    auto mass = item["mass"].asDouble();
    auto volume = item["volume"].asDouble();
    auto pos = Eigen::Vector3d(item["pos"]["x"].asDouble(),
                               item["pos"]["y"].asDouble(),
                               item["pos"]["z"].asDouble());
    auto vel = Eigen::Vector3d(item["vel"]["x"].asDouble(),
                               item["vel"]["y"].asDouble(),
                               item["vel"]["z"].asDouble());

    std::array<double, 3> color = {item["color"]["r"].asDouble(),
                                   item["color"]["g"].asDouble(),
                                   item["color"]["b"].asDouble()};
    bodies.emplace_back(std::move(name),
                        std::make_shared<Body>(mass, pos, vel, volume, color));
  }

  return bodies;
}

}  // namespace Json

namespace factory {

std::unique_ptr<IBodySystem> create_bodysystem(
    const std::filesystem::path& file) {
  if (!std::filesystem::is_regular_file(file))
    throw std::runtime_error("could not open file: " + file.string());

  std::ifstream ifs(file);
  Json::Value system_json;
  ifs >> system_json;

  if (!system_json.isMember("gravity_constant"))
    throw std::runtime_error("could not find 'gravity_constant' field");

  if (!system_json.isMember("bodies"))
    throw std::runtime_error("could not find 'bodies' field");

  auto gravity = system_json["gravity_constant"].asDouble();
  auto bodies_json = system_json["bodies"].as<JsonBodies>();

  auto system = std::make_unique<BodySystem>(gravity);

  for (const auto& body : bodies_json) {
    system->addBody(body.first, body.second);
  }

  return system;
}
}  // namespace factory