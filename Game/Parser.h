//
// Created by Yaroslav on 21.03.2024.
//


#ifndef MGBI_BOMONKA_PARSER_H
#define MGBI_BOMONKA_PARSER_H

#include <string>
#include <vector>

#include "Text.h"
#include "Texture.h"

struct loader
{
    int id;
    Text text;
    Texture prepod;
    Texture fon;
    std::string music;
    int button_count;
    std::vector <std::pair<std::string, int>> buttons;
    std::string sys;
};

#endif //MGBI_BOMONKA_PARSER_H
