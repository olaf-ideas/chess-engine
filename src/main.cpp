#include <iostream>

#include "types.hpp"

int main() {
    Move myMove = make_move(A1, A2);
    std::cerr << myMove << '\n';
    std::cerr << NO_PIECE_TYPE << '\n';
    std::cerr << PAWN << '\n';
    std::cerr << KNIGHT << '\n';
}