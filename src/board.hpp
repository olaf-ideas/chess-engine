#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "types.hpp"

class Board {
private:
    Piece board[SQUARE_NB];
    Bitboard type_board[PIECE_NB];
    Bitboard color_board[COLOR_NB];
    Bitboard occupied;
    Color turn;

public:

    Board();
    Board(const std::string &);

    void make_move(Move);

    std::string get_fen() const;

    void set(Square, Piece);
    void unset(Square);
};

#endif