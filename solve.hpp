#pragma once

#include "defines.hpp"
#include "compressed_board.hpp"

constexpr auto valid_nums(board_type const &board, int row, int col) {
    lmj::static_vector<int, grid_size> result;
    if (board[row][col]) {
        result.push_back(-1);
        return result;
    }

    bool possible[grid_size + 1]{};
    std::fill(std::begin(possible), std::end(possible), true);
    for (int i = 0; i < grid_size; ++i)
        possible[board[row][i]] = false;

    for (int i = 0; i < grid_size; ++i)
        possible[board[i][col]] = false;

    const int top_left_row = row - row % box_size, top_left_col = col - col % box_size;
    for (int i = 0; i < box_size; ++i) {
        for (int j = 0; j < box_size; ++j) {
            possible[board[i + top_left_row][j + top_left_col]] = false;
        }
    }

    for (int i = 1; i <= grid_size; ++i) {
        if (possible[i]) {
            result.push_back(i);
        }
    }
    return result;
}

constexpr bool is_valid(board_type const &board) {
    // check rows
    for (int i = 0; i < grid_size; ++i) {
        bool row[grid_size + 1]{};
        for (int j = 0; j < grid_size; ++j) {
            int curr = board[i][j];
            if (!curr)
                continue;
            if (!(curr >= 1 && curr <= grid_size))
                return false;
            if (row[curr])
                return false;
            else
                row[curr] = true;
        }
    }

    // check columns
    for (int i = 0; i < grid_size; ++i) {
        bool col[grid_size + 1]{};
        for (int j = 0; j < grid_size; ++j) {
            int curr = board[j][i];
            if (!curr)
                continue;
            if (col[curr])
                return false;
            else
                col[curr] = true;
        }
    }

    // check boxes
    for (int box_i = 0; box_i < box_size; ++box_i) {
        for (int box_j = 0; box_j < box_size; ++box_j) {
            bool box[grid_size + 1]{};
            for (int i = 0; i < box_size; ++i) {
                for (int j = 0; j < box_size; ++j) {
                    int curr = board[box_i * box_size + i][box_j * box_size + j];
                    if (!curr)
                        continue;
                    if (box[curr])
                        return false;
                    else
                        box[curr] = true;
                }
            }
        }
    }
    return true;
}

constexpr bool is_solved(board_type const &board) {
    int sum = 0;
    for (int i = 0; i < grid_size; ++i)
        for (int j = 0; j < grid_size; ++j)
            sum += board[i][j];
    constexpr auto row_sum = (grid_size * (grid_size + 1)) / 2;
    return sum == grid_size * row_sum && is_valid(board);
}

template<typename T>
constexpr auto solve_impl(T &solutions, board_type &board, int max_solutions,
                          std::pair<uint8_t, uint8_t> end_point = {-1, -1}) {
    if ((int) solutions.size() == max_solutions)
        return;
    if (end_point == std::pair<uint8_t, uint8_t>{-1, -1}) {
        bool found = false;
        for (int i = 9; i-- > 0 && !found;) {
            for (int j = 9; j-- > 0 && !found;) {
                if (!board[i][j]) {
                    end_point = {i, j};
                    found = true;
                }
            }
        }
        if (!found)
            return;
    }

    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            if (!board[i][j]) {
                auto nums = valid_nums(board, i, j);
                if (!nums.empty()) {
                    if (!std::is_constant_evaluated())
                        scramble_vector(nums);
                    for (auto num: nums) {
                        board[i][j] = num;
                        if ((i == end_point.first) && (j == end_point.second)) {
                            solutions[board] = true;
                        }
                        solve_impl(solutions, board, max_solutions, end_point);
                    }
                    board[i][j] = 0;
                }
                return;
            }
        }
    }
}

struct board_hasher {
    constexpr std::size_t operator()(compressed_board const &b) const {
        std::size_t hash = 0;
        for (auto &i: b.data) {
            hash ^= (i << 5) ^ (i >> 4);
        }
        return hash;
    }

    constexpr std::size_t operator()(board_type const &b) const {
        std::size_t hash = 0;
        for (auto &i: b) {
            std::size_t temp = 0;
            for (auto &j: i)
                temp = (temp << 4) | j;
            hash ^= (temp << 5) ^ (temp >> (8 * sizeof(std::size_t) - 5));
        }
        return hash;
    }
};

auto n_solutions(board_type board, int n) {
    lmj::hash_table<compressed_board, bool, board_hasher> solutions;
    solve_impl(solutions, board, n);
    std::vector<board_type> ans;
    ans.reserve(solutions.size());
    for (auto &[solution, solved]: solutions)
        ans.push_back(solution);
    return ans;
}

// doesn't actually find ALL solutions, only up to 1000
constexpr auto all_solutions(board_type board) {
    lmj::static_hash_table<compressed_board, bool, 2048, board_hasher> solutions;
    solve_impl(solutions, board, 1000);
    lmj::static_vector<compressed_board, 1000> ans;
    for (auto &&[solution, solved]: solutions)
        ans.push_back(solution);
    return ans;
}

constexpr board_type solve(board_type board) {
    lmj::static_hash_table<compressed_board, bool, 1, board_hasher> solutions;
    solve_impl(solutions, board, 1);
    if (!solutions.size())
        return {};
    else
        return solutions.begin()->first;
}
