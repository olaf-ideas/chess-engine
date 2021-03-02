#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>

// move number meaning:
// 0  -  5: destination square (0 - 63)
// 6  - 11: origin square (0 - 63)
// 12 - 13: promotion piece type - 2 (KNIGHT - 2 to QUEEN - 2) / castling type 1 - left, 2 - right
// 14 - 15: 0 - normal move, 1 - promotion, 2 - en passant, 3 - castling

enum Move : uint16_t {
    MOVE_NONE,
    MOVE_NULL = 65
};

enum MoveType {
    NORMAL,
    PROMOTION  = 1 << 14,
    EN_PASSANT = 2 << 14,
    CASTLING   = 3 << 14
};

enum Color {
    WHITE, BLACK, COLOR_NB = 2
};

enum PieceType {
    NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
    ALL_PIECES    = 0,
    PIECE_TYPE_NB = 8
};

enum Piece {
    NO_PIECE,
    W_PAWN = PAWN,     W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = PAWN + 8, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    PIECE_NB = 16
};

enum Castle {
    NO_CASTLE,
    CASTLE_LEFT  = 1 << 12,
    CASTLE_RIGHT = 2 << 12,
    ANY_CASTLE   = 3 << 12,
};

enum Square : int {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,

    SQUARE_ZERO = 0,
    SQUARE_NB   = 64,
};

inline Square& operator+= (Square &sq, int i) { sq = Square(sq + i); return sq; }
inline Square& operator++ (Square &sq, int) { sq = Square(sq + 1); return sq; }

enum Direction : int {
    NORTH  = +8,
    EAST   = +1,
    SOUTH  = -8,
    WEST   = -1,

    NORTH_EAST = NORTH + EAST,
    SOUTH_EAST = SOUTH + EAST,
    SOUTH_WEST = SOUTH + WEST,
    NORTH_WEST = NORTH + WEST
};

inline Move make_move(const Square &from, const Square &to) {
    return Move(NORMAL | to | (from << 6));
}

inline Move make_promotion(const Square &pos, const PieceType &type) {
    return Move(PROMOTION | pos | (type - 2) << 12);
}

inline Move make_en_passant(const Square &from, const Square &to) {
    return Move(EN_PASSANT | to | (from << 6));
}

inline Move make_castle(const Square &from, const Square &to, const Castle &dir) {
    return Move(CASTLING | to | (from << 6) | dir);
}

inline Square get_to(const Move &move) {
    return Square(move & 63);
}

inline Square get_from(const Move &move) {
    return Square((move >> 6) & 63);
}

inline MoveType get_move_type(const Move &move) {
    return MoveType((move & (3 << 14)) >> 14);
}

inline PieceType get_piece_type(const Move &move) {
    return PieceType((move >> 12) & 3);
}

typedef uint64_t Bitboard;

#endif