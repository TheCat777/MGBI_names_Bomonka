//
// Created by SvCat on 14.03.2024.
//

#ifndef PROJECT_NAME_GAME_H
#define PROJECT_NAME_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <filesystem>


class Base_Scene{
public:
    std::vector<sf::Sprite> Sprites;
    std::vector<sf::Texture> Textures;
    std::vector<sf::Text> Texts;

    void draw_all(sf::RenderWindow & window){
        window.clear();
        for (const auto& sprite : Sprites)
            window.draw(sprite);

        window.display();
    }
    void events(sf::RenderWindow & window){
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
protected:
    void add_sprite(const sf::Sprite& new_sprite){
        Sprites.push_back(new_sprite);
    }
    void add_text(const sf::Text& new_text){
        Texts.push_back(new_text);
    }
    void add_texture(const sf::Texture& new_texture){
        Textures.push_back(new_texture);
    }
public:
    void load(){};
    Base_Scene(){
        load();
    }
    void start(sf::RenderWindow & window){
        while (window.isOpen()){
            events(window);
            draw_all(window);
        }
    }
};


#endif //PROJECT_NAME_GAME_H
