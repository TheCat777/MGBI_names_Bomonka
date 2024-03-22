//
// Created by Андрей on 22.03.2024.
//

#ifndef MGBI_BOMONKA_MINIGAME_H
#define MGBI_BOMONKA_MINIGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>


class MiniGame : public Base_Scene{
private:
    double SPEED = 1;
public:
    MiniGame(sf::RenderWindow & window) {
        Load();
        while (window.isOpen()) {
            EventsMiniGame(window);
            DrawMiniGame(window);
        }
    }

    void DrawMiniGame(sf::RenderWindow & window){
        window.clear();
        for (auto& texture : Textures)
            texture.draw(window);
        window.display();
    }
    void Load() {
        Texture student;
        Texture wall;
        student.create("\\resources\\student.jpg", {100, 500});
        wall.create("\\resources\\wall.png", {0, 0});

        Textures.push_back(student);
        Textures.push_back(wall);
    }
    void EventsMiniGame(sf::RenderWindow & window){
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {Textures[0].move(0, -SPEED); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {Textures[0].move(-SPEED, 0); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {Textures[0].move(0, SPEED); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {Textures[0].move(SPEED, 0); }

        if (Textures[0].GetSprite().getGlobalBounds().intersects(Textures[1].GetSprite().getGlobalBounds())) {

        }

    }
};

#endif //MGBI_BOMONKA_MINIGAME_H
