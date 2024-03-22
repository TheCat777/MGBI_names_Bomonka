//
// Created by SvCat on 21.03.2024.
//

#ifndef MGBI_BOMONKA_BUTTON_H
#define MGBI_BOMONKA_BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "Texture.h"
#include "Text.h"

class Button{
private:
    sf::Vector2u coords = {0, 0};
    sf::Vector2u size = {10000, 10000};
    Texture active;
    Texture disactive;
    Text text;
    bool is_active = false;
    bool visible = false;
public:
    void create(const std::wstring& _text, sf::Vector2u _coords){
        visible = true;
        coords = _coords;
        active.create("\\resources\\active.png", coords);
        disactive.create("\\resources\\no_active.png", coords);
        size = active.get_size();
        text.create(_text, 22, sf::Color::Black, {coords.x + 30, coords.y + 20}, sf::Text::Style::Bold);
    }
    Button(const std::wstring& _text, sf::Vector2u _coords){
        visible = true;
        create(_text, _coords);
    }
    Button()= default;
    bool is_clicked() const{
        if (is_pointed() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return true;
        return false;
    }
    bool is_pointed() const{
        sf::Vector2i position = sf::Mouse::getPosition();
        if (coords.x + 7 < position.x && position.x < coords.x + 7 + size.x && coords.y + 31 < position.y && position.y < coords.y + 31 + size.y){
            return true;
        }
        return false;
    }
    void draw(sf::RenderWindow & window){
        is_active = is_pointed();
        if (visible) {
            if (is_active)
                active.draw(window);
            else
                disactive.draw(window);
            text.draw(window);
        }
    }
};

#endif //MGBI_BOMONKA_BUTTON_H
