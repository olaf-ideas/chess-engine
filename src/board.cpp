#include "board.hpp"

#include <string.h> // for memset

#include <iostream>

Board::Board() {
    turn = WHITE;
}

Board::Board(const std::string &fen) {
    memset(board, NO_PIECE, sizeof(board));
    Square sq = A1;
    for(int i = 0; i < (int) fen.size(); i++) {
        if(fen[i] == ' ') {
            if(fen[i + 1] == 'w')   turn = WHITE;
            else                    turn = BLACK;
            break;
        }
        Piece piece = NO_PIECE;
        switch(fen[i]) {
            case 'P': piece = W_PAWN;   break;
            case 'N': piece = W_KNIGHT; break;
            case 'B': piece = W_BISHOP; break;
            case 'R': piece = W_ROOK;   break;
            case 'Q': piece = W_QUEEN;  break;
            case 'K': piece = W_KING;   break;

            case 'p': piece = B_PAWN;   break;
            case 'n': piece = B_KNIGHT; break;
            case 'b': piece = B_BISHOP; break;
            case 'r': piece = B_ROOK;   break;
            case 'q': piece = B_QUEEN;  break;
            case 'k': piece = B_KING;   break;
            
            case '/': break;
            
            default: sq += int(fen[i] - '0'); break;
        }

        if(piece != NO_PIECE) {
            type_board[piece] |= 1ull << sq;
            board[sq] = piece;
            sq += 1;
        }
    }
}

void Board::make_move(Move move) {

}

std::string Board::get_fen() const {
    std::string fen;
    for(Square sq = A1; sq <= H8; sq++) {
        int skip = 0; char c = '@';
        switch(board[sq]) {
            case W_PAWN:   c = 'P'; break;
            case W_KNIGHT: c = 'N'; break;
            case W_BISHOP: c = 'B'; break;
            case W_ROOK:   c = 'R'; break;
            case W_QUEEN:  c = 'Q'; break;
            case W_KING:   c = 'K'; break;

            case B_PAWN:   c = 'p'; break;
            case B_KNIGHT: c = 'n'; break;
            case B_BISHOP: c = 'b'; break;
            case B_ROOK:   c = 'r'; break;
            case B_QUEEN:  c = 'q'; break;
            case B_KING:   c = 'k'; break;

            case NO_PIECE: skip++; break;
        }
        std::cerr << int(sq) << ' ' << skip << ' ' << c << '\n';
        if(c != '@') {
            if(skip > 0)    fen += std::to_string(skip), skip = 0;
            fen += c;
        }
        if(sq % 8 == 7) {
            if(skip > 0)    fen += std::to_string(skip), skip = 0;
            fen +=  '/'; 
        }
    }
    fen +=  ' ';
    if(turn == WHITE)   fen += 'w';
    else                fen += 'b';

    return fen;
}

void Board::set(Square sq, Piece piece) {
    
}

void Board::unset(Square sq) {
    
}