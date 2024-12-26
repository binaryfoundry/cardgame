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

void TestFullDeckPlayer1Wins()
{
    Game game({
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    });
    const Player winner = game.PlayGame();

    assert(winner == Player::Player1);
    assert(game.GetPlayer1Score() == 26);
    assert(game.GetPlayer2Score() == 0);

    std::cout << "TestFullDeckPlayer1Wins passed." << std::endl;
}

void TestFullDeckPlayer2Wins()
{
    Game game({
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    });
    const Player winner = game.PlayGame();

    assert(winner == Player::Player2);
    assert(game.GetPlayer1Score() == 0);
    assert(game.GetPlayer2Score() == 26);

    std::cout << "TestFullDeckPlayer2Wins passed." << std::endl;
}

int main(int argc, char* argv[]) {
    TestFullDeckDraw();
    TestFullDeckPlayer1Wins();
    TestFullDeckPlayer2Wins();
    return 0;
}
