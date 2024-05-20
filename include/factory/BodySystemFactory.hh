#pragma once

#include <filesystem>

#include "interfaces/IBodySystem.hh"

namespace factory {
std::unique_ptr<IBodySystem> create_bodysystem(
    const std::filesystem::path& file);
}