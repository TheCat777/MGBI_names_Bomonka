//
// Created by Yaroslav on 22.03.2024.
//

#ifndef MGBI_BOMONKA_DIALOG_H
#define MGBI_BOMONKA_DIALOG_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include "Parser.h"


class Dialog : public Base_Scene{
    private:
        sf::SoundBuffer buffer;
        sf::Sound sound;
    public:
        explicit Dialog(sf::RenderWindow & window) {
            Load();
            while (window.isOpen()) {
                EventsDialog(window);
                DrawDialog(window);
            }
        }

        void DrawDialog(sf::RenderWindow & window){
            window.clear();
            for (auto& texture : Textures)
                texture.draw(window);
            window.display();
        }
        void Load() {
            Texture fon;
            Texture prepod;
            fon.create("\\resources\\fon-1.png", {0, 0});
            prepod.create("\\resources\\prep-1.png", {0, 0});

            Textures.push_back(fon);
            Textures.push_back(prepod);

            
            std::string path_to_game = std::filesystem::current_path().parent_path().parent_path().string();
            if (!buffer.loadFromFile(path_to_game + "\\resources\\gimn.mp3")){
                //Error audio
            }
            
            sound.setBuffer(buffer);
            sound.setVolume(5.f);
            sound.setLoop(true);
            sound.play();
        }
        void EventsDialog(sf::RenderWindow & window){
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
            /*
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {Textures[0].move(0, -SPEED); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {Textures[0].move(-SPEED, 0); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {Textures[0].move(0, SPEED); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {Textures[0].move(SPEED, 0); }
            */

        }
};

#endif //MGBI_BOMONKA_DIALOG_H
