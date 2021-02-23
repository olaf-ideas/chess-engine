#ifndef BOARD_HPP
#define BOARD_HPP

#include "types.hpp"

#include <SFML/Graphics.hpp>

class Board : public sf::Drawable {
public:
    Square m_board[64] = {};

    void init_textures();

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    sf::Texture m_pieces_tex;
    sf::IntRect m_pieces_rec[64];
    sf::RectangleShape m_board_shape[64];
};

#endif