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
    sf::Vector2f cameraDirection = {-3.14f, 0.f}, size_of_window = sf::Vector2f((float)WIDTH, (float)HEIGHT);

    float move_speed = 0.175f;
    bool stop = false;
    float fps_to = 60;

    void load(){
        if (!sf::Shader::isAvailable()) {
            std::cout << "Shaders is not supported" << std::endl;
            return;
        }
        if (!fragShader.loadFromFile(path_to_game + R"(\resources\Shaders\Black-Hole-fragment-shader.glsl)", sf::Shader::Fragment)) {
            return;
        }
    }
    void Events(sf::RenderWindow & window){
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop = true;
                return;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    stop = true;
                    return;
                }
                if (!false) {
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
                }
            }
        }
        if (true){
            cameraPosition.x -= move_speed * cameraPosition.x / std::sqrt(cameraPosition.z * cameraPosition.z + cameraPosition.y * cameraPosition.y + cameraPosition.z * cameraPosition.z) / (float)fps_to * (std::fabs(cameraPosition.z) - 0.7f);
            cameraPosition.y -= move_speed * cameraPosition.y / std::sqrt(cameraPosition.z * cameraPosition.z + cameraPosition.y * cameraPosition.y + cameraPosition.z * cameraPosition.z) / (float)fps_to * (std::fabs(cameraPosition.z) - 0.7f);
            cameraPosition.z -= move_speed * cameraPosition.z / std::sqrt(cameraPosition.z * cameraPosition.z + cameraPosition.y * cameraPosition.y + cameraPosition.z * cameraPosition.z) / (float)fps_to * (std::fabs(cameraPosition.z) - 0.7f);

        }
    }

    void move_Mouse(float & const_x, float & const_y, const sf::Vector2u & window_size){
        if (sf::Mouse::getPosition().x > window_size.x-10){
            const_x -= 1;
            sf::Mouse::setPosition({sf::Mouse::getPosition().x - 150, sf::Mouse::getPosition().y});
        }
        if (sf::Mouse::getPosition().x < 10){
            const_x += 1;
            sf::Mouse::setPosition({sf::Mouse::getPosition().x + 150, sf::Mouse::getPosition().y});
        }
        if (sf::Mouse::getPosition().y < 10){
            const_y -= 1;
            sf::Mouse::setPosition({sf::Mouse::getPosition().x, sf::Mouse::getPosition().y + 150});
        }
        if (sf::Mouse::getPosition().y > window_size.y-10){
            const_y += 1;
            sf::Mouse::setPosition({sf::Mouse::getPosition().x, sf::Mouse::getPosition().y - 150});
        }
        cameraDirection.x = (float) -sf::Mouse::getPosition().x / 150 + const_x;
        cameraDirection.y = (float) sf::Mouse::getPosition().y / 150 + const_y;
    }
public:
    Black_hole(){
        load();
    }
    void start(sf::RenderWindow & window) {
        clock_t t;
        sf::RectangleShape rect(size_of_window);
        sf::RenderStates shader(&fragShader);
        float const_x = 2.7f, const_y = 3.7f;
        window.setMouseCursorVisible(false);
        sf::Mouse::setPosition({400, 400});


        sf::Transform transform;

        fragShader.setUniform("resolution", size_of_window);
        fragShader.setUniform("transform", (sf::Glsl::Mat3) transform);
        fragShader.setUniform("zoom", 1.0f);
        while (window.isOpen() && !stop) {
            t = clock();
            move_Mouse(const_x, const_y, window.getSize());
            if (std::fabs(cameraPosition.x) + std::fabs(cameraPosition.y) + std::fabs(cameraPosition.z) < 1.1){
                return;
            }
            Events(window);
            cameraDirection.x = (float) -sf::Mouse::getPosition().x / 150 + const_x;
            cameraDirection.y = (float) sf::Mouse::getPosition().y / 150 + const_y;


            fragShader.setUniform("rayOrigin", cameraPosition);
            fragShader.setUniform("cameraDirection", cameraDirection);
            fragShader.setUniform("iTime", (float)clock() / CLOCKS_PER_SEC);

            window.clear();
            window.draw(rect, shader);

            window.display();
            t = clock() - t;
            fps_to = CLOCKS_PER_SEC / (double) t;
        }
        window.setMouseCursorVisible(true);
    }
};


#endif //MGBI_BOMONKA_BLACK_HOLE_H
