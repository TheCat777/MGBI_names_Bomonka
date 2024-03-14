#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{ { 1200u, 800u }, "MGBI by N.E. Bomonki" };
    window.setFramerateLimit(144);

    sf::Texture texture;
    texture.loadFromFile("C:\\cmake-sfml-project-master\\src\\cat.jpg");

    sf::Sprite sprite(texture);


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
        window.display();
    }
}