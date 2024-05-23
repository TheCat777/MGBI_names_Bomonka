//
// Created by SvCat on 14.03.2024.
//

#ifndef PROJECT_NAME_GAME_H
#define PROJECT_NAME_GAME_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "Scene.h"
#include "MiniGame.h"
#include "Dialog.h"
#include "Black hole.h"


class MainGame{
private:
    sf::RenderWindow window;

    void execute(const std::string& var, int val){
        if (var == "WIDTH"){ WIDTH = val; return;}
        if (var == "HEIGHT"){ HEIGHT = val; return;}
        if (var == "MAX_FRAME_LIMIT"){ MAX_FRAME_LIMIT = val; return;}
        if (var == "FULLSCREEN"){ FULLSCREEN = (bool)val; return;}
    }

    bool load_settings(){
        try {
            std::ifstream file((path_to_game + R"(\resources\settings)").c_str());
            std::string var; int val;
            while (!file.eof()) {
                file >> var >> val;
                execute(var, val);
            }
        }
        catch (...){
            return false;
        }
        return true;
    }

    void init_window(){
        window.create({ WIDTH, HEIGHT }, "MGBI by N.E. Bomonki", FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Default);
        window.setFramerateLimit(MAX_FRAME_LIMIT);
    }
public:
    MainGame(){
        if (!load_settings()) return;
        init_window();
        if (true) {
//            Loading_Scene loadingScene;
//            loadingScene.load();
//            loadingScene.start(window);
            MiniGame g;
//            std::thread t(show_scene, std::ref(g));
//            t.detach();
            g.start(window);
        }
        else if(true){
            Dialog g;
//            std::thread t(show_scene, std::ref(g));
//            t.detach();
            g.start(window);
        }
        else if(!true){
            Black_hole blackHole;
            Bad_end_scene scene;
            scene.load();
            Sound sound("Bad ending2.mp3", 15.f, true);
            sound.play();
            blackHole.start(window);
            std::thread t(show_scene, std::ref(scene));
            t.detach();
            scene.start(window);
        }
        else{
            Good_end_scene scene;
            scene.load();
            Kaleidoscope good_scene;
            Sound sound("Skaneika.mp3", 20.f, true);
            sound.play();
            good_scene.start(window);
            std::thread t(show_scene, std::ref(scene));
            t.detach();
            scene.start(window);
        }
        window.close();
    }
};

#endif //PROJECT_NAME_GAME_H
