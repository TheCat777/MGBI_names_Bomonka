//
// Created by Yaroslav on 21.03.2024.
//


#ifndef MGBI_BOMONKA_PARSER_H
#define MGBI_BOMONKA_PARSER_H

#include <string>
#include <vector>

struct loader
{
    int id;
    std::wstring text;
    std::string prepod;
    std::string fon;
    std::string music;
    int button_count;
    std::vector <std::pair<std::wstring, int>> buttons;
    std::string sys;
};

#endif //MGBI_BOMONKA_PARSER_H
