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


const int HEIGHT_MAP = 60;
const int WIDTH_MAP = 65;
sf::String Map[HEIGHT_MAP] = {
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0                     0                                        0",
        "0                     0                                        0",
        "0                     0                                        0",
        "0                     0                                        0",
        "0                     0                                        0",
        "0       0000000                                                0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0     00000000000000000000                                     0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                                                              0",
        "0                       00000000000000000                      0",
        "0                       01111111111111110                      0",
        "0                       01111111111111110                      0",
        "0                       01111111111111110                      0",
        "0                       01111111111111110                      0",
        "0   00000000000000000000011111111111111100000000000000000000   0",
        "0   01111111111111111111111111111111111111111111111111111110   0",
        "0   01111111111111111111111111111111111111111111111111111110   0",
        "0   01111111111111111111111111111111111111111111111111111110   0",
        "0   01111111111111111111111111111111111111111111111111111110   0",
        "0   01111111111111111111111111111111111111111111111111111110   0",
        "0   01111111111111111111111111111111111111111111111111111110   0",
        "0   01111111111111111111111111111111111111111111111111111110   0",
        "0   01111111111111111111111111111111111111111111111111111110   0",
        "0000011111111111111111111111111111111111111111111111111111100000"
};

class MiniGame : public Base_Scene{
private:
    sf::View camera;
    sf::Clock clock;
    float time;
    double SPEED_W, SPEED_A, SPEED_S, SPEED_D;
    int dw, da, ds, dd;
public:
    sf::View getViewCoords(float x, float y) {
        float tempX = x; float tempY = y;
        if (x <= 480) tempX = 480;
        if (y <= 270) tempY = 270;
        if (y >= 2730) tempY = 2730;
        if (x >= 2730) tempX = 2720;
        camera.setCenter(tempX, tempY);
        return camera;
    }
    MiniGame() {}
    void start(sf::RenderWindow & window){
        Load(window);
        Sound music("stress.mp3", 10.f, true);
        music.play();
        while (window.isOpen()) {
            TimeCounter();
            //std::cout << Textures[0].GetSprite().getPosition().x << " " << Textures[0].GetSprite().getPosition().y << std::endl;
            EventsMiniGame(window);
            WASD(window);
            DrawMiniGame(window);
        }
    }
    void Load(sf::RenderWindow & window) {
        Texture block;
        Texture floor;
        Texture student;
        student.create("student.jpg", {100, 100});
        block.create("block.jpg", {0, 0});
        floor.create("floor2.png", {0, 0});
        add_texture(student);
        add_texture(block);
        add_texture(floor);

        camera.setSize(960, 540);
        camera.setCenter(student.GetSprite().getPosition());

    }
    void TimeCounter() {
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/3200;
    }
    void DrawMiniGame(sf::RenderWindow & window){
        window.clear();
        for (int i = 0; i < HEIGHT_MAP; i++) {
            for (int j = 0; j < WIDTH_MAP; j++) {
                if (Map[i][j] == '0' && (camera.getCenter().x-530 < j*50) && (j*50 < camera.getCenter().x+530) && (camera.getCenter().y-330 < i*50) && (i*50 < camera.getCenter().y+330)) {
                    Textures[1].SetPosition({j * 50, i * 50});
                    Textures[1].draw(window);
                    CreateCollision(Textures[1]);
                }
                if (Map[i][j] == ' ' && (camera.getCenter().x-530 < j*50) && (j*50 < camera.getCenter().x+530) && (camera.getCenter().y-330 < i*50) && (i*50 < camera.getCenter().y+330)) {
                    Textures[2].SetPosition({j * 50, i * 50});
                    Textures[2].draw(window);
                }
            }
        }
        window.setView(camera);
        Textures[0].draw(window);
        window.display();
    }
    void WASD(sf::RenderWindow & window) {
        SPEED_W = 1, SPEED_A = 1, SPEED_S = 1, SPEED_D = 1;
        dw = 0, da = 0, ds = 0, dd = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {Textures[0].move(0, -SPEED_W*time); dw = 1;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {Textures[0].move(-SPEED_A*time, 0); da = 1;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {Textures[0].move(0, SPEED_S*time); ds = 1;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {Textures[0].move(SPEED_D*time, 0); dd = 1;}
        getViewCoords(Textures[0].GetSprite().getPosition().x, Textures[0].GetSprite().getPosition().y);

    }
    void CreateCollision(Texture txr) {
        if (Textures[0].GetSprite().getGlobalBounds().intersects(txr.GetSprite().getGlobalBounds())) {
            if (dw) {SPEED_W = 0; Textures[0].move(0, SPEED_S*time);}
            if (da) {SPEED_A = 0; Textures[0].move(SPEED_D*time, 0);}
            if (ds) {SPEED_S = 0; Textures[0].move(0, -SPEED_W*time);}
            if (dd) {SPEED_D = 0; Textures[0].move(-SPEED_A*time, 0);}
            getViewCoords(Textures[0].GetSprite().getPosition().x, Textures[0].GetSprite().getPosition().y);
        }
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

    }
};

#endif //MGBI_BOMONKA_MINIGAME_H
