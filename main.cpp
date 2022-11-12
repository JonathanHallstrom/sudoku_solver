#include "defines.hpp"
#include "helperfuncs.hpp"
#include "solve.hpp"
#include <iostream>

int main() {
    constexpr auto board_1 = board_from_string(
            "2 3 0 4 1 5 0 6 8\n"
            "0 8 0 2 3 6 5 1 9\n"
            "1 6 0 9 8 7 2 3 4\n"
            "3 1 7 0 9 4 0 2 5\n"
            "4 5 8 1 2 0 6 9 7\n"
            "9 2 6 0 5 8 3 0 1\n"
            "0 0 0 5 0 0 1 0 2\n"
            "0 0 0 8 4 2 9 0 3\n"
            "5 9 2 3 7 1 4 8 6\n"
    );
    std::cout << "initial board:\n";
    print_board(board_1);
    std::cout << "solution:\n";
    auto sol_1 = solve(board_1);
    print_board(sol_1);

    constexpr auto board_2 = board_from_string(
            "3 0 6 5 0 8 4 0 0\n"
            "5 2 0 0 0 0 0 0 0\n"
            "0 8 7 0 0 0 0 3 1\n"
            "0 0 3 0 1 0 0 8 0\n"
            "9 0 0 8 6 3 0 0 5\n"
            "0 5 0 0 9 0 6 0 0\n"
            "1 3 0 0 0 0 2 5 0\n"
            "0 0 0 0 0 0 0 7 4\n"
            "0 0 5 2 0 6 3 0 0\n"
    );
    std::cout << "initial board:\n";
    print_board(board_2);
    std::cout << "solution:\n";
    auto sol_2 = solve(board_2);
    print_board(sol_2);

    constexpr auto board_3 = board_from_string(
            "0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0\n"
    );
    std::cout << "initial board:\n";
    print_board(board_3);
    std::cout << "solution:\n";
    auto sol_3 = solve(board_3);
    print_board(sol_3);
}
