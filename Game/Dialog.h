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

#include <string>
#include <vector>

#include "Parser.h"
#include "Scene.h"
#include "Constants.h"


class Dialog : public Base_Scene{
    private:
        loader line;
        Sound music;

        bool stop = false;
    public:
        Dialog() {}
        int start(sf::RenderWindow & window){
            line.id = 0;
            line.text = L"Так! Уважаемые студенты!";
            line.prepod = "Корзинов";
            line.fon = "Ауд224";
            line.music = "Zagadka.mp3";
            line.button_count = 4;
            line.buttons.push_back(std::make_pair(L"Тише себя вести", 1));
            line.buttons.push_back(std::make_pair(L"Продолжить болтать", 2));
            line.buttons.push_back(std::make_pair(L"Поспать", 3));
            line.buttons.push_back(std::make_pair(L"Открыть тетрадь", 4));
            //line.sys;

            Load();
            while (window.isOpen()) {
                EventsDialog(window);
                auto t = draw_all(window);
                if (t != INT32_MIN)
                    return t;
                if (stop)
                    return INT32_MIN;
            }
        }

        void Load() {
            Texture fon;
            Texture prepod;
            Texture panel;
            fon.create("fon-1.png", {0, 0});
            prepod.create("prep-1.png", {0, 0});
            panel.create("dialog_panel.png", {WIDTH/2-480, HEIGHT/1.5f});
            add_texture(fon);
            add_texture(prepod);
            add_texture(panel);

            music.create(line.music, 50.0f, true);
            music.play();

            Text beseda(line.text, 36, sf::Color::Black, {WIDTH/2-480+40, HEIGHT/1.5f+30}, 0);
            add_text(beseda);

            for(int i = 0; i < line.button_count; i++){
                Button var(line.buttons[i].first, {WIDTH/2-250, HEIGHT/1.8+i*80}, 0);
                add_button(var);
            }
            /*Button var1(line.buttons[0].first, {WIDTH/2-500-20, HEIGHT/1.5f});
            Button var2(line.buttons[1].first, {WIDTH/2+20, HEIGHT/1.5f});
            Button var3(L"wewfwf", {WIDTH/2-500-20, HEIGHT/1.2f});
            Button var4(L"wewfwf", {WIDTH/2+20, HEIGHT/1.2f});
            add_button(var1);
            add_button(var2);
            add_button(var3);
            add_button(var4);*/
        }
        void EventsDialog(sf::RenderWindow & window){
            for (auto event = sf::Event{}; window.pollEvent(event);) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        stop = true;
                        return;
                    }
                }
                if (event.type == sf::Event::Closed) {
                    stop = true;
                    return;
                }
            }
            /*
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {Textures[0].move(SPEED, 0); }
            */

        }
};

#endif //MGBI_BOMONKA_DIALOG_H
