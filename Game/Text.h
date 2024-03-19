//
// Created by SvCat on 19.03.2024.
//

#ifndef MGBI_BOMONKA_TEXT_H
#define MGBI_BOMONKA_TEXT_H

#include <SFML/Graphics.hpp>

class Text{
private:
    std::string path_to_game = std::filesystem::current_path().parent_path().parent_path().string();
    sf::Text text;
    sf::Font font;
public:
    explicit Text(const std::string& words, const unsigned int size, const sf::Color color, sf::Vector2f pos, const unsigned int style){
        if (!font.loadFromFile(path_to_game + "\\resources\\wgs.ttf"))
        {
            std::cerr << "Fail to load font" << std::endl;
        }
        //_________________СОЗДАЮ ТЕКСТ_____________
        text.setFont(font); // выбираем шрифт // font это sf::Font
        text.setString(words); // выбираем отображаемую строку
        text.setCharacterSize(size); // в пикселях, а не точках! // выбираем размер символов
        text.setColor(color); // выбираем цвет
        text.setStyle(style); // выбираем стиль текста
        text.setPosition(sf::Vector2f(pos));
    }
    void draw(sf::RenderWindow & window){
        text.setFont(font);
        window.draw(text);
    }
};

#endif //MGBI_BOMONKA_TEXT_H
