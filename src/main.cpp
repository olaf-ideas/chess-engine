#include <iostream>

#include "types.hpp"
#include "board.hpp"

int main() {
    Board board("r1bqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");
    std::cerr << board.get_fen() << '\n';
}