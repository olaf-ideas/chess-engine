#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>

typedef uint32_t Square;

enum Piece {
    BLACK  = 0b10000,
    WHITE  = 0b01000,

    NONE   = 0b00000,
    PAWN   = 0b00001,
    KNIGHT = 0b00010,
    BISHOP = 0b00011,
    ROOK   = 0b00100,
    QUEEN  = 0b00101,
    KING   = 0b00110,
};

#endif