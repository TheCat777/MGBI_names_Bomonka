#include "Game/game.h"
#include <filesystem>

int main(){
    std::filesystem::path Path = std::filesystem::current_path().parent_path();
    std::cout << Path.filename().string();
    if (Path.filename().string() != "MGBI names Bomonka") throw "Encorrected path";
    Game gm;
    return 0;
}
