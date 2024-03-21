//
// Created by SvCat on 19.03.2024.
//

#ifndef MGBI_BOMONKA_SCENE_H
#define MGBI_BOMONKA_SCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "Button.h"
#include "Text.h"
#include "Texture.h"


class Base_Scene{
public:

    std::vector<Texture> Textures;
    std::vector<Text> Texts;
    std::vector<Button> Buttons;

    void draw_all(sf::RenderWindow & window){
        window.clear();
        for (auto& texture : Textures)
            texture.draw(window);
        for (auto& text : Texts) {
            text.draw(window);
        }
        for (auto& button : Buttons) {
            button.draw(window);
        }
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
    void add_text(const Text& new_text){
        Texts.push_back(new_text);
    }
    void add_texture(const Texture& texture){
        Textures.push_back(texture);
    }
    void add_button(const Button& but){
        Buttons.push_back(but);
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

class Loading_Scene : public Base_Scene{
private:
    std::string path_to_game = std::filesystem::current_path().parent_path().parent_path().string();
public:
    void load(){
        Texture t("\\resources\\logo.png", {0, 0});
        add_texture(t);

        Text text1(L"Аладин", 42, sf::Color::Black, {200, 130}, sf::Text::Bold);
        add_text(text1);

        Button but1;
        but1.create(L"1. Жить или не жить", {400, 300});
        add_button(but1);
    }
};

#endif //MGBI_BOMONKA_SCENE_H
