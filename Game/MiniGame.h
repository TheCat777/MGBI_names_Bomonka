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

#include "Button.h"
#include "Constants.h"
#include "Sound.h"


const int HEIGHT_MAP = 60, WIDTH_MAP = 65;
const sf::Vector2f CAMERA_SIZE = {960, 540};
const sf::Vector2f CAMERA_BORDER_TOP = {480, 270};
const sf::Vector2f CAMERA_BORDER_BOTTOM = {2720, 2730};
const sf::Vector2u FINISH_COORDS = {2120, 2350};
const sf::Vector2f DRAWING_BORDER = {530, 330};  // циферки всякие

sf::String Map[HEIGHT_MAP] = {
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0      0       01111110                                        0",
        "0      0       01111110                                        0",
        "0      0       01111110                                        0",
        "0      0       01111110                                        0",
        "0      0       01111110     00000000000000       0000000       0",
        "0      0       01111110     0            0       0     0       0",
        "0                           0    1 1     0       0     0       0",
        "0                           0     1      0       0     0       0",
        "0                           0    1 1     0       0     0       0",
        "0                           0            0       0     000000000",
        "0              00000000000000000         0                     0",
        "00000000       0               0         0                     0",
        "0              0               0         0                     0",
        "0              0               0         0                     0",
        "0              0        00000000         000000000000000       0",
        "0              0                                               0",
        "0              0                                               0",
        "0              0                                               0",
        "0              0                                               0",
        "0     000000000000000000000           00000000000000000000000000",
        "0                         0                                    0",
        "0                         0                                    0",
        "0                         0                                    0",
        "0                         0                                    0",
        "0000000000000000000       0000000000000000000000000000000      0",
        "0                         0                             0      0",
        "0     11  11              0                             0      0",
        "0                         0                             0      0",
        "0    1      1             0     00000000000000000       00000000",
        "0     111111      0       0     0      0        0              0",
        "0                 0       0     0      0        0              0",
        "0     0000000000000       0     0      0        0              0",
        "0     0111111111110       0     0      0        0       0      0",
        "0     0111111111110       0     0                       0      0",
        "0     0111111111110       0     0                       0      0",
        "0     0111111111110       0     0                       0      0",
        "0     0111111111110                                     0      0",
        "0     0000000111110                    0       00       0      0",
        "0           0111110                    0        0       0      0",
        "0           0111110                    0        0       0      0",
        "0           0111110000000000000000000000        0       0      0",
        "0           0111110                             0       0      0",
        "000000      0000000                             0       0      0",
        "0                                               0       00000000",
        "0                       0000000000000000000000000              0",
        "0                       01111111111111110                      0",
        "0        0000000        01111111111111110             000      0",
        "0                       01111111111111110               0      0",
        "0                       01111111111111110               0      0",
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
    float SPEED_W, SPEED_A, SPEED_S, SPEED_D;
    int dw, da, ds, dd;
    bool finish = false;
    float elapsedTime = 0.0f;
    Text timerText;
    sf::Clock timerClock;

public:
    sf::View getViewCoords(float x, float y) {
        float tempX = x; float tempY = y;
        if (x <= CAMERA_BORDER_TOP.x) tempX = CAMERA_BORDER_TOP.x;
        if (y <= CAMERA_BORDER_TOP.y) tempY = CAMERA_BORDER_TOP.y;
        if (y >= CAMERA_BORDER_BOTTOM.y) tempY = CAMERA_BORDER_BOTTOM.y;
        if (x >= CAMERA_BORDER_BOTTOM.x) tempX = CAMERA_BORDER_BOTTOM.x;
        camera.setCenter(tempX, tempY);
        return camera;
    }
    MiniGame() {}
    void start(sf::RenderWindow & window) {
        Sound music("stress.mp3", 10.f, true);
        music.play();
        StartWindow(window);
        Load();
        while (window.isOpen()) {
            if(checkFinish()) { break; }
            if(!TimeCounter()) { break; }
            EventsMiniGame(window);
            WASD(window);
            DrawMiniGame(window);
        }
        if(finish) {
            GoodFinish(window);
        }
        else {
            music.set_path("Igromaniya.mp3");
            music.play();
            BadFinish(window);
        }

    }
    void Load() {
        Texture block;
        Texture floor;
        Texture student;

        Texture pol1;
        Texture pol2;
        Texture pol3;
        student.create("playerm.png", {100, 100});
//        block.create("block.jpg", {0, 0});
//        floor.create("floor2.png", {0, 0});

        add_texture(student);
//        add_texture(block);
//        add_texture(floor);

        pol1.create("plitka-2m.png", {0, 0});
        pol2.create("plitka-1m.png", {0, 0});
        pol3.create("plitka-3.png", {0, 0});
        add_texture(pol1);
        add_texture(pol2);
        add_texture(pol3);

        timerText.create(L"00:00", 20, sf::Color::Black, {0, 0}, 0);

        camera.setSize(CAMERA_SIZE.x, CAMERA_SIZE.y);
        camera.setCenter(student.GetSprite().getPosition());
    }
    bool TimeCounter() {
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/3200;

        elapsedTime = timerClock.getElapsedTime().asSeconds();
        if (elapsedTime >= 120.0f) { // 2 minutes
            return false;
        }

        int minutes = static_cast<int>(elapsedTime) / 60;
        int seconds = static_cast<int>(elapsedTime) % 60;
        timerText.setPosition({camera.getCenter().x - camera.getSize().x / 2 + 10, camera.getCenter().y - camera.getSize().y / 2 + 10});
        timerText.set_text(L"Время тикает: " + std::to_wstring(1 - minutes) + L"m " + std::to_wstring(59 - seconds) + L"s");
        return true;
    }
    void DrawMiniGame(sf::RenderWindow & window){
        window.clear();
        int i, j;
        for (i = 0; i < HEIGHT_MAP; ++i) {
            for (j = 0; j < WIDTH_MAP; ++j) {
                if((camera.getCenter().x-DRAWING_BORDER.x < j*50) && (j*50 < camera.getCenter().x+DRAWING_BORDER.x) && (camera.getCenter().y-DRAWING_BORDER.y < i*50) && (i*50 < camera.getCenter().y+DRAWING_BORDER.y)) {
                    if (Map[i][j] == '0') {
                        Textures[1].SetPosition({j * 50, i * 50});
                        Textures[1].draw(window);
                        CreateCollision(Textures[1]);
                    }
                    else if (Map[i][j] == ' ') {
                        Textures[2].SetPosition({j * 50, i * 50});
                        Textures[2].draw(window);
                    }
//                    else if (Map[i][j] == '2' || Map[i][j] == '3' || Map[i][j] == '1'){
//                        Textures[3].SetPosition({j * 50, i * 50});
//                        Textures[3].draw(window);
//                    }
                }
            }
        }
        timerText.draw(window);
        window.setView(camera);
        Textures[0].draw(window);
        if(finish) Textures[3].draw(window);
        window.display();
    }
    void StartWindow(sf::RenderWindow & window) {
        camera.setSize(WIDTH, HEIGHT);
        camera.setCenter(window.getSize().x/2, window.getSize().y/2);
        Button buttonStart;
        Text t, info;
        info.create(L"Вы только что покинули аудиторию 501ю, следующей парой была физика... \nВы посмотрели время на телефоне и осознали ужасающую реальность.......\nДо начала лекции осталось лишь 2 минуты...\nВаше горе, отчаяние, боль, разочарование и непреодолимый страх не знали границ...  \nИ да время уже идет!", 20, sf::Color::Red, {(window.getSize().x - 64*10)/2, window.getSize().y/2-100}, 0);
        t.create(L"Бежать на физику!!!", 40, sf::Color::Red, {(window.getSize().x - 19*20)/2, window.getSize().y/2+100}, 0);
        buttonStart.create(0);
        while(window.isOpen() && !buttonStart.is_clicked(window)) {
            window.clear();
            EventsMiniGame(window);
            window.setView(camera);
            t.draw(window);
            info.draw(window);
            buttonStart.draw(window);
            window.display();
        }
    }
    bool checkFinish() {
        if (fabs(Textures[0].GetSprite().getPosition().x - FINISH_COORDS.x) <= 50 && fabs(Textures[0].GetSprite().getPosition().y - FINISH_COORDS.y) <= 50) {
            finish = true;
            return true;
        }
        return false;
    }
    void GoodFinish(sf::RenderWindow & window) {
        camera.setSize(WIDTH, HEIGHT);
        camera.setCenter(window.getSize().x/2, window.getSize().y/2);
        Button buttonStart;
        Text t, info;
        info.create(L"Чудом добравшись до заветной аудитории, \nвы получили множество полезных знаний, которые помогут закрыть долги.", 20, sf::Color::Red, {(window.getSize().x - 60*10)/2, window.getSize().y/2-100}, 0);
        t.create(L"Полным надежд отправляйся дальше!", 40, sf::Color::Red, {(window.getSize().x - 30*20)/2, window.getSize().y/2+100}, 0);
        buttonStart.create(0);
        while(window.isOpen() && !buttonStart.is_clicked(window)) {
            window.clear();
            EventsMiniGame(window);
            window.setView(camera);
            t.draw(window);
            info.draw(window);
            buttonStart.draw(window);
            window.display();
        }
    }
    void BadFinish(sf::RenderWindow & window) {
        camera.setSize(WIDTH, HEIGHT);
        camera.setCenter(window.getSize().x/2, window.getSize().y/2);
        Button buttonStart;
        Text t, info;
        info.create(L"Вот и пришел твой конец...", 20, sf::Color::Red, {(window.getSize().x - 30*10)/2, window.getSize().y/2-100}, 0);
        t.create(L"В отчаянии отправляйся дальше, сдаваться ещё рано!", 40, sf::Color::Red, {(window.getSize().x - 48*20)/2, window.getSize().y/2+100}, 0);
        buttonStart.create(0);
        while(window.isOpen() && !buttonStart.is_clicked(window)) {
            window.clear();
            EventsMiniGame(window);
            window.setView(camera);
            t.draw(window);
            info.draw(window);
            buttonStart.draw(window);
            window.display();
        }
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
