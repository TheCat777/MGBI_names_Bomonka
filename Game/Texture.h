#ifndef MGBI_BOMONKA_TEXTURE_H
#define MGBI_BOMONKA_TEXTURE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Texture{
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    explicit Texture(const std::string& path){
        if (!texture.loadFromFile(path)){
            std::cerr << "Failure to load texture from file " << path << std::endl;
        }
        sprite.setTexture(texture);
    }
    void draw(sf::RenderWindow & window){
        sprite.setTexture(texture);
        window.draw(sprite);
    }
};


#endif //MGBI_BOMONKA_TEXTURE_H
