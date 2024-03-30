//
// Created by SvCat on 23.03.2024.
//

#ifndef MGBI_BOMONKA_SOUND_H
#define MGBI_BOMONKA_SOUND_H

#include <SFML/Audio.hpp>
#include "Constants.h"

class Sound{
private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
public:
    Sound(){}
    Sound(const std::string &path, const float & volume, bool loopted){
        create(path, volume, loopted);
    }
    void create(const std::string &path, const float & volume, bool loopted){
        if (!buffer.loadFromFile(path_to_game + "\\resources\\Music\\" + path)){
            //Error audio
        }
        sound.setBuffer(buffer);
        sound.setVolume(volume);
        sound.setLoop(loopted);
    }
    void play(){
        sound.play();
    }
    void pause(){
        sound.pause();
    }
    void set_volume(const float & volume){
        sound.setVolume(volume);
    }
};


#endif //MGBI_BOMONKA_SOUND_H
