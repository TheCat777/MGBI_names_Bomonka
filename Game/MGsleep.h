//
// Created by Yaroslav on 26.05.2024.
//

#ifndef MGBI_BOMONKA_MGSLEEP_H
#define MGBI_BOMONKA_MGSLEEP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <ctime>

#include <string>
#include <vector>

#include "Parser.h"
#include "Scene.h"
#include "Sound.h"
#include "Constants.h"


class MGsleep : public Base_Scene{
    private:
        bool lock_next;
        std::vector<std::wstring> fraza = {L"Так сказать вообще",
        L"Будьте здоровы отсюда!",
        L"Ты в таком виде на выборы не ходи...\nДа шучу я, шучу",
        L"Итак, начнём и будем заканчивать.",
        L"Это ненулевое слагаемое?\nТуда его!",
        L"Сейчас неделя будет посвободнее по идее"};
        Sound music;
        bool stop = false;
        sf::Clock Clock;
        sf::Clock Timer;
        double opacity = 0;
        int speed = 15;
        int slide = 0;
    public:
        MGsleep() {}
        int start(sf::RenderWindow & window, int id=0){

            
            
            load();
            while (window.isOpen()) {
                EventsDialog(window);
                if(slide == 0){game(window);}
                else if(slide == 1){fail(window);}
                else{win(window);}
                auto t = draw_all(window);
                if (t != INT32_MIN)
                    return t;
                if (stop)
                    return INT32_MIN;
            }
            return 0;
        }

        void load(int id = 0) {
            
            Texture fon;
            fon.create("korzinov-2.png", {0, 0});
            add_texture(fon);
            
            Text info(L"Нажимайте на кнопку, чтобы бороться со сном", 28, sf::Color{0x0047abFF}, {WIDTH/6-10, HEIGHT/1.3f}, 0);
            add_text(info);
            Text fraz(fraza[random(0, fraza.size()-1)], 28, sf::Color{0xFFFFFFFF}, {WIDTH/6-10, HEIGHT/10}, 0);
            add_text(fraz);
            Text timer(L"", 28, sf::Color{0xFFFFFFFF}, {WIDTH/1.5-10, HEIGHT/10}, 0);
            add_text(timer);

            Texture son;
            son.create("black.png", {0, 0});
            son.setVisibility(0);
            add_texture(son);

            Button bnext;
            bnext.create(0);
            add_button(bnext);
            
            music.create("Cvetok.mp3", 30.0f, true);
            music.play();
        }
        double dt(){
            return Clock.restart().asSeconds();
        }
        void fail(sf::RenderWindow & window){
            Texts[0].set_text(L"Нажмите, чтобы предотвратить это и переиграть\n\n                                                   ... приятных снов");
            Texts[1].set_text(L"ВЫ ЗАСНУЛИ И ПРОСПАЛИ ВСЮ ЛЕКЦИЮ!");
            
            if(Buttons[0].is_clicked(window)){
                
                Texts[0].set_text(L"Нажимайте, чтобы бороться со сном");
                Texts[1].set_text(fraza[random(0, fraza.size()-1)]);
                slide = 0;
                Timer.restart();
            }
        }
        void win(sf::RenderWindow & window){
            Texts[0].set_text(L"Лекция записана и вы успешно ничего не поняли из неё");
            Texts[1].set_text(L"ПОЗДРАВЛЯЕМ!");
            if(Buttons[0].is_clicked(window)){
                stop = true;
            }
        }
        void game(sf::RenderWindow & window){
            opacity += dt()*speed*(abs(opacity)+1)/10;

            if(opacity <= 0){
                Textures[1].setVisibility(0);
            }
            else if (opacity > 0 && opacity <= 255){
                Textures[1].setVisibility(opacity);
            }
            else if (opacity > 255 && opacity < 300){
                Textures[1].setVisibility(255);
            }
            else{
                slide = 1;
                opacity = 255;
            }
            
            if(Timer.getElapsedTime().asSeconds() > 60 && opacity < 255){
                slide = 2;
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(!lock_next){
                    if(Buttons[0].is_clicked(window)){
                        lock_next = true;
                        opacity = random(-10, 0);
                        speed = random(10, 50);
                    }
                }
            }
            else{
                lock_next = false;
            }
            Texts[2].set_text(L"До конца пары: "+std::to_wstring(60-int(Timer.getElapsedTime().asSeconds()))+L" минут");
        }
        int random(int s, int e){
            return rand() % (e - s + 1) + s;
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
            
        }
};

#endif //MGBI_BOMONKA_MGSLEEP_H
