#include <iostream>
#include <vector> 

#include <SFML/Graphics.hpp>

#include "config.hpp"
#include "board.hpp"
#include "arrow.hpp"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 10;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "", sf::Style::Default, settings);
    window.setFramerateLimit(30u);
    Board board;

    board.m_board[0] = KING | WHITE;
    board.m_board[1] = QUEEN | BLACK;
    board.m_board[8] = PAWN | WHITE;
    board.init_textures();

    Square holding_piece = NONE;
    // int holding_row = 0, holding_col = 0;
    sf::Sprite holding_sprite(board.m_pieces_tex);
    holding_sprite.setScale(0.5f, 0.5f);
    holding_sprite.setOrigin(SQUARE_SIZE, SQUARE_SIZE);

    std::vector<Arrow> arrows;
    bool space_pressed = false;

    Arrow *arrow_now = nullptr;

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

        if(0 <= mouse_pos.x && mouse_pos.x <= SCREEN_WIDTH &&
           0 <= mouse_pos.y && mouse_pos.y <= SCREEN_HEIGHT) {
            Square &piece = board.m_board[mouse_pos.x / SQUARE_SIZE + mouse_pos.y / SQUARE_SIZE * 8];
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if(piece != NONE && holding_piece == NONE) {
                    // holding_row = mouse_pos.x / SQUARE_SIZE;
                    // holding_col = mouse_pos.y / SQUARE_SIZE;
                    holding_piece = piece;
                    piece = 0;
                    holding_sprite.setTextureRect(board.m_pieces_rec[holding_piece]);
                }
            } else if(holding_piece != NONE) {
                piece = holding_piece;
                holding_piece = NONE;
                // holding_row = 0;
                // holding_col = 0;
            }

            if(arrow_now == nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                arrow_now = new Arrow(mouse_pos.x / SQUARE_SIZE, mouse_pos.y / SQUARE_SIZE, 0, 0);
            } else if(arrow_now != nullptr && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                int row = mouse_pos.x / SQUARE_SIZE, col = mouse_pos.y / SQUARE_SIZE;
                if(arrow_now->get_start_row() != row || arrow_now->get_start_col() != col) {
                    arrows.push_back(Arrow(arrow_now->get_start_row(), arrow_now->get_start_col(), 
                                            row * SQUARE_SIZE + SQUARE_SIZE / 2, 
                                            col * SQUARE_SIZE + SQUARE_SIZE / 2));
                }
                delete arrow_now;
                arrow_now = nullptr;
            }
        }

        if(!arrows.empty()) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if(!space_pressed) {
                    arrows.pop_back();
                    space_pressed = true;
                }
            } else {
                space_pressed = false;
            }
        }

        if(arrow_now != nullptr) {
            *arrow_now = Arrow(arrow_now->get_start_row(), arrow_now->get_start_col(), mouse_pos.x, mouse_pos.y);
        }

        if(holding_piece != NONE) {
            holding_sprite.setPosition(mouse_pos.x, mouse_pos.y);
        }

        window.clear();
        window.draw(board);
        if(holding_piece != NONE) {
            window.draw(holding_sprite);
        }
        for(const Arrow &arrow : arrows) {
            window.draw(arrow);
        }
        if(arrow_now != nullptr)    window.draw(*arrow_now);
        window.display();
    }

    return 0;
}
