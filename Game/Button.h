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
        active.create("active.png", coords);
        disactive.create("no_active.png", coords);
        size = active.get_size();
        text.create(_text, 22, sf::Color(0, 0, 0, 0), {coords.x + 30, coords.y + 20}, sf::Text::Style::Bold);
    }
    Button(const std::wstring& _text, sf::Vector2u _coords){
        visible = true;
        create(_text, _coords);
    }
    Button()= default;
    bool is_clicked(sf::RenderWindow & window) const{
        if (is_pointed(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return true;
        return false;
    }
    bool is_pointed(sf::RenderWindow & window) const{
        sf::Vector2i position = sf::Mouse::getPosition() - window.getPosition();
        if (coords.x < position.x && position.x < coords.x + size.x && coords.y< position.y && position.y < coords.y + size.y){
            return true;
        }
        return false;
    }
    void setVisibility(unsigned int visibility){
        text.setVisibility(visibility);
        active.setVisibility(visibility);
        disactive.setVisibility(visibility);
    }
    void draw(sf::RenderWindow & window){
        is_active = is_pointed(window);
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
