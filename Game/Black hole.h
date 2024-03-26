//
// Created by SvCat on 23.03.2024.
//

#ifndef MGBI_BOMONKA_BLACK_HOLE_H
#define MGBI_BOMONKA_BLACK_HOLE_H


#include "Constants.h"
#include <string>
#include "Text.h"
#include <SFML/Graphics.hpp>

class Black_hole{
private:
    sf::Shader fragShader;
    sf::Vector3f cameraPosition = {0.f, 1.35f, -10.f};
    sf::Vector2f cameraDirection = {-3.14f, 0.f};
    Text fps;
    Text coords;
    Text direction;
    Text direction_cos;

    float move_speed = 0.05;
    float rotate_speed = 0.02;
    void load(){
        fps.create(L"-- fps", 42, sf::Color::Red, {0, 900}, sf::Text::Bold);
        coords.create(L"-- fps", 42, sf::Color::Red, {0, 0}, sf::Text::Bold);
        direction.create(L"-- fps", 42, sf::Color::Red, {1750, 0}, sf::Text::Bold);
        direction_cos.create(L"-- fps", 42, sf::Color::Red, {1650, 900}, sf::Text::Bold);
        if (!sf::Shader::isAvailable()) {
            std::cout << "Shaders is not supported" << std::endl;
            return;
        }
        if (!fragShader.loadFromFile(path_to_game + "\\resources\\Shaders\\Black-Hole-fragment-shader.glsl", sf::Shader::Fragment)) {
            return;
        }
    }
    void Events(sf::RenderWindow & window){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::D) {
                    cameraPosition.z += move_speed * sin(cameraDirection.x);
                    cameraPosition.x += move_speed * cos(cameraDirection.x);

                }
                if (event.key.code == sf::Keyboard::A) {
                    cameraPosition.z -= move_speed * sin(cameraDirection.x);
                    cameraPosition.x -= move_speed * cos(cameraDirection.x);
                }
                if (event.key.code == sf::Keyboard::W) {
                    cameraPosition.z += move_speed * cos(cameraDirection.x);
                    cameraPosition.x -= move_speed * sin(cameraDirection.x);
                    cameraPosition.y -= move_speed * sin(cameraDirection.y);
                }

                if (event.key.code == sf::Keyboard::S) {
                    cameraPosition.z -= move_speed * cos(cameraDirection.x);
                    cameraPosition.x += move_speed * sin(cameraDirection.x);
                    cameraPosition.y += move_speed * sin(cameraDirection.y);
                }

                if (event.key.code == sf::Keyboard::Space)
                    cameraPosition.y += move_speed;
                if (event.key.code == sf::Keyboard::LShift)
                    cameraPosition.y -= move_speed;

                if (event.key.code == sf::Keyboard::Down)
                    cameraDirection.y += rotate_speed;
                if (event.key.code == sf::Keyboard::Up)
                    cameraDirection.y -= rotate_speed;
                if (event.key.code == sf::Keyboard::Left)
                    cameraDirection.x += rotate_speed;
                if (event.key.code == sf::Keyboard::Right)
                    cameraDirection.x -= rotate_speed;
            }

        }
    }
public:
    Black_hole(){
        load();
    }
    void start(sf::RenderWindow & window) {
        clock_t t;
        float const_x = 2.7f, const_y = 3.7f;
        window.setMouseCursorVisible(false);
        sf::Mouse::setPosition({400, 400});
        double fps_to = 0;
        while (window.isOpen()) {
            if (sf::Mouse::getPosition().x > 600){
                const_x -= 1;
                sf::Mouse::setPosition({sf::Mouse::getPosition().x - 150, sf::Mouse::getPosition().y});
            }
            if (sf::Mouse::getPosition().x < 300){
                const_x += 1;
                sf::Mouse::setPosition({sf::Mouse::getPosition().x + 150, sf::Mouse::getPosition().y});
            }
            if (sf::Mouse::getPosition().y < 300){
                const_y -= 1;
                sf::Mouse::setPosition({sf::Mouse::getPosition().x, sf::Mouse::getPosition().y + 150});
            }
            if (sf::Mouse::getPosition().y > 600){
                const_y += 1;
                sf::Mouse::setPosition({sf::Mouse::getPosition().x, sf::Mouse::getPosition().y - 150});
            }
            cameraDirection.x = (float) -sf::Mouse::getPosition().x / 150 + const_x;
            cameraDirection.y = (float) sf::Mouse::getPosition().y / 150 + const_y;
            t = clock();
            Events(window);
            sf::Vector2u screenSize = window.getSize();

            sf::RectangleShape rect(sf::Vector2f(screenSize.x, screenSize.y));

            // the direction of each ray is transformed with this matrix before marching
            sf::Transform transform;

            fragShader.setUniform("resolution", sf::Vector2f(screenSize.x, screenSize.y));
            fragShader.setUniform("rayOrigin", cameraPosition);
            fragShader.setUniform("cameraDirection", cameraDirection);
            fragShader.setUniform("transform", (sf::Glsl::Mat3) transform);
            fragShader.setUniform("zoom", 1.0f);


            sf::RenderStates shader(&fragShader);

            coords.set_text(L"x: " + std::to_wstring(cameraPosition.x) + L"\ny: " + std::to_wstring(cameraPosition.y) + L"\nz: " + std::to_wstring(cameraPosition.z));
            direction.set_text(L"x: " + std::to_wstring(cameraDirection.x) + L"\ny: " + std::to_wstring(cameraDirection.y));
            direction_cos.set_text(L"cos(x): " + std::to_wstring(cos(cameraDirection.x)) + L"\ncos(y): " + std::to_wstring(cos(cameraDirection.y)));
            window.clear();
            window.draw(rect, shader);
            fps.draw(window);
            coords.draw(window);
            direction.draw(window);
            direction_cos.draw(window);
            fps.set_text(std::to_wstring(fps_to) + L" fps");

            window.display();
            t = clock() - t;
            fps_to = CLOCKS_PER_SEC / (double) t;
        }

        window.setMouseCursorVisible(true);
    }
};


#endif //MGBI_BOMONKA_BLACK_HOLE_H
