#include "cardgame/Game.hpp"

#include <iostream>
#include <cassert>

void TestFullDeckDraw()
{
    Game game({
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    });
    const Player winner = game.PlayGame();

    assert(winner == Player::None);
    assert(game.GetPlayer1Score() == 26);
    assert(game.GetPlayer2Score() == 26);

    std::cout << "TestFullDeckDraw passed." << std::endl;
}

int main(int argc, char* argv[]) {
    TestFullDeckDraw();
    return 0;
}
