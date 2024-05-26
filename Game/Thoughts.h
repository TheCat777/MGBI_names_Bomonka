//
// Created by Андрей on 25.05.2024.
//
#ifndef MGBI_BOMONKA_THOUGHTS_H
#define MGBI_BOMONKA_THOUGHTS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "Constants.h"
#include "Sound.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <ctime>
#include <vector>

const std::wstring texts[] = {
        L"Привет!",
        L"абоба",
        L"Добро пожаловать!",
        L"Случайный текст",
        L"Программирование",
        L"SFML",
        L"Фигуры и текст"
};


enum ThoughtType {
    STATICTHOUGHT,
    RUNTHOUGHT,
    RANDOMMOVETHOUGHT,
    ROTATETHOUGHT
};
class TemplateThought {
protected:
    Texture texture;
    Text text;
    float dx, dy;
    float rotationSpeed;
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move(sf::RenderWindow& window) = 0;
    virtual void action() = 0;
    bool is_pointed(sf::RenderWindow & window) {
        sf::Vector2i position = sf::Mouse::getPosition() - window.getPosition();
        if (texture.GetPosition().x < position.x && position.x < texture.GetPosition().x + texture.get_size().x
                && texture.GetPosition().y< position.y && position.y < texture.GetPosition().y + texture.get_size().y){
            return true;
        }
        return false;
    }
    bool is_clicked(sf::RenderWindow & window) {
        if (is_pointed(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return true;
        }
        return false;
    }
    void mouseMoving(sf::RenderWindow & window) {
        if (is_clicked(window)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            sf::Vector2u size = texture.get_size();
            texture.SetPosition({static_cast<int>(mousePos.x-size.x/2), static_cast<int>(mousePos.y-size.y/2)});
            text.setPosition({static_cast<float>(mousePos.x-size.x/2), static_cast<float>(mousePos.y-size.y/2)});
        }
    }
};

class StaticThought : public TemplateThought {
public:
    StaticThought() {
        unsigned int x = rand() % WIDTH + 1;
        unsigned int y = rand() % HEIGHT + 1;
        texture.create("student.jpg", {x, y});
        text.create(texts[rand() % 6], 20, sf::Color::Red, {x, y}, 0);
    }
    void draw(sf::RenderWindow& window) override {
        texture.draw(window);
        text.draw(window);
    }

    void move(sf::RenderWindow& window) override {}
    void action() override {}
};
class RunThought : public TemplateThought{
public:
    RunThought() {
        unsigned int x = rand() % WIDTH + 1;
        unsigned int y = rand() % HEIGHT + 1;
        texture.create("student.jpg", {x, y});
        text.create(texts[rand() % 6], 20, sf::Color::Red, {x, y}, 0);
        dx = static_cast<float>(rand() % 5 - 2); // Горизонтальное движение
        dy = static_cast<float>(rand() % 5 - 2); // Вертикальное движение
    }

    void move(sf::RenderWindow& window) override {
        texture.move(dx, dy);
        text.move(dx, dy);
        if (texture.GetPosition().x <= 0 || texture.GetPosition().x >= window.getSize().x) {
            dx = -dx;
        }
        if (texture.GetPosition().y <= 0 || texture.GetPosition().y >= window.getSize().y) {
            dy = -dy;
        }
    }

    void draw(sf::RenderWindow& window) override {
        move(window);
        texture.draw(window);
        text.draw(window);
    }
    void action() override {}
};
class RandomMoveThought : public TemplateThought{
public:
    RandomMoveThought() {
        unsigned int x = rand() % WIDTH + 1;
        unsigned int y = rand() % HEIGHT + 1;

        texture.create("student.jpg", {x, y});
        text.create(texts[rand() % 6], 20, sf::Color::Red, {x, y}, 0);
        texture.SetOrigin(texture.get_size().x / 2, texture.get_size().y / 2);
        
        dx = static_cast<float>(rand() % 5 - 2); // Горизонтальное движение
        dy = static_cast<float>(rand() % 5 - 2); // Вертикальное движение
        rotationSpeed = static_cast<float>(rand() % 5 - 2);
    }

    void move(sf::RenderWindow& window) override {
        texture.move(dx, dy);
        texture.rotate(rotationSpeed);
        text.move(dx, dy);
        text.rotate(rotationSpeed);
        if (texture.GetPosition().x <= 0 || texture.GetPosition().x >= window.getSize().x) {
            dx = -dx;
            rotationSpeed = -rotationSpeed;
        }
        if (texture.GetPosition().y <= 0 || texture.GetPosition().y >= window.getSize().y) {
            dy = -dy;
        }
    }

    void draw(sf::RenderWindow& window) override {
        move(window);
        texture.draw(window);
        text.draw(window);
    }
    void action() override {}
};
class FactoryThought {
public:
    static TemplateThought* createThought() {
        TemplateThought *th = NULL;
        short random = rand() % 3;
        switch (random) {
            case STATICTHOUGHT:
                th = new StaticThought();
                return th;
            case RUNTHOUGHT:
                th = new RunThought();
                return th;
            case RANDOMMOVETHOUGHT:
                th = new RandomMoveThought();
                return th;
        }

    }
};
class ThoughtMiniGame {
public:
    void start(sf::RenderWindow & window) {
        srand(time(NULL));
        std::vector<TemplateThought*> thoughts;
        for (int i = 0; i < 20; i++) {
            thoughts.push_back(FactoryThought::createThought());
        }
        while(window.isOpen()) {
            window.clear();
            Events(window);
            Draw(window, thoughts);
        }
        //for (auto t : thoughts) { delete t; }
    }
    void Draw(sf::RenderWindow & window, std::vector<TemplateThought*> thoughts) {
        for (auto s : thoughts) {
            s->draw(window);
            s->mouseMoving(window);
        }
        window.display();
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




#endif //MGBI_BOMONKA_THOUGHTS_H