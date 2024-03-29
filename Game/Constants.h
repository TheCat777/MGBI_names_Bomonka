//
// Created by SvCat on 23.03.2024.
//

#ifndef MGBI_BOMONKA_CONSTANTS_H
#define MGBI_BOMONKA_CONSTANTS_H
#include <filesystem>

std::string path_to_game = std::filesystem::current_path().parent_path().parent_path().string();
unsigned int WIDTH, HEIGHT, MAX_FRAME_LIMIT;
bool FULLSCREEN;

#endif //MGBI_BOMONKA_CONSTANTS_H
