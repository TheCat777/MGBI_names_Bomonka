#ifndef MGBI_BOMONKA_TEXTURE_H
#define MGBI_BOMONKA_TEXTURE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Texture{
private:
    std::string path_to_game = std::filesystem::current_path().parent_path().parent_path().string();
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Texture(){}
    explicit Texture(const std::string& path, sf::Vector2u _coords){
        create(path, _coords);
    }
    sf::Vector2u get_size(){
        return texture.getSize();
    }
    void create(const std::string& path, sf::Vector2u _coords){
        if (!texture.loadFromFile(path_to_game + path)){
            std::cerr << "Failure to load texture from file " << path << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition({(float)_coords.x, (float)_coords.y});
    }
    void draw(sf::RenderWindow & window){
        sprite.setTexture(texture);
        window.draw(sprite);
    }
};


#endif //MGBI_BOMONKA_TEXTURE_H
