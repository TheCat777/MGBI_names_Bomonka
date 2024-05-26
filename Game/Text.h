//
// Created by SvCat on 19.03.2024.
//

#ifndef MGBI_BOMONKA_TEXT_H
#define MGBI_BOMONKA_TEXT_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

class Text{
private:
    sf::Text text;
    sf::Font font;
public:
    Text()= default;
    explicit Text(const std::wstring& words, const unsigned int size, const sf::Color color, sf::Vector2u pos, const unsigned int style){
        create(words, size, color, pos, style);
    }
    void create(const std::wstring& words, const unsigned int size, const sf::Color color, sf::Vector2u pos, const unsigned int style){
        if (!font.loadFromFile(path_to_game + "\\resources\\Fonts\\wgs.ttf"))
        {
            std::cerr << "Fail to load font" << std::endl;
        }
        //_________________СОЗДАЮ ТЕКСТ_____________
        text.setFont(font); // выбираем шрифт // font это sf::Font
        text.setString(words); // выбираем отображаемую строку
        text.setCharacterSize(size); // в пикселях, а не точках! // выбираем размер символов
        text.setFillColor(color); // выбираем цвет
        text.setStyle(style); // выбираем стиль текста
        text.setPosition(sf::Vector2f(pos));
        setVisibility(255);
    }
    void set_text(const std::wstring& words){
        text.setString(words);
    }
    void setVisibility(unsigned int visibility){
        auto temp = text.getFillColor();
        temp.a = visibility;
        text.setFillColor(temp);
    }
    void draw(sf::RenderWindow & window){
        text.setFont(font);
        window.draw(text);
    }
    void setPosition(const sf::Vector2f coords) {
        text.setPosition(coords);
    }
    sf::Vector2f getSize() {
        return {text.getGlobalBounds().width, text.getGlobalBounds().height};
    }
    void move(float x, float y) {
        text.move(x, y);
    }
    void rotate (float rotationSpeed) {
        text.rotate(rotationSpeed);
    }
    void setOrigin(float x, float y) {
        text.setOrigin(x, y);
    }
};

#endif //MGBI_BOMONKA_TEXT_H
