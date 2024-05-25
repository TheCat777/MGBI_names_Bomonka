#ifndef MGBI_BOMONKA_TEXTURE_H
#define MGBI_BOMONKA_TEXTURE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"

class Texture{
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Texture()= default;
    explicit Texture(const std::string& path, sf::Vector2u _coords){
        create(path, _coords);
    }
    sf::Vector2u get_size(){
        return texture.getSize();
    }
    void create(const std::string& path, sf::Vector2u _coords){
        if (!texture.loadFromFile(path_to_game + "\\resources\\Textures\\" + path)){
            std::cerr << "Failure to load texture from file " << path << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setColor(sf::Color(255, 255, 255, 0));
        sprite.setPosition({(float)_coords.x, (float)_coords.y});
        setVisibility(255);
    }
    void setColor(const sf::Color & color){
        sprite.setColor(color);
    }
    void setVisibility(unsigned int visibility){
        auto temp = sprite.getColor();
        temp.a = visibility;
        sprite.setColor(temp);
    }
    double getVisibility(){
        return sprite.getColor().a;
    }
    void draw(sf::RenderWindow & window){
        sprite.setTexture(texture);
        window.draw(sprite);
    }
    void move(float x, float y) {
        sprite.move(x, y);
    }
    sf::Sprite GetSprite() const {
        return sprite;
    }
    void SetPosition(sf::Vector2i _coords) {
        sprite.setPosition({(float)_coords.x,(float)_coords.y});
    }
    sf::Vector2f GetPosition() {
        return sprite.getPosition();
    }
    bool is_colided(const Texture & another){
        auto first_colider = sprite.getGlobalBounds();
        auto second_colider = another.GetSprite().getGlobalBounds();
        return first_colider.intersects(second_colider);
    }
};


#endif //MGBI_BOMONKA_TEXTURE_H
