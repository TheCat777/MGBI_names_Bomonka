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
#include <thread>
#include <mutex>

#include "Button.h"
#include "Text.h"
#include "Texture.h"


class Base_Scene{
public:

    std::vector<Texture> Textures;
    std::vector<Text> Texts;
    std::vector<Button> Buttons;

    int draw_all(sf::RenderWindow & window){
        window.clear();
        for (auto& texture : Textures)
            texture.draw(window);
        for (auto& text : Texts) {
            text.draw(window);
        }
        for (auto& button : Buttons) {
            button.draw(window);
            if (button.is_clicked(window))
                return button.get_id();
        }
        window.display();
        return INT32_MIN;
    }
    static void events(sf::RenderWindow & window){
        for (auto event = sf::Event{}; window.pollEvent(event);){
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
            }
            if (event.type == sf::Event::Closed){
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
    virtual void load(){};
    int start(sf::RenderWindow & window){
        while (window.isOpen()){
            events(window);
            int temp = draw_all(window);
            if (temp != INT32_MIN){
                return temp;
            }
        }
    }
    void setVisibility(unsigned int visibility){
        for (auto & i : Texts){
            i.setVisibility(visibility);
        }
        for (auto & i : Textures){
            i.setVisibility(visibility);
        }
        for (auto & i : Buttons){
            i.setVisibility(visibility);
        }
    }
};


class Loading_Scene : public Base_Scene{
public:
    void load() override{
        Texture t("logo.png", {0, 0});
        add_texture(t);

        Text text1(L"Аладин", 42, sf::Color(0, 0, 0, 0), {200, 130}, sf::Text::Bold);
        add_text(text1);

        Button but1;
        but1.create(L"Aboba", {200, 200}, 0);
        add_button(but1);
    }
};

class Bad_end_scene : public Base_Scene{
public:
    void load() override{
        Texture t("bad_ending.jpg", {0, 0});
        add_texture(t);
    }
};

void show_scene(Base_Scene & scene){
    for (unsigned int visibility = 0; visibility <= 255; ++visibility){
        scene.setVisibility(visibility);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void hide_scene(Base_Scene & scene){
    for (unsigned int visibility = 255; visibility > 0; --visibility){
        scene.setVisibility(visibility);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    scene.setVisibility(0);
}


#endif //MGBI_BOMONKA_SCENE_H
