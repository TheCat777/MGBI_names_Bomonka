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
        L"пара идет?",
        L"лалалалал",
        L"СпАтЬ хочу!",
        L"2+2=5",
        L"Какие дифуры?",
        L"Помогите",
        L"Что я тут делаю?",
        L"C++",
        L"определитель\nматрицы",
        L"ЭКЗАМЕНЫ",
        L"y = f(x)",
        L"инкапсуляция",
        L"operator\noverloading",
        L"Factory\nPattren"
};


enum ThoughtType {
    STATICTHOUGHT,
    RUNTHOUGHT,
    RANDOMMOVETHOUGHT,
};
int counter = 0;

class TemplateThought {
protected:
    Texture texture;
    Text text;
    float dx, dy;
    float rotationSpeed;
    bool correct;
public:
    ~TemplateThought() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move(sf::RenderWindow& window) = 0;
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
    void setCorrect(bool cor) {
        correct = cor;
    }
    bool getCorrect() const {
        return correct;
    }
    void action(sf::RenderWindow & window) {
        if (fabs(texture.GetPosition().x) <= 100 && fabs(texture.GetPosition().y - 720) <= 100 && is_clicked(window)) {
            if (getCorrect()) {
                counter += 1;
                texture.SetPosition({-1000, -1000});
                text.setPosition({-1000, -1000});
                std::cout << counter << std::endl;
            }
            else {
                counter -= 1;
                std::cout << counter << std::endl;
            };
        }
    }
};

class StaticThought : public TemplateThought {
public:
    StaticThought() {
        unsigned int x = rand() % (WIDTH-50) + 1;
        unsigned int y = rand() % (HEIGHT-50) + 1;
        texture.create("thought.jpg", {x, y});
        text.create(texts[rand() % 13], 20, sf::Color::Black, {x, y}, 0);
    }
    void draw(sf::RenderWindow& window) override {
        texture.draw(window);
        text.draw(window);
    }

    void move(sf::RenderWindow& window) override {}

};
class RunThought : public TemplateThought{
public:
    RunThought() {
        unsigned int x = rand() % WIDTH + 1;
        unsigned int y = rand() % HEIGHT + 1;
        texture.create("thought.jpg", {x, y});
        text.create(texts[rand() % 13], 20, sf::Color::Black, {x, y}, 0);
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

};
class RandomMoveThought : public TemplateThought{
public:
    RandomMoveThought() {
        unsigned int x = rand() % WIDTH + 1;
        unsigned int y = rand() % HEIGHT + 1;
        texture.create("thought.jpg", {x, y});
        text.create(texts[rand() % 13], 20, sf::Color::Black, {x, y}, 0);
        texture.SetOrigin(texture.get_size().x / 2, texture.get_size().y / 2);
        text.setOrigin(texture.get_size().x / 2, texture.get_size().y / 2);

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

class ThoughtMiniGame : public Base_Scene{
private:
    Text text;
    Texture fon, trash;
    Button but;
    bool stop = false;
public:
    void start(sf::RenderWindow & window) {
        Sound music("Igrivaya.mp3", 10.f, true);
        music.play();
        trash.create("trash.png", {30, 630});
        fon.create("seminar.png", {0, 0});
        srand(time(NULL));
        std::vector<TemplateThought*> thoughts;
        for (int i = 0; i < 50; i++) {
            TemplateThought* temp = FactoryThought::createThought();
            temp->setCorrect(true);
            thoughts.push_back(temp);
        }
        while(window.isOpen() && !stop) {
            window.clear();
            Events(window);
            Draw(window, thoughts);
            if(counter == 50) {
                music.set_path("Cvetok.mp3");
                music.play();
                Finish(window);
                break;
            }
            window.display();
        }
    }
    void Finish(sf::RenderWindow & window) {
        but.create(0);
        text.create(L"Фух... наконец смог сосредоточиться, вряд ли конечно это поможет...", 40, sf::Color::Black, {50, 600}, 0);
        fon.create("seminar.png", {0, 0});
        while(window.isOpen() && !stop) {
            window.clear();
            Events(window);
            fon.draw(window);
            text.draw(window);
            but.draw(window);
            window.display();
        }
    }
    void Draw(sf::RenderWindow & window, std::vector<TemplateThought*> thoughts) {
        fon.draw(window);
        trash.draw(window);
        for (auto s : thoughts) {
            s->draw(window);
            s->mouseMoving(window);
            s->action(window);
        }
    }
    void Events(sf::RenderWindow & window){
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    stop = true;
                }
                if (event.key.code == sf::Keyboard::Space) {
                    stop = true;
                }
            }
            if (event.type == sf::Event::Closed) {
                stop = true;
            }
        }
    }
    ThoughtMiniGame() {}
};




#endif //MGBI_BOMONKA_THOUGHTS_H