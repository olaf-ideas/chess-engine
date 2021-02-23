#include "board.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <cassert>

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
    static sf::Sprite board_pieces[64];

    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            target.draw(m_board_shape[row + col * 8], states);
            
            if(m_board[row + col * 8] & 15) {
                board_pieces[row + col * 8].setTexture(m_pieces_tex);
                board_pieces[row + col * 8].setTextureRect(m_pieces_rec[m_board[row + col * 8]]);
                board_pieces[row + col * 8].setPosition(row * SQUARE_SIZE, col * SQUARE_SIZE);
                board_pieces[row + col * 8].setScale(0.5f, 0.5f);
                target.draw(board_pieces[row + col * 8], states);
            }
        }
    }
}