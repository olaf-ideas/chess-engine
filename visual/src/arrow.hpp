#ifndef ARROW_HPP
#define ARROW_HPP

#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>

#include "config.hpp"

class Arrow : public sf::Drawable {
private:
    int start_row, start_col;
    sf::ConvexShape shape;

public:
    Arrow(int row, int col, int end_x, int end_y) : start_row(row), start_col(col) {
        sf::Vector2f o(row * SQUARE_SIZE + SQUARE_SIZE / 2, col * SQUARE_SIZE + SQUARE_SIZE / 2);
        sf::Vector2f p(end_x, end_y);
    
        shape.setPointCount(32);
        shape.setPoint(0, p);
        sf::Vector2f v = p - o;

        // chess strzalka - Autor: Olaf Surgut 2021

        // wez wektor od poczatku do konca, przeskaluj go do dlugosci 25, obroc o 90 stopni w prawo a otrzymamy pierwsza styczna
        // obroc o 90 w lewo aby otrzymac druga
        v /= sqrt(v.x * v.x + v.y * v.y);
        v *= 25.f;

        sf::Vector2f a = sf::Vector2f(-v.y, +v.x) + o;

        shape.setPoint(1, a);

        sf::Vector2f b = sf::Vector2f(+v.y, -v.x) + o;

        shape.setPoint(2, b);

        shape.setFillColor(sf::Color(0, 0, 255, 88));
    
        // aby otrzymac polkolo nalezy wziasc otrzymany wczesnij wektor i obracac go o maly kat 
        static constexpr float pi = acos(-1);
        v = sf::Vector2f(-v.y, +v.x);
        for(int i = 0; i < (int) shape.getPointCount() - 2; i++) {
            float c = cos(pi / 30 * i), s = sin(pi / 30 * i);
            sf::Vector2f d = sf::Vector2f(v.x * c - v.y * s, v.x * s + v.y * c) + o;
            shape.setPoint(2 + i, d);
        }
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(shape, states);
    }

    int get_start_row() const { return start_row; }
    int get_start_col() const { return start_col; }

};

#endif