#pragma once

#include <filesystem>

#include "interfaces/IBodySystem.hh"

namespace factory {
std::unique_ptr<IBodySystem> create_bodysystem(std::filesystem::path file);
}