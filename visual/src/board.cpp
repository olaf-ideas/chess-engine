#include "board.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <cassert>
#include <string.h>

Board::Board() { memset(m_board, 0, sizeof(m_board)); }

Board::Board(const std::string &fen) {
    int pos = 0;
    for(int i = 0; i < (int) fen.size(); i++) {
        if(fen[i] == ' ')   break;
        switch(fen[i]) {
            case 'P': m_board[pos++] = PAWN   | WHITE; break;
            case 'N': m_board[pos++] = KNIGHT | WHITE; break;
            case 'B': m_board[pos++] = BISHOP | WHITE; break;
            case 'R': m_board[pos++] = ROOK   | WHITE; break;
            case 'Q': m_board[pos++] = QUEEN  | WHITE; break;
            case 'K': m_board[pos++] = KING   | WHITE; break;

            case 'p': m_board[pos++] = PAWN   | BLACK; break;
            case 'n': m_board[pos++] = KNIGHT | BLACK; break;
            case 'b': m_board[pos++] = BISHOP | BLACK; break;
            case 'r': m_board[pos++] = ROOK   | BLACK; break;
            case 'q': m_board[pos++] = QUEEN  | BLACK; break;
            case 'k': m_board[pos++] = KING   | BLACK; break;
            
            case '/': break;
            
            default: pos += int(fen[i] - '0'); break;
        }
    }
}

void Board::init_textures() {
    if(!m_pieces_tex.loadFromFile("img/pieces.png")) {
        printf("cannot load file: ../img/pieces.png\n");
        assert(false);
    }
    printf("file ../img/pieces.png loaded\n");
    m_pieces_tex.setSmooth(true);

    m_pieces_rec[KING   | WHITE] = sf::IntRect(0,    0, 200, 200);
    m_pieces_rec[QUEEN  | WHITE] = sf::IntRect(200,  0, 200, 200);
    m_pieces_rec[BISHOP | WHITE] = sf::IntRect(400,  0, 200, 200);
    m_pieces_rec[KNIGHT | WHITE] = sf::IntRect(600,  0, 200, 200);
    m_pieces_rec[ROOK   | WHITE] = sf::IntRect(800,  0, 200, 200);
    m_pieces_rec[PAWN   | WHITE] = sf::IntRect(1000, 0, 200, 200);

    m_pieces_rec[KING   | BLACK] = sf::IntRect(0,    200, 200, 200);
    m_pieces_rec[QUEEN  | BLACK] = sf::IntRect(200,  200, 200, 200);
    m_pieces_rec[BISHOP | BLACK] = sf::IntRect(400,  200, 200, 200);
    m_pieces_rec[KNIGHT | BLACK] = sf::IntRect(600,  200, 200, 200);
    m_pieces_rec[ROOK   | BLACK] = sf::IntRect(800,  200, 200, 200);
    m_pieces_rec[PAWN   | BLACK] = sf::IntRect(1000, 200, 200, 200);

    for(uint8_t row = 0; row < 8; row++) {
        for(uint8_t col = 0; col < 8; col++) {
            m_board_shape[row + col * 8].setPosition(sf::Vector2f(row * SQUARE_SIZE, col * SQUARE_SIZE));
            m_board_shape[row + col * 8].setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));

            if((row + col) & 1) {
                m_board_shape[row + col * 8].setFillColor(sf::Color(232, 235, 239));
            } else {
                m_board_shape[row + col * 8].setFillColor(sf::Color(125, 145, 150));
            }
        }
    }
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    static sf::Sprite m_board_pieces[64];

    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            target.draw(m_board_shape[row + col * 8], states);
            
            if(m_board[row + col * 8] & 15) {
                m_board_pieces[row + col * 8].setTexture(m_pieces_tex);
                m_board_pieces[row + col * 8].setTextureRect(m_pieces_rec[m_board[row + col * 8]]);
                m_board_pieces[row + col * 8].setPosition(row * SQUARE_SIZE, col * SQUARE_SIZE);
                m_board_pieces[row + col * 8].setScale(0.5f, 0.5f);
                target.draw(m_board_pieces[row + col * 8], states);
            }
        }
    }
}