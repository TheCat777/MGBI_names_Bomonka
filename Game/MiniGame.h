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

#include "Constants.h"
#include "Sound.h"


class MiniGame : public Base_Scene{
private:
    float SPEED_W, SPEED_A, SPEED_S, SPEED_D;
    int dw, da, ds, dd;
    Sound music;
public:
    MiniGame(sf::RenderWindow & window) {
        Load();
        music.create("\\resources\\fonk.mp3", 10.0f, true);
        music.play();
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
    void Collision(const Texture& txr) {
        if (Textures[0].GetSprite().getGlobalBounds().intersects(txr.GetSprite().getGlobalBounds())) {
            if (dw) {Textures[0].move(0, SPEED_S); SPEED_W = 0;}
            if (da) {Textures[0].move(SPEED_D, 0); SPEED_A = 0;}
            if (ds) {Textures[0].move(0, -SPEED_W); SPEED_S = 0;}
            if (dd) {Textures[0].move(-SPEED_A, 0); SPEED_D = 0;}
        }
    }
    void Load() {
        Texture student;
        Texture wall;
        Texture wall2;

        student.create("\\resources\\student.jpg", {100, 600});
        wall.create("\\resources\\wall.png", {100, 100});
        wall2.create("\\resources\\wall.png", {400, 800});

        add_texture(student);
        add_texture(wall);
        add_texture(wall2);
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
        
        SPEED_W = 5, SPEED_A = 5, SPEED_S = 5, SPEED_D = 5;
        dw = 0, da = 0, ds = 0, dd = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {Textures[0].move(0, -SPEED_W); dw = 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {Textures[0].move(-SPEED_A, 0); da = 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {Textures[0].move(0, SPEED_S); ds = 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {Textures[0].move(SPEED_D, 0); dd = 1; }

        Collision(Textures[1]);
        Collision(Textures[2]);
    }
};


#endif //MGBI_BOMONKA_MINIGAME_H
