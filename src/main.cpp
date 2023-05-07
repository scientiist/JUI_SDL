#include "TestBench/JUIDemoGame.hpp"

int main() {
    auto* game = new JUIDemoGame();
    game->Initialize();
    game->Run();
    game->Cleanup();
    delete game;
    return 0;
}