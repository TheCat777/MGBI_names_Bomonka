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
        parser parser;
        nowScene line;
        int numScene;

        bool lock_next = true;
        Sound music;

        bool stop = false;

        std::vector<std::string> listFons = {"224l.png", "fon-1.png", "black.png"};
    public:
        Dialog() {}
        int start(sf::RenderWindow & window, int id=0){
            parser.load();
            numScene = id;
            
            /*line.id = 0;
            line.text = L"Так! Уважаемые студенты!";
            line.prepod = "Корзинов";
            line.fon = "Ауд224";
            line.music = "Zagadka.mp3";
            line.button_count = 4;
            line.buttons.push_back(std::make_pair(L"Тише себя вести", 1));
            line.buttons.push_back(std::make_pair(L"Продолжить болтать", 2));
            line.buttons.push_back(std::make_pair(L"Поспать", 3));
            line.buttons.push_back(std::make_pair(L"Открыть тетрадь", 4));*/
            //line.sys;

            //music.create(line.music, 30.0f, true);
            //music.play();

            load(numScene);
            while (window.isOpen()) {
                EventsDialog(window);
                auto t = draw_all(window);
                if (t != INT32_MIN)
                    return t;
                if (stop)
                    return INT32_MIN;
            }
            return 0;
        }

        void load(int id = 0) {
            line = parser.get(id);
            lock_next = true;

            Texture fon;
            fon.create(listFons[line.fon], {0, 0});
            add_texture(fon);
            
            if(line.prepod != 0){
                Texture prepod;
                prepod.create("prep-1.png", {0, 0});
                add_texture(prepod);
            }

            if(line.button_count == 0){
                Texture panel;
                panel.create("dialog_panel.png", {WIDTH/2-480, int(HEIGHT/1.5f)});
                add_texture(panel);
                Text nameprep(line.name, 28, sf::Color{0x4A66C1FF}, {WIDTH/6-10, HEIGHT/1.5f+6}, 0);
                add_text(nameprep);

                for(int i = 1; i <= line.text.length()/50; i++){
                    if(line.text.rfind(L" ", i*50) != std::wstring::npos){
                        line.text.replace(line.text.rfind(L" ", i*50), 1, L"\n");
                    }
                }
                Text beseda(line.text, 36, sf::Color::Black, {WIDTH/2-480+40, HEIGHT/1.5f+30}, 0);
                add_text(beseda);
            }

            if(line.music != ""){
                if(line.music != "-"){music.create(line.music, 30.0f, true);music.play();}
                else{music.pause();}
            }

            for(int i = 0; i < line.button_count; i++){
                Button var(line.buttons[i].first, {WIDTH/2-250, HEIGHT/1.8+i*80}, line.buttons[i].second);
                add_button(var);
            }
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
                /*if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        Textures.clear();
                        Texts.clear();
                        Buttons.clear();
                        numScene++;
                        load(numScene);
                    }
                }*/
            }
            

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if(!lock_next && line.button_count == 0){
                    Textures.clear();
                    Texts.clear();
                    Buttons.clear();
                    numScene++;
                    load(numScene);
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if(!lock_next){
                    Textures.clear();
                    Texts.clear();
                    Buttons.clear();
                    numScene--;
                    load(numScene);
                }
            }
            else{
                lock_next = false;
            }

            for(int i = 0; i < line.button_count; i++){
                if(Buttons[i].is_clicked(window)){
                    Textures.clear();
                    Texts.clear();
                    Buttons.clear();
                    numScene = line.buttons[i].second;
                    std::cout << numScene << "\n";
                    load(numScene);
                    
                }
            }

        }
};

#endif //MGBI_BOMONKA_DIALOG_H
