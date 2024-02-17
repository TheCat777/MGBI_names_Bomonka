#include "Game/game.h"
#include <filesystem>

int main(){
    std::cout << std::filesystem::current_path().string();
    Game gm;
    return 0;
}
