#pragma once

#include "defines.hpp"

struct compressed_row {
    uint32_t data;

    constexpr compressed_row() = default;

    constexpr compressed_row(uint32_t data) : data{data} {}

    constexpr compressed_row(row_type row) : data{} {
        int32_t mul = 1e8;
        for (auto i: row) {
            data += i * mul;
            mul /= 10;
        }
    }

    constexpr operator row_type() const {
        return {static_cast<std::uint8_t>((data / 100000000) % 10),
                static_cast<std::uint8_t>((data / 10000000) % 10),
                static_cast<std::uint8_t>((data / 1000000) % 10),
                static_cast<std::uint8_t>((data / 100000) % 10),
                static_cast<std::uint8_t>((data / 10000) % 10),
                static_cast<std::uint8_t>((data / 1000) % 10),
                static_cast<std::uint8_t>((data / 100) % 10),
                static_cast<std::uint8_t>((data / 10) % 10),
                static_cast<std::uint8_t>((data / 1) % 10)};
    }


    constexpr bool operator==(compressed_row other) const {
        return data == other.data;
    }

    constexpr bool operator!=(compressed_row other) const {
        return data != other.data;
    }
};

struct compressed_board {
    std::array<uint32_t, grid_size> data;

    constexpr compressed_board() = default;

    constexpr compressed_board(board_type board) : data{} {
        for (int i = 0; i < grid_size; ++i)
            data[i] = static_cast<compressed_row>(board[i]).data;
    }

    constexpr operator board_type() const {
        board_type res;
        for (int i = 0; i < grid_size; ++i)
            res[i] = compressed_row{data[i]};
        return res;
    }

    constexpr bool operator==(compressed_board const &other) const {
        return data == other.data;
    }

    constexpr bool operator!=(compressed_board const &other) const {
        return data != other.data;
    }
};