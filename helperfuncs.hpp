#pragma once

#include "defines.hpp"
#include <iostream>
#include <random>

struct invalid_board_exception : std::exception {
    [[nodiscard]] constexpr const char *what() const noexcept override {
        return "invalid board";
    }
};

constexpr board_type board_from_string(std::string_view str) {
    lmj::static_vector<char, grid_size * grid_size + 1> cleaned_string;
    for (char i: str)
        if (i >= '0' && i <= '9')
            if (cleaned_string.size() <= grid_size * grid_size)
                cleaned_string.push_back(i);
    if (cleaned_string.size() != grid_size * grid_size)
        throw invalid_board_exception{};
    board_type res{};
    for (int i = 0; i < grid_size; ++i)
        for (int j = 0; j < grid_size; ++j)
            res[i][j] = cleaned_string[i * grid_size + j] - '0';
    return res;
}

void print_board_impl(std::ostream &out, board_type const &board) {
    out << "+-------+-------+-------+\n";
    for (int i = 0; i < grid_size; ++i) {
        out << "| ";
        for (int j = 0; j < grid_size; ++j) {
            if (j) {
                if (j % 3)
                    out << ' ';
                else
                    out << " | ";
            }
            if (board[i][j] == 0)
                out << ' ';
            else
                out << static_cast<int>(board[i][j]);
        }
        out << " |\n";
        if (i % 3 == 2)
            out << "+-------+-------+-------+\n";
    }
    out << '\n';
}

void print_board(board_type const &board) {
    std::cout << std::flush;
    print_board_impl(std::cout, board);
}

void print_board_debug(board_type const &board) {
    std::cerr << std::flush;
    print_board_impl(std::cerr, board);
}

template<class T, std::size_t sz>
void scramble_vector(lmj::static_vector<T, sz> &v) {
    static lmj::constexpr_rand_generator gen{};
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::swap(v[i], v[lmj::rand() % v.size()]);
    }
}
