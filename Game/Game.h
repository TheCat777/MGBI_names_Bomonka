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

class Texture{
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Texture(const std::string& path){
        texture.loadFromFile(path);
        sprite.setTexture(texture);
    }
    void draw(sf::RenderWindow & window){
        window.draw(sprite);
    }
};

class Base_Scene{
public:
    std::vector<sf::Sprite> Sprites;
    std::vector<sf::Texture> Textures;
    std::vector<Texture> Textures_;
    std::vector<sf::Text> Texts;

    void draw_all(sf::RenderWindow & window){
        window.clear();
        for (const auto& sprite : Sprites)
            //window.draw(sprite);
        for (const auto& text : Texts) {
            window.draw(text);
        }
        for (auto& texture : Textures_)
            texture.draw(window);
        window.display();
    }
    void events(sf::RenderWindow & window){
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
protected:
    void add_sprite(const sf::Sprite& new_sprite){
        Sprites.push_back(new_sprite);
    }
    void add_text(const sf::Text& new_text){
        Texts.push_back(new_text);
    }
    void add_texture(const sf::Texture& new_texture){
        Textures.push_back(new_texture);
    }
    void add_(const Texture& texture){
        Textures_.push_back(texture);
    }
public:
    void load(){};
    Base_Scene(){
        load();
    }
    void start(sf::RenderWindow & window){
        while (window.isOpen()){
            events(window);
            draw_all(window);
        }
    }
};

#define AppW 1366
#define AppH 768
std::string path_to_game = std::filesystem::current_path().parent_path().parent_path().string();

class Loading_Scene : public Base_Scene{
public:
    void load(){
        //_________________СОЗДАЮ КАРТИНКУ_____________
        sf::Texture texture;
        texture.loadFromFile(path_to_game + "\\resources\\logo.png");
        add_texture(texture);
        sf::Sprite sprite(Textures[Textures.size()-1]);


        //_________________ОБЪЯВЛЯЮ ШРИФТ_____________
        sf::Font font;
        if (!font.loadFromFile(path_to_game + "\\resources\\wgs.ttf"))
        {
            std::cerr << "Fail to load font" << std::endl;
            // ошибка...
        }
        //_________________СОЗДАЮ ТЕКСТ_____________
        sf::Text text;
        text.setFont(font); // выбираем шрифт // font это sf::Font
        text.setString("Hello"); // выбираем отображаемую строку
        text.setCharacterSize(42); // в пикселях, а не точках! // выбираем размер символов
        text.setColor(sf::Color::Black); // выбираем цвет
        text.setStyle(sf::Text::Bold | sf::Text::Underlined); // выбираем стиль текста

        //_________________ВЫРАВНИВАЕМ ПО ЦЕНТРУ ТЕКСТ_____________
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top  + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(AppW/2.0f,AppH/2.0f));


        add_sprite(sprite);
        add_text(text);
    }
};


class MainGame{
private:
    sf::RenderWindow window;
    unsigned int WIDTH, HEIGHT, MAX_FRAME_LIMIT;
    bool FULLSCREEN;

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
    static void test(){
        std::filesystem::path Path = std::filesystem::current_path().parent_path().parent_path();
        auto window = sf::RenderWindow{ { AppW, AppH }, "MGBI by N.E. Bomonki", sf::Style::Fullscreen};
        window.setFramerateLimit(144);
//_________________СОЗДАЮ КАРТИНКУ_____________
        sf::Texture texture;
        texture.loadFromFile(Path.string() + "\\resources\\logo.png");
        sf::Sprite sprite(texture);


        //_________________ОБЪЯВЛЯЮ ШРИФТ_____________
        sf::Font font;
        if (!font.loadFromFile(Path.string() + "\\resources\\wgs.ttf"))
        {
            // ошибка...
        }
        //_________________СОЗДАЮ ТЕКСТ_____________
        sf::Text text;
        text.setFont(font); // выбираем шрифт // font это sf::Font
        text.setString(L"Привет"); // выбираем отображаемую строку
        text.setCharacterSize(42); // в пикселях, а не точках! // выбираем размер символов
        text.setColor(sf::Color::Black); // выбираем цвет
        text.setStyle(sf::Text::Bold | sf::Text::Underlined); // выбираем стиль текста

        //_________________ВЫРАВНИВАЕМ ПО ЦЕНТРУ ТЕКСТ_____________
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top  + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(AppW/2.0f,AppH/2.0f));


        //_________________МУЗЫКА_____________
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(Path.string() + "\\resources\\1.mp3")){
            //Error audio
        }
        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.setVolume(10.f);
        sound.setLoop(true);
        sound.play();


        while (window.isOpen())
        {
            for (auto event = sf::Event{}; window.pollEvent(event);)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                }
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            window.clear();
            window.draw(sprite);
            window.draw(text);
            window.display();
        }
    }
public:
    MainGame(){
        if (!load_settings()) return;
        init_window();
        Loading_Scene loadingScene;
        loadingScene.load();
        loadingScene.start(window);
    }
};

#endif //PROJECT_NAME_GAME_H
