#include "cardgame/Game.hpp"
#include "cardgame/Presentation.hpp"

int main(int argc, char* argv[]) {
    Game game;
    PrintPlayGame(game, std::cout);
    return 0;
}
