#include "cardgame/Game.hpp"

#include <iostream>
#include <cassert>

/*
 * From the requirements:
 * - We start with the deck of 52 cards, each uniquely numbered from 1 to 52
 * - The deck is shuffled
 * - We deal out those cards between the 2 players.Each player gets half the deck.
 * - On each turn of the game, both players turn over their top most card and they compare the value of those cards.
 * - The player with the higher valued card "wins" the round and gets a point.The two cards being compared are discarded.
 * - Rounds are played until all the cards are discarded.
 *
 * Therefore using the default constructor to shuffle the deck there can not be draws in a round.
*/

void TestGame()
{
    for (uint32_t i = 0; i < 20; i++)
    {
        Game game;
        const Player winner = game.PlayGame([&](const size_t played_round, const int32_t player_1_card, const int32_t player_2_card, const Player winner)
        {
            assert(winner != Player::None);
        });

        assert(game.GetPlayer1Score() + game.GetPlayer2Score() == 26);
    }

    std::cout << "TestGame passed." << std::endl;
}

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

constexpr uint32_t uint32_t_max_value = std::numeric_limits<uint32_t>::max();
constexpr uint32_t uint32_t_min_value = std::numeric_limits<uint32_t>::min();
constexpr uint32_t uint32_t_infinity = std::numeric_limits<uint32_t>::infinity();
constexpr uint32_t uint32_t_nan = std::numeric_limits<uint32_t>::quiet_NaN();

// This isn't a problem for uint32_t, but it's a good habit to have incase the type ever changes.
void TestUnusualValues()
{
    Game game({
        uint32_t_max_value, uint32_t_min_value, uint32_t_nan, 1, uint32_t_infinity, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        uint32_t_min_value, uint32_t_max_value, 1, uint32_t_nan, 0, uint32_t_infinity, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    });
    const Player winner = game.PlayGame();

    assert(winner == Player::None);
    assert(game.GetPlayer1Score() == 25);
    assert(game.GetPlayer2Score() == 25);

    std::cout << "TestUnusualValues passed." << std::endl;
}

int main(int argc, char* argv[]) {
    TestGame();
    TestFullDeckDraw();
    TestFullDeckPlayer1Wins();
    TestFullDeckPlayer2Wins();
    TestUnusualValues();
    return 0;
}
