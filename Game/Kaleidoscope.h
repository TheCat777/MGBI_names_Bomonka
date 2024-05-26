//
// Created by SvCat on 11.05.2024.
//

#ifndef MGBI_BOMONKA_KALEIDOSCOPE_H
#define MGBI_BOMONKA_KALEIDOSCOPE_H



class Kaleidoscope{
private:
    sf::Shader fragShader;


    bool stop = false;

    void load(){
        if (!sf::Shader::isAvailable()) {
            std::cout << "Shaders is not supported" << std::endl;
            return;
        }
        if (!fragShader.loadFromFile(path_to_game + R"(\resources\Shaders\Kaleidoscope.glsl)", sf::Shader::Fragment)) {
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
            }
        }
    }

public:
    Kaleidoscope(){
        load();
    }
    void start(sf::RenderWindow & window) {
        //window.create({ 1920, 1080 }, "MGBI by N.E. Bomonki", FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Default);
        //sf::Vector2f size_of_window = {1920, 1080};
        sf::Vector2f size_of_window = {1280, 720};
        sf::RectangleShape rect(size_of_window);
        sf::RenderStates shader(&fragShader);
        window.setMouseCursorVisible(false);

        sf::Transform transform;
        float t = clock();

        fragShader.setUniform("resolution", size_of_window);
        while (window.isOpen() && !stop) {
            Events(window);

            fragShader.setUniform("iTime", ((float)clock() - t) / CLOCKS_PER_SEC);

            window.clear();
            window.draw(rect, shader);
            window.display();
            if (std::fabs((((float)clock() - t) / CLOCKS_PER_SEC) - 21) < 0.1){
                stop = true;
            }
        }
        window.setMouseCursorVisible(true);
        //window.create({ 1280, 720 }, "MGBI by N.E. Bomonki", FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Default);
    }
};



#endif //MGBI_BOMONKA_KALEIDOSCOPE_H
