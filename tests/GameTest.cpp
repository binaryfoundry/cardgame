#include "cardgame/Game.hpp"

using namespace cardgame;

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
        const Player winner = game.Play([&](const uint32_t played_round, const uint32_t player_1_card, const uint32_t player_2_card, const Player winner)
        {
            assert(winner != Player::None);

            if (winner == Player::Player1)
            {
                assert(player_1_card > player_2_card);
            }
            else if (winner == Player::Player2)
            {
                assert(player_2_card > player_1_card);
            }
        });

        assert(game.GetPlayer1Score() + game.GetPlayer2Score() == Game::NUM_CARDS_HALF);
    }

    std::cout << "TestGame passed." << std::endl;
}

void TestGameMultiplePlays()
{
    for (uint32_t i = 0; i < 20; i++)
    {
        Game game;
        const Player winner = game.Play([&](const uint32_t played_round, const uint32_t player_1_card, const uint32_t player_2_card, const Player winner)
        {
            assert(winner != Player::None);
        });

        const uint32_t player_1_score = game.GetPlayer1Score();
        const uint32_t player_2_score = game.GetPlayer2Score();

        const Player winner2 = game.Play();

        assert(player_1_score + player_2_score == Game::NUM_CARDS_HALF);
        assert(player_1_score == game.GetPlayer1Score());
        assert(player_2_score == game.GetPlayer2Score());
        assert(winner == winner2);
    }

    std::cout << "TestGameMultiplePlays passed." << std::endl;
}

void TestFullDeckDraw()
{
    Game game({
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    });
    const Player winner = game.Play();

    assert(winner == Player::None);
    assert(game.GetPlayer1Score() == Game::NUM_CARDS_HALF);
    assert(game.GetPlayer2Score() == Game::NUM_CARDS_HALF);

    std::cout << "TestFullDeckDraw passed." << std::endl;
}

void TestFullDeckPlayer1Wins()
{
    Game game({
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    });
    const Player winner = game.Play();

    assert(winner == Player::Player1);
    assert(game.GetPlayer1Score() == Game::NUM_CARDS_HALF);
    assert(game.GetPlayer2Score() == 0);

    std::cout << "TestFullDeckPlayer1Wins passed." << std::endl;
}

void TestFullDeckPlayer2Wins()
{
    Game game({
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    });
    const Player winner = game.Play();

    assert(winner == Player::Player2);
    assert(game.GetPlayer1Score() == 0);
    assert(game.GetPlayer2Score() == Game::NUM_CARDS_HALF);

    std::cout << "TestFullDeckPlayer2Wins passed." << std::endl;
}

constexpr uint32_t uint32_t_max_value = std::numeric_limits<uint32_t>::max();
constexpr uint32_t uint32_t_min_value = std::numeric_limits<uint32_t>::min();
constexpr uint32_t uint32_t_infinity = std::numeric_limits<uint32_t>::infinity();
constexpr uint32_t uint32_t_nan = std::numeric_limits<uint32_t>::quiet_NaN();

/**
 * @brief Tests the game with unusual values in the deck.
 *
 * This test uses a deck with maximum, minimum, NaN, and infinity values to ensure
 * the game logic handles these edge cases correctly. Note that while uint32_t
 * cannot represent NaN or infinity, this test is designed to check robustness
 * in case the type ever changes.
 */
void TestUnusualValues()
{
    Game game({
        uint32_t_max_value, uint32_t_min_value, uint32_t_nan, 1, uint32_t_infinity, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        uint32_t_min_value, uint32_t_max_value, 1, uint32_t_nan, 0, uint32_t_infinity, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    });
    const Player winner = game.Play();

    assert(winner == Player::None);
    assert(game.GetPlayer1Score() == Game::NUM_CARDS_HALF - 1);
    assert(game.GetPlayer2Score() == Game::NUM_CARDS_HALF - 1);

    std::cout << "TestUnusualValues passed." << std::endl;
}

int main(int argc, char* argv[])
{
    TestGame();
    TestGameMultiplePlays();
    TestFullDeckDraw();
    TestFullDeckPlayer1Wins();
    TestFullDeckPlayer2Wins();
    TestUnusualValues();
    return 0;
}
