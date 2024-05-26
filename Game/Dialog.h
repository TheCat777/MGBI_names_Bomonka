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

        std::vector<std::string> listFons = {"korzinov-1.png", "korzinov-2.png", "korzinov-3.png", "black.png",
        "arkadii-1.png", "arkadii-2.png", "arkadii-3.png",};
    public:
        Dialog() {}
        int start(sf::RenderWindow & window, int id=0){
            parser.load();
            numScene = id;

            Button bnext;
            bnext.create(0);
            add_button(bnext);
            
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

                Button bnext;
                bnext.create(0);
                add_button(bnext);
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
        void reset(){
            Textures.clear();
            Texts.clear();
            Buttons.clear();
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
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if(!lock_next && line.button_count == 0){
                    reset();
                    numScene++;
                    load(numScene);
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if(!lock_next && numScene > 0){
                    reset();
                    numScene--;
                    load(numScene);
                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(!lock_next){
                    if(line.button_count == 0){
                        if(Buttons[0].is_clicked(window)){
                            reset();
                            numScene++;
                            load(numScene);
                        }
                    }
                    else{
                        for(int i = 0; i < line.button_count; i++){
                            if(Buttons[i].is_clicked(window)){
                                reset();
                                numScene = line.buttons[i].second;
                                load(numScene);
                            }
                        }
                    }

                }
            }
            else{
                lock_next = false;
            }
            if(line.sys > 0){
                reset();
                numScene = line.sys;
                load(numScene);
            }
            
            else if(line.sys < 0){
                if(line.sys == -1){
                    music.pause();
                    numScene++;
                    MGsleep g;
                    g.start(window);
                    load(numScene);
                }
                else if(line.sys == -2){
                    music.pause();
                    numScene++;
                    MiniGame g;
                    g.start(window);
                    load(numScene);
                }
                else if(line.sys == -3){
                    music.pause();
                    numScene++;
                    ThoughtMiniGame g;
                    g.start(window);
                    load(numScene);
                }
                else if(line.sys == -4){
                    music.pause();
                    numScene++;
                    
                    Black_hole blackHole;
                    Bad_end_scene scene;
                    scene.load();
                    scene.setVisibility(0);
                    Sound sound("Bad ending2.mp3", 15.f, true);
                    sound.play();
                    blackHole.start(window);
                    std::thread t(show_scene, std::ref(scene));
                    t.detach();
                    scene.start(window);

                    stop = true;
                }
                else if(line.sys == -5){
                    music.pause();
                    numScene++;
                    
                    Good_end_scene scene;
                    scene.load();
                    scene.setVisibility(0);
                    Kaleidoscope good_scene;
                    Sound sound("Skaneika.mp3", 20.f, true);
                    sound.play();
                    good_scene.start(window);
                    std::thread t(show_scene, std::ref(scene));
                    t.detach();
                    scene.start(window);

                    stop = true;
                }
            }

        }
};

#endif //MGBI_BOMONKA_DIALOG_H
