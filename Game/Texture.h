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
    Texture()= default;
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
    void move(float x, float y) {
        sprite.move(x, y);
    }
    sf::Sprite GetSprite() const {
        return sprite;
    }
    bool is_colided(const Texture & another){
        auto first_colider = sprite.getGlobalBounds();
        auto second_colider = another.GetSprite().getGlobalBounds();
        return first_colider.intersects(second_colider);
    }
    char where_colided(const Texture & another) {
        auto first_colider = sprite.getGlobalBounds();
        auto second_colider = another.GetSprite().getGlobalBounds();
        if (is_colided(another)) {
            if (first_colider.top - first_colider.height < second_colider.top && second_colider.top < first_colider.top &&
                first_colider.left < second_colider.top < second_colider.left + second_colider.width)
                return 't';
            if (first_colider.top - first_colider.height < second_colider.top - second_colider.height && second_colider.top - second_colider.height < first_colider.top &&
                first_colider.left < second_colider.top < second_colider.left + second_colider.width)
                return 'b';
            if (first_colider.top - first_colider.height < second_colider.top && second_colider.top < first_colider.top &&)
                return 'l';
            if ()
                return 'r';
        }
        return '-';
    }
};


#endif //MGBI_BOMONKA_TEXTURE_H
