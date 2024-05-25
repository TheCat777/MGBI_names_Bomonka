//
// Created by Андрей on 25.05.2024.
//
#ifndef MGBI_BOMONKA_THOUGHTS_H
#define MGBI_BOMONKA_THOUGHTS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <ctime>
#include <vector>

const std::wstring texts[] = {
        L"Привет!",
        L"Я ChatGPT!",
        L"Добро пожаловать!",
        L"Случайный текст",
        L"Программирование",
        L"SFML",
        L"Фигуры и текст"
};


enum ThoughtType {
    STATICTHOUGHT,
    RUNTHOUGHT,
    ROTATETHOUGHT,
    RANDOMMOVETHOUGHT
};
class TemplateThought {
protected:
    Texture texture;
    Text text;
    float dx, dy;
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move() = 0;
    virtual void action() = 0;
    bool is_pointed(sf::RenderWindow & window) {
        sf::Vector2i position = sf::Mouse::getPosition() - window.getPosition();
        if (texture.GetPosition().x < position.x && position.x < texture.GetPosition().x + texture.get_size().x
                && texture.GetPosition().y< position.y && position.y < texture.GetPosition().y + texture.get_size().y){
            return true;
        }
        return false;
    }
};

class StaticThought : public TemplateThought {
public:
    StaticThought() {

        unsigned int x = rand() % WIDTH/2 + 1;
        unsigned int y = rand() % HEIGHT/2 + 1;
        texture.create("student.jpg", {x, y});
        text.create(texts[rand() % 6], 20, sf::Color::Red, {x, y}, 0);
    }
    void draw(sf::RenderWindow& window) override {
        texture.draw(window);
        text.draw(window);
    }
    void move() override {}
    void action() override {};
};

class FactoryThought {
public:
    static TemplateThought* createThought() {
        TemplateThought *th = NULL;
        short random = rand() % 4;
        switch (STATICTHOUGHT) {
            case STATICTHOUGHT:
                th = new StaticThought();
                return th;
        }

    }
};
class ThoughtMiniGame {
public:
    void start(sf::RenderWindow & window) {
        srand(time(NULL));
        std::vector<TemplateThought*> thoughts;
        for (int i = 0; i < 10; i++) {
            thoughts.push_back(FactoryThought::createThought());
        }
        while(window.isOpen()) {
            window.clear();
            for (auto s : thoughts) {
                s->draw(window);
            }
            Events(window);
            window.display();
        }
        //for (auto t : thoughts) { delete t; }
    }
    void Events(sf::RenderWindow & window){
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
    ThoughtMiniGame() {}
};

#include "Button.h"
#include "Constants.h"
#include "Sound.h"


#endif //MGBI_BOMONKA_THOUGHTS_H