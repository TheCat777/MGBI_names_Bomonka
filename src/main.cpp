#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define AppW 1366
#define AppH 768

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << argv[1] << "\n";
    auto window = sf::RenderWindow{ { AppW, AppH }, "MGBI by N.E. Bomonki" };
    window.setFramerateLimit(144);


    //_________________СОЗДАЮ КАРТИНКУ_____________
    sf::Texture texture;
    texture.loadFromFile("D:\\My\\MGTU\\PTP\\_sfml-sprite\\src\\resources\\logo.png");
    sf::Sprite sprite(texture);


    //_________________ОБЪЯВЛЯЮ ШРИФТ_____________
    sf::Font font;
    if (!font.loadFromFile("D:\\My\\MGTU\\PTP\\_sfml-sprite\\src\\resources\\wgs.ttf"))
    {
        // ошибка...
    }
    //_________________СОЗДАЮ ТЕКСТ_____________
    sf::Text text;
    text.setFont(font); // выбираем шрифт // font это sf::Font
    text.setString(L"Привет"); // выбираем отображаемую строку
    text.setCharacterSize(42); // в пикселях, а не точках! // выбираем размер символов
    text.setColor(sf::Color::Black); // выбираем цвет
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined); // выбираем стиль текста

    //_________________ВЫРАВНИВАЕМ ПО ЦЕНТРУ ТЕКСТ_____________
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(AppW/2.0f,AppH/2.0f));


    //_________________МУЗЫКА_____________
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("D:\\My\\MGTU\\PTP\\_sfml-sprite\\src\\resources\\gimn.mp3")){
        //Error audio
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(10.f);
    sound.play();


    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
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