//
// Created by SvCat on 23.03.2024.
//

#ifndef MGBI_BOMONKA_BLACK_HOLE_H
#define MGBI_BOMONKA_BLACK_HOLE_H


#include "Constants.h"
#include <string>
#include "Text.h"
#include <SFML/Graphics.hpp>


sf::Texture load_buffer_A(const sf::Texture& previous){
    sf::Texture temp1, temp2;

    temp1.loadFromFile((path_to_game + "\\resources\\Textures\\noise.png"));
    temp2.loadFromFile((path_to_game + "\\resources\\Textures\\orinial 1.jpg"));
    sf::Shader shader;
    shader.loadFromFile(path_to_game + R"(\resources\Shaders\buffer_A.glsl)", sf::Shader::Fragment);
    shader.setUniform("iResolution", sf::Vector2f(WIDTH, HEIGHT));
    shader.setUniform("iTime", (float)clock() / CLOCKS_PER_SEC);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        shader.setUniform("iMouse", sf::Vector3f((float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().x, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)));
    }
    shader.setUniform("iChannel0", temp1);
    shader.setUniform("iChannel1", temp2);
    shader.setUniform("iChannel2", previous);

    sf::RenderTexture renderTexture;
    sf::RectangleShape rect(sf::Vector2f(WIDTH, HEIGHT));
    renderTexture.create(WIDTH, HEIGHT);
    renderTexture.clear();
    renderTexture.draw(rect, &shader);
    renderTexture.display();
    return renderTexture.getTexture();
}

sf::Texture load_buffer_B(const sf::Texture& buf_A){
    sf::Shader shader;
    shader.loadFromFile(path_to_game + R"(\resources\Shaders\buffer_B.glsl)", sf::Shader::Fragment);
    shader.setUniform("iResolution", sf::Vector2f(WIDTH, HEIGHT));
    shader.setUniform("iChannel0", buf_A);

    sf::RenderTexture renderTexture;
    sf::RectangleShape rect(sf::Vector2f(WIDTH, HEIGHT));
    renderTexture.create(WIDTH, HEIGHT);
    renderTexture.clear();
    renderTexture.draw(rect, &shader);
    renderTexture.display();
    return renderTexture.getTexture();
}

sf::Texture load_buffer_C(const sf::Texture& buf_B){
    sf::Shader shader;
    shader.loadFromFile(path_to_game + R"(\resources\Shaders\buffer_C.glsl)", sf::Shader::Fragment);
    shader.setUniform("iResolution", sf::Vector2f(WIDTH, HEIGHT));
    shader.setUniform("iChannel0", buf_B);

    sf::RenderTexture renderTexture;
    sf::RectangleShape rect(sf::Vector2f(WIDTH, HEIGHT));
    renderTexture.create(WIDTH, HEIGHT);
    renderTexture.clear();
    renderTexture.draw(rect, &shader);
    renderTexture.display();
    return renderTexture.getTexture();
}

sf::Texture load_buffer_D(const sf::Texture& buf_C){
    sf::Shader shader;
    shader.loadFromFile(path_to_game + R"(\resources\Shaders\buffer_D.glsl)", sf::Shader::Fragment);
    shader.setUniform("iResolution", sf::Vector2f(WIDTH, HEIGHT));
    shader.setUniform("iChannel0", buf_C);

    sf::RenderTexture renderTexture;
    sf::RectangleShape rect(sf::Vector2f(WIDTH, HEIGHT));
    renderTexture.create(WIDTH, HEIGHT);
    renderTexture.clear();
    renderTexture.draw(rect, &shader);
    renderTexture.display();
    return renderTexture.getTexture();
}


class Black_hole{
private:
    sf::Shader fragShader;
    sf::Vector3f cameraPosition = {0.f, 1.35f, -10.f};
    sf::Vector2f cameraDirection = {-3.14f, 0.f};
    Text fps;
    Text coords;

    int fps_to = 10;
    float move_speed = 0.175f;
    bool stop = false;

    void load(){
        fps.create(L"-- fps", 12, sf::Color::Red, {0, 0}, sf::Text::Bold);
        coords.create(L"", 12, sf::Color::Red, {0, 650}, sf::Text::Bold);
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
                if (false) {
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
public:
    Black_hole(){
        load();
    }
    void test(sf::RenderWindow & window){
        clock_t t = clock();
        fps.create(L"00 fps", 42, sf::Color::Red, {0, 0}, sf::Text::Bold);

        sf::Shader shader;
        shader.loadFromFile(path_to_game + "\\resources\\Shaders\\test.glsl", sf::Shader::Fragment);

        sf::Texture texture1, texture2;
        sf::Shader mainShader;
        mainShader.loadFromFile(path_to_game + "\\resources\\Shaders\\image.glsl", sf::Shader::Fragment);
        sf::Event event;
        sf::Vector2u screenSize = window.getSize();
        sf::RectangleShape rect(sf::Vector2f(screenSize.x, screenSize.y));
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || stop)
                    return;
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                        return;

                }
            }

            window.clear();

            texture1 = load_buffer_A(texture1);
            sf::Sprite sprite(texture1);
            texture2 = load_buffer_D(load_buffer_C(load_buffer_B(texture1)));

            mainShader.setUniform("iResolution", sf::Vector2f(WIDTH, HEIGHT));
            mainShader.setUniform("iChannel0", texture1);
            mainShader.setUniform("iChannel3", texture2);

            sf::RenderStates _shader(&mainShader);
            window.draw(rect, _shader);
            //window.draw(sprite);
            fps.draw(window);
            fps.set_text(std::to_wstring(fps_to) + L" fps");
            window.display();
            t = clock() - t;
            fps_to = CLOCKS_PER_SEC / (double) t;
        }
    }
    void start(sf::RenderWindow & window) {
        clock_t t;
        float const_x = 2.7f, const_y = 3.7f;
        window.setMouseCursorVisible(false);
        sf::Mouse::setPosition({400, 400});
        while (window.isOpen()) {
            t = clock();
            if (sf::Mouse::getPosition().x > window.getSize().x-10){
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
            if (sf::Mouse::getPosition().y > window.getSize().y-10){
                const_y += 1;
                sf::Mouse::setPosition({sf::Mouse::getPosition().x, sf::Mouse::getPosition().y - 150});
            }
            if (std::fabs(cameraPosition.x) + std::fabs(cameraPosition.y) + std::fabs(cameraPosition.z) < 1.1){
                return;
            }
            if (stop){
                return;
            }
            cameraDirection.x = (float) -sf::Mouse::getPosition().x / 150 + const_x;
            cameraDirection.y = (float) sf::Mouse::getPosition().y / 150 + const_y;
            Events(window);

            sf::RectangleShape rect(sf::Vector2f(WIDTH, HEIGHT));

            // the direction of each ray is transformed with this matrix before marching
            sf::Transform transform;

            fragShader.setUniform("resolution", sf::Vector2f(WIDTH, HEIGHT));
            fragShader.setUniform("rayOrigin", cameraPosition);
            fragShader.setUniform("cameraDirection", cameraDirection);
            fragShader.setUniform("transform", (sf::Glsl::Mat3) transform);
            fragShader.setUniform("zoom", 1.0f);
            fragShader.setUniform("iTime", (float)clock() / CLOCKS_PER_SEC);

            sf::RenderStates shader(&fragShader);


            coords.set_text(L"x: " + std::to_wstring(cameraPosition.x) + L"\ny: " + std::to_wstring(cameraPosition.y) + L"\nz: " + std::to_wstring(cameraPosition.z));
            window.clear();
            window.draw(rect, shader);
            fps.draw(window);
            coords.draw(window);
            fps.set_text(std::to_wstring(fps_to) + L" fps");

            window.display();
            t = clock() - t;
            fps_to = CLOCKS_PER_SEC / (double) t;
        }

        window.setMouseCursorVisible(true);
    }
};


#endif //MGBI_BOMONKA_BLACK_HOLE_H
