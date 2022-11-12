#pragma once

#include <array>
#include <cstdint>
#include <include_all.hpp>

constexpr int grid_size = 9;
constexpr int box_size = 3;
static_assert(box_size * box_size == grid_size);
using row_type = std::array<std::uint8_t, grid_size>;
using board_type = std::array<row_type, grid_size>;